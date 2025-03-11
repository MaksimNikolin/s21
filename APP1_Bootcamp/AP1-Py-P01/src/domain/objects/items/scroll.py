import random
from datalayer.stats import RogueStats
from domain.objects.items.item import Item
from domain.objects.utils import Effects, RogueEffect, RogueEvent

class Scroll(Item):
    type, symbol, color = "scroll", "ʃ", 26

    def __init__(self, level: int):
        self.feature = random.choice(list(Effects)[:3])
        feature_base = 100 if self.feature == Effects.MAX_HEALTH else 15 if self.feature == Effects.STRENGTH else 12
        self.points = round(random.uniform(feature_base * 0.05 * pow(1.15, level - 1), feature_base * 0.15 * pow(1.15, level - 1)))
        self.__effect = RogueEffect(self.feature, self.points, 0)

    @property
    def effect(self): return self.__effect

    def pick_up(self) -> list[RogueEvent]: return [RogueEvent(f"You find a scroll: Scroll {self.feature.label}", 11)]

    def drop(self) -> tuple[list[RogueEvent], Item]: return [RogueEvent(f"You dropped a scroll: Scroll {self.feature.label}")], self

    def use(self) -> tuple[list[RogueEvent], RogueEffect]:
        RogueStats.get_instance().used_scrolls += 1
        # if self.feature == Effects.AGILITY: spelling = "Agility increase"
        # elif self.feature == Effects.STRENGTH: spelling = "Strength increase"
        # else: spelling = "Health increase"
        return [], self.__effect

    def _dump(self) -> dict:
        return {
            "feature": self.feature.name,
            "points": self.points,
        }

    def _load(self, feature: str, points: int):
        self.feature = Effects[feature]
        self.points = points
        self.__effect = RogueEffect(self.feature, self.points, 0)

    def __str__(self): return f"Scroll {self.feature.label}"

    def __lt__(self, other: Item): return self.feature.label < other.feature.label