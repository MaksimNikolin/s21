import math
from random import random
from dataclasses import dataclass
from enum import Enum

class MovePattern(Enum):
    STANDARD = 1
    DIAGONAL = 2
    JUMP = 3
    ITEM = 4

class Effects(Enum):
    MAX_HEALTH = ("изменение максимального HP", "здоровья")
    AGILITY = ("изменение ловкости", "ловкости")
    STRENGTH = ("изменение силы", "силы")
    SLEEP = ("сон", "")
    HEALTH = ("изменение HP", "")

    def __init__(self, value, label):
        self._value = value
        self._label = label

    @property
    def value(self): return self._value

    @property
    def label(self): return self._label

@dataclass(slots=True)
class RogueEffect:
    effect: Effects
    value: int
    period: int

@dataclass(slots=True)
class RogueEvent:
    info: str
    color: int = 1

def is_enemy_hits(attacker_agility, defender_agility) -> bool:
    k = 0.25
    probability_hit = 0.33 + (0.67 * (1 / (1 + math.exp(-k * (attacker_agility - defender_agility)))))
    if attacker_agility:
        min_hit_probability = 0.33
        probability_hit = max(probability_hit, min_hit_probability)
    return random() <= probability_hit
