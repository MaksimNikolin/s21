from domain.objects.backpack.item_list import ItemList
from domain.objects.items import Weapon
from domain.objects.items.gold import Gold
from domain.objects.items.item import Item
from domain.objects.utils import RogueEvent
from utils.logger import domain_log

class Backpack:
    __instance = None

    MIN_SLOT, MAX_SLOT = 1, 9

    def __new__(cls, *args, **kwargs):
        if cls.__instance is None:
            cls.__instance = super().__new__(cls, *args, **kwargs)
        return cls.__instance

    @classmethod
    def get_instance(cls): return cls.__instance

    def __init__(self): self.items = ItemList()

    def add_item(self, item: Item) -> tuple[list[RogueEvent], bool]:
        domain_log.info("Adding item to backpack")
        if isinstance(item, Gold):
            domain_log.error("Adding gold to backpack")
            raise TypeError("You're trying to add gold to backpack")
        events = []
        added = self.items.add(item)
        if added: events.extend(item.pick_up())
        else: events.append(RogueEvent(f"Backpack is full, type: '{item.type}'"))
        return events, added

    def drop_item(self, item_type, slot: int) -> tuple[list[RogueEvent], Item | None]:
        domain_log.info(f"Dropping item from slot {slot} {item_type.__name__} compartment of backpack")
        type_size = self.items.type_size(item_type)
        item = None
        events = []

        if 0 < slot <= type_size:
            events, item = self.items.drop(item_type, slot - 1)
        else:
            events.append(RogueEvent("Backpack is empty" if type_size == 0 else f"Incorrect select"))
        return events, item

    def drop_weapon(self, weapon: Weapon | None):
        if weapon: self.items.weapons.remove(weapon)

    def use_item(self, item_type, slot: int) -> tuple[list[RogueEvent], Item | None]:
        domain_log.info(f"Using item from slot {slot} {item_type.__name__} section of backpack")
        events = []
        item = None

        type_size = self.items.type_size(item_type)
        if 0 < slot <= type_size:
            use_events, item = self.items.use(item_type, slot - 1)
            events.extend(use_events)
        else:
            events.append(RogueEvent("Backpack is empty" if type_size == 0 else f"Incorrect select"))
        return events, item

    def show_items(self, item_type):
        domain_log.info(f"Get backpack contents for {item_type.__name__}")
        return self.items.show(item_type)
