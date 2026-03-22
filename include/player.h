//
// Created by matei on 3/22/2026.
//

#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H
#include <string>
#include "inventory.h"

class player {
private:
    const std::string nume="Billy"; // aici vreau sa fac o chestie
                                    // daca bati jocul once o sa poti sa schimbi numele
                                    // oricum nu o sa fie o componenta super relevanta in logica jocului sau cv
    int hp;
    int maxHp;
    inventory a;

public:

    player();
    player(const int hp,const int maxHp, const int maxInventoryCapacity);
    ~player();
    player(const player &p);
    player &operator=(const player &p);
    friend std::ostream &operator<<(std::ostream &os, const player &p);
    inventory get_inventory() const;
};

#endif //OOP_PLAYER_H