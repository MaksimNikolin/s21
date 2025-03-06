import curses
from contextlib import suppress
from enum import Enum
from time import sleep
import time
from controller.game_info import GameInfo
from datalayer.stats import RogueStats
from domain.map.level_map import LevelMap
from domain.map.settings import HEIGHT, MAX_LEVEL, WIDTH
from domain.objects.backpack.backpack import Backpack
from domain.objects.character import Character
from domain.objects.items.food import Food
from domain.objects.items.potion import Potion
from domain.objects.items.scroll import Scroll
from domain.objects.items.weapon import Weapon
from domain.objects.utils import RogueEvent
from utils.logger import controller_log, domain_log
from presentation.map_renderer import MapRenderer

class GameState(Enum):
    INPUT = 1
    INVENTORY = 2
    DROP = 3
    DROP_SLOT = 4
    ROGUE_MOVE = 5
    DEATH = 6
    WIN = 7
    QUIT = 8
    END = 9

class UserAction(Enum):
    MOVE = "move"
    QUIT = "q"
    ENTER = "\n"
    INVENTORY = "inventory"
    SLOT = "slot"
    DROP = "l"

    @classmethod
    def from_key(cls, key: str):
        return (
            cls.MOVE
            if key in {"w", "a", "s", "d"}
            else cls.INVENTORY
            if key in {"h", "j", "k", "e"}
            else cls.SLOT
            if key.isdigit() and Backpack.MIN_SLOT <= int(key) <= Backpack.MAX_SLOT
            else cls(key)
        )

