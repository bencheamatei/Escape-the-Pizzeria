#include <string>
#include <utility>
#include "exceptions.h"

game_exception::game_exception(const std::string &message) : message(message) {}

const char *game_exception::what() const noexcept {
    return message.c_str();
}

inventory_exception::inventory_exception(const std::string &message) :
    game_exception("inventory error: "+message) {}

craft_exception::craft_exception(const std::string &message) :
    game_exception("crafting error: "+message) {}

combat_exception::combat_exception(const std::string &message) :
    game_exception("combat error: "+message) {}