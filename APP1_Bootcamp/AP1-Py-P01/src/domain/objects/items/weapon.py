from domain.objects.items.item import Item
from domain.objects.utils import Effects, RogueEffect, RogueEvent

weapon_types = {"Короткий меч": 3, "Шипастая палица": 5, "Булава": 9, "Алебарда": 15, "Глефа": 21, "Двуручный меч": 30, "Молот войны": 50,}
base_weights = {"Короткий меч": 60, "Шипастая палица": 24, "Булава": 10, "Алебарда": 3, "Глефа": 2, "Двуручный меч": 0.9, "Молот войны": 0.1,}
alpha_values = {"Короткий меч": 0.12, "Шипастая палица": 0.12, "Булава": 0.08, "Алебарда": 0.02, "Глефа": 0.01, "Двуручный меч": 0.01, "Молот войны": 0.05,}

class Weapon(Item):
    type, symbol, color = "оружие", "†", 27

    def __init__(self, level: int):
        self.name, self.power = self._random_type(level, weapon_types, base_weights, alpha_values)
        self.__effect = RogueEffect(Effects.STRENGTH, self.power, 0)
        self.held = False

    @property
    def effect(self): return self.__effect

    def pick_up(self) -> list[RogueEvent]:
        return [RogueEvent(f"Вы нашли оружие {self.name}", 11)]

    def drop(self) -> tuple[list[RogueEvent], Item]:
        self.held = False
        return [RogueEvent(f"Вы выбросили оружие {self.name}")], self

    def use(self) -> tuple[list[RogueEvent], RogueEffect]:
        self.held = True
        return [RogueEvent(f"Теперь вы держите оружие {self.name}")], self.__effect

    def _dump(self) -> dict:
        return {
            "name": self.name,
            "power": self.power,
            "held": self.held,
        }

    def _load(self, name: str, power: int, held: bool):
        self.name = name
        self.power = power
        self.held = held
        self.__effect = RogueEffect(Effects.STRENGTH, self.power, 0)

    def __str__(self): return f"{self.name}{' (в руках)' if self.held else ''}"

    def __lt__(self, other: Item): return self.power < other.power
