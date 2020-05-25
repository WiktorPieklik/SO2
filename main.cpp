#include "../header/GameManager.h"
#include <iostream>
#include <string>

int main() {
    string instruction = "\n***************************************\n"
                         "Aby zakonczyc program nacisnij 's'\n"
                         "***************************************\n\n";
    int thread_count = 0;
    std::cout << instruction;
    std::cout << "Prosze podac liczbe kulek do wygenerowania: ";
    std::cin >> thread_count;

    GameManager gameManager = GameManager(thread_count);
    int generated = gameManager.run();
    gameManager.requestJoin();

    std::cout << "Program executed successfully" << endl;
    std::cout << "Generated: " << generated << " of " << thread_count << " balls" << endl;

    return 0;
}