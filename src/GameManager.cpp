//
// Created by Wiktor Pieklik on 16/03/2020.
//

#include "../header/GameManager.h"

GameManager::GameManager(int thread_count)
{
    //GameManager::terminate = false;
    init(thread_count);
    for(int i=0; i<thread_count;i++) {
        balls.emplace_back(stdscr, i, coordinates);
        threads.emplace_back(&Ball::run, balls[i]);
    }
    for(int i=0; i<thread_count;i++) {
        if (threads[i].joinable()){}
            threads[i].detach();
    }
    std::thread exit ([](GameManager *manager){
        char c = getch();
        if(c == 's'){
          manager->exec();
        }
    }, this);
    run();
}

void GameManager::init(int thread_count)
{
    initscr();
    noecho();
    curs_set(FALSE);
    coordinates = new int*[2];
    for(int i=0; i<2; i++) {
        coordinates[i] = new int[thread_count];
    }
}

void GameManager::run()
{
    while(!terminate) {
        clear();
        for (size_t i = 0; i < balls.size(); i++) {
            int x = coordinates[1][i];
            int y = coordinates[0][i];
            mvprintw(y, x, "o");
        }
        refresh();
    }
    endwin();
}

void GameManager::exec()
{
    for(size_t i=0; i<balls.size(); i++) {
        balls[i].exec();
    }
    terminate = true;
}

