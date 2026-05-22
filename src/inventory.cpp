//
// Created by matei on 3/22/2026.
//

#include <iostream>
#include "inventory.h"
#include <queue>
#include "exceptions.h"

inventory::inventory() : max_capacity(5) {
    items.resize(5);
}

inventory::inventory(int capacity) : max_capacity(capacity) {
    items.resize(capacity);
}

void inventory::copy_inventory_from(const inventory &other) {
    this->max_capacity = other.max_capacity;
    items.clear();
    items.resize(this->max_capacity);
    for (int i = 0; i < max_capacity; i++) {
        if (other.items[i]) {
            this->items[i] = std::make_unique<inventorySlot>(*other.items[i]);
        }
    }
}

inventory::inventory(const inventory &other) {
    copy_inventory_from(other);
}

inventory &inventory::operator=(inventory other) {
    swap(*this, other);
    return *this;
}

inventory::inventory(std::initializer_list<inventorySlot> list) {
    this->max_capacity = (int) list.size();
    items.resize((int) list.size());
    for (const auto &it: list) {
        addItem(it);
    }
}

inventory::inventory(std::initializer_list<inventorySlot> list, int capacity) {
    if (capacity < (int) list.size()) {
        throw inventory_exception("capacity too small");
    }

    this->max_capacity = capacity;
    for (const auto &it: list) {
        addItem(it);
    }
}

inventory::~inventory() = default;

int inventory::firstEmptySlot() const {
    for (int i = 0; i < max_capacity; i++) {
        if (!items[i]) {
            return i;
        }
    }
    return -1;
}

void inventory::rearrangeItems() {
    // sa zicem ca elementele din inventarul meu sunt (le scriu doar countul)
    // 1 2 0 0 3
    // eu vreau sa transform asta in 1 2 3 0 0
    // adica le aranjez frumos

    if (isFull() || isEmpty()) {
        return;
    }

    std::queue<int> libere;
    for (int i = 0; i < max_capacity; i++) {
        if (this->items[i] == nullptr) {
            libere.push(i);
        } else {
            if (libere.empty()) {
                continue;
            }
            int pos = libere.front();
            libere.pop();
            std::swap(this->items[pos], this->items[i]);
            libere.push(i);
        }
    }

    while (!libere.empty()) {
        libere.pop();
    }
}

int inventory::get_size() const {
    int count = 0;
    for (int i = 0; i < max_capacity; i++) {
        if (items[i]) {
            count++;
        }
    }
    return count;
}

int inventory::get_capacity() const {
    return this->max_capacity;
}

inventorySlot inventory::get_item_at_index(int index) const {
    if (!is_valid_index(index)) {
        throw inventory_exception("slot out of range");
    }

    if (!items[index]) {
        return inventorySlot();
    }
    return *(this->items[index]);
}

void inventory::addItem(const inventorySlot &x) {
    if (isFull()) {
        throw inventory_exception("inventory is full");
    }
    int pos = firstEmptySlot();
    items[pos] = std::make_unique<inventorySlot>(x);
}

inventorySlot inventory::pop_from_pos(int pos) {
    if (!is_valid_index(pos)) {
        throw inventory_exception("slot out of range");
    }

    if (!items[pos]) {
        return inventorySlot();
    }

    inventorySlot aux = *(this->items[pos]);
    items[pos].reset();
    return aux;
}

// de folosit pentru atunci cand implementez itemul de tip rucsac
// se va spawna doar unul pe harta si o sa mareasca inventarul de la 5 la 8

void inventory::resize_inventory(const int capacity) {
    if (capacity < max_capacity) {
        throw inventory_exception("can't resize to a smaller capacity");
    }
    items.resize(capacity);
    this->max_capacity = capacity;
}

std::ostream &operator<<(std::ostream &os, const inventory &x) {
    os << "Inventar: \n";
    for (int i = 0; i < x.max_capacity; i++) {
        os << x.get_item_at_index(i) << '\n';
    }
    return os;
}

bool inventory::isEmpty() const {
    return get_size() == 0;
}

bool inventory::isFull() const {
    return get_size() == max_capacity;
}

bool inventory::is_valid_index(int idx) const {
    if (idx < 0 || idx >= max_capacity) {
        return false;
    }
    return true;
}

const inventorySlot &inventory::get_at(int pos) const {
    if (!is_valid_index(pos) || this->items[pos] == nullptr) {
        throw inventory_exception("slot invalid/gol");
    }
    return *(this->items[pos]);
}

void inventory::decrease_at_pos(int pos, int cnt) {
    if (!is_valid_index(pos) || this->items[pos] == nullptr) {
        throw inventory_exception("slot invalid/gol");
    }

    this->items[pos]->changeCntItem(-cnt);
    if (this->items[pos]->getCntItem() <= 0) {
        items[pos].reset();
    }
}

void inventory::merge_identic_slots() {
    for (int i = 0; i < max_capacity; i++) {
        if (this->items[i] == nullptr) {
            continue;
        }

        for (int j = i + 1; j < max_capacity; j++) {
            if (this->items[j] == nullptr) {
                continue;
            }
            if (this->items[j]->getItem()->get_nume() == this->items[i]->getItem()->get_nume()) {
                this->items[i]->changeCntItem(this->items[j]->getCntItem());
                items[j].reset();
            }
        }
    }
    rearrangeItems();
}

void swap(inventory &x, inventory &y) noexcept {
    std::swap(x.items, y.items);
    std::swap(x.max_capacity, y.max_capacity);
}