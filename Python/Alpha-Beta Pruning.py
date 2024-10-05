import math

class AlphaBetaGame:
    def __init__(self):
        self.board = [None] * 9  # Simple Tic-Tac-Toe example
        self.current_winner = None

    def available_moves(self):
        """Returns available moves."""
        return [i for i, x in enumerate(self.board) if x is None]

    def make_move(self, index, player):
        """Makes a move on the board."""
        if self.board[index] is None:
            self.board[index] = player
            if self.check_winner(player):
                self.current_winner = player
            return True
        return False

    def check_winner(self, player):
        """Checks for a winner."""
        win_combinations = [
            [0, 1, 2], [3, 4, 5], [6, 7, 8],  # Horizontal
            [0, 3, 6], [1, 4, 7], [2, 5, 8],  # Vertical
            [0, 4, 8], [2, 4, 6]              # Diagonal
        ]
        return any(all(self.board[i] == player for i in combo) for combo in win_combinations)

    def alpha_beta(self, depth, alpha, beta, is_maximizing):
        """Alpha-Beta pruning implementation."""
        # Check terminal states
        if self.current_winner == 'X':
            return 1
        elif self.current_winner == 'O':
            return -1
        elif all(x is not None for x in self.board):
            return 0

        if is_maximizing:
            max_eval = -math.inf
            for move in self.available_moves():
                self.make_move(move, 'X')
                eval = self.alpha_beta(depth + 1, alpha, beta, False)
                self.board[move] = None
                self.current_winner = None
                max_eval = max(max_eval, eval)
                alpha = max(alpha, eval)
                if beta <= alpha:
                    break  # Beta cutoff
            return max_eval
        else:
            min_eval = math.inf
            for move in self.available_moves():
                self.make_move(move, 'O')
                eval = self.alpha_beta(depth + 1, alpha, beta, True)
                self.board[move] = None
                self.current_winner = None
                min_eval = min(min_eval, eval)
                beta = min(beta, eval)
                if beta <= alpha:
                    break  # Alpha cutoff
            return min_eval

    def best_move(self):
        """Determines the best move for the maximizer ('X')."""
        best_score = -math.inf
        move = None
        for m in self.available_moves():
            self.make_move(m, 'X')
            score = self.alpha_beta(0, -math.inf, math.inf, False)
            self.board[m] = None
            self.current_winner = None
            if score > best_score:
                best_score = score
                move = m
        return move


# Example usage:
if __name__ == "__main__":
    game = AlphaBetaGame()
    game.make_move(0, 'X')
    game.make_move(1, 'O')
    print("Best move for X:", game.best_move())
