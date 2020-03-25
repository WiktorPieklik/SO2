//
// Created by Wiktor Pieklik on 16/03/2020.
//

#ifndef SO2_1_GAMEMANAGER_H
#define SO2_1_GAMEMANAGER_H

#include <vector>
#include "Ball.h"

class GameManager {
private:
    std::vector<std::thread> threads;
    std::vector<Ball> balls;
    int** coordinates{};
    void init(int thread_count);
    bool terminate = false;

public:
    explicit GameManager(int thread_count);
    void run();
    void exec();
};


#endif //SO2_1_GAMEMANAGER_H
