"""
Knight's Tour
Author: DSA Code Repository
Date: 2025-10-02

This file contains:
- A pure backtracking solver (guaranteed correct, can be slow)
- An optimized solver using Warnsdorff's heuristic (practical & fast)
- Utilities to print and verify solutions
- A simple CLI for experimenting

Usage examples:
    python knights_tour.py --size 8 --method warnsdorff
    python knights_tour.py --size 5 --method backtracking
    python knights_tour.py --size 6 --method find_all --max_tours 3
"""

from typing import List, Optional, Tuple
import argparse
import sys

# Allowed knight moves (8 possibilities)
X_MOVES = [2, 1, -1, -2, -2, -1, 1, 2]
Y_MOVES = [1, 2, 2, 1, -1, -2, -2, -1]


def is_safe(x: int, y: int, board: List[List[int]], n: int) -> bool:
    """Return True if (x,y) is inside the board and not yet visited."""
    return 0 <= x < n and 0 <= y < n and board[x][y] == -1


def print_solution(board: List[List[int]], n: int) -> None:
    """Nicely print the board with move indices."""
    print("\nKnight's Tour Solution:")
    for i in range(n):
        for j in range(n):
            print(f"{board[i][j]:3d}", end=" ")
        print()


def verify_solution(board: List[List[int]], n: int) -> bool:
    """Verify that board contains all numbers 0..n*n-1 exactly once."""
    seen = set()
    for i in range(n):
        for j in range(n):
            val = board[i][j]
            if val < 0 or val >= n * n or val in seen:
                return False
            seen.add(val)
    return len(seen) == n * n


# ----------------------------
# Backtracking (exact solver)
# ----------------------------
def _bt_util(x: int, y: int, move_count: int, board: List[List[int]], n: int) -> bool:
    """
    Utility recursion for backtracking solver.
    Returns True when a full tour is found.
    """
    if move_count == n * n:
        return True

    for i in range(8):
        nx, ny = x + X_MOVES[i], y + Y_MOVES[i]
        if is_safe(nx, ny, board, n):
            board[nx][ny] = move_count
            if _bt_util(nx, ny, move_count + 1, board, n):
                return True
            # Backtrack
            board[nx][ny] = -1
    return False


def solve_knights_tour_backtracking(n: int, start_x: int = 0, start_y: int = 0) -> Optional[List[List[int]]]:
    """
    Solve Knight's Tour by backtracking (brute force).
    Very slow for 8x8 in worst case, but guaranteed to find a solution if one exists.
    """
    if n <= 0:
        raise ValueError("Board size must be >= 1")
    # Trivial case
    if n == 1:
        return [[0]]

    board = [[-1] * n for _ in range(n)]
    board[start_x][start_y] = 0

    if _bt_util(start_x, start_y, 1, board, n):
        return board
    return None


# -------------------------------------
# Warnsdorff's heuristic (optimized)
# -------------------------------------
def count_onward_moves(x: int, y: int, board: List[List[int]], n: int) -> int:
    """Count valid onward moves from (x,y). Used by Warnsdorff's heuristic."""
    cnt = 0
    for i in range(8):
        nx, ny = x + X_MOVES[i], y + Y_MOVES[i]
        if is_safe(nx, ny, board, n):
            cnt += 1
    return cnt


