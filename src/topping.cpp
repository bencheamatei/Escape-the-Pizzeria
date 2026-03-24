//
// Created by matei on 3/22/2026.
//

#include "topping.h"

#include <chrono>
#include <ostream>
#include <string>
#include <cmath>

topping::topping() : item("topping"), damage(0) {}

topping::topping(const std::string &nume, int damage) : item(nume), damage(damage) {}

topping::~topping() = default;

int topping::get_damage() const {
    return this->damage;
}

void topping::set_damage(int dmg) {
    this->damage=dmg;
}

std::ostream &operator<<(std::ostream &os, const topping &ob) {
    os << "Topping\n";
    os << "Nume: " << ob.get_nume() << " | ";
    os << "Damage: " << ob.get_damage();
    return os;
}

std::istream &operator>>(std::istream &is, topping &ob) {
    is >> ob.nume >> ob.damage;
    return is;
}

item *topping::get_clone() const {
    return new topping(*this);
}
