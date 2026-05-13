//
// Created by matei on 3/24/2026.
//

#include "pizza.h"
#include <iostream>

void pizza::calculate_total_dmg() {
    this->total_dmg = 0;
    for (const auto& it:toppings) {
        this->total_dmg+=it.get_damage();
    }
}

pizza::pizza() : item("pizza"), total_dmg(0) {
    this->toppings={};
}

pizza::pizza(const std::vector<topping> &toppings) : item("pizza") {
    this->toppings=toppings;
    calculate_total_dmg();
}

pizza::pizza(const std::initializer_list<topping> v) : item("pizza") {
    this->toppings={};
    for (const auto& it:v) {
        this->toppings.push_back(it);
    }
    calculate_total_dmg();
}

pizza::~pizza() = default;

item *pizza::get_clone() const {
    return new pizza(*this);
}

// o sa folosesc cand implementez mecanica de a arunca pizza

// int pizza::get_dmg() const {
//     return this->total_dmg;
// }

void pizza::display(std::ostream &os) const {
    os << "Pizza: {";
    for (const auto& it:toppings) {
        os << it;
    }
    os << "}";
}

std::ostream &operator<<(std::ostream &os, const pizza &pizza) {
    pizza.display(os);
    return os;
}

void pizza::on_use(player &p) {
    calculate_total_dmg();
    p.heal(this->total_dmg);
}
