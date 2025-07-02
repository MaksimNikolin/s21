from domain.service.interfaces import IGameService
from domain.model.game import Game
from datasource.repository.interfaces import IGameRepository

class MinimaxGameService(IGameService):
    def __init__(self, repository: IGameRepository):
        self.repository = repository

    def get_next_move(self, game: Game) -> Game:
        matrix = game.field.matrix
        best_score = float('-inf')
        best_move = None

        for i in range(3):
            for j in range(3):
                if matrix[i][j] == 0:
                    matrix[i][j] = 2
                    score = self.minimax(matrix, 0, False)
                    matrix[i][j] = 0
                    if score > best_score:
                        best_score = score
                        best_move = (i, j)

        if best_move:
            i, j = best_move
            matrix[i][j] = 2
            self.repository.save_game(game)

        return game

    def minimax(self, matrix: list[list[int]], depth: int, is_maximizing: bool) -> int:
        winner = self.check_winner(matrix)
        if winner == 2:
            return 10 - depth
        elif winner == 1:
            return depth - 10
        elif self.is_draw(matrix):
            return 0

        if is_maximizing:
            best_score = float('-inf')
            for i in range(3):
                for j in range(3):
                    if matrix[i][j] == 0:
                        matrix[i][j] = 2
                        score = self.minimax(matrix, depth + 1, False)
                        matrix[i][j] = 0
                        best_score = max(score, best_score)
            return best_score
        else:
            best_score = float('inf')
            for i in range(3):
                for j in range(3):
                    if matrix[i][j] == 0:
                        matrix[i][j] = 1
                        score = self.minimax(matrix, depth + 1, True)
                        matrix[i][j] = 0
                        best_score = min(score, best_score)
            return best_score

    def check_winner(self, matrix: list[list[int]]) -> int | None:
        for i in range(3):
            if matrix[i][0] == matrix[i][1] == matrix[i][2] != 0:
                return matrix[i][0]
            if matrix[0][i] == matrix[1][i] == matrix[2][i] != 0:
                return matrix[0][i]
        if matrix[0][0] == matrix[1][1] == matrix[2][2] != 0:
            return matrix[0][0]
        if matrix[0][2] == matrix[1][1] == matrix[2][0] != 0:
            return matrix[0][2]
        return None

    def is_draw(self, matrix: list[list[int]]) -> bool:
        return all(cell != 0 for row in matrix for cell in row)

    def validate_field(self, game: Game) -> bool:
        stored_game = self.repository.get_game(game.id)
        if stored_game is None:
            self.repository.save_game(game)
            return True
        return stored_game.field.matrix == game.field.matrix

    def check_game_over(self, game: Game) -> bool:
        winner = self.check_winner(game.field.matrix)
        return winner is not None or self.is_draw(game.field.matrix)