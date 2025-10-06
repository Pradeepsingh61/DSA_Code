/*
 * Algorithm Name:
 * N-Queens Problem (Backtracking Algorithm)
 *
 * Programming Language:
 * C
 *
 * Category:
 * Backtracking / Constraint Satisfaction Problems
 *
 * Difficulty Level:
 * Medium to Hard
 *
 * Problem Description:
 *
 * 1. Problem Statement:
 *    -> Place N chess queens on an N×N chessboard so that no two queens
 *       attack each other. Queens can attack horizontally, vertically, and
 *       diagonally in all directions.
 *
 * 2. Constraints:
 *    -> No two queens can be in the same row
 *    -> No two queens can be in the same column
 *    -> No two queens can be on the same diagonal
 *
 * 3. Approach / Algorithm:
 *    -> Use backtracking to systematically try all possible placements
 *    -> Place queens one row at a time
 *    -> For each row, try placing queen in each column
 *    -> Check if placement is safe (no conflicts with existing queens)
 *    -> If safe, recursively solve for next row
 *    -> If no safe placement found, backtrack to previous row
 *
 * 4. Complexity:
 *    Time: O(N!) in worst case, but pruning makes it much faster in practice
 *    Space: O(N) for recursion stack and board representation
 *
 * 5. Applications:
 *    -> Constraint satisfaction problems
 *    -> Game AI and puzzle solving
 *    -> Resource allocation problems
 *    -> Scheduling and optimization
 *    -> Educational tool for backtracking concepts
 *
 * 6. Variants Implemented:
 *    -> Basic backtracking solution
 *    -> Optimized backtracking with bit manipulation
 *    -> Solution counting (find all solutions)
 *    -> Interactive step-by-step solver
 *    -> Performance analysis and visualization
 *
 * Author:
 * Rishan Menezes
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define MAX_N 20
#define MAX_SOLUTIONS 1000

// Structure to store solution information
typedef struct {
    int board[MAX_N];  // board[i] = column position of queen in row i
    int n;
    int solutionCount;
    bool showSteps;
    int stepCount;
} NQueens;

// Function prototypes
bool solveNQueens(NQueens* nq, int row);
bool solveNQueensOptimized(int n, int row, int cols, int diag1, int diag2, int* solution);
int countAllSolutions(int n);
void printBoard(int* board, int n);
void printBoardVisual(int* board, int n);
bool isSafe(int* board, int row, int col);
bool isSafeOptimized(int row, int col, int cols, int diag1, int diag2);
void demonstrateBacktracking(int n);
void analyzeNQueens(int maxN);
void findAllSolutions(int n);
void interactiveSolver(int n);
double measureSolveTime(int n);
void printSolutionStats(int n);
void visualizeConflicts(int* board, int n, int row, int col);
bool hasConflict(int* board, int n, int row, int col);
void printQueenSymbol();
void printEmptySquare();

int main() {
    int choice, n;
    
    printf("=== N-Queens Problem - Backtracking Algorithm ===\n\n");
    printf("The N-Queens problem places N chess queens on an N×N chessboard\n");
    printf("such that no two queens attack each other.\n\n");
    
    while (1) {
        printf("\n=== N-Queens Operations ===\n");
        printf("1.  Solve N-Queens (find one solution)\n");
        printf("2.  Solve N-Queens (optimized bit manipulation)\n");
        printf("3.  Find all solutions\n");
        printf("4.  Count total solutions\n");
        printf("5.  Interactive step-by-step solver\n");
        printf("6.  Demonstrate backtracking process\n");
        printf("7.  Performance analysis (N=1 to 12)\n");
        printf("8.  Solution statistics for specific N\n");
        printf("9.  Visualize conflict detection\n");
        printf("10. Educational explanation\n");
        printf("0.  Exit\n");
        printf("Enter your choice: ");
        
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter board size N (4-%d): ", MAX_N);
                scanf("%d", &n);
                
                if (n < 4 || n > MAX_N) {
                    printf("Invalid size! N must be between 4 and %d\n", MAX_N);
                    break;
                }
                
                NQueens nq = {0};
                nq.n = n;
                nq.showSteps = false;
                
                printf("\nSolving %d-Queens problem...\n", n);
                clock_t start = clock();
                
                if (solveNQueens(&nq, 0)) {
                    clock_t end = clock();
                    double time = ((double)(end - start)) / CLOCKS_PER_SEC;
                    
                    printf("✅ Solution found in %.6f seconds!\n", time);
                    printf("\nSolution (Queen positions by row):\n");
                    for (int i = 0; i < n; i++) {
                        printf("Row %d: Column %d\n", i, nq.board[i]);
                    }
                    printf("\nVisual representation:\n");
                    printBoardVisual(nq.board, n);
                } else {
                    printf("❌ No solution exists for %d-Queens\n", n);
                }
                break;
                
            case 2:
                printf("Enter board size N (4-%d): ", MAX_N);
                scanf("%d", &n);
                
                if (n < 4 || n > MAX_N) {
                    printf("Invalid size! N must be between 4 and %d\n", MAX_N);
                    break;
                }
                
                int solution[MAX_N];
                printf("\nSolving %d-Queens with optimized algorithm...\n", n);
                
                start = clock();
                bool found = solveNQueensOptimized(n, 0, 0, 0, 0, solution);
                clock_t end = clock();
                double time = ((double)(end - start)) / CLOCKS_PER_SEC;
                
                if (found) {
                    printf("✅ Solution found in %.6f seconds!\n", time);
                    printBoardVisual(solution, n);
                } else {
                    printf("❌ No solution exists for %d-Queens\n", n);
                }
                break;
                
            case 3:
                printf("Enter board size N (4-12 recommended): ");
                scanf("%d", &n);
                
                if (n < 4 || n > 15) {
                    printf("Size should be between 4 and 15 for reasonable time\n");
                    break;
                }
                
                findAllSolutions(n);
                break;
                
            case 4:
                printf("Enter board size N (4-15 recommended): ");
                scanf("%d", &n);
                
                if (n < 4 || n > 15) {
                    printf("Size should be between 4 and 15 for reasonable time\n");
                    break;
                }
                
                printf("Counting all solutions for %d-Queens...\n", n);
                start = clock();
                int totalSolutions = countAllSolutions(n);
                end = clock();
                time = ((double)(end - start)) / CLOCKS_PER_SEC;
                
                printf("Total solutions for %d-Queens: %d\n", n, totalSolutions);
                printf("Time taken: %.6f seconds\n", time);
                break;
                
            case 5:
                printf("Enter board size N (4-8 recommended for visualization): ");
                scanf("%d", &n);
                
                if (n < 4 || n > 10) {
                    printf("Size should be between 4 and 10 for good visualization\n");
                    break;
                }
                
                interactiveSolver(n);
                break;
                
            case 6:
                printf("Enter board size N (4-6 recommended for demo): ");
                scanf("%d", &n);
                
                if (n < 4 || n > 8) {
                    printf("Size should be between 4 and 8 for clear demonstration\n");
                    break;
                }
                
                demonstrateBacktracking(n);
                break;
                
            case 7:
                printf("Running performance analysis...\n");
                analyzeNQueens(12);
                break;
                
            case 8:
                printf("Enter board size N: ");
                scanf("%d", &n);
                
                if (n < 4 || n > 15) {
                    printf("Size should be between 4 and 15\n");
                    break;
                }
                
                printSolutionStats(n);
                break;
                
            case 9:
                printf("Enter board size N (4-8): ");
                scanf("%d", &n);
                
                if (n < 4 || n > 8) {
                    printf("Size should be between 4 and 8\n");
                    break;
                }
                
                int testBoard[MAX_N] = {0};
                printf("Demonstrating conflict detection for %d-Queens:\n", n);
                
                // Place some queens and show conflicts
                testBoard[0] = 0;  // Queen at (0,0)
                testBoard[1] = 2;  // Queen at (1,2)
                
                printf("\nCurrent board with queens at (0,0) and (1,2):\n");
                printBoardVisual(testBoard, n);
                
                printf("\nTrying to place queen at different positions in row 2:\n");
                for (int col = 0; col < n; col++) {
                    printf("\nPosition (2,%d): ", col);
                    if (hasConflict(testBoard, n, 2, col)) {
                        printf("❌ CONFLICT");
                        visualizeConflicts(testBoard, n, 2, col);
                    } else {
                        printf("✅ SAFE");
                    }
                }
                break;
                
            case 10:
                printf("\n=== N-Queens Educational Explanation ===\n\n");
                printf("🔹 Problem: Place N queens on N×N board with no attacks\n");
                printf("🔹 Constraints:\n");
                printf("   • No two queens in same row\n");
                printf("   • No two queens in same column\n");
                printf("   • No two queens on same diagonal\n\n");
                
                printf("🔹 Backtracking Algorithm:\n");
                printf("   1. Place queens row by row\n");
                printf("   2. For each row, try each column\n");
                printf("   3. Check if placement is safe\n");
                printf("   4. If safe, recurse to next row\n");
                printf("   5. If no safe placement, backtrack\n\n");
                
                printf("🔹 Complexity:\n");
                printf("   • Time: O(N!) worst case, much better with pruning\n");
                printf("   • Space: O(N) for recursion stack\n\n");
                
                printf("🔹 Applications:\n");
                printf("   • Constraint satisfaction problems\n");
                printf("   • Resource allocation\n");
                printf("   • Scheduling optimization\n");
                printf("   • Game AI development\n");
                break;
                
            case 0:
                printf("Exiting N-Queens program. Goodbye!\n");
                return 0;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}

/**
 * Solve N-Queens using backtracking
 * 
 * @param nq: NQueens structure containing board and parameters
 * @param row: Current row to place queen
 * @return: true if solution found, false otherwise
 */
