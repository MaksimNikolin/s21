from .food import Food
from .gold import Gold
from .potion import Potion
from .scroll import Scroll
from .weapon import Weapon

ITEMS = [Gold, Food, Weapon, Scroll, Potion]
ITEMS_GEN = [Gold, Gold, Food, Food, Food, Food, Weapon, Scroll, Scroll, Potion, Potion]
ITEMS_MAPPING = {"Gold": Gold, "Food": Food, "Weapon": Weapon, "Scroll": Scroll, "Potion": Potion}
