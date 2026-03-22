//
// Created by matei on 3/22/2026.
//

#include "topping.h"

#include <chrono>
#include <ostream>
#include <string>
#include <cmath>

topping::topping() {
    this->nume="topping";
    this->timp=0;
    this->damage=0;
}

topping::topping(const std::string &nume, int damage, float timp) {
    this->nume=nume;
    this->timp=timp;
    this->damage=damage;
}

std::string topping::get_nume() const {
    return this->nume;
}

int topping::get_damage() const {
    return this->damage;
}

float topping::get_timp() const {
    return this->timp;
}

void topping::set_damage(int damage) {
    this->damage=damage;
}

void topping::set_timp(float timp) {
    this->timp=timp;
}

void topping::set_nume(const std::string &nume) {
    this->nume=nume;
}

int topping::calculate_damage(float time) {
    return floor(std::min(time,timp))*damage;
}

int topping::calculate_overall_damage() {
    if (timp==0) {
        return damage;
    }
    return calculate_damage(timp);
}

std::ostream &operator<<(std::ostream &os, const topping &ob) {
    os << "Nume: " << ob.get_nume() << " | ";
    os << "Damage: " << ob.get_damage() << " | ";
    os << "Timp: " << ob.get_timp();
    return os;
}



