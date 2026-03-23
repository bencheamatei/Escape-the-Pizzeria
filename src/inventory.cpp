//
// Created by matei on 3/22/2026.
//

#include <iostream>
#include "inventory.h"
#include <queue>

inventory::inventory() {
    this->maxCapacity = 5;
    this->cntItems = 0;
    this->items = new inventorySlot[maxCapacity];
}

inventory::inventory(const int capacity) {
    this->maxCapacity = capacity;
    this->cntItems = 0;
    this->items = new inventorySlot[maxCapacity];
}

inventory::inventory(const inventory &other) {
    this->maxCapacity = other.maxCapacity;
    this->cntItems = other.cntItems;
    this->items = new inventorySlot[maxCapacity];
    for (int i=0; i<maxCapacity; i++) {
        this->items[i] = other.items[i];
    }
}

inventory &inventory::operator=(const inventory &other) {
    if (this==&other) {
        return *this;
    }

    delete[] this->items;
    this->maxCapacity = other.maxCapacity;
    this->cntItems = other.cntItems;

    this->items = new inventorySlot[maxCapacity];
    for (int i=0; i<maxCapacity; i++) {
        this->items[i] = other.items[i];
    }
    return *this;
}

inventory::~inventory() {
    delete[] items;
}

int inventory::firstEmptySlot() const {
    for (int i=0; i<maxCapacity; i++) {
        if (items[i].isEmpty()) {
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

    std::queue<int> libere;
    for (int i=0; i<maxCapacity; i++) {
        if (this->items[i].isEmpty()) {
            libere.push(i);
        }
        else {
            if (libere.empty()) {
                continue;
            }
            int pos=libere.front();
            libere.pop();

            std::swap(this->items[pos], this->items[i]);
            libere.push(pos);
        }
    }

    while (!libere.empty()) {
        libere.pop();
    }
}

int inventory::get_size() const {
    return this->cntItems;
}

int inventory::get_capacity() const {
    return this->maxCapacity;
}

inventorySlot inventory::get_item_at_index(int index) const {
    if (index < 0 || index >= maxCapacity) {
        throw std::out_of_range("index out of range");
    }
    return this->items[index];
}

void inventory::putItem_at_pos(const inventorySlot &x, int pos) {
    if (pos<0 || pos>=maxCapacity) {
        throw std::out_of_range("index out of range");
    }
    this->items[pos]=x;
}

void inventory::addItem(const inventorySlot &x) {
    int pos=firstEmptySlot();
    if (pos==-1) {
        // e plin inventarul
        return;
    }
    putItem_at_pos(x,pos);
    cntItems++;
}

inventorySlot inventory::pop_from_pos(int pos) {
    if (pos<0 || pos>=maxCapacity) {
        throw std::out_of_range("index out of range");
    }
    inventorySlot aux(this->items[pos]);
    this->items[pos]=inventorySlot();
    return aux;
}

void inventory::set_capacity(const int capacity) {
    this->maxCapacity = capacity;
}

std::ostream &operator<<(std::ostream &os, const inventory &x) {
    os << "Inventar: \n";
    for (int i=0; i<x.get_capacity(); i++) {
        os << x.get_item_at_index(i) << '\n';
    }
    return os;
}

bool inventory::isEmpty() const {
    return this->cntItems==0;
}

bool inventory::isFull() const {
    return this->cntItems==maxCapacity;
}
