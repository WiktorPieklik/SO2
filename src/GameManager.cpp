//
// Created by Wiktor Pieklik
//

#include "../header/GameManager.h"

GameManager::GameManager(int thread_count) {
    this->thread_count = thread_count;
    init();
    exit_thread = std::thread([](GameManager *manager) {
        while (true) {
            char c = getch();
            if (c == 's') {
                manager->terminate = true;
                break;
            }
        }
    }, this);
}

void GameManager::init() {
    initscr();
    noecho();
    curs_set(FALSE);
    coordinates = new int *[2];
    refreshFreq = 10000;
    for (int i = 0; i < 2; i++) {
        coordinates[i] = new int[thread_count];
    }
    barrier = new Barrier(stdscr);
}

void GameManager::drawObjects() {
    while (!this->terminate) {
        clear();

        threadMutex.lock();
        for (size_t i = 0; i < balls.size(); i++) {
            int x = coordinates[1][i];
            int y = coordinates[0][i];
            mvprintw(y, x, "o");
        }
        threadMutex.unlock();
        barrier->draw();

        this_thread::sleep_for(chrono::microseconds(refreshFreq));
        refresh();
    }
}

int GameManager::run() {
    std::thread createThread(&GameManager::create_threads, this);
    barrier_thread = std::thread(&Barrier::run, barrier);
    drawObjects();
    if (createThread.joinable()) {
        createThread.join();
    }
    this->terminate_program();
    return balls.size();
}

void GameManager::create_threads() {
    std::srand(std::time(nullptr));
    for (int i = 0; i < thread_count && !this->terminate; i++) {
        threadMutex.lock();
        shared_ptr<Ball> ball(new Ball(stdscr, i, coordinates, barrier));
        balls.push_back(ball);
        threads.emplace_back(&Ball::run, balls[i]);
        threadMutex.unlock();
        this_thread::sleep_for(chrono::seconds(rand() % 4));
    }
}

void GameManager::requestJoin() {
    for (int i = 0; i < balls.size(); i++) {
        if (this->threads[i].joinable())
            this->threads[i].join();
    }
    if (this->exit_thread.joinable()) {
        this->exit_thread.join();
    }
    if (barrier_thread.joinable()) {
        barrier_thread.join();
    }
}

void GameManager::terminate_program() {
    threadMutex.lock();
    for (auto &ball : balls) {
        ball->terminate_exec();
    }
    threadMutex.unlock();
    barrier->terminate_exec();
    endwin();
}

GameManager::~GameManager() {
    delete[] this->coordinates;
    balls.clear();
    this->threads.clear();
}