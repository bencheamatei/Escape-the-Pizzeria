//
// Created by matei on 3/22/2026.
//

#include "inventorySlot.h"
#include <iostream>
#include <climits>

inventorySlot::inventorySlot() : Item(nullptr), cntItem(0) {}

inventorySlot::inventorySlot(const item &x, int cnt) : cntItem(cnt) {
    this->Item=x.get_clone();
}

inventorySlot::inventorySlot(const inventorySlot &other) {
    this->cntItem=other.cntItem;
    if (other.Item==nullptr) {
        this->Item=nullptr;
    }
    else {
        this->Item=other.Item->get_clone();
    }
}

void inventorySlot::setItem(const item &x, int cnt) {
    delete this->Item;
    this->Item=x.get_clone();
    this->cntItem=cnt;
}

inventorySlot &inventorySlot::operator=(const inventorySlot &other) {
    if (this==&other)
        return *this;

    delete this->Item;
    this->cntItem=other.cntItem;
    if (other.Item==nullptr) {
        this->Item=nullptr;
    }
    else {
        this->Item=other.Item->get_clone();
    }
    return *this;
}

inventorySlot::~inventorySlot() {
    delete this->Item;
}

void inventorySlot::changeCntItem(const int cnt) {
    if (cnt==0)
        return ;
    if (cnt<0) {
        if (-cnt>cntItem || 1LL*cnt+1LL*cntItem<INT_MIN)
            return ;
        cntItem+=cnt;
    }
    else {
        if (1LL*cnt+1LL*cntItem>INT_MAX)
            return ;
        cntItem+=cnt;
    }
}

bool inventorySlot::isEmpty() const{
    return this->cntItem==0 || this->Item==nullptr;
}

std::ostream &operator<<(std::ostream &os, const inventorySlot &x) {
    os << "Slot de inventar\n";
    os << "Item: ";
    if (x.Item==nullptr) {
        os << "null";
    }
    else {
        os << *x.Item;
    }
    os << " | CntItem: " << x.cntItem << '\n';
    return os;
}

int inventorySlot::getCntItem() const {
    return this->cntItem;
}

const item* inventorySlot::getItem() const {
    return this->Item;
}
