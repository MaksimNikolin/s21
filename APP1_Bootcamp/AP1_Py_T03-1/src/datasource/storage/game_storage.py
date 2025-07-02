from threading import Lock

class GameStorage:
    _instance = None
    _lock = Lock()

    def __new__(cls):
        with cls._lock:
            if cls._instance is None:
                cls._instance = super().__new__(cls)
                cls._instance._data = {}
            return cls._instance

    def get(self, game_id):
        return self._data.get(game_id)

    def set(self, game_id, game):
        self._data[game_id] = game