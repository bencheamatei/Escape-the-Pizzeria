//
// Created by matei on 6/23/2026.
//

#ifndef OOP_EVERYTHING_BUILDER_H
#define OOP_EVERYTHING_BUILDER_H

#include "player.h"
#include "room.h"
#include "enemy.h"

class everything_builder {
public:
    static std::vector<room> build_rooms();
    static void build_enemies(std::vector<enemy>& enemies_list);
    static void setup_starting_inventory(player& p);
};


#endif //OOP_EVERYTHING_BUILDER_H