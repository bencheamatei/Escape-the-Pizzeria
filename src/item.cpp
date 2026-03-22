//
// Created by matei on 3/22/2026.
//

#include "item.h"
#include <ostream>
#include <string>

item::item() {
    this->nume="item";
}
item::item(const std::string &denumire) {
    this->nume=denumire;
}
item::~item() = default;
std::string item::get_nume() const {
    return nume;
}
void item::set_nume(const std::string &denumire) {
    this->nume = denumire;
}

std::ostream &operator<<(std::ostream &os, const item &ob) {
    os << "Nume: " << ob.get_nume();
    return os;
}