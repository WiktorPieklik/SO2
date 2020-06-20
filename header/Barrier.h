//
// Created by Wiktor Pieklik on 20/06/2020.
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

class Barrier {
private:
    char representingSign;
    int length;
    int max_x, max_y;
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

};


#endif //SO2_1_BARRIER_H
