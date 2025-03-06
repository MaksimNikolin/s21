import random
from domain.objects.utils import RogueEvent

class Gold:
    type, symbol, color = "золото", "◈", 9

    def __init__(self, level: int):
        self.__amount = int(random.uniform(10, 20 + level) * (level / 7))

    @staticmethod
    def spelling(value: int) -> str:
        sp = "золотых монет"
        if value % 10 == 1: sp = "золотую монету"
        elif value % 10 in {2, 3, 4}: sp = "золотые монеты"
        return sp

    def pick_up(self) -> tuple[list[RogueEvent], int]:
        return [RogueEvent(f"Вы нашли {self.__amount} {self.spelling(self.__amount)}")], self.__amount

    @property
    def amount(self) -> int: return self.__amount

    def __str__(self): return f"Золото: {self.__amount}"
