import math
import random
from abc import ABC, abstractmethod
from typing import Any

class Item(ABC):
    type, symbol, color = "item", "?", 8

    @property
    @abstractmethod
    def effect(self): raise NotImplementedError

    @staticmethod
    def _random_type(level: int, item_types, base_weights, alpha_values) -> tuple[Any, Any]:  # TODO типы!
        target = 0.5

        weights = {
            item: base_weights[item] * math.exp(-alpha_values[item] * (level - 1))
            + target * (1 - math.exp(-alpha_values[item] * (level - 1)))
            for item in item_types
        }

        total_weight = sum(weights.values())
        normalized_weights = {item: weight / total_weight for item, weight in weights.items()}
        items = list(normalized_weights.keys())
        probabilities = list(normalized_weights.values())
        chosen_item = random.choices(items, probabilities, k=1)[0]
        return chosen_item, item_types[chosen_item]

    @abstractmethod
    def pick_up(self): raise NotImplementedError

    @abstractmethod
    def drop(self): raise NotImplementedError

    @abstractmethod
    def use(self): raise NotImplementedError

    @abstractmethod
    def __str__(self): raise NotImplementedError

    @abstractmethod
    def __lt__(self, other): raise NotImplementedError
