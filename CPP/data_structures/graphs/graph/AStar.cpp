#include <bits/stdc++.h>
using namespace std;

// Structure to represent a node in the grid
struct Node {
    int x, y;       // Coordinates
    int gCost;      // Cost from start node
    int hCost;      // Heuristic cost to goal
    int fCost;      // Total cost = g + h
    Node* parent;   // Pointer to parent node for path reconstruction

    Node(int _x, int _y, int _g, int _h, Node* _parent = nullptr)
        : x(_x), y(_y), gCost(_g), hCost(_h), parent(_parent) {
        fCost = gCost + hCost;
    }
};

// Heuristic function: Manhattan distance
int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Check if a position is valid and walkable
bool isValid(int x, int y, int rows, int cols, vector<vector<int>>& grid) {
    return x >= 0 && y >= 0 && x < rows && y < cols && grid[x][y] == 0;
}

// A* algorithm to find shortest path
vector<pair<int,int>> aStar(vector<vector<int>>& grid, pair<int,int> start, pair<int,int> goal) {
    int rows = grid.size();
    int cols = grid[0].size();

    auto cmp = [](Node* a, Node* b) { return a->fCost > b->fCost; };
    priority_queue<Node*, vector<Node*>, decltype(cmp)> openSet(cmp);

    vector<vector<bool>> closedSet(rows, vector<bool>(cols, false));

    Node* startNode = new Node(start.first, start.second, 0, heuristic(start.first, start.second, goal.first, goal.second));
    openSet.push(startNode);

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!openSet.empty()) {
        Node* current = openSet.top();
        openSet.pop();

        if (current->x == goal.first && current->y == goal.second) {
            // Reconstruct path
            vector<pair<int,int>> path;
            while (current) {
                path.push_back({current->x, current->y});
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        if (closedSet[current->x][current->y]) continue;
        closedSet[current->x][current->y] = true;

        for (int i = 0; i < 4; i++) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            if (isValid(nx, ny, rows, cols, grid) && !closedSet[nx][ny]) {
                int g = current->gCost + 1;
                int h = heuristic(nx, ny, goal.first, goal.second);
                Node* neighbor = new Node(nx, ny, g, h, current);
                openSet.push(neighbor);
            }
        }
    }

    return {}; // No path found
}

// Example usage
int main() {
    vector<vector<int>> grid = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0}
    };

    pair<int,int> start = {0, 0};
    pair<int,int> goal = {4, 4};

    vector<pair<int,int>> path = aStar(grid, start, goal);

    if (!path.empty()) {
        cout << "Path found:\n";
        for (auto p : path) {
            cout << "(" << p.first << "," << p.second << ") ";
        }
        cout << endl;
    } else {
        cout << "No path found.\n";
    }

    return 0;
}
