//
// Created by matei on 3/22/2026.
//

#include <iostream>
#include <string>
#include "player.h"
#include "inventory.h"

player::player() {
    this->hp=100;
    this->maxHp=100;
    this->a.set_capacity(5);
}

player::player(const int hp, const int maxHp, const int maxInventoryCapacity) {
    this->hp=hp;
    this->maxHp=maxHp;
    this->a.set_capacity(maxInventoryCapacity);
}

player &player::operator=(const player &other) {
    if (this==&other)
        return *this;
    this->hp=other.hp;
    this->maxHp=other.maxHp;
    this->a=other.a;
    return *this;
}

player::player(const player &other) {
    this->hp=other.hp;
    this->maxHp=other.maxHp;
    this->a=other.a;
}

player::~player() = default;

inventory player::get_inventory() const {
    return this->a;
}

std::ostream &operator<<(std::ostream &os, const player &p) {
    os << "Nume: " << p.nume << "\n";
    os << "Hp: " << p.hp << "\n";
    os << "Max Hp: " << p.maxHp << "\n";
    os << p.a;
    return os;
}
