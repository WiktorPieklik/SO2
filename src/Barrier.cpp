//
// Created by Wiktor Pieklik on 20/06/2020.
//

#include "../header/Barrier.h"

Barrier::Barrier(WINDOW *window) {
    getmaxyx(window, max_y, max_x);
    init();
}

void Barrier::init() {
    blockingSide = South;
    representingSign = 'x';
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

void Barrier::rotate() {
    blockingSideMutex.lock();
    int nextPosition = ((int) blockingSide + 1) % 4;
    blockingSide = (BlockingSide) nextPosition;
    blockingSideMutex.unlock();
}

void Barrier::run() {
    while (!terminated) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        rotate();
    }
}

void Barrier::terminate_exec() {
    terminated = true;
}
