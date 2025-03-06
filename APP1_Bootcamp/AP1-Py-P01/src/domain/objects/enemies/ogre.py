from ..utils import Effects, RogueEffect
from .enemy import Enemy

class Ogre(Enemy):
    def __init__(self, level: int):
        super().__init__("O", level)

    def attack(self) -> tuple[str, int, int, RogueEffect | None]:
        self._effects[Effects.SLEEP].append(RogueEffect(Effects.SLEEP, 0, 1))
        name, strength, agility, effect = super().attack()
        return name, strength, agility, effect
