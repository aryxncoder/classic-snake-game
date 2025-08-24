#include <iostream>
#include <conio.h>     
#include <windows.h>   // For Sleep()
#include <vector>
using namespace std;

const int WIDTH = 20;
const int HEIGHT = 20;

int x, y, fruitX, fruitY, score;
vector<pair<int, int>> tail;

enum Direction { STOP, LEFT, RIGHT, UP, DOWN };
Direction dir;
bool gameOver;

void Setup() {
    gameOver = false;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
    tail.clear();
}

void Draw() {
    system("cls");

    // Top border
    for (int i = 0; i < WIDTH + 2; i++) cout << "#";
    cout << endl;

    // Game area
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0) cout << "#";

            if (i == y && j == x)
                cout << "O"; // Head
            else if (i == fruitY && j == fruitX)
                cout << "F"; // Fruit
            else {
                bool printed = false;
                for (auto segment : tail) {
                    if (segment.first == j && segment.second == i) {
                        cout << "o";
                        printed = true;
                        break;
                    }
                }
                if (!printed) cout << " ";
            }

            if (j == WIDTH - 1) cout << "#";
        }
        cout << endl;
    }

    // Bottom border
    for (int i = 0; i < WIDTH + 2; i++) cout << "#";
    cout << "\nScore: " << score << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 72: dir = UP; break;
            case 80: dir = DOWN; break;
            case 75: dir = LEFT; break;
            case 77: dir = RIGHT; break;
            case 'x': gameOver = true; break;
        }
    }
}

void Logic() {
    // Update tail positions
    if (!tail.empty()) {
        tail.insert(tail.begin(), {x, y});
        tail.pop_back();
    }

    // Move head
    switch (dir) {
        case LEFT:  x--; break;
        case RIGHT: x++; break;
        case UP:    y--; break;
        case DOWN:  y++; break;
        default:    break;
    }

    // Boundary collision
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) gameOver = true;

    // Self collision
    for (auto segment : tail) {
        if (segment.first == x && segment.second == y) {
            gameOver = true;
            break;
        }
    }

    // Eating fruit
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        tail.push_back({-1, -1}); // Add a new segment
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100);
    }
    cout << "\nGame Over! Final Score: " << score << "\n";
    return 0;
}
