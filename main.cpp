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
}