from uuid import UUID
from domain.model.game import Game
from domain.model.game_field import GameField
from web.model.game_model import GameWebModel

def web_to_domain_game(web_model: GameWebModel, game_id: UUID) -> Game:
    field = GameField(web_model.field)
    return Game(game_id=game_id, field=field)

def domain_to_web_game(domain_model: Game) -> GameWebModel:
    return GameWebModel(
        game_id=str(domain_model.id),
        field=domain_model.field.matrix
    )