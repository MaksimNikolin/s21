from random import random
from domain import Coordinate
from ..utils import RogueEffect
from .enemy import Enemy

class Ghost(Enemy):
    __INVIS_PROP = 0.5

    def __init__(self, level: int):
        super().__init__("g", level)

    def is_engaged(self, crd: Coordinate) -> bool:
        engaged = super().is_engaged(crd)
        if not engaged: self.__estimate_visibility()
        else: self._is_visible = True
        return engaged

    def __estimate_visibility(self):
        self._is_visible = random() < self.__INVIS_PROP

    def attack(self) -> tuple[str, int, int, RogueEffect | None]:
        name, strength, agility, effect = super().attack()
        return name, strength, agility, effect
