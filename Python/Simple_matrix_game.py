import numpy as np

class MatrixGame:
    def __init__(self, payoff_matrix_p1, payoff_matrix_p2):
        self.payoff_matrix_p1 = payoff_matrix_p1
        self.payoff_matrix_p2 = payoff_matrix_p2

    def find_nash_equilibrium(self):
        p1_strategies = list(range(self.payoff_matrix_p1.shape[0]))
        p2_strategies = list(range(self.payoff_matrix_p1.shape[1]))

        # Eliminate dominated strategies for both players
        p1_strategies = self.eliminate_dominated(p1_strategies, self.payoff_matrix_p1)
        p2_strategies = self.eliminate_dominated(p2_strategies, self.payoff_matrix_p2.T)

        if p1_strategies and p2_strategies:
            return [(p1, p2) for p1 in p1_strategies for p2 in p2_strategies]
        else:
            return "No Nash Equilibrium found"

    def eliminate_dominated(self, strategies, payoff_matrix):
        dominated = set()
        for i in strategies:
            for j in strategies:
                if i != j and np.all(payoff_matrix[i] <= payoff_matrix[j]):
                    dominated.add(i)
        return [s for s in strategies if s not in dominated]

# Example payoff matrices for Player 1 and Player 2
payoff_matrix_p1 = np.array([[3, 1], [0, 2]])  # Player 1's payoffs
payoff_matrix_p2 = np.array([[2, 1], [3, 0]])  # Player 2's payoffs

game = MatrixGame(payoff_matrix_p1, payoff_matrix_p2)
nash_equilibria = game.find_nash_equilibrium()
print("Nash Equilibria:", nash_equilibria)
