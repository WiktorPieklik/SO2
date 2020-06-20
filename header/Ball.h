//
// Created by Wiktor Pieklik
//
#ifndef SO2_1_BALL_H
#define SO2_1_BALL_H

#include <unistd.h>
#include <ncurses.h>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <random>

using namespace std;

class Ball {
private:
    int x, y;
    int id;
    int max_x, max_y;
    int x_direction, y_direction;
    std::atomic<int **> coordinates;
    std::atomic<bool> terminated{false};
//    std::atomic<bool> isBlocked{false};

    void move();

    void handleCollision(int next_x, int next_y);

public:
    Ball(WINDOW *window, int id, int **coordinates);

    void run();
    void terminate_exec();
//    void setBlocked(bool isBlocked);
};


#endif //SO2_1_BALL_H
