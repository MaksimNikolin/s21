import random
from domain.objects.utils import RogueEvent

class Gold:
    type, symbol, color = "gold", "◈", 9

    def __init__(self, level: int):
        self.__amount = int(random.uniform(10, 20 + level) * (level / 7))

    def pick_up(self) -> tuple[list[RogueEvent], int]:
        return [RogueEvent(f"You find: {self.__amount} gold")], self.__amount

    @property
    def amount(self) -> int: return self.__amount

    def __str__(self): return f"Gold: {self.__amount}"
