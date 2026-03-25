//
// Created by matei on 3/22/2026.
//

#include "topping.h"
#include <ostream>
#include <string>

topping::topping() : item("topping"), damage(0) {}

topping::topping(const std::string &nume, const int damage) : item(nume), damage(damage) {}

topping::~topping() = default;

int topping::get_damage() const {
    return this->damage;
}

void topping::set_damage(const int dmg) {
    this->damage=dmg;
}

void topping::print(std::ostream &os) const {
    os << "Topping: {Nume: " << nume << ", Damage: " << damage << "} ";
}

std::ostream &operator<<(std::ostream &os, const topping &ob) {
    ob.print(os);
    return os;
}

std::istream &operator>>(std::istream &is, topping &ob) {
    is >> ob.nume >> ob.damage;
    return is;
}

item *topping::get_clone() const {
    return new topping(*this);
}
