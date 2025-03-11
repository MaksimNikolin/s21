from datalayer.stats import RogueStats
from domain.objects.items.item import Item
from domain.objects.utils import Effects, RogueEffect, RogueEvent

food_types =   {"Apple": 10,  "Mango": 50,  "Banana": 150}
base_weights = {"Apple": 60,  "Mango": 15,  "Banana": 2  }
alpha_values = {"Apple": 0.3, "Mango": 0.2, "Banana": 0.1}

class Food(Item):
    type, symbol, color = "food", "®", 24

    def __init__(self, level: int):
        self.name, self.health_points = self._random_type(level, food_types, base_weights, alpha_values)
        self.__effect = RogueEffect(Effects.HEALTH, self.health_points, 0)

    @property
    def effect(self): return self.__effect

    def pick_up(self) -> list[RogueEvent]: return [RogueEvent(f"You find a food: {self.name}", 11)]

    def drop(self) -> tuple[list[RogueEvent], Item]: return [RogueEvent(f"You dropped a food: {self.name}")], self

    def use(self) -> tuple[list[RogueEvent], RogueEffect]:
        RogueStats.get_instance().eaten_food += 1
        return [], self.__effect
    
    def _dump(self) -> dict: return {"name": self.name, "hp": self.health_points}

    def _load(self, name: str, hp: int):
        self.name = name
        self.health_points = hp
        self.__effect = RogueEffect(Effects.HEALTH, self.health_points, 0)

    def __str__(self): return f"{self.name}"

    def __lt__(self, other: Item): return self.health_points < other.health_points