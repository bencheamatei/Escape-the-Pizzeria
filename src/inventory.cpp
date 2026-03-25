//
// Created by matei on 3/22/2026.
//

#include <iostream>
#include "inventory.h"
#include <queue>

inventory::inventory() {
    this->maxCapacity = 5;
    this->cntItems = 0;
    this->items = new inventorySlot *[maxCapacity];
    for (int i=0; i<maxCapacity; i++) {
        this->items[i] = nullptr;
    }
}

inventory::inventory(const int capacity) {
    this->maxCapacity = capacity;
    this->cntItems = 0;
    this->items = new inventorySlot *[maxCapacity];
    for (int i=0; i<maxCapacity; i++) {
        this->items[i] = nullptr;
    }
}

void inventory::copy_inventory_from(const inventory &other) {
    this->maxCapacity = other.maxCapacity;
    this->cntItems = other.cntItems;
    this->items = new inventorySlot *[maxCapacity];
    for (int i=0; i<maxCapacity; i++) {
        if (other.items[i]!=nullptr) {
            this->items[i] = new inventorySlot(*other.items[i]);
        }
        else {
            this->items[i] = nullptr;
        }
    }
}

inventory::inventory(const inventory &other) {
    copy_inventory_from(other);
}

inventory &inventory::operator=(const inventory &other) {
    if (this==&other) {
        return *this;
    }

    for (int i=0; i<maxCapacity; i++) {
        delete this->items[i];
    }
    delete[] this->items;
    copy_inventory_from(other);
    return *this;
}

inventory::inventory(std::initializer_list<inventorySlot> list) {
    this->maxCapacity = (int)list.size();
    this->cntItems = 0;
    this->items = new inventorySlot *[maxCapacity];
    for (int i=0; i<maxCapacity; i++) {
        this->items[i] = nullptr;
    }
    for (const auto &it:list) {
        this->addItem(it);
    }
}

inventory::inventory(std::initializer_list<inventorySlot> list,int capacity) {
    if (capacity<(int)list.size()) {
        throw std::runtime_error("capacity too small");
    }
    this->maxCapacity = capacity;
    this->cntItems = 0;
    this->items = new inventorySlot *[maxCapacity];
    for (int i=0; i<maxCapacity; i++) {
        this->items[i] = nullptr;
    }
    for (const auto &it:list) {
        this->addItem(it);
    }
}

inventory::~inventory() {
    for (int i=0; i<maxCapacity; i++) {
        delete this->items[i];
    }
    delete[] this->items;
}

int inventory::firstEmptySlot() const {
    for (int i=0; i<maxCapacity; i++) {
        if (this->items[i]==nullptr) {
            return i;
        }
    }
    return -1;
}

void inventory::insert_item_at_index(const inventorySlot &other, int pos) {
    if (!is_valid_index(pos)) {
        return;
    }
    delete this->items[pos];
    this->items[pos]=new inventorySlot(other);
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
    for (int i=0; i<maxCapacity; i++) {
        if (this->items[i]==nullptr) {
            libere.push(i);
        }
        else {
            if (libere.empty()) {
                continue;
            }
            int pos=libere.front();
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
    return this->cntItems;
}

int inventory::get_capacity() const {
    return this->maxCapacity;
}

inventorySlot inventory::get_item_at_index(int index) const {
    if (!is_valid_index(index)) {
        throw std::out_of_range("index out of range");
    }

    if (this->items[index]==nullptr) {
        return inventorySlot();
    }
    return *(this->items[index]);
}

void inventory::addItem(const inventorySlot &x) {
    if (isFull()) {
        return;
    }
    int pos=firstEmptySlot();
    this->items[pos]=new inventorySlot(x);
    cntItems++;
}

inventorySlot inventory::pop_from_pos(int pos) {
    if (!is_valid_index(pos)) {
        throw std::out_of_range("index out of range");
    }

    if (this->items[pos]==nullptr) {
        return inventorySlot();
    }

    inventorySlot aux=*(this->items[pos]);
    delete this->items[pos];
    this->items[pos]=nullptr;
    cntItems--;
    return aux;
}

void inventory::resize_inventory(const int capacity) {
    if (capacity<this->maxCapacity) {
        return;
    }

    inventorySlot **aux=new inventorySlot*[capacity];
    for (int i=0; i<this->maxCapacity; i++) {
        aux[i]=this->items[i];
    }
    for (int i=this->maxCapacity; i<capacity; i++) {
        aux[i]=nullptr;
    }
    delete[] this->items;
    this->items=aux;
    this->maxCapacity=capacity;
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

bool inventory::is_valid_index(int idx) const {
    if (idx<0 || idx>=maxCapacity) {
        return false;
    }
    return true;
}

const inventorySlot &inventory::get_at(int pos) const {
    if (!is_valid_index(pos) || this->items[pos]==nullptr) {
        throw std::runtime_error("index out of range or null item");
    }
    return *(this->items[pos]);
}

void inventory::decrease_at_pos(int pos, int cnt) {
    if (!is_valid_index(pos) || this->items[pos]==nullptr) {
        throw std::runtime_error("index out of range or null item");
    }

    this->items[pos]->changeCntItem(-cnt);
    if (this->items[pos]->getCntItem()==0) {
        delete this->items[pos];
        this->items[pos]=nullptr;
        cntItems--;
    }
}

void inventory::merge_identic_slots() {
    for (int i=0; i<this->maxCapacity; i++) {
        if (this->items[i]==nullptr) {
            continue;
        }

        for (int j=i+1; j<this->maxCapacity; j++) {
            if (this->items[j]==nullptr) {
                continue;
            }
            if (this->items[j]->getItem()->get_nume()==this->items[i]->getItem()->get_nume()) {
                this->items[i]->changeCntItem(this->items[j]->getCntItem());
                delete this->items[j];
                this->items[j]=nullptr;
                this->cntItems--;
            }
        }
    }
    rearrangeItems();
}
