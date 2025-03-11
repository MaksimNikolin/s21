from domain.objects.items.item import Item
from domain.objects.utils import Effects, RogueEffect, RogueEvent

weapon_types = {"Sword": 5,   "Spear": 10,  "Mace": 15 }
base_weights = {"Sword": 30,  "Spear": 15,  "Mace": 5  }
alpha_values = {"Sword": 0.3, "Spear": 0.2, "Mace": 0.1}

class Weapon(Item):
    type, symbol, color = "weapon", "†", 27

    def __init__(self, level: int):
        self.name, self.power = self._random_type(level, weapon_types, base_weights, alpha_values)
        self.__effect = RogueEffect(Effects.STRENGTH, self.power, 0)
        self.held = False

    @property
    def effect(self): return self.__effect

    def pick_up(self) -> list[RogueEvent]:
        return [RogueEvent(f"You find a weapon: {self.name}", 11)]

    def drop(self) -> tuple[list[RogueEvent], Item]:
        self.held = False
        return [RogueEvent(f"You dropped a weapon: {self.name}")], self

    def use(self) -> tuple[list[RogueEvent], RogueEffect]:
        self.held = True
        return [RogueEvent(f"Weapon is using now: {self.name}")], self.__effect

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

    def __str__(self): return f"{self.name}{' (using)' if self.held else ''}"

    def __lt__(self, other: Item): return self.power < other.power