bool solveNQueens(NQueens* nq, int row) {
    // Base case: all queens placed successfully
    if (row >= nq->n) {
        return true;
    }
    
    // Try placing queen in each column of current row
    for (int col = 0; col < nq->n; col++) {
        if (isSafe(nq->board, row, col)) {
            // Place queen
            nq->board[row] = col;
            
            if (nq->showSteps) {
                nq->stepCount++;
                printf("\nStep %d: Placing queen at (%d, %d)\n", nq->stepCount, row, col);
                printBoardVisual(nq->board, nq->n);
                printf("Press Enter to continue...");
                getchar();
            }
            
            // Recursively solve for next row
            if (solveNQueens(nq, row + 1)) {
                return true;
            }
            
            // Backtrack: remove queen
            if (nq->showSteps) {
                printf("\nBacktracking: Removing queen from (%d, %d)\n", row, col);
            }
            nq->board[row] = -1;
        }
    }
    
    return false; // No solution found
}

/**
 * Optimized N-Queens solver using bit manipulation
 * 
 * @param n: Board size
 * @param row: Current row
 * @param cols: Bitmask for occupied columns
 * @param diag1: Bitmask for occupied main diagonals
 * @param diag2: Bitmask for occupied anti-diagonals
 * @param solution: Array to store solution
 * @return: true if solution found
 */
