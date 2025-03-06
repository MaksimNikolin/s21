import curses
import time
from controller.game_info import GameInfo
from domain.objects.utils import RogueEvent
from presentation import utils

class EventSlot:
    def __init__(self, position: int, width: int, x: int = 3):
        self.window = curses.newwin(1, width, position + 1, x)
        self.position = position
        self.info = ""
        self.color = 1
        self.__width = width

    def render(self, value: str, color: int = 1):
        self.info = value
        self.color = color
        self.window.erase()
        self.window.addstr(0, 0, self.info[: self.__width - 1], curses.color_pair(self.color))
        self.window.refresh()

    def pop(self) -> str:
        v = self.info
        c = self.color
        self.info = ""
        self.color = 1
        return v, c

class MapRenderer:
    def __init__(self, height: int, width: int):
        self.height = height + 9
        self.width = max(width + 8, len(utils.STATS_TABLE_HEADER_1) + 4)
        self.game_width = width

        self.common_window = curses.newwin(self.height, self.width, 0, 0)
        self.game_window = curses.newwin(self.height - 11, self.game_width + 2, 7, 2)
        self.game_info_window = curses.newwin(3, self.game_width + 2, self.height - 4, 2)
        self.event_box = curses.newwin(6, self.game_width + 2, 1, 2)
        self.controls_box = curses.newwin(self.height - 2, self.width - self.game_width - 7, 1, self.game_width + 5)
        self.__init_colors()

        self.slot_1, self.slot_2, self.slot_3, self.slot_4 = (
            EventSlot(4, self.game_width),
            EventSlot(3, self.game_width),
            EventSlot(2, self.game_width),
            EventSlot(1, self.game_width),
        )

    @staticmethod    
    def __init_colors() -> None:
        curses.curs_set(0)
        curses.start_color()
        curses.init_color(84, 0, 500, 0)                               # darkgreen_color
        curses.init_color(200, 1000, 500, 0)                           # orange_color                          
        curses.init_pair(1, curses.COLOR_WHITE, curses.COLOR_BLACK)    # Free_space
        curses.init_pair(2, curses.COLOR_GREEN, curses.COLOR_BLACK)    # Rooms
        curses.init_pair(3, curses.COLOR_RED, curses.COLOR_BLACK)      # Vampire
        curses.init_pair(4, curses.COLOR_YELLOW, curses.COLOR_BLACK)   # Hero
        # TODO 
        # curses.init_pair(4, curses.COLOR_YELLOW, curses.COLOR_BLACK)   # Hero in Room
        # curses.init_pair(101, curses.COLOR_BLACK, curses.COLOR_CYAN)   # Hero in Corridor
        curses.init_pair(5, 200, curses.COLOR_BLACK)                   # Borders
        curses.init_pair(6, curses.COLOR_BLACK, 241)                   # Coridors
        curses.init_pair(7, curses.COLOR_BLACK, 84)                    # Exit
        curses.init_pair(8, curses.COLOR_CYAN, curses.COLOR_BLACK)     # Items
        curses.init_pair(9, 221, curses.COLOR_BLACK)                   # Gold
        curses.init_pair(10, 197, curses.COLOR_BLACK)                  # Attack_color
        curses.init_pair(11, curses.COLOR_YELLOW, curses.COLOR_BLACK)  # Properties_window
        curses.init_pair(12, 58, curses.COLOR_BLACK)                   # Zombie
        curses.init_pair(13, curses.COLOR_WHITE, curses.COLOR_BLACK)   # Ghost
        curses.init_pair(14, curses.COLOR_YELLOW, curses.COLOR_BLACK)  # Ogre
        curses.init_pair(15, curses.COLOR_WHITE, curses.COLOR_BLACK)   # Snake-mage
        curses.init_pair(16, curses.COLOR_BLACK, curses.COLOR_RED)     # Red_door
        curses.init_pair(17, curses.COLOR_BLACK, curses.COLOR_GREEN)   # Green_door
        curses.init_pair(18, curses.COLOR_BLACK, curses.COLOR_BLUE)    # Blue_door
        curses.init_pair(19, curses.COLOR_RED, curses.COLOR_BLACK)     # Red_Key
        curses.init_pair(20, curses.COLOR_GREEN, curses.COLOR_BLACK)   # Green_Key
        curses.init_pair(21, curses.COLOR_BLUE, curses.COLOR_BLACK)    # Blue_Key
        curses.init_pair(22, curses.COLOR_RED, curses.COLOR_BLACK)     # Controls_keys
        curses.init_pair(23, curses.COLOR_BLUE, curses.COLOR_BLACK)    # Controls_authors
        curses.init_pair(24, 136, curses.COLOR_BLACK)                  # Food
        curses.init_pair(25, 160, curses.COLOR_BLACK)                  # Potions
        curses.init_pair(26, 229, curses.COLOR_BLACK)                  # Scrolls
        curses.init_pair(27, 129, curses.COLOR_BLACK)                  # Weapon

    def render_control_panel(self):
        self.controls_box.clear()
        self.draw_controls_box()

        self.controls_box.addstr(1, 2, utils.GAMEPLAY_LOGO_str1, curses.color_pair(22))
        self.controls_box.addstr(2, 2, utils.GAMEPLAY_LOGO_str2, curses.color_pair(22))
        self.controls_box.addstr(3, 2, utils.GAMEPLAY_LOGO_str3, curses.color_pair(22))
        self.controls_box.addstr(4, 2, utils.GAMEPLAY_LOGO_str4, curses.color_pair(22))
        self.controls_box.addstr(5, 2, utils.GAMEPLAY_LOGO_str5, curses.color_pair(22))

        self.controls_box.addstr(10, 9, "CONTROL  PANEL", curses.color_pair(22) | curses.A_BOLD)
        self.controls_box.addstr(12, 14, "[W]", curses.color_pair(22) | curses.A_BOLD)
        self.controls_box.addstr(14, 9, "[A]", curses.color_pair(22) | curses.A_BOLD)
        self.controls_box.addstr(14, 20, "[D]", curses.color_pair(22) | curses.A_BOLD)
        self.controls_box.addstr(16, 14, "[S]", curses.color_pair(22) | curses.A_BOLD)
        self.controls_box.addstr(13, 15, "🡅", curses.color_pair(1) | curses.A_DIM)
        self.controls_box.addstr(14, 13, "🡄", curses.color_pair(1) | curses.A_DIM)
        self.controls_box.addstr(14, 17, "🡆", curses.color_pair(1) | curses.A_DIM)
        self.controls_box.addstr(15, 15, "🡇", curses.color_pair(1) | curses.A_DIM)

        for i, (key, action) in enumerate(utils.CONTROLS_DICT.items()):
            self.controls_box.addstr(i * 2 + 18, 2, key, curses.color_pair(22) | curses.A_BOLD)
            self.controls_box.addstr(i * 2 + 18, 10, action)

        self.controls_box.refresh()

    def render_event(self, event: RogueEvent):
        self.draw_event_box()
        self.slot_4.render(*self.slot_3.pop())
        self.slot_3.render(*self.slot_2.pop())
        self.slot_2.render(*self.slot_1.pop())
        self.slot_1.render(event.info, event.color)

    def show_intro(self, start=True, death=True, pause=False):
        self.common_window.erase()
        self.common_window.box()

        logo = utils.START_LOGO if start else utils.GAME_OVER_LOGO if death else utils.WIN_LOGO

        start_y = (self.height - len(logo)) // 2
        for i, line in enumerate(logo):
            start_x = (self.width - len(line)) // 2
            self.common_window.addstr(start_y + i, start_x, line)

        self.common_window.refresh()

        if pause:
            start_time = time.time()
            pause_time = 3

            self.common_window.nodelay(True)

            while time.time() - start_time < pause_time:
                key = self.common_window.getch()
                if key != -1:
                    break
                time.sleep(0.05)

            self.common_window.nodelay(False)
        else:
            time.sleep(3)

        curses.flushinp()

    def clear_intro(self):
        self.common_window.erase()
        self.common_window.box()
        self.common_window.refresh()

    def __render_question(self, question: str, choice: str, is_in_game: bool = False) -> int | str:
        win_height, win_width = 4, max(len(choice), len(question)) + 7
        win_y = self.height // 2 + 8
        win_x = self.game_width // 2 - win_width // 2 if is_in_game else self.width // 2 - win_width // 2

        win = curses.newwin(win_height, win_width, win_y, win_x)

        win.box()
        win.addstr(1, 4, question.center(win_width - 7), curses.A_BOLD)
        win.addstr(2, 2, choice.center(win_width - 7), curses.A_DIM)
        win.refresh()

        ch = win.get_wch()
        win.erase()
        win.refresh()
        curses.flushinp()

        return ch

    def render_load_question(self) -> int | str:
        return self.__render_question(utils.LOAD_QUESTION, utils.LOAD_CHOICE)

    def render_start_question(self) -> int | str:
        return self.__render_question(utils.START_QUESTION, utils.START_CHOICE)

    def get_input(self, game_state: int) -> int | str:
        curses.flushinp()
        if game_state == 3:
            return self.__render_question(utils.DROP_QUESTION, utils.DROP_CHOICE, True)

        return self.common_window.get_wch()

    def get_player_name(self) -> str:
        input_win_height, input_win_width = 4, len(utils.GET_NAME_CHOICE) + 4
        input_win_y = self.height // 2 + 8
        input_win_x = self.width // 2 - input_win_width // 2
        input_win = curses.newwin(input_win_height, input_win_width, input_win_y, input_win_x)
        input_win.box()

        max_name_length = 12

        input_win.addstr(1, input_win_width // 2 - len(utils.GET_NAME_QUESTION) // 2, utils.GET_NAME_QUESTION, curses.A_BOLD)
        input_win.refresh()

        name = ""

        ch = " "
        min_ch, max_ch = 32, 126

        while ch not in {curses.KEY_ENTER, 10, 13} or not name:
            input_win.addstr(2, 1, " " * (input_win_width - 2))
            centered_x = max(1, input_win_width // 2 - len(name) // 2)
            input_win.addstr(2, centered_x, name)
            input_win.refresh()

            curses.flushinp()
            ch = input_win.getch()

            if ch in {curses.KEY_BACKSPACE, 127, 8} and name: name = name[:-1]
            elif min_ch <= ch <= max_ch and len(name) < max_name_length: name += chr(ch)
        curses.flushinp()
        return name

    def confirm_name(self) -> int | str:
        return self.__render_question(utils.CHANGE_NAME_QUESTION, utils.CHANGE_NAME_CHOICE)

    def render_game_info(self, game_info: GameInfo):
        self.game_info_window.erase()
        text_style = curses.A_BOLD | curses.color_pair(11)
        _, width = self.game_info_window.getmaxyx()
        width -= 2
        info_lines = (
            f"Level:{game_info.floor}",
            f"Hits:{game_info.hp}({game_info.max_hp})",
            f"Str:{game_info.str}({game_info.str})",
            f"Ag:{game_info.ag}({game_info.ag})",
            f"Gold:{game_info.gold}",
            f"Exp:{game_info.exp}/{game_info.max_exp}",
        )
        letters = sum(map(len, info_lines))
        space = (width - letters) // len(info_lines[:-1])
        extra_space = (width - letters) % len(info_lines[:-1])
        indent = 0
        for line in info_lines:
            self.game_info_window.addstr(1, indent + 1, line, text_style)
            indent += len(line) + space + (extra_space > 0)
            extra_space -= 1
        self.game_info_window.box()
        self.game_info_window.refresh()

    def draw_inventory(self, content: list[str], question: str, choice: str) -> int | str:
        self.game_window.erase()
        self.render_inventory(content)
        self.game_window.box()
        self.game_window.refresh()
        ch = self.__render_question(question, choice, True)
        curses.flushinp()
        return ch

    def clear_game_window(self):
        self.game_window.erase()

    def refresh_game_window(self):
        self.game_window.box()
        self.game_window.refresh()

    def render_map_crd(self, y: int, x: int, symbol: str, color: int):
        self.game_window.addch(y + 1, x + 1, symbol, curses.color_pair(color))

    def render_inventory(self, content: list[str]):
        for i in range(len(content)):
            self.game_window.addstr(i + 1, 1, f"{i + 1}) {content[i]}")

    def draw_exit_window(self) -> int | str:
        return self.__render_question(utils.QUIT_QUESTION, utils.QUIT_CHOICE, True)

    def render_inventory_choice(self, question, choice):
        self.__render_question(question, choice)

    def show_stats(self, stats: list[dict]):
        self.common_window.erase()
        self.common_window.border(0)
        self.common_window.refresh()

        slot_header = EventSlot(0, len(utils.STATS_TABLE_HEADER_1) + 2, 1)
        slot_tite_1 = EventSlot(2, len(utils.STATS_TABLE_HEADER_1) + 2, 1)
        slot_tite_2 = EventSlot(3, len(utils.STATS_TABLE_HEADER_1) + 2, 1)
        slot_header.render(utils.STATS_HEADER.center(len(utils.STATS_TABLE_HEADER_1)), 9)
        slot_tite_1.render(utils.STATS_TABLE_HEADER_1, 2)
        slot_tite_2.render(utils.STATS_TABLE_HEADER_2, 2)

        slot_limit = 18
        stat_slots = [EventSlot(6 + i * 2 - 1, len(utils.STATS_TABLE_HEADER_1) + 2, 1) for i in range(slot_limit)]

        def __render(slot_: EventSlot, index: int):
            slot_.render(
                stats[index]["Никнейм"][:12].center(12) 
                + ": "
                + str(stats[index]["Золото"]).center(6)
                + " : "
                + str(stats[index]["Уровень подземелья"]).center(10)
                + " : "
                + str(stats[index]["Поверженные враги"]).center(11)
                + " : "
                + str(stats[index]["Съеденной еды"]).center(9)
                + " : "
                + str(stats[index]["Использованных зелий"]).center(5)
                + " : "
                + str(stats[index]["Использованных свитков"]).center(5)
                + " : "
                + str(stats[index]["Нанесенных ударов"]).center(10)
                + " : "
                + str(stats[index]["Промахов"]).center(8)
                + " : "
                + str(stats[index]["Пройденных клеток"]).center(10),
                color=9 if stats[index]["last_record"] else 1,
            )

        n = len(stats)
        s = f = 0
        for j in range(n):
            if stats[j]["last_record"]:
                s = f = j - 1 if j else 0
                break

        def base_loop():
            nonlocal stat_slots, s, f
            k = s
            for base_loop_slot in stat_slots:
                if k >= n:
                    break
                if k - s == 0 and s > 0:
                    base_loop_slot.render(utils.STATS_UP.center(len(utils.STATS_TABLE_HEADER_1)))
                elif k - s == slot_limit - 1 and n - k != 1:
                    base_loop_slot.render(utils.STATS_DOWN.center(len(utils.STATS_TABLE_HEADER_1)))
                else:
                    __render(base_loop_slot, k)
                f = k
                k += 1

        base_loop()
        while (w_char := self.common_window.get_wch()) not in ["q", "Q", "й", "Й"]:
            if w_char in ["s", "S", "ы", "Ы"] and f < n - 1:
                s += 1
            elif w_char in ["w", "W", "ц", "Ц"] and s > 0:
                s -= 1
            elif s != 0:
                continue
            base_loop()

        self.common_window.refresh()
        curses.flushinp()

    def draw_event_box(self):
        self.event_box.box()
        self.event_box.refresh()

    def draw_controls_box(self):
        self.controls_box.box()
        self.controls_box.refresh()
