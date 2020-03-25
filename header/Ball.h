//
// Created by Wiktor Pieklik on 16/03/2020.
//
#ifndef SO2_1_BALL_H
#define SO2_1_BALL_H

#include <unistd.h>
#include <ncurses.h>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <mutex>

using namespace std;

class Ball {
private:
    int x, y;
    int id;
    int max_x, max_y;
    int stepInMillis;
    int x_direction, y_direction;
    int** coordinates;
    bool terminate = false;
    void move();
    void handleCollision(int next_x, int next_y);

public:
    Ball(WINDOW *window, int id, int** coordinates);
    void run();
    void exec();
};


#endif //SO2_1_BALL_H
