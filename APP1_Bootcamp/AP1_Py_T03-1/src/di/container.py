from datasource.storage.game_storage import GameStorage
from datasource.repository.game_repository import GameRepository
from domain.service.minimax_service import MinimaxGameService

class Container:
    def __init__(self):
        self._storage = GameStorage()
        self.repository = GameRepository(self._storage)
        self.game_service = MinimaxGameService(self.repository)