bool solveNQueensOptimized(int n, int row, int cols, int diag1, int diag2, int* solution) {
    if (row == n) {
        return true;
    }
    
    // Available positions = positions not attacked by any queen
    int available = ((1 << n) - 1) & (~(cols | diag1 | diag2));
    
    while (available) {
        // Get rightmost available position
        int pos = available & (-available);
        available ^= pos; // Remove this position from available
        
        // Find column number
        int col = 0;
        int temp = pos;
        while (temp > 1) {
            temp >>= 1;
            col++;
        }
        
        solution[row] = col;
        
        // Recursively solve for next row
        if (solveNQueensOptimized(n, row + 1, 
                                  cols | pos,
                                  (diag1 | pos) << 1,
                                  (diag2 | pos) >> 1,
                                  solution)) {
            return true;
        }
    }
    
    return false;
}

/**
 * Count all possible solutions for N-Queens
 * 
 * @param n: Board size
 * @return: Total number of solutions
 */
int countAllSolutions(int n) {
    int count = 0;
    
    // Helper function to count solutions
    void countSolutions(int row, int cols, int diag1, int diag2) {
        if (row == n) {
            count++;
            return;
        }
        
        int available = ((1 << n) - 1) & (~(cols | diag1 | diag2));
        
        while (available) {
            int pos = available & (-available);
            available ^= pos;
            
            countSolutions(row + 1,
                          cols | pos,
                          (diag1 | pos) << 1,
                          (diag2 | pos) >> 1);
        }
    }
    
    countSolutions(0, 0, 0, 0);
    return count;
}

