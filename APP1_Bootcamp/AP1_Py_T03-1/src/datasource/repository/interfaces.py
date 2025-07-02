from abc import ABC, abstractmethod
from uuid import UUID
from domain.model.game import Game

class IGameRepository(ABC):
    @abstractmethod
    def get_game(self, game_id: UUID) -> Game:
        pass

    @abstractmethod
    def save_game(self, game: Game) -> None:
        pass