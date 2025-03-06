from random import choice
from domain.objects.items import ITEMS
from domain.objects.utils import RogueEffect
from .enemy import Enemy, EnemyState

class Mimic(Enemy):
    def __init__(self, level: int):
        super().__init__("m", level)
        mimic_item = choice(ITEMS)
        self.mimic_color = mimic_item.color
        self.mimic_symbol = mimic_item.symbol

    def attack(self) -> tuple[str, int, int, RogueEffect | None]:
        name, strength, agility, effect = super().attack()
        return name, strength, agility, effect
    
    @property
    def symbol(self):
        if self._state != EnemyState.ENGAGED: return self.mimic_symbol
        return self._symbol

    @property
    def color(self):
        if self._state != EnemyState.ENGAGED: return self.mimic_color
        return self._color