/**
 * Check if placing queen at (row, col) is safe
 * 
 * @param board: Current board state
 * @param row: Row to place queen
 * @param col: Column to place queen
 * @return: true if safe, false otherwise
 */
bool isSafe(int* board, int row, int col) {
    // Check all previously placed queens
    for (int i = 0; i < row; i++) {
        // Check column conflict
        if (board[i] == col) {
            return false;
        }
        
        // Check diagonal conflicts
        if (abs(board[i] - col) == abs(i - row)) {
            return false;
        }
    }
    
    return true;
}

/**
 * Optimized safety check using bit manipulation
 */
bool isSafeOptimized(int row, int col, int cols, int diag1, int diag2) {
    return !(cols & (1 << col)) && 
           !(diag1 & (1 << (row + col))) && 
           !(diag2 & (1 << (row - col + MAX_N)));
}

/**
 * Print board in simple format
 */
void printBoard(int* board, int n) {
    for (int i = 0; i < n; i++) {
        printf("Row %d: Queen at column %d\n", i, board[i]);
    }
}

/**
 * Print board with visual representation
 */
void printBoardVisual(int* board, int n) {
    printf("\n");
    
    // Print column numbers
    printf("   ");
    for (int j = 0; j < n; j++) {
        printf(" %2d", j);
    }
    printf("\n");
    
    // Print top border
    printf("   ");
    for (int j = 0; j < n; j++) {
        printf("───");
    }
    printf("\n");
    
    for (int i = 0; i < n; i++) {
        printf("%2d│", i);
        for (int j = 0; j < n; j++) {
            if (board[i] == j) {
                printf(" ♛ ");  // Queen symbol
            } else {
                // Checkerboard pattern
                if ((i + j) % 2 == 0) {
                    printf(" · ");
                } else {
                    printf("   ");
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Interactive step-by-step solver
 */
void interactiveSolver(int n) {
    NQueens nq = {0};
    nq.n = n;
    nq.showSteps = true;
    nq.stepCount = 0;
    
    // Initialize board
    for (int i = 0; i < n; i++) {
        nq.board[i] = -1;
    }
    
    printf("\n=== Interactive N-Queens Solver ===\n");
    printf("Watch the algorithm place queens step by step.\n");
    printf("Press Enter after each step to continue.\n\n");
    
    printf("Initial empty board:\n");
    printBoardVisual(nq.board, n);
    printf("Press Enter to start...");
    getchar();
    getchar(); // Consume newline
    
    if (solveNQueens(&nq, 0)) {
        printf("\n🎉 Solution found!\n");
        printf("Final board:\n");
        printBoardVisual(nq.board, n);
        printf("Total steps: %d\n", nq.stepCount);
    } else {
        printf("No solution exists for %d-Queens\n", n);
    }
}

/**
 * Demonstrate backtracking process
 */
void demonstrateBacktracking(int n) {
    printf("\n=== Backtracking Demonstration ===\n");
    printf("This shows how the algorithm explores and backtracks.\n\n");
    
    // Manual demonstration for educational purposes
    int board[MAX_N];
    for (int i = 0; i < n; i++) board[i] = -1;
    
    printf("Step 1: Try placing first queen at (0,0)\n");
    board[0] = 0;
    printBoardVisual(board, n);
    
    printf("Step 2: Try placing second queen at (1,0) - CONFLICT!\n");
    printf("Queens attack each other vertically.\n\n");
    
    printf("Step 3: Try placing second queen at (1,1) - CONFLICT!\n");
    printf("Queens attack each other diagonally.\n\n");
    
    printf("Step 4: Try placing second queen at (1,2) - SAFE!\n");
    board[1] = 2;
    printBoardVisual(board, n);
    
    printf("Continue this process for all rows...\n");
    printf("When no safe position found, BACKTRACK to previous row.\n");
}

/**
 * Analyze N-Queens performance for different board sizes
 */
void analyzeNQueens(int maxN) {
    printf("\n=== N-Queens Performance Analysis ===\n");
    printf("Board Size | Solutions | Time (seconds)\n");
    printf("-----------|-----------|---------------\n");
    
    for (int n = 4; n <= maxN; n++) {
        clock_t start = clock();
        int solutions = countAllSolutions(n);
        clock_t end = clock();
        double time = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        printf("%10d | %9d | %13.6f\n", n, solutions, time);
    }
}

/**
 * Find and display all solutions for given N
 */
void findAllSolutions(int n) {
    printf("Finding all solutions for %d-Queens...\n", n);
    
    int allSolutions[MAX_SOLUTIONS][MAX_N];
    int solutionCount = 0;
    
    // Helper function to find all solutions
    void findAll(int row, int* board) {
        if (row == n) {
            if (solutionCount < MAX_SOLUTIONS) {
                for (int i = 0; i < n; i++) {
                    allSolutions[solutionCount][i] = board[i];
                }
                solutionCount++;
            }
            return;
        }
        
        for (int col = 0; col < n; col++) {
            if (isSafe(board, row, col)) {
                board[row] = col;
                findAll(row + 1, board);
                board[row] = -1;
            }
        }
    }
    
    int board[MAX_N];
    for (int i = 0; i < n; i++) board[i] = -1;
    
    clock_t start = clock();
    findAll(0, board);
    clock_t end = clock();
    double time = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("Found %d solutions in %.6f seconds\n", solutionCount, time);
    
    if (solutionCount > 0 && solutionCount <= 10) {
        printf("\nAll solutions:\n");
        for (int s = 0; s < solutionCount; s++) {
            printf("\nSolution %d:\n", s + 1);
            printBoardVisual(allSolutions[s], n);
        }
    } else if (solutionCount > 10) {
        printf("\nFirst 3 solutions:\n");
        for (int s = 0; s < 3; s++) {
            printf("\nSolution %d:\n", s + 1);
            printBoardVisual(allSolutions[s], n);
        }
        printf("... and %d more solutions\n", solutionCount - 3);
    }
}

/**
 * Print solution statistics
 */
void printSolutionStats(int n) {
    printf("\n=== %d-Queens Statistics ===\n", n);
    
    double time = measureSolveTime(n);
    int solutions = countAllSolutions(n);
    
    printf("Board size: %d×%d\n", n, n);
    printf("Total solutions: %d\n", solutions);
    printf("Time to find all: %.6f seconds\n", time);
    printf("Search space: ~%d! positions\n", n);
    
    if (solutions > 0) {
        printf("Solution density: %.2e%%\n", (double)solutions * 100 / pow(n, n));
    }
}

/**
 * Measure time to solve N-Queens
 */
double measureSolveTime(int n) {
    clock_t start = clock();
    countAllSolutions(n);
    clock_t end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

/**
 * Check if there's a conflict at given position
 */
bool hasConflict(int* board, int n, int row, int col) {
    return !isSafe(board, row, col);
}

/**
 * Visualize conflicts for educational purposes
 */
void visualizeConflicts(int* board, int n, int row, int col) {
    printf("\n   Conflicts with:\n");
    
    for (int i = 0; i < row; i++) {
        if (board[i] == col) {
            printf("   • Queen at (%d,%d) - same column\n", i, board[i]);
        }
        if (abs(board[i] - col) == abs(i - row)) {
            printf("   • Queen at (%d,%d) - diagonal attack\n", i, board[i]);
        }
    }
}
