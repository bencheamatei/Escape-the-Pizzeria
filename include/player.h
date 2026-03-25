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
    player(int , int , int );
    ~player();
    player(const player &);
    player &operator=(const player &);
    friend std::ostream &operator<<(std::ostream &, const player &);
    const inventory& get_inventory() const;
    void addItem(const inventorySlot &);
    bool isAlive() const;
    int getHp() const;
    void receiveDmg(const int x);
    void heal(const int x);
    void craftPizza();
    void drop_item(const int);
    void arrange();
    void enlarge_inventory(int);
    void eat_item(int);
};

#endif //OOP_PLAYER_H