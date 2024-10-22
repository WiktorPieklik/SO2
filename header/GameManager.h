//
// Created by Wiktor Pieklik
//

#ifndef SO2_1_GAMEMANAGER_H
#define SO2_1_GAMEMANAGER_H

#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include "Ball.h"
#include "Barrier.h"

class GameManager {
private:
    std::vector<std::thread> threads;
    std::vector<std::shared_ptr<Ball>> balls;
    std::thread exit_thread, barrier_thread;
    std::atomic<int **> coordinates{};

    void init();

    void create_threads();

    int thread_count;
    int refreshFreq{};
    Barrier *barrier;
    std::mutex threadMutex;


public:
    explicit GameManager(int thread_count);

    ~GameManager();

    int run();

    void terminate_program();
    void requestJoin();
    void drawObjects();

    std::atomic<bool> terminate{false};
};


#endif //SO2_1_GAMEMANAGER_H
