"""
Algorithm: A* (A-star) Search
Description: Finds the shortest path between a start node and a goal node using 
             g(n) (actual cost so far) + h(n) (heuristic).
Time Complexity: O(E) in worst case
Space Complexity: O(V)
Author: Kashyap
Date: 2025-10-04
"""

import heapq

class Node:
    def __init__(self, position, parent=None, g=0, h=0):
        self.position = position  # (row, col)
        self.parent = parent      # previous node in path
        self.g = g                # cost from start
        self.h = h                # heuristic (to goal)
        self.f = g + h            # total cost

    def __lt__(self, other):
        return self.f < other.f   # needed for heapq priority

def heuristic(a, b):
    """Manhattan distance heuristic"""
    return abs(a[0] - b[0]) + abs(a[1] - b[1])

def a_star(grid, start, goal):
    """
    Perform A* search on a grid.
    
    Args:
        grid (list[list[int]]): 0 = free cell, 1 = obstacle
        start (tuple): (row, col) start position
        goal (tuple): (row, col) goal position
    
    Returns:
        path (list[tuple]): shortest path from start to goal
    """
    open_set = []
    heapq.heappush(open_set, Node(start, None, 0, heuristic(start, goal)))
    visited = set()

    while open_set:
        current = heapq.heappop(open_set)

        if current.position == goal:
            # Reconstruct path
            path = []
            while current:
                path.append(current.position)
                current = current.parent
            return path[::-1]  # reverse path

        visited.add(current.position)

        # Explore neighbors (up, down, left, right)
        directions = [(0,1), (0,-1), (1,0), (-1,0)]
        for d in directions:
            neighbor = (current.position[0] + d[0], current.position[1] + d[1])

            # Skip if out of bounds or obstacle
            if (0 <= neighbor[0] < len(grid) and
                0 <= neighbor[1] < len(grid[0]) and
                grid[neighbor[0]][neighbor[1]] == 0 and
                neighbor not in visited):

                g_cost = current.g + 1
                h_cost = heuristic(neighbor, goal)
                heapq.heappush(open_set, Node(neighbor, current, g_cost, h_cost))
    
    return None  # no path found


# main func()
if __name__ == "__main__":
    # Test Case 1: Normal case
    grid1 = [
        [0, 1, 0, 0, 0],
        [0, 1, 0, 1, 0],
        [0, 0, 0, 1, 0],
        [0, 1, 0, 0, 0],
        [0, 0, 0, 1, 0]
    ]
    start1 = (0, 0)
    goal1 = (4, 4)
    path1 = a_star(grid1, start1, goal1)
    print("Test Case 1 Path:", path1) # Expected: a valid path like [(0,0),(1,0),(2,0),(2,1),...(4,4)]

    # Test Case 2: Blocked path
    grid2 = [
        [0, 1, 1],
        [1, 1, 1],
        [0, 0, 0]
    ]
    start2 = (0, 0)
    goal2 = (2, 2)
    path2 = a_star(grid2, start2, goal2)
    print("Test Case 2 Path:", path2) # Expected: None (no path exists)

    # Test Case 3: Start = Goal
    grid3 = [
        [0, 0],
        [0, 0]
    ]
    start3 = (0, 0)
    goal3 = (0, 0)
    path3 = a_star(grid3, start3, goal3)
    print("Test Case 3 Path:", path3) # Expected: [(0, 0)] (trivial path)

    # Test Case 4: Larger grid with obstacles
    grid4 = [
        [0, 0, 0, 0, 0, 0],
        [1, 1, 1, 1, 1, 0],
        [0, 0, 0, 0, 0, 0],
        [0, 1, 1, 1, 1, 1],
        [0, 0, 0, 0, 0, 0]
    ]
    start4 = (0, 0)
    goal4 = (4, 5)
    path4 = a_star(grid4, start4, goal4)
    print("Test Case 4 Path:", path4) # Expected: a valid path from top-left to bottom-right