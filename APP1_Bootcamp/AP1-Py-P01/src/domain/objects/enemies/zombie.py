from ..utils import RogueEffect
from .enemy import Enemy

class Zombie(Enemy):
    def __init__(self, level: int):
        super().__init__("z", level)

    def attack(self) -> tuple[str, int, int, RogueEffect | None]:
        name, strength, agility, effect = super().attack()
        return name, strength, agility, effect
