//
// Created by matei on 3/22/2026.
//

#include "topping.h"

#include <chrono>
#include <ostream>
#include <string>
#include <cmath>

topping::topping() : item("topping"){
    this->timp=0;
    this->damage=0;
}

topping::topping(const std::string &nume, int damage, int timp) : item(nume){
    this->timp=timp;
    this->damage=damage;
}

topping::~topping() = default;

int topping::get_damage() const {
    return this->damage;
}

int topping::get_timp() const {
    return this->timp;
}

void topping::set_damage(int dmg) {
    this->damage=dmg;
}

void topping::set_timp(int timpi) {
    this->timp=timpi;
}

int topping::calculate_damage(int time) {
    return std::min(time,timp)*damage;
}

int topping::calculate_overall_damage() {
    if (timp==0.0) {
        return damage;
    }
    return calculate_damage(timp);
}

std::ostream &operator<<(std::ostream &os, const topping &ob) {
    os << "Topping\n";
    os << "Nume: " << ob.get_nume() << " | ";
    os << "Damage: " << ob.get_damage() << " | ";
    os << "Timp: " << ob.get_timp();
    return os;
}

std::istream &operator>>(std::istream &is, topping &ob) {
    is >> ob.nume >> ob.damage >> ob.timp;
    return is;
}

