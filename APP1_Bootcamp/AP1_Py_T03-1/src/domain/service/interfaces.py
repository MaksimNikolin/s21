from abc import ABC, abstractmethod
from domain.model.game import Game

class IGameService(ABC):
    @abstractmethod
    def get_next_move(self, game: Game) -> Game:
        pass

    @abstractmethod
    def validate_field(self, game: Game) -> bool:
        pass

    @abstractmethod
    def check_game_over(self, game: Game) -> bool:
        pass