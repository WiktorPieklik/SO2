//
// Created by Wiktor Pieklik
//

#include "../header/Barrier.h"

Barrier::Barrier(WINDOW *window) {
    getmaxyx(window, max_y, max_x);
    init();
}

void Barrier::init() {
    blockingSide = South;
    representingSign = 'x';
    dx = 2;
    dy = 1;
}

void Barrier::calculatePosition() {
    int ref_y = max_y / 2, ref_x = max_x / 2;
    if (blockingSide == South || blockingSide == North) {
        x = ref_x - ref_x / 2;
        y = ref_y;
        length = x * 2;
    } else {
        x = ref_x;
        y = ref_y - ref_y / 2;
        length = y * 2;
    }
}

void Barrier::draw() {
    blockingSideMutex.lock();
    calculatePosition();
    if (blockingSide == South || blockingSide == North) {
        mvhline(y, x, representingSign, length);
    } else {
        mvvline(y, x, representingSign, length);
    }
    blockingSideMutex.unlock();
}

BlockingRect Barrier::getBlockingCoordinates() {
    BlockingRect rect;
    blockingSideMutex.lock();
    if (blockingSide == North || blockingSide == South) {
        rect.top_left_x = x;
        rect.bottom_right_x = x + length;
        rect.top_left_y = y - dy;
        rect.bottom_right_y = y + dy;
    } else {
        rect.top_left_x = x - dx;
        rect.bottom_right_x = x + dx;
        rect.top_left_y = y;
        rect.bottom_right_y = y + length;
    }
    rect.side = blockingSide;
    blockingSideMutex.unlock();

    return rect;
}

void Barrier::rotate() {
    blockingSideMutex.lock();
    int nextPosition = ((int) blockingSide + 1) % 4;
    blockingSide = (BlockingSide) nextPosition;
    blockingSideMutex.unlock();
}

void Barrier::run() {
    while (!terminated) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        rotate();
    }
}

void Barrier::terminate_exec() {
    terminated = true;
}
