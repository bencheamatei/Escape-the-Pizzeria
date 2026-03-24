//
// Created by matei on 3/22/2026.
//

#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H
#include <string>
#include "inventory.h"

class player {
private:
    const std::string nume="Billy";
    int hp;
    int maxHp;
    inventory rucsac;
    void normalizeHp();
public:
    player();
    player(const int hp,const int maxHp, const int maxInventoryCapacity);
    ~player();
    player(const player &p);
    player &operator=(const player &p);
    friend std::ostream &operator<<(std::ostream &os, const player &p);
    const inventory& get_inventory() const;
    void addItem(const inventorySlot &other);
    inventorySlot pickItem(const inventorySlot &other,int pos);
    bool isAlive() const;
    bool isDead() const;
    int getHp() const;
    void receiveDmg(const int x);
    void heal(const int x);
    void craftPizza();
};

#endif //OOP_PLAYER_H