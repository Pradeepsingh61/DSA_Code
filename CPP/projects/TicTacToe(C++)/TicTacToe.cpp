// -------------------------------------------------------------
// 🔹 SMALL BOARD (3x3) OPERATIONS:
// -------------------------------------------------------------
// 1️⃣ checkWin(board, player):
//     - Checks 3 rows, 3 columns, 2 diagonals → constant time
//     - Time Complexity: O(1)

// 2️⃣ isBoardFull(board):
//     - Traverses 9 cells → constant time
//     - Time Complexity: O(1)

// -------------------------------------------------------------
// 🔹 BIG BOARD (9 SMALL BOARDS):
// -------------------------------------------------------------
// Each small board = 3x3 = 9 cells  
// Total cells = 9 boards × 9 cells = 81 moves max

// Each move performs:
//   - Input validation → O(1)
//   - checkWin on small board → O(1)
//   - checkWin on big board → O(1)
//   - isBoardFull calls → O(1)
// Thus each move = O(1) operations.

// Total Moves = 81 → Total Time = 81 × O(1) = **O(1)** (constant since board size is fixed)

// ✅ **Overall Time Complexity:** O(1)  
// (even though practically 81 moves happen, it’s a fixed-size board → constant)

// -------------------------------------------------------------
// 🔹 SPACE COMPLEXITY:
// -------------------------------------------------------------
// 1️⃣ gameBoards → 3×3×3×3 = 81 cells
// 2️⃣ bigBoardState → 3×3 = 9 cells
// 3️⃣ Constant auxiliary variables (no recursion, no dynamic allocation)

// ✅ **Overall Space Complexity:** O(1)

// -------------------------------------------------------------
// 🔹 EXAMPLE WALKTHROUGH:
// -------------------------------------------------------------
// Suppose Player X plays first move at:
// (big_row=0, big_col=0, small_row=1, small_col=2)

// → Marks X in small board (0,0)
// → Next player O must play in board (1,2)

// This continues until:
// - One player wins 3 small boards in a row/col/diagonal on bigBoardState → Win
// - OR all 9 small boards are full → Draw

// Each step requires checking:
// - small board win → O(1)
// - big board win → O(1)
// So even for all 81 turns, the total computation is bounded → **O(1)** overall.
// */

//make tic tak toe game in cpp where we have a big parent having 9 points and then u fill a particular board nd 1st player has completre ffreedom to play and the second player will have to the playu on th board which player 1 
//second player will have to play on the the child board of that player 1]
#include <iostream>
#include <vector>

// --- Constants ---
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';
const char EMPTY = ' ';

// --- Function Prototypes ---
void printBoard(const std::vector<std::vector<std::vector<std::vector<char>>>>& boards);
bool checkWin(const std::vector<std::vector<char>>& board, char player);
bool isBoardFull(const std::vector<std::vector<char>>& board);

