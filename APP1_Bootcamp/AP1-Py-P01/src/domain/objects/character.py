from random import randint, uniform
import curses
from datalayer.stats import RogueStats
from domain import Coordinate
from domain.objects.backpack.backpack import Backpack
from domain.objects.items import ITEMS_MAPPING
from domain.objects.items.gold import Gold
from domain.objects.items.item import Item
from domain.objects.items.weapon import Weapon
from domain.objects.utils import Effects, RogueEffect, RogueEvent, is_enemy_hits
from utils.logger import domain_log

class Character:
    __instance = None
    symbol, base_color, harm_color = "☻", 4, 10
    __hp_started = 100
    __str_started = 8
    __agil_started = 6
    __exp_started = 5
    __exp_to_lvl_scale = 1.25
    __hp_scale = 0.15
    __str_scale = 0.15
    __agil_scale = 0.15
    __attr_random = 0.3

    def __new__(cls, *args, **kwargs):
        if cls.__instance is None:
            cls.__instance = super().__new__(cls)
        return cls.__instance

    def __init__(self, nickname: str):
        self.nickname = nickname
        self.__color = self.base_color
        RogueStats.get_instance().nickname = nickname
        self.__level = 1
        self.__exp = 0
        self.__y = self.__x = 0

        self.__base_hp = self.__hp = self.__max_hp = self.__hp_started
        self.__base_strength = self.__strength = self.__str_started
        self.__base_agility = self.__agility = self.__agil_started
        self.__max_exp = self.__exp_started

        self.__effects = {eff: [] for eff in list(Effects)}
        self.__backpack = Backpack()
        self.__weapon_slot = None
        self.__gold = 0
        self.__is_visible = True
        self.keys = []

        domain_log.info("{cls} initialized: nickname={nn}", cls=self.__class__.__name__, nn=self.nickname)

    @property
    def color(self): return self.__color

    @classmethod
    def get_instance(cls): return cls.__instance

    @classmethod
    def reset_instance(cls): cls.__instance = None

    @property
    def level(self): return self.__level

    @property
    def exp(self): return self.__exp

    @property
    def max_exp(self): return self.__max_exp

    @property
    def hp(self): return self.__hp

    @property
    def max_hp(self): return self.__max_hp

    @property
    def strength(self): return self.__strength

    @property
    def agility(self): return self.__agility

    @property
    def alive(self): return self.__hp > 0

    @property
    def gold(self): return self.__gold

    @property
    def is_visible(self): return self.__is_visible

    @property
    def held_weapon(self) -> Weapon | None: return self.__weapon_slot

    def __decrease_hp(self, value: int) -> bool:
        self.__hp -= value
        domain_log.info("{cls} decrease to {v} hp={hp}", cls=self.__class__.__name__, v=value, hp=self.__hp)
        return self.__hp > 0

    def add_experience(self, value) -> list[RogueEvent]:
        domain_log.info("{cls} add exp={exp}", cls=self.__class__.__name__, exp=value)
        events = []
        events.extend(self.__convert_exp_to_gold(value))
        self.__exp += value
        events.extend(self.__up_level())
        return events

    def __up_level(self) -> list[RogueEvent]:
        events = []
        while self.__exp >= self.__max_exp:
            self.__exp -= self.max_exp
            self.__level += 1
            self.__max_exp = round(self.__exp_to_lvl_scale * self.max_exp)

            hp_up = self.__calculate_attr_up(self.__base_hp, self.__hp_scale)
            self.__max_hp += hp_up
            self.__hp += hp_up

            str_up = self.__calculate_attr_up(self.__base_strength, self.__str_scale)
            self.__base_strength += str_up
            self.__strength += str_up

            agil_up = self.__calculate_attr_up(self.__base_agility, self.__agil_scale)
            self.__base_agility += agil_up
            self.__agility += agil_up

            domain_log.info("{cls} new_level = {lvl}", cls=self.__class__.__name__, lvl=self.__level)
            message = f"Повышение уровня до {self.__level}! Здоровье +{hp_up} Сила +{str_up} Ловкость +{agil_up}"
            events.append(RogueEvent(message, 20))
        return events

    def __calculate_attr_up(self, attr, scale):
        return round(attr * uniform(scale * (1 - self.__attr_random), scale * (1 + self.__attr_random)))

    def __convert_exp_to_gold(self, value: int) -> list[RogueEvent]:
        gold_ = randint(value // 2, value * 2)
        self.__gold += gold_
        RogueStats.get_instance().gold += gold_
        return [RogueEvent(f"{self.nickname} получает {value} опыта и {gold_} {Gold.spelling(gold_)}.")]

    @staticmethod
    def __add_attack_effect() -> RogueEffect | None: return None

    def attack(self) -> tuple[str, int, int, RogueEffect]:
        return self.nickname, self.strength, self.agility, self.__add_attack_effect()

    def harm(self, e_name: str, e_strength: int, e_agility, e_effect: RogueEffect) -> tuple[list[RogueEvent], bool]:
        events = []
        damage_value = 0
        if is_enemy_hits(e_agility, self.agility):
            self.__color = self.harm_color
            damage_value = e_strength
            domain_log.info(f"{e_name} атакует {self.nickname} нанося {damage_value} урона")
            events.append(RogueEvent(f"{e_name} атакует {self.nickname} нанося {damage_value} урона", 22))
            if e_effect: events.extend(self.apply_effect(e_effect))
        else:
            domain_log.info(f"{e_name} атакует {self.nickname} и промахивается")
            events.append(RogueEvent(f"{e_name} атакует {self.nickname} и промахивается"))
        return events, self.__decrease_hp(damage_value)

    def use_item(self, item: Item) -> list[RogueEvent]:
        events, effect = item.use()
        if effect: events.extend(self.apply_effect(effect))
        return events, effect

    def add_gold(self, item: Gold) -> list[RogueEvent]:
        events, value = item.pick_up()
        self.__gold += value
        RogueStats.get_instance().gold += value
        return events

    def apply_effect(self, effect: RogueEffect) -> list[RogueEvent]:
        if effect.period:
            if effect.effect == Effects.SLEEP and self.__effects[effect.effect]:
                self.__effects[effect.effect].clear()
                self.__effects[effect.effect].append(effect)
            else: self.__effects[effect.effect].append(effect)

        match effect.effect:
            case Effects.MAX_HEALTH:
                self.__max_hp += effect.value
                if effect.value > 0: self.__hp = self.__hp + effect.value
                self.__hp = self.__hp if self.__hp <= self.__max_hp else self.__max_hp
            case Effects.HEALTH: self.__hp = self.__hp + effect.value if self.__hp + effect.value <= self.__max_hp else self.__max_hp
            case Effects.AGILITY: self.__agility += effect.value
            case Effects.STRENGTH: self.__strength += effect.value

        val = "" if effect.value == 0 else f" на {effect.value} ед."
        per = "" if effect.period == 0 else f" длительностью {effect.period}"

        domain_log.info(
            "{name} получает эффект {eff}, value {val}, period {period}",
            name=self.nickname,
            eff=effect.effect.value,
            val=effect.value,
            period=effect.period,
        )
        return [RogueEvent(f"{self.nickname} получает эффект {effect.effect.value}{val}{per}")]

    def __remove_effect(self, effect: RogueEffect) -> list[RogueEvent]:
        try:
            self.__effects[effect.effect].remove(effect)
        except ValueError:
            domain_log.info("Effect is not found in the Character effect list with period")

        match effect.effect:
            case Effects.MAX_HEALTH: self.__max_hp -= effect.value
            case Effects.HEALTH: self.__hp -= effect.value
            case Effects.AGILITY: self.__agility -= effect.value
            case Effects.STRENGTH: self.__strength -= effect.value

        domain_log.info("{name} has lost an effect {eff}", name=self.nickname, eff=effect.effect.name)

        return [RogueEvent(f"{self.nickname} теряет эффект {effect.effect.value} на {effect.value} ед.")]

    def check_object_effects(self) -> tuple[list[RogueEvent], bool]:
        self.__color = self.base_color
        can_move = True
        events, eff_to_remove = [], []
        for effects_list in self.__effects.values():
            for effect in effects_list:
                if not effect.period:
                    eff_to_remove.append(effect)
                    continue
                if effect.effect == Effects.SLEEP:
                    can_move = False
                    events.append(RogueEvent(f"{self.__class__.__name__} слишком устал."))
                effect.period -= 1
        for effect in eff_to_remove:
            events.extend(self.__remove_effect(effect))
        # TODO если снятие эффекта снимает последнее ХП нет вывода на завершение
        return events, can_move

    def place(self, crd: Coordinate): self.__y, self.__x = crd

    def get_crd(self) -> Coordinate: return self.__y, self.__x

    def pick_up_item(self, item: Item) -> tuple[list[RogueEvent], bool]:
        domain_log.info(f"Character picks up item : {item.type}")
        if isinstance(item, Gold): return self.add_gold(item), True
        return self.__backpack.add_item(item)

    def equip_weapon(self, weapon: Weapon) -> tuple[list[RogueEvent], Weapon | None]:
        events, weapon_to_drop = self.drop_weapon()
        self.__weapon_slot = weapon
        use_events, effect = weapon.use()
        events.extend(use_events)
        if effect: events.extend(self.apply_effect(effect))
        return events, weapon_to_drop

    def drop_weapon(self) -> tuple[list[RogueEvent], Weapon | None]:
        events = []
        weapon_to_drop = self.__weapon_slot
        if weapon_to_drop:
            events.extend(weapon_to_drop.drop()[0])
            events.extend(self.__remove_effect(weapon_to_drop.effect))
            self.__weapon_slot = None
        return events, weapon_to_drop

    def _dump(self) -> dict:
        return {
            "level": self.__level,
            "strength": self.__strength - self.__weapon_slot.effect.value if self.__weapon_slot else self.__strength,
            "agility": self.__agility,
            "max_hp": self.__max_hp,
            "hp": self.__hp,
            "exp": self.__exp,
            "max_exp": self.__max_exp,
            "gold": self.__gold,
            "effects": [
                {"effect": effect.effect.name, "value": effect.value, "period": effect.period}
                for effects in self.__effects.values()
                for effect in effects
            ],
            "items": [
                {"cls": item.__class__.__name__, "dump": item._dump()}
                for item in self.__backpack.items.food
                + self.__backpack.items.potions
                + self.__backpack.items.scrolls
                + self.__backpack.items.weapons
            ],
        }

    def _load(self, **kwargs):
        for key, value in kwargs.items():
            match key:
                case "level": self.__level = value
                case "strength": self.__strength = value
                case "agility": self.__agility = value
                case "max_hp": self.__max_hp = value
                case "hp": self.__hp = value
                case "exp": self.__exp = value
                case "max_exp": self.__max_exp = value
                case "gold": self.__gold = value
                case "effects":
                    for eff in value: self.__effects[Effects[eff["effect"]]].append(RogueEffect(Effects[eff["effect"]], eff["value"], eff["period"]))
                case "items":
                    for dct in value:
                        item = ITEMS_MAPPING[dct["cls"]](1)
                        item._load(**dct["dump"])
                        self.__backpack.add_item(item)
                        if isinstance(item, Weapon) and item.held: self.equip_weapon(item)
                case _: raise ValueError(f"Unknown load option {key}")

    def __str__(self) -> str: return f"Ник: {self.nickname}, сила: {self.strength}, ловкость: {self.agility}, хп {self.__hp}/{self.__max_hp}"

    def __repr__(self) -> str: return self.__str__()
