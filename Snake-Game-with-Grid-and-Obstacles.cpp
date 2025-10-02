#include <bits/stdc++.h>
#include <conio.h> // For _kbhit() and _getch() on Windows
#include <thread>
#include <chrono>
using namespace std;

struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

struct PointHash {
    size_t operator()(const Point& p) const {
        return hash<int>()(p.x) ^ hash<int>()(p.y);
    }
};

class SnakeGame {
    int width, height;
    deque<Point> snake;                // snake body
    unordered_set<Point, PointHash> snakeSet; // for fast collision check
    Point food;
    unordered_set<Point, PointHash> obstacles;
    char dir;                          // 'w','a','s','d'
    int score;
    bool gameOver;

public:
    SnakeGame(int w, int h) : width(w), height(h), dir('d'), score(0), gameOver(false) {
        snake.push_back({w/2, h/2});
        snakeSet.insert(snake.front());
        spawnFood();
        spawnObstacles(5);
    }

    void spawnFood() {
        while (true) {
            int fx = rand() % width;
            int fy = rand() % height;
            Point f = {fx, fy};
            if (!snakeSet.count(f) && !obstacles.count(f)) {
                food = f;
                break;
            }
        }
    }

    void spawnObstacles(int n) {
        while (obstacles.size() < n) {
            int ox = rand() % width;
            int oy = rand() % height;
            Point o = {ox, oy};
            if (!snakeSet.count(o) && !(o == food))
                obstacles.insert(o);
        }
    }

    void changeDirection(char c) {
        if ((dir == 'w' && c != 's') || (dir == 's' && c != 'w') ||
            (dir == 'a' && c != 'd') || (dir == 'd' && c != 'a'))
            dir = c;
    }

    void move() {
        Point head = snake.front();
        switch(dir) {
            case 'w': head.y--; break;
            case 's': head.y++; break;
            case 'a': head.x--; break;
            case 'd': head.x++; break;
        }

        // Check collisions
        if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height ||
            snakeSet.count(head) || obstacles.count(head)) {
            gameOver = true;
            return;
        }

        snake.push_front(head);
        snakeSet.insert(head);

        if (head == food) {
            score += 10;
            spawnFood();
        } else {
            Point tail = snake.back();
            snakeSet.erase(tail);
            snake.pop_back();
        }
    }

    void display() {
        system("cls"); // For Windows, use "clear" on Linux
        for(int y=0;y<height;y++){
            for(int x=0;x<width;x++){
                Point p = {x,y};
                if (snake.front() == p) cout << "O"; // head
                else if(snakeSet.count(p)) cout << "o"; // body
                else if(food == p) cout << "*"; // food
                else if(obstacles.count(p)) cout << "#"; // obstacles
                else cout << ".";
            }
            cout << "\n";
        }
        cout << "Score: " << score << "\n";
    }

    void run() {
        while(!gameOver) {
            if (_kbhit()) {
                char c = _getch();
                changeDirection(c);
            }
            move();
            display();
            this_thread::sleep_for(chrono::milliseconds(200));
        }
        cout << "Game Over! Final Score: " << score << endl;
    }
};

int main() {
    srand(time(0));
    SnakeGame game(20, 10);
    game.run();
    return 0;
}
