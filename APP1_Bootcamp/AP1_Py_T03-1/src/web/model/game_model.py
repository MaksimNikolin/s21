class GameWebModel:
    def __init__(self, game_id: str, field: list[list[int]]):
        self.game_id = game_id
        self.field = field

    @classmethod
    def from_dict(cls, data: dict):
        return cls(
            game_id=data["game_id"],
            field=data["field"]
        )

    def to_dict(self):
        return {
            "game_id": self.game_id,
            "field": self.field
        }