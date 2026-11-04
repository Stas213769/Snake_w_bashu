#include <iostream>
using namespace std;

void drawBorder(int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1) {
                cout << "#";
            }
            else if (j == 0 || j == width - 1) {
                cout << "#";
            }
            else {
                cout << " ";
            }
        }
        cout << endl;
    }
}

void drawSnake(int snakeX, int snakeY) {
    for (int i = 0; i < snakeY; i++) {
        cout << endl;
        for (int j = 0; j < snakeX; j++) {
            cout << "0";
        }
    }
    cout << endl;
}

int main() {
    drawBorder(30, 15);
    drawSnake(5, 5);
    int width, height, a, snakeX, snakeY;
    width = 30;
    height = 15;
    snakeX = 5;
    snakeY = 5;
}