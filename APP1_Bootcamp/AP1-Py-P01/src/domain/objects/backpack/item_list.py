from domain.objects.items.food import Food
from domain.objects.items.item import Item
from domain.objects.items.potion import Potion
from domain.objects.items.scroll import Scroll
from domain.objects.items.weapon import Weapon
from domain.objects.utils import RogueEvent
from utils.logger import domain_log

class ItemList:
    MAX_ITEMS_PER_TYPE = 9

    def __init__(self):
        self.food: list[Food] = []
        self.potions: list[Potion] = []
        self.scrolls: list[Scroll] = []
        self.weapons: list[Weapon] = []

    def size(self) -> int:
        return len(self.food) + len(self.potions) + len(self.scrolls) + len(self.weapons)

    def type_size(self, item_type) -> int:
        return len(
            self.food
            if item_type == Food
            else self.potions
            if item_type == Potion
            else self.scrolls
            if item_type == Scroll
            else self.weapons
        )

    def add(self, item: Item) -> bool:
        added = False
        if isinstance(item, Food) and len(self.food) < self.MAX_ITEMS_PER_TYPE:
            added = self._add_to_list(self.food, item)
        elif (isinstance(item, Potion)) and len(self.potions) < self.MAX_ITEMS_PER_TYPE:
            added = self._add_to_list(self.potions, item)
        elif (isinstance(item, Scroll)) and len(self.scrolls) < self.MAX_ITEMS_PER_TYPE:
            added = self._add_to_list(self.scrolls, item)
        elif (isinstance(item, Weapon)) and len(self.weapons) < self.MAX_ITEMS_PER_TYPE:
            added = self._add_to_list(self.weapons, item)
        domain_log.info(
            f"food: {len(self.food)}/9 potion: {len(self.potions)}/9 scroll:"
            f" {len(self.scrolls)}/9 weapon: {len(self.weapons)}/9"
        )
        return added

    @staticmethod
    def _add_to_list(lst: list, item: Item) -> bool:
        domain_log.info("adding to list")
        lst.append(item)
        lst.sort()
        return True

    def drop(self, item_type, slot: int) -> tuple[list[RogueEvent], Item]:
        if item_type == Food: events, item = self._drop_from_list(self.food, slot)
        elif item_type == Potion: events, item = self._drop_from_list(self.potions, slot)
        elif item_type == Scroll: events, item = self._drop_from_list(self.scrolls, slot)
        elif item_type == Weapon: events, item = self._drop_from_list(self.weapons, slot)
        else: raise NotImplementedError("Unknown item type")
        return events, item

    def _drop_from_list(self, lst: list[Item], slot: int) -> tuple[list[RogueEvent], Item]:
        events, item = lst[slot].drop()
        del lst[slot]
        return events, item

    def use(self, item_type, slot: int) -> tuple[list[RogueEvent], Item | None]:
        item = None
        events = []
        if item_type == Food:
            item = self.food[slot]
            del self.food[slot]
        elif item_type == Potion:
            item = self.potions[slot]
            del self.potions[slot]
        elif item_type == Scroll:
            item = self.scrolls[slot]
            del self.scrolls[slot]
        elif item_type == Weapon:
            if self.weapons[slot].held: events.append(RogueEvent("Это оружие уже в руках"))
            else: item = self.weapons[slot]
        else: raise NotImplementedError("Unknown item type")
        return events, item

    def show(self, item_type):
        domain_log.info(f"showing {self.type_size(item_type)} items of {item_type.__name__}")
        return (
            [str(food) for food in self.food]
            if item_type == Food
            else [str(potion) for potion in self.potions]
            if item_type == Potion
            else [str(scroll) for scroll in self.scrolls]
            if item_type == Scroll
            else [str(weapon) for weapon in self.weapons]
        )
