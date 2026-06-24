//
// Created by matei on 3/22/2026.
//

#include "inventorySlot.h"
#include "../include/items/pizza.h"
#include "../include/items/topping.h"
#include "../include/items/dough.h"
#include "../include/items/soda.h"
#include "../include/items/key.h"
#include <iostream>

#include "../include/items/backpack.h"
#include "exceptions.h"

inventorySlot::inventorySlot() : Item(nullptr), cntItem(0) {
}

inventorySlot::inventorySlot(const item &x, int cnt) {
    if (cnt <= 0) {
        throw inventory_exception("the count of an item must be > 0");
    }
    this->cntItem = cnt;
    this->Item = x.get_clone();
}

inventorySlot::inventorySlot(const inventorySlot &other) {
    this->cntItem = other.cntItem;
    if (other.Item == nullptr) {
        this->Item = nullptr;
    } else {
        this->Item = other.Item->get_clone();
    }
}

void swap(inventorySlot &x, inventorySlot &y) noexcept {
    std::swap(x.cntItem, y.cntItem);
    std::swap(x.Item, y.Item);
}

inventorySlot &inventorySlot::operator=(inventorySlot other) {
    swap(*this, other);
    return *this;
}

inventorySlot::~inventorySlot() {
    delete this->Item;
}

void inventorySlot::changeCntItem(const int cnt) {
    if (cnt == 0) {
        return;
    }

    int new_count = this->cntItem + cnt;
    if (new_count < 0) {
        throw inventory_exception("can't pop more items than you have");
    }

    if (new_count == 0) {
        this->clear();
        return;
    }
    this->cntItem = new_count;
}

bool inventorySlot::isEmpty() const {
    return this->cntItem == 0 || this->Item == nullptr;
}

std::ostream &operator<<(std::ostream &os, const inventorySlot &x) {
    if (x.Item == nullptr) {
        os << "Slot: {Empty}";
    } else {
        os << "Slot: {" << *x.Item << ", " << x.cntItem << "}";
    }
    return os;
}

int inventorySlot::getCntItem() const {
    return this->cntItem;
}

const item *inventorySlot::getItem() const {
    return this->Item;
}

bool inventorySlot::is_pizza() const {
    return dynamic_cast<pizza *>(Item) != nullptr;
}

bool inventorySlot::is_topping() const {
    return dynamic_cast<topping *>(Item) != nullptr;
}

bool inventorySlot::is_dough() const {
    return dynamic_cast<dough *>(Item) != nullptr;
}

bool inventorySlot::is_backpack() const {
    return dynamic_cast<backpack *>(Item) != nullptr;
}

void inventorySlot::clear() {
    delete this->Item;
    this->Item = nullptr;
    this->cntItem = 0;
}

bool inventorySlot::is_soda() const {
    return dynamic_cast<soda *>(Item) != nullptr;
}

bool inventorySlot::is_key() const {
    return dynamic_cast<key *>(Item) != nullptr;
}