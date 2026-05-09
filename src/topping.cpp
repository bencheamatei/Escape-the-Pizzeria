//
// Created by matei on 3/22/2026.
//

#include "player.h"
#include "topping.h"
#include <ostream>
#include <string>

topping::topping() : item("topping"), damage(0) {}

topping::topping(const std::string &nume, int damage) : item(nume), damage(damage) {}

topping::~topping() = default;

item *topping::get_clone() const {
    return new topping(*this);
}

void topping::apply_effect(player &p) {
    // aici o sa facem ceva (at some point)
}

int topping::get_damage() const {
    return this->damage;
}

void topping::set_damage(const int dmg) {
    this->damage=dmg;
}

void topping::display(std::ostream &os) const {
    os << "Topping: {Nume: " << nume << ", Damage: " << damage << "} ";
}

std::istream &operator>>(std::istream &is, topping &it) {
    is >> it.nume >> it.damage;
    return is;
}

