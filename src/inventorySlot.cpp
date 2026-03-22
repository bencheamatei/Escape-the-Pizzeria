//
// Created by matei on 3/22/2026.
//

#include "inventorySlot.h"
#include <iostream>
#include <string>
#include <climits>

inventorySlot::inventorySlot() {
    cntItem=0;
}

inventorySlot::inventorySlot(const item &x, int cnt) {
    this->Item=x;
    this->cntItem=cnt;
}

inventorySlot::inventorySlot(const inventorySlot &other) {
    this->Item=other.Item;
    this->cntItem=other.cntItem;
}

inventorySlot &inventorySlot::operator=(const inventorySlot &other) =default;

inventorySlot::~inventorySlot() = default;

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
    return cntItem==0;
}

std::ostream &operator<<(std::ostream &os, const inventorySlot &x) {
    os << "Item:" << x.Item.get_nume() << " ";
    os << "CntItem:" << x.cntItem;
    return os;
}