def solve_knights_tour_warnsdorff(n: int, start_x: int = 0, start_y: int = 0) -> Optional[List[List[int]]]:
    """
    Solve Knight's Tour using Warnsdorff's heuristic:
    Always move to the square with the fewest onward moves.
    This is not a strict guarantee but works extremely well in practice for standard sizes.
    """
    if n <= 0:
        raise ValueError("Board size must be >= 1")
    if n == 1:
        return [[0]]

    board = [[-1] * n for _ in range(n)]
    x, y = start_x, start_y
    board[x][y] = 0

    for move_count in range(1, n * n):
        # Build list of candidate moves with onward counts
        candidates: List[Tuple[int, int, int]] = []  # (onward_count, nx, ny)
        for i in range(8):
            nx, ny = x + X_MOVES[i], y + Y_MOVES[i]
            if is_safe(nx, ny, board, n):
                onward = count_onward_moves(nx, ny, board, n)
                candidates.append((onward, nx, ny))

        if not candidates:
            return None

        # Choose the candidate with minimum onward moves (tie-breaker: the one that appears first)
        candidates.sort(key=lambda t: (t[0], t[1], t[2]))  # deterministic tie-break
        _, next_x, next_y = candidates[0]

        board[next_x][next_y] = move_count
        x, y = next_x, next_y

    return board


# -------------------------------------
# Find multiple tours (using Warnsdorff attempts)
# -------------------------------------
def find_all_tours(n: int, max_tours: int = 5) -> List[Tuple[List[List[int]], int, int]]:
    """
    Attempt to find multiple tours using Warnsdorff's heuristic from a set of starting positions.
    Returns a list of tuples (board, start_x, start_y).
    Note: This is heuristic and won't enumerate all possible tours; used for examples.
    """
    tours = []
    # Try starting positions (limit number for efficiency)
    # We iterate across a small subset first, but you can try all n*n starts if desired
    for sx in range(min(n, 6)):
        for sy in range(min(n, 6)):
            if len(tours) >= max_tours:
                break
            board = solve_knightss_tour_warnsdorff(n, sx, sy)
            if board:
                tours.append((board, sx, sy))
        if len(tours) >= max_tours:
            break
    return tours


# ----------------------------
# CLI / Example usage
# ----------------------------
def main():
    parser = argparse.ArgumentParser(description="Knight's Tour solver (backtracking and Warnsdorff variants).")
    parser.add_argument("--size", "-s", type=int, default=8, help="Board size n (n x n). Default 8")
    parser.add_argument("--start", "-st", type=str, default="0,0", help="Starting position 'row,col' (default 0,0)")
    parser.add_argument("--method", "-m", type=str, default="warnsdorff",
                        choices=["backtracking", "warnsdorff", "find_all"],
                        help="Method to use: 'backtracking', 'warnsdorff', or 'find_all'. Default 'warnsdorff'")
    parser.add_argument("--max_tours", type=int, default=3, help="Used with find_all to limit results")
    args = parser.parse_args()

    try:
        sx_str, sy_str = args.start.split(",")
        sx, sy = int(sx_str), int(sy_str)
    except Exception:
        print("Invalid start position format. Use 'row,col' (e.g. 0,0).")
        sys.exit(1)

    n = args.size
    print(f"Knight's Tour: size={n}, start=({sx},{sy}), method={args.method}")

    if args.method == "backtracking":
        print("Running backtracking solver (may be slow for n>=8)...")
        board = solve_knights_tour_backtracking(n, sx, sy)
        if board:
            print_solution(board, n)
            print("Verification:", "Valid" if verify_solution(board, n) else "Invalid")
        else:
            print("No solution found (backtracking).")
    elif args.method == "warnsdorff":
        print("Running Warnsdorff's heuristic solver...")
        board = solve_knights_tour_warnsdorff(n, sx, sy)
        if board:
            print_solution(board, n)
            print("Verification:", "Valid" if verify_solution(board, n) else "Invalid")
        else:
            print("No solution found with Warnsdorff's heuristic.")
    else:  # find_all
        print(f"Attempting to find up to {args.max_tours} tours using Warnsdorff's heuristic from multiple starts...")
        tours = find_all_tours(n, max_tours=args.max_tours)
        print(f"Found {len(tours)} tours.")
        for idx, (tour, tx, ty) in enumerate(tours):
            print(f"\nTour #{idx+1} (start={tx},{ty}):")
            print_solution(tour, n)
            print("Verification:", "Valid" if verify_solution(tour, n) else "Invalid")


if __name__ == "__main__":
    main()
