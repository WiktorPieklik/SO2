//
// Created by Wiktor Pieklik
//

#include "../header/Ball.h"

Ball::Ball(WINDOW *window, int id, int **coordinates) {
    getmaxyx(window, max_y, max_x);
    x = max_x / 2;
    y = max_y - 1;

    x_direction = (std::rand() % 5 + 1) * (1 - (std::rand() % 3) + 1);
    y_direction = std::rand() % 3 + 1;
    this->coordinates = coordinates;
    this->id = id;
}

void Ball::move()
{
    int next_x = x + x_direction;
    int next_y = y + y_direction;
    handleCollision(next_x, next_y);
    coordinates[0][id] = y;
    coordinates[1][id] = x;
    this_thread::sleep_for(std::chrono::milliseconds(35));
}

void Ball::handleCollision(int next_x, int next_y)
{
    //horizontal collisions
    if(next_x > max_x || next_x < 0) {
        x_direction *= -1;
    }
    else {
        x = next_x;
    }
    //vertical collisions
    if(next_y > max_y || next_y < 0) {
        y_direction *= -1;
    }
    else {
        y = next_y;
    }
}

void Ball::run() {
    while (!this->terminated) {
        move();
    }
}

void Ball::terminate_exec() {
    this->terminated = true;
}