#include <iostream>
#include <thread>
#include <chrono>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

void drawBoard(int width, int height, const vector<pair<int, int>> &snake, int foodX, int foodY) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 ||
                j == 0 || j == width - 1) {
                mvaddch(i, j, '#');
            }
            else {
                bool isSnake = false;
                for (size_t k = 0; k < snake.size(); k++) {
                    if (snake[k].first == j && snake[k].second == i) {
                        if (k == 0) {
                            mvaddch(i, j, 'O');
                        }
                        else {
                            mvaddch(i, j, 'o');
                        }
                        isSnake = true;
                        break;
                    }
                }
                if (!isSnake && j == foodX && i == foodY) {
                    mvaddch(i, j, '*');
                }
            }
        }
    }
}

void spawnFood(int &foodX, int &foodY, int width, int height) {
    foodX = rand() % (width - 2) + 1;
    foodY = rand() % (height - 2) + 1;
}

void showScore(int score) {
    mvprintw(20, 0, "Score: %d", score);
}

void moveSnake(vector<pair<int, int>> &snake, char direction) {
    switch (direction) {
        case 'w':
            snake[0].second--;
            break;
        case 's':
            snake[0].second++;
            break;
        case 'a':
            snake[0].first--;
            break;
        case 'd':
            snake[0].first++;
            break;    
    }
}

int main() {
    int width, height, foodX, foodY, score;
    width = 30;
    height = 15;
    foodX = 25;
    foodY = 10;
    score = 0;
    char direction = 'd';
    vector<pair<int, int>> snake;
    snake.push_back({15, 8});
    snake.push_back({14, 8});
    snake.push_back({13, 8});
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    spawnFood(foodX, foodY, width, height);
    while (true) {
        int key = getch();
        if (key == 'q') {
            break;
        }
        if (key != ERR) {
            if ((direction == 'w' && key != 's') ||
                (direction == 's' && key != 'w') ||
                (direction == 'a' && key != 'd') ||
                (direction == 'd' && key != 'a')) {
                direction = key;
            }
        }
        moveSnake(snake, direction);
        if (snake[0].first <= 0 || 
            snake[0].first >= width - 1 || 
            snake[0].second <= 0 || 
            snake[0].second >= height - 1) {
            break;
        }
        if (snake[0].first == foodX && snake[0].second == foodY) {
            spawnFood(foodX, foodY, width, height);
            score++;
        }
        clear();
        drawBoard(width, height, snake, foodX, foodY);
        showScore(score);
        refresh();
        this_thread::sleep_for(chrono::milliseconds(150));
    }
    endwin();
}