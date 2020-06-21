//
// Created by Wiktor Pieklik
//

#ifndef SO2_1_BARRIER_H
#define SO2_1_BARRIER_H

#include <atomic>
#include <ncurses.h>
#include <thread>
#include <chrono>
#include <mutex>

enum BlockingSide {
    //Describes blocking side to balls. This sequention is anti-clockwise
    South = 0,
    East = 1,
    North = 2,
    West = 3,
};

typedef struct blocking_rectangle {
    int top_left_x;
    int top_left_y;
    int bottom_right_x;
    int bottom_right_y;
    BlockingSide side;
} BlockingRect;

class Barrier {
private:
    char representingSign;
    int length;
    int max_x, max_y;
    int dx, dy; //defines offset in collision detection
    int x, y; //top left, bottom right
    BlockingSide blockingSide;
    std::mutex blockingSideMutex;
    std::atomic<bool> terminated{false};

    void calculatePosition();

    void init();

    void rotate(); //anti-clockwise

public:
    Barrier(WINDOW *window);

    void run();
    void draw();

    void terminate_exec();

    BlockingRect getBlockingCoordinates();

};


#endif //SO2_1_BARRIER_H
