from enum import Enum, auto
from math import ceil
from random import uniform
from datalayer.stats import RogueStats
from domain import Coordinate
from domain.objects.character import Character
from domain.objects.utils import Effects, MovePattern, RogueEffect, RogueEvent, is_enemy_hits
from utils.logger import domain_log


class EnemyState(Enum):
    WALKING = auto()
    ENGAGED = auto()


class Enemy:
    __enemy_scale = 1.15

    __enemies_attr_map = {
        "z": (28, 5, 1, 5, 5),    # health, agility, speed, strength, hostility
        "v": (32, 9, 1, 4, 8),
        "g": (20, 10, 0, 2, 3),
        "O": (45, 4, 2, 10, 6),
        "s": (25, 12, 1, 2, 10),
        "m": (30, 8, 1, 4, 2),
    }

    __enemies_names = {
        "z": "Зомби",
        "v": "Вампир",
        "g": "Привидение",
        "O": "Огр",
        "s": "Змей-маг",
        "m": "Мимик",
    }

    __enemies_colors = {
        "z": 12,
        "v": 3,
        "g": 13,
        "O": 14,
        "s": 15,
        "m": 15,
    }

    __enemies_patterns = {
        "z": MovePattern.STANDARD,
        "v": MovePattern.STANDARD,
        "g": MovePattern.JUMP,
        "O": MovePattern.STANDARD,
        "s": MovePattern.DIAGONAL,
        "m": MovePattern.ITEM,
    }

    harm_color = 10

    def __init__(self, enemy_type: str, level: int):
        self._symbol = enemy_type
        self._color = self.__enemies_colors[enemy_type]

        base_health, base_agility, base_speed, base_strength, base_hostility = self.__enemies_attr_map[enemy_type]
        scale_factor = pow(self.__enemy_scale, (level - 1))
        self.__max_health = base_health
        self.__health = self.__attr_randomize(base_health * scale_factor)
        self.__agility = self.__attr_randomize(base_agility * scale_factor)
        self.__strength = self.__attr_randomize(base_strength * scale_factor)
        self.__speed = base_speed
        self._hostility = base_hostility

        self.__level = level
        self._state = EnemyState.WALKING
        self.__coord = None
        self.name = self.__enemies_names[self._symbol]
        self._effects = {eff: [] for eff in list(Effects)}
        self._is_visible = True
        self.pattern = self.__enemies_patterns[self._symbol]

        # self.__miss_sound = SoundController.get_instance().get_sound(SoundType.Enemy, SoundUsage.miss)
        # self.__engaged_sound = SoundController.get_instance().get_sound(SoundType.Enemy, SoundUsage.engaged)

    @property
    def color(self): return self._color

    @property
    def health(self): return self.__health

    @property
    def agility(self): return self.__agility

    @property
    def speed(self): return self.__speed

    @property
    def strength(self): return self.__strength

    @property
    def hostility(self): return self._hostility

    @property
    def symbol(self): return self._symbol

    @property
    def is_visible(self): return self._is_visible

    @staticmethod
    def __attr_randomize(scaled_attr: int) -> float:
        return round(scaled_attr * uniform(0.8, 1.2))

    def add_attack_effect(self) -> RogueEffect | None:
        return None

    def attack(self) -> tuple[str, int, int, RogueEffect | None]:
        damage = round(uniform(self.__strength * 0.8, self.__strength * 1.2))
        return self.name, damage, int(self.__agility), self.add_attack_effect()

    def harm(self, e_name: str, e_strength: int, e_agility, e_effect: RogueEffect) -> tuple[list[RogueEvent], int]:
        events = []
        if is_enemy_hits(e_agility, self.__agility):
            # sound.play()
            RogueStats.get_instance().total_hits += 1
            self._color = self.harm_color
            self.__health -= e_strength
            self.__health = max(self.__health, 0)
            events.append(RogueEvent(f"{e_name} атакует {self.name} нанося {e_strength} урона", 23))
            if e_effect:
                events.extend(self.apply_effect(e_effect))
        else:
            # self.__miss_sound.play()
            RogueStats.get_instance().missed_hits += 1
            events.append(RogueEvent(f"{e_name} атакует {self.name} и промахивается"))

        return events, self.__exp_count()

    def __exp_count(self) -> int:
        if self.is_alive():
            return 0
        return ceil((self.__strength + self.__agility) * 0.1 + self._hostility * 0.08 + self.__max_health * 0.05)

    def apply_effect(self, effect: RogueEffect) -> list[RogueEvent]:
        """
        Применить эффект.
        Стакается только сон.
        """
        if effect.period:
            if effect.effect == Effects.SLEEP and self._effects[effect.effect]:
                self._effects[effect.effect].clear()
                self._effects[effect.effect].append(effect)
            else: self._effects[effect.effect].append(effect)

        match effect.effect:
            case Effects.AGILITY: self.__agility += effect.value
            case Effects.STRENGTH: self.__strength += effect.value
            case _: pass

        val = "" if effect.value == 0 else f" на {effect.value} ед. "
        per = "" if effect.period == 0 else f" на {effect.period} ходов"

        domain_log.info(
            "{name} got an effect {eff}, value {val}, period {period}",
            name=self.__class__.__name__,
            eff=effect.effect.name,
            val=effect.value,
            period=effect.period,
        )

        return [RogueEvent(f"{self.name} получает эффект {effect.value}{val}{per}")]

    def check_object_effects(self) -> tuple[list[RogueEvent], bool]:
        """
        Перевести эффекты на один ход вперед.
        :return: Список RogueEvent, True - если объект может продолжить ход, False - если нет.
        """
        self._color = self.__enemies_colors[self._symbol]
        can_move = True
        events, eff_to_remove = [], []
        
        for effects_list in self._effects.values():
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
        return events, can_move

    def __remove_effect(self, effect: RogueEffect) -> list[RogueEvent]:
        """
        Удалить эффект.
        """
        self._effects[effect.effect].remove(effect)

        match effect.effect:
            case Effects.MAX_HEALTH: pass
            case Effects.HEALTH: pass
            case Effects.AGILITY: self.__agility -= effect.value
            case Effects.STRENGTH: self.__strength -= effect.value

        domain_log.info("{name} has lost an effect {eff}", name=self.__class__.__name__, eff=effect.effect.name)

        return [RogueEvent(f"{self.name} теряет эффект {effect.effect.value}")]

    def is_alive(self): return self.__health > 0

    def is_engaged(self, crd: Coordinate) -> bool:
        y_enemy, x_enemy = crd
        y_ch, x_ch = Character.get_instance().get_crd()
        s = (abs(x_ch - x_enemy) ** 2 + abs(y_ch - y_enemy) ** 2) ** 0.5
        engaged = s <= self._hostility
        if not engaged: self._state = EnemyState.WALKING
        return engaged

    def set_engaged_status(self):
        if self._state != EnemyState.ENGAGED:
            # self.__engaged_sound.play()
            self._state = EnemyState.ENGAGED

    def status_engaged(self):
        return self._state == EnemyState.ENGAGED

    def __str__(self):
        return (
            f"{self.name} (Уровень: {self.__level}) - "
            f"Здоровье: {self.__health:.2f}, Ловкость: {self.__agility:.2f}, "
            f"Скорость: {self.__speed}, Сила: {self.__strength:.2f}, "
            f"Враждебность: {self._hostility}"
        )
