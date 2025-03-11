from domain.objects.character import Character
from utils.logger import controller_log

class GameInfo:
    def __init__(self, floor):
        self.floor = 0
        self.hp = 0
        self.max_hp = 0
        self.str = 0
        self.ag = 0
        self.gold = 0
        self.exp = 0
        self.max_exp = 0
        self.level = 0

        self.character = Character.get_instance()
        self.refresh(floor)

        controller_log.info("{cls} initialized.", cls=self.__class__.__name__)

    def refresh(self, floor):
        if self.character is None:
            controller_log.error("Initializing GameInfo when Character doesn't exist")
            raise ValueError("Character doesn't exist")

        self.floor = floor
        self.hp = self.character.hp
        self.max_hp = self.character.max_hp
        self.str = self.character.strength
        self.ag = self.character.agility
        self.gold = self.character.gold
        self.exp = self.character.exp
        self.max_exp = self.character.max_exp
        self.level = self.character.level
