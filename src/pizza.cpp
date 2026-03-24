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

pizza::pizza() : item("pizza"){
    this->toppings={};
    calculate_total_dmg();
}

pizza::pizza(const std::vector<topping> &toppings) : item("pizza") {
    this->toppings=toppings;
    calculate_total_dmg();
}

pizza::pizza(std::initializer_list<topping> v) : item("pizza") {
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

int pizza::get_dmg() const {
    return this->total_dmg;
}

const std::vector<topping> &pizza::get_toppings() const {
    return this->toppings;
}

std::ostream &operator<<(std::ostream &os, const pizza &pizza) {
    os << "Pizza: \n";
    for (const auto& it:pizza.get_toppings()) {
        os << it << "\n";
    }
    os << pizza.get_dmg() << "\n";
    return os;
}