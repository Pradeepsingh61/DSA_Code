import math

# Representing players
PLAYER_X = "X"  # Maximizer
PLAYER_O = "O"  # Minimizer
EMPTY = " "

class TicTacToe:
    def __init__(self):
        self.board = [EMPTY] * 9  # A 3x3 grid represented as a 1D array
        self.current_winner = None

    def print_board(self):
        """Print the current board."""
        for row in [self.board[i*3:(i+1)*3] for i in range(3)]:
            print("| " + " | ".join(row) + " |")

    def available_moves(self):
        """Return the indices of available moves."""
        return [i for i, spot in enumerate(self.board) if spot == EMPTY]

    def empty_squares(self):
        """Check if there are any empty squares on the board."""
        return EMPTY in self.board

    def winner(self, player):
        """Check if the given player has won the game."""
        win_combinations = [
            [0, 1, 2], [3, 4, 5], [6, 7, 8],  # Horizontal
            [0, 3, 6], [1, 4, 7], [2, 5, 8],  # Vertical
            [0, 4, 8], [2, 4, 6],             # Diagonal
        ]
        for combo in win_combinations:
            if all(self.board[i] == player for i in combo):
                return True
        return False

    def make_move(self, index, player):
        """Make a move on the board."""
        if self.board[index] == EMPTY:
            self.board[index] = player
            if self.winner(player):
                self.current_winner = player
            return True
        return False

    def minimax(self, is_maximizing):
        """Minimax algorithm to determine the best move."""
        # Check if the game is over
        if self.current_winner == PLAYER_X:
            return 1  # Maximizer wins
        elif self.current_winner == PLAYER_O:
            return -1  # Minimizer wins
        elif not self.empty_squares():
            return 0  # Draw

        # Maximizing player (X)
        if is_maximizing:
            best_score = -math.inf
            for move in self.available_moves():
                self.make_move(move, PLAYER_X)
                score = self.minimax(False)
                self.board[move] = EMPTY
                self.current_winner = None
                best_score = max(best_score, score)
            return best_score

        # Minimizing player (O)
        else:
            best_score = math.inf
            for move in self.available_moves():
                self.make_move(move, PLAYER_O)
                score = self.minimax(True)
                self.board[move] = EMPTY
                self.current_winner = None
                best_score = min(best_score, score)
            return best_score

    def best_move(self):
        """Determine the best move for the maximizing player (X)."""
        best_score = -math.inf
        move = None
        for possible_move in self.available_moves():
            self.make_move(possible_move, PLAYER_X)
            score = self.minimax(False)
            self.board[possible_move] = EMPTY
            self.current_winner = None
            if score > best_score:
                best_score = score
                move = possible_move
        return move


# Example game
if __name__ == "__main__":
    t = TicTacToe()
    t.print_board()

    # Play a few moves manually (you can add user input here)
    t.make_move(0, PLAYER_X)
    t.make_move(1, PLAYER_O)
    t.make_move(4, PLAYER_X)
    t.make_move(3, PLAYER_O)

    # Let Minimax choose the best move for PLAYER_X
    print("Computer's move (X):")
    best_move = t.best_move()
    t.make_move(best_move, PLAYER_X)
    t.print_board()
