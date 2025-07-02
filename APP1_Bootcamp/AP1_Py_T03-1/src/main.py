# For installing enter in your terminal a command: ./run.sh

from flask import Flask
from di.container import Container
from web.route.game_route import register_game_routes

app = Flask(__name__)

container = Container()
register_game_routes(app, container.game_service)

if __name__ == "__main__":
    app.run(debug=True)