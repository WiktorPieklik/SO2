//
// Created by Wiktor Pieklik
//

#include "../header/Ball.h"

Ball::Ball(WINDOW *window, int id, int **coordinates, Barrier *barrier) {
    getmaxyx(window, max_y, max_x);
    x = max_x / 2 + 6;
    y = max_y - 1;

    x_direction = (std::rand() % 5 + 1) * (1 - (std::rand() % 3) + 1);
    y_direction = std::rand() % 3 + 1;
    this->coordinates = coordinates;
    this->id = id;
    this->barrier = barrier;
}

void Ball::move() {
    if (!isCollidingWithBarrier()) {
        int next_x = x + x_direction;
        int next_y = y + y_direction;
        handleCollision(next_x, next_y);
        coordinates[0][id] = y;
        coordinates[1][id] = x;
        this_thread::sleep_for(std::chrono::milliseconds(45));
    }
}

void Ball::draw() {
    mvprintw(y, x, "o");
}

void Ball::handleCollision(int next_x, int next_y) {
    //horizontal collisions
    if (next_x > max_x || next_x < 0) {
        x_direction *= -1;
    } else {
        x = next_x;
    }
    //vertical collisions
    if (next_y > max_y || next_y < 0) {
        y_direction *= -1;
    } else {
        y = next_y;
    }
}

bool Ball::isCollidingWithBarrier() {
    BlockingRect rect = barrier->getBlockingCoordinates();
    bool shouldStop = false;
    if (isTouchingBarrier(rect)) {
        switch ((int) rect.side) {
            case 0: //South
                shouldStop = y_direction < 0;
                break;
            case 1: //East
                shouldStop = x_direction < 0;
                break;
            case 2: //North
                shouldStop = y_direction > 0;
                break;
            case 3: //West
                shouldStop = x_direction > 0;
                break;
        }
    }

    return shouldStop;
}

bool Ball::isTouchingBarrier(BlockingRect blockingRect) {
    return x >= blockingRect.top_left_x && x <= blockingRect.bottom_right_x
           && y >= blockingRect.top_left_y && y <= blockingRect.bottom_right_y;
}

void Ball::run() {
    while (!this->terminated) {
        move();
    }
}

void Ball::terminate_exec() {
    this->terminated = true;
}