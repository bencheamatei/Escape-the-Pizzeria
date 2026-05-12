#include "game.h"
#include "exceptions.h"
#include <iostream>

int main() {
    try {
        game game;
        game.run();
    }
    catch (const game_exception& e) {
        std::cerr << "[game error] " << e.what() << "\n";
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "[fatal] " << e.what() << "\n";
        return 1;
    }
    return 0;
}