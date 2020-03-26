//
// Created by Wiktor Pieklik on 16/03/2020.
//

#include "../header/Ball.h"

Ball::Ball(WINDOW *window, int id, int **coordinates) {
    getmaxyx(window, max_y, max_x);
    x = rand() % max_x;
    y = rand() % max_y;
    stepInMillis = rand() % 20001 + 20000;
    x_direction = 1;
    y_direction = 1;
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
    this_thread::sleep_for(chrono::microseconds(stepInMillis));
}

void Ball::handleCollision(int next_x, int next_y)
{
    //horizontal collisons
    if(next_x > max_x || next_x < 0) {
        x_direction *= -1;
    }
    else {
        x = next_x;
    }

    if(next_y > max_y || next_y < 0) {
        y_direction *= -1;
    }
    else {
        y = next_y;
    }
}

void Ball::run()
{
    while(!terminate) {
        move();
    }
}

void Ball::exec()
{
    terminate = true;
}