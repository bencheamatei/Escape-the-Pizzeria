//
// Created by matei on 3/22/2026.
//

#include "item.h"
#include <ostream>
#include <string>

item::item() {
    this->nume="item";
}
item::item(const std::string &nume) {
    this->nume=nume;
}
item::~item() = default;
std::string item::get_nume() const {
    return nume;
}

std::ostream &operator<<(std::ostream &os, const item &it) {
    it.display(os);
    return os;
}

std::istream &operator>>(std::istream &is, item &it) {
    is >> it.nume;
    return is;
}

void item::display(std::ostream &os) const {
    os << "Item: {Nume: " << this->nume << "}";
}

void item::print(std::ostream &os) const {
    display(os);
}
