from datasource.storage.game_storage import GameStorage
from datasource.repository.interfaces import IGameRepository

class GameRepository(IGameRepository):
    def __init__(self, storage: GameStorage):
        self._storage = storage

    def get_game(self, game_id):
        return self._storage.get(game_id)

    def save_game(self, game):
        self._storage.set(game.id, game)