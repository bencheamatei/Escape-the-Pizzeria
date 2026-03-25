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

void item::print(std::ostream &os) const {
    os << "Item: {Nume: " << nume << "} ";
}

std::ostream &operator<<(std::ostream &os, const item &ob) {
    ob.print(os);
    return os;
}

std::istream &operator>>(std::istream &is, item &ob) {
    is >> ob.nume;
    return is;
}

item *item::get_clone() const {
    return new item(*this);
}
