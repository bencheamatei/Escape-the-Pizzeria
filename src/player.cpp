//
// Created by matei on 3/22/2026.
//

#include <iostream>
#include <string>
#include "player.h"
#include "inventory.h"

player::player() : rucsac(5) {
    this->hp=100;
    this->maxHp=100;
}

player::player(const int hp, const int maxHp, const int maxInventoryCapacity) : rucsac(maxInventoryCapacity){
    this->hp=hp;
    this->maxHp=maxHp;
}

player &player::operator=(const player &other) {
    if (this==&other)
        return *this;
    this->hp=other.hp;
    this->maxHp=other.maxHp;
    this->rucsac=other.rucsac;
    return *this;
}

player::player(const player &other) {
    this->hp=other.hp;
    this->maxHp=other.maxHp;
    this->rucsac=other.rucsac;
}

player::~player() = default;

const inventory& player::get_inventory() const {
    return this->rucsac;
}

std::ostream &operator<<(std::ostream &os, const player &p) {
    os << "Player\n";
    os << "Nume: " << p.nume << "\n";
    os << "Hp: " << p.hp << "\n";
    os << "Max Hp: " << p.maxHp << "\n";
    os << p.rucsac;
    return os;
}

void player::addItem(const inventorySlot &other) {
    if (this->rucsac.isFull()) {
        return;
    }
    this->rucsac.addItem(other);
}

bool player::isALive() const {
    return this->hp>0;
}

bool player::isDead() const {
    return this->hp==0;
}

int player::getHp() const {
    return this->hp;
}

void player::normalizeHp() {
    if (this->hp>this->maxHp) {
        this->hp=this->maxHp;
    }
    if (this->hp<0) {
        this->hp=0;
    }
}

void player::receiveDmg(const int x) {
    if (x<=0) {
        return;
    }
    hp-=x;
    normalizeHp();
}

void player::heal(const int x) {
    if (x<=0) {
        return;
    }
    hp+=x;
    normalizeHp();
}