class Controller:
    __ru_to_en = {
        "ц": "w",
        "ф": "a",
        "ы": "s",
        "в": "d",
        "р": "h",
        "о": "j",
        "л": "k",
        "у": "e",
        "й": "q",
        "д": "l",
    }
    __inventory_mapping = {
        "j": Food,
        "k": Potion,
        "e": Scroll,
        "h": Weapon,
    }

    def __init__(self):
        self.rogue_stats = RogueStats()
        self.stdscr = None
        self.renderer: MapRenderer | None = None
        self.game_info: GameInfo | None = None
        self.height = HEIGHT
        self.width = WIDTH
        self.state = GameState.INPUT
        self.fsm = self.__generate_fsm()
        self.inventory_section = None
        self.level = 1
        self.level_map = None
        self.map = []
        self.__prev_hp = 0

        controller_log.info("{cls} initialized", cls=self.__class__.__name__)

    def __generate_fsm(self):
        return {
            (GameState.INPUT, UserAction.MOVE): self.__move,
            (GameState.INPUT, UserAction.QUIT): self.__quit_confirmation,
            (GameState.INPUT, UserAction.ENTER): self.__enter,
            (GameState.INPUT, UserAction.INVENTORY): self.__inventory,
            (GameState.INPUT, UserAction.DROP): self.drop,
            (GameState.INVENTORY, UserAction.QUIT): self.close_inventory,
            (GameState.INVENTORY, UserAction.SLOT): self.slot,
            (GameState.DROP, UserAction.INVENTORY): self.__inventory,
            (GameState.DROP, UserAction.QUIT): self.close_inventory,
            (GameState.DROP_SLOT, UserAction.SLOT): self.drop_slot,
            (GameState.DROP_SLOT, UserAction.QUIT): self.close_inventory,
            (GameState.DEATH, UserAction.QUIT): self.__quit_confirmation,
            (GameState.QUIT, UserAction.ENTER): self.__quit,
            (GameState.QUIT, UserAction.QUIT): self.__cancel_quit,
        }

    def __curser_init(self, stdscr):
        self.stdscr = stdscr
        self.stdscr.clear()
        curses.cbreak()
        self.stdscr.keypad(True)

    def start_rogue(self): curses.wrapper(self.__start)

    def __start(self, stdscr):
        self.__curser_init(stdscr)
        while self.state != GameState.END:
            self.renderer = MapRenderer(self.height, self.width)
            self.renderer.show_intro(pause=True)
            self.__try_load()
            if self.state == GameState.END: break
            self.renderer.clear_intro()
            self.game_info = GameInfo(self.level)
            self.level_map = LevelMap(self.height, self.width, self.level, 1)
            self.__game_loop()
            self.rogue_stats.rogue_level = self.level
            if self.state != GameState.END:
                self.renderer.show_stats(self.rogue_stats.get_sorted_stats())
                self.state = GameState.INPUT
                self.rogue_stats = RogueStats()
                self.renderer.show_intro(pause=True)

    def __try_load(self):
        if save := self.rogue_stats.load_json_save():
            user_input = UserAction.DROP
            with suppress(ValueError):
                user_input = UserAction.from_key(self.__normalize_input(self.renderer.render_load_question()))
            if user_input == UserAction.ENTER:
                self.__load_save(save)
                return
            if user_input == UserAction.QUIT:
                self.state = GameState.END
                return
        self.__start_new_game()

    def __load_save(self, save):
        if Character.get_instance(): Character.reset_instance()
        Character(save["nickname"])._load(**save["character_state"])
        self.level = save["stats"]["rogue_level"]
        self.rogue_stats._load(**save["stats"])
        self.__prev_hp = Character.get_instance().hp

    def __start_new_game(self):
        user_input = UserAction.DROP
        with suppress(ValueError):
            if UserAction.from_key(self.__normalize_input(self.renderer.render_start_question())) == UserAction.QUIT:
                self.state = GameState.END
                return

        ch_name = self.renderer.get_player_name()
        while not self.rogue_stats.check_nickname(ch_name):
            with suppress(ValueError):
                user_input = UserAction.from_key(self.renderer.confirm_name())
            if user_input == UserAction.ENTER: break
            self.renderer.show_intro()
            ch_name = self.renderer.get_player_name()
        if Character.get_instance():
            Character.reset_instance()
            self.level = 1
        Character(ch_name)
        self.__prev_hp = Character.get_instance().hp

    def __game_loop(self):
        self.renderer.render_game_info(self.game_info)
        self.__draw_map()
        self.renderer.draw_event_box()
        self.renderer.render_control_panel()
        self.renderer.render_logo_panel()
        self.renderer.render_extra_panel()

        controller_log.debug("loop started")
        while self.state not in {GameState.DEATH, GameState.WIN, GameState.END}:
            if self.state in {GameState.INVENTORY, GameState.DROP_SLOT}:
                self.__input_to_action(
                    self.renderer.draw_inventory(
                        self.inventory_content,
                        f"Введите номер предмета, который хотите "
                        f"{'выбрать' if self.state == GameState.INVENTORY else 'выбросить'}",
                        "1 - 9",
                    )
                )
            elif self.state == GameState.QUIT: self.__input_to_action(self.renderer.draw_exit_window())
            else: self.__input_to_action(self.renderer.get_input(self.state.value))

            if self.state == GameState.ROGUE_MOVE:
                self.state = GameState.INPUT
                self.__update_rogue_state()

        if self.state == GameState.DEATH:
            self.rogue_stats.dump_json_stats()
            self.rogue_stats.remove_save()
            self.renderer.show_intro(start=False, death=True)
            
        if self.state == GameState.WIN:
            self.rogue_stats.dump_json_stats()
            self.rogue_stats.remove_save()
            self.renderer.show_intro(start=False, death=False)

    def __input_to_action(self, key: int):
        controller_log.info(f"Processing user input: {key}")
        key_str = self.__normalize_input(key)
        controller_log.info(f"Normalized user input to: {key_str}")
        user_input = None
        try:
            user_input = UserAction.from_key(key_str)
            controller_log.info(f"{self.state} {user_input}")
        except ValueError:
            controller_log.info(f"key: '{key_str}' is not in input options. Ignore")
        if user_input and (action := self.fsm.get((self.state, user_input))):
            controller_log.info(f"action: {action.__name__}")
            events = action(key_str)
            for event in events:
                self.renderer.render_event(event)
            self.game_info.refresh(self.level)
            self.renderer.render_game_info(self.game_info)
            self.__draw_map()

    def __update_rogue_state(self):
        controller_log.info("Getting Rogue update")
        events, alive = self.level_map.make_rogue_move()
        for event in events: self.renderer.render_event(event)
        if not alive:
            controller_log.info("state = death")
            self.state = GameState.DEATH
            self.renderer.render_event(RogueEvent("Персонаж погиб"))
        self.game_info.refresh(self.level)
        self.__draw_map()
        self.renderer.render_game_info(self.game_info)

    def __normalize_input(self, key: str | int) -> str:
        key_str = chr(key).lower() if isinstance(key, int) else key.lower()
        return self.__ru_to_en.get(key_str, key_str)

    def __move(self, direction: str) -> list[RogueEvent]:
        self.state = GameState.ROGUE_MOVE
        return self.level_map.move_character(direction)

    def __quit_confirmation(self, _=None):
        controller_log.debug("__quit_confirmation")
        self.state = GameState.QUIT
        return []

    def __quit(self, _=None) -> list[RogueEvent]:
        self.state = GameState.END
        return []

    def __cancel_quit(self, _=None):
        self.state = GameState.INPUT
        return []

    def __calc_complexity_coef(self) -> float:
        max_coef = 2
        coef = Character.get_instance().hp / (self.__prev_hp / 2)
        self.__prev_hp = Character.get_instance().hp
        controller_log.info(f"Complexity coef: {coef}")
        return coef if coef <= max_coef else max_coef

    def __enter(self, _=None) -> list[RogueEvent]:
        controller_log.info("Enter")
        events = []
        if self.level_map.is_exit() and self.level == MAX_LEVEL:
            self.state = GameState.WIN
            events = [RogueEvent("Поздравляем, вы прошли игру!")]
            sleep(1)
        elif self.level_map.is_exit():
            controller_log.info("On exit")
            self.level += 1
            self.rogue_stats.rogue_level += 1
            self.level_map = LevelMap(self.height, self.width, self.level, self.__calc_complexity_coef())
            self.rogue_stats.dump_json_save()
            events = [RogueEvent(f"Вы перешли на уровень {self.level}")]
        return events

    def __inventory(self, key: str) -> list[RogueEvent]:
        self.inventory_section = self.__inventory_mapping[key]
        self.state = GameState(self.state.value + 1)
        controller_log.info(f"opening {self.inventory_section, __name__} section")
        self.inventory_content = Backpack.get_instance().show_items(self.inventory_section)
        events = []
        if len(self.inventory_content) == 0:
            events.append(RogueEvent(f"У вас нет предметов типа {self.inventory_section(1).type}"))
            self.state = GameState(self.state.value - 1)
        return events

    def close_inventory(self, _=None) -> list[RogueEvent]:
        self.state = GameState.INPUT
        return []

    def slot(self, key: str) -> list[RogueEvent]:
        slot = int(key)
        controller_log.info(f"using slot {slot} in {self.inventory_section, __name__} section")
        events, item = Backpack.get_instance().use_item(self.inventory_section, slot)
        if item:
            domain_log.debug(f"item: {item.__str__()}")
            if isinstance(item, Weapon):
                w_events, weapon_to_drop = Character.get_instance().equip_weapon(item)
                events.extend(w_events)
                Backpack.get_instance().drop_weapon(weapon_to_drop)
                self.level_map.drop_item(weapon_to_drop)
            else:
                events.extend(Character.get_instance().use_item(item))
            self.state = GameState.ROGUE_MOVE
        return events

    def drop(self, _=None) -> list[RogueEvent]:
        self.state = GameState.DROP
        return []

    def drop_slot(self, key: str) -> list[RogueEvent]:
        slot = int(key)
        events, item = Backpack.get_instance().drop_item(self.inventory_section, slot)
        if item:
            if isinstance(item, Weapon) and item is Character.get_instance().held_weapon:
                events, _ = Character.get_instance().drop_weapon()
            self.level_map.drop_item(item)
            self.state = GameState.ROGUE_MOVE
        return events

    def __draw_map(self):
        self.renderer.clear_game_window()
        for y in range(1, self.height - 3):
            for x in range(1, self.width + 1):
                self.renderer.render_map_crd(y - 1, x - 1, *self.level_map.get_cell(y - 1, x - 1))
        self.renderer.refresh_game_window()
