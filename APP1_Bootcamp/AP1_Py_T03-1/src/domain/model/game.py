from uuid import UUID
from domain.model.game_field import GameField

class Game:
    def __init__(self, game_id: UUID, field: GameField):
        self.id = game_id
        self.field = field
