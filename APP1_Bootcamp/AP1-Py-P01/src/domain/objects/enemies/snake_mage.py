from copy import copy
from random import random
from domain.objects.utils import RogueEffect
from .enemy import Effects, Enemy
from utils.logger import domain_log

class SnakeMage(Enemy):
    __SLEEP_PROP = 0.2

    def __init__(self, level: int):
        super().__init__("s", level)
        self.__effect = RogueEffect(Effects.SLEEP, 0, (level // 7 or 1))

    def add_attack_effect(self) -> RogueEffect | None:
        domain_log.debug(f"{self.__class__.__name__} adding effect {self.__effect}")
        return None if random() > self.__SLEEP_PROP else copy(self.__effect)

    def attack(self) -> tuple[str, int, int, RogueEffect | None]:
        name, strength, agility, effect = super().attack()
        return name, strength, agility, effect
