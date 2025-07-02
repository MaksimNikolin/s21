from flask import request, jsonify
from flask import Flask
from domain.service.interfaces import IGameService
from web.model.game_model import GameWebModel
from web.mapper.game_mapper import web_to_domain_game, domain_to_web_game
import uuid

def register_game_routes(app: Flask, game_service: IGameService):
    @app.route('/game/<string:game_id>', methods=['POST'])
    def update_game(game_id):
        try:
            game_uuid = uuid.UUID(game_id)
            data = request.get_json()
            if not data:
                return jsonify({"error": "Empty JSON"}), 400
            web_game = GameWebModel.from_dict(data)
            domain_game = web_to_domain_game(web_game, game_uuid)
            if not game_service.validate_field(domain_game):
                return jsonify({"error": "Invalid move"}), 400
            updated_game = game_service.get_next_move(domain_game)
            game_over = game_service.check_game_over(updated_game)
            response_game = domain_to_web_game(updated_game)
            return jsonify({
                "game": response_game.to_dict(),
                "game_over": game_over
            })
        except Exception as e:
            return jsonify({"error": str(e)}), 500