int main() {
    // A 4D vector to represent the game:
    // [big_board_row][big_board_col][small_board_row][small_board_col]
    std::vector<std::vector<std::vector<std::vector<char>>>> gameBoards(3, std::vector<std::vector<std::vector<char>>>(3, std::vector<std::vector<char>>(3, std::vector<char>(3, EMPTY))));

    // A 2D vector to track the state of the big board (who won each smaller board)
    std::vector<std::vector<char>> bigBoardState(3, std::vector<char>(3, EMPTY));

    char currentPlayer = PLAYER_X;
    int bigRow = -1; // -1 indicates the first player has free choice
    int bigCol = -1;
    bool gameOver = false;
    char winner = EMPTY;

    std::cout << "Welcome to Ultimate Tic-Tac-Toe!" << std::endl;
    std::cout << "Player X goes first." << std::endl;

    while (!gameOver) {
        printBoard(gameBoards);

        std::cout << "Player " << currentPlayer << "'s turn." << std::endl;

        // If the next move is restricted to a specific sub-board
        if (bigRow != -1 && bigBoardState[bigRow][bigCol] == EMPTY) {
            std::cout << "You must play on the board at (" << bigRow << ", " << bigCol << ")." << std::endl;
        } else {
            std::cout << "You can play on any available board." << std::endl;
            bigRow = -1; // Reset to allow free choice
            bigCol = -1;
        }

        int row, col, boardRow, boardCol;
        bool validMove = false;

        while (!validMove) {
            std::cout << "Enter your move (big_board_row big_board_col small_board_row small_board_col): ";
            std::cin >> boardRow >> boardCol >> row >> col;

            // Check if coordinates are within the board boundaries
            if (boardRow < 0 || boardRow > 2 || boardCol < 0 || boardCol > 2 || row < 0 || row > 2 || col < 0 || col > 2) {
                std::cout << "Invalid coordinates. Please try again." << std::endl;
                continue;
            }

            // Check if the move is on the correct board
            if (bigRow != -1 && (boardRow != bigRow || boardCol != bigCol)) {
                std::cout << "Invalid move. You must play on the designated board." << std::endl;
                continue;
            }

            // Check if the chosen board is already won
            if (bigBoardState[boardRow][boardCol] != EMPTY) {
                std::cout << "This board is already won. Please choose a different one." << std::endl;
                // Since the board is won, the next player gets a free choice
                if (bigRow != -1) {
                    bigRow = -1;
                    bigCol = -1;
                }
                continue;
            }

            // Check if the specific spot is already taken
            if (gameBoards[boardRow][boardCol][row][col] != EMPTY) {
                std::cout << "This spot is already taken. Please try again." << std::endl;
                continue;
            }

            // All checks passed, the move is valid
            validMove = true;
            gameBoards[boardRow][boardCol][row][col] = currentPlayer;

            // Update the next player's required board
            bigRow = row;
            bigCol = col;
        }

        // Check if the current move won the small board
        if (checkWin(gameBoards[boardRow][boardCol], currentPlayer)) {
            bigBoardState[boardRow][boardCol] = currentPlayer;
        } else if (isBoardFull(gameBoards[boardRow][boardCol])) {
            bigBoardState[boardRow][boardCol] = 'D'; // 'D' for Draw
        }
        
        // Check if the current move won the entire game on the big board
        if (checkWin(bigBoardState, currentPlayer)) {
            winner = currentPlayer;
            gameOver = true;
        }

        // Check for a draw on the big board
        if (isBoardFull(bigBoardState) && !gameOver) {
            gameOver = true;
        }

        // Switch players
        if (!gameOver) {
            currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
        }
    }

    printBoard(gameBoards);

    if (winner != EMPTY) {
        std::cout << "Congratulations, Player " << winner << " wins the game!" << std::endl;
    } else {
        std::cout << "The game is a draw!" << std::endl;
    }

    return 0;
}

// Function to print the entire Ultimate Tic-Tac-Toe board
void printBoard(const std::vector<std::vector<std::vector<std::vector<char>>>>& boards) {
    // Print column numbers
    std::cout << "    0   1   2       0   1   2       0   1   2" << std::endl;
    std::cout << "  +---+---+---+   +---+---+---+   +---+---+---+" << std::endl;

    for (int bigRow = 0; bigRow < 3; ++bigRow) {
        for (int smallRow = 0; smallRow < 3; ++smallRow) {
            // Print row numbers
            std::cout << bigRow * 3 + smallRow << " |";
            for (int bigCol = 0; bigCol < 3; ++bigCol) {
                for (int smallCol = 0; smallCol < 3; ++smallCol) {
                    std::cout << " " << boards[bigRow][bigCol][smallRow][smallCol] << " |";
                }
                std::cout << "   |";
            }
            std::cout << std::endl;
            std::cout << "  +---+---+---+   +---+---+---+   +---+---+---+" << std::endl;
        }
    }
}

// Function to check for a win on a single 3x3 board
bool checkWin(const std::vector<std::vector<char>>& board, char player) {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return false;
}

// Function to check if a single 3x3 board is full
bool isBoardFull(const std::vector<std::vector<char>>& board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}
