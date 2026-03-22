#include <iostream>
#include <fstream>
#include "include/player.h"

int main() {

    std::ifstream fin("tastatura.txt");

    player p;
    std::cout << p;
    fin.close();
    return 0;
}
