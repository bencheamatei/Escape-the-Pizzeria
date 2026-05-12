//
// Created by matei on 3/22/2026.
//

#include "../../include/player.h"
#include "../../include/items/topping.h"
#include "../../include/exceptions.h"
#include <ostream>
#include <string>

topping::topping() : item("topping"), damage(0) {}

topping::topping(const std::string &nume, int damage) : item(nume), damage(damage) {
    if (damage<0) {
        throw craft_exception("topping damage must be positive");
    }
}

topping::~topping() = default;

item *topping::get_clone() const {
    return new topping(*this);
}

void topping::apply_effect(player &p) {
    p.heal(1); // not really worth eating plain pepperoni
}

int topping::get_damage() const {
    return this->damage;
}

void topping::display(std::ostream &os) const {
    os << "Topping: {Nume: " << nume << ", Damage: " << damage << "} ";
}

std::istream &operator>>(std::istream &is, topping &it) {
    is >> it.nume >> it.damage;
    return is;
}

