#include <iostream>
#include <thread>
#include <chrono>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

void drawBoard(int width, int height, int snakeX, int snakeY, int foodX, int foodY) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 ||
                j == 0 || j == width - 1) {
                mvaddch(i, j, '#');
            }
            else if (j == snakeX && i == snakeY) {
                mvaddch(i, j, 'O');
            }
            else if (j == foodX && i == foodY) {
                mvaddch(i, j, '*');
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

void moveSnake(int &snakeX, int &snakeY, char direction) {
    switch (direction) {
        case 'w':
            snakeY--;
            break;
        case 's':
            snakeY++;
            break;
        case 'a':
            snakeX--;
            break;
        case 'd':
            snakeX++;
            break;    
    }
}
int main() {
    int width, height, snakeX, snakeY, foodX, foodY, score;
    width = 30;
    height = 15;
    snakeX = 15;
    snakeY = 8;
    foodX = 25;
    foodY = 10;
    score = 0;
    char direction = 'd';
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
        moveSnake(snakeX, snakeY, direction);
        if (snakeX <= 0 || 
            snakeX >= width - 1 || 
            snakeY <= 0 || 
            snakeY >= height - 1) {
            break;
        }
        if (snakeX == foodX && snakeY == foodY) {
            spawnFood(foodX, foodY, width, height);
            score++;
        }
        clear();
        drawBoard(width, height, snakeX, snakeY, foodX, foodY);
        showScore(score);
        refresh();
        this_thread::sleep_for(chrono::milliseconds(150));
    }
    endwin();
}