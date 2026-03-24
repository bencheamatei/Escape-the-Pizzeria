//
// Created by matei on 3/22/2026.
//

#ifndef OOP_INVENTORYSLOT_H
#define OOP_INVENTORYSLOT_H

#include <iostream>
#include "item.h"

class inventorySlot {
private:
    item *Item;
    int cntItem;
public:
    inventorySlot();
    inventorySlot(const item &x, int cnt);
    inventorySlot(const inventorySlot &);
    inventorySlot &operator=(const inventorySlot &);
    ~inventorySlot();
    friend std::ostream &operator<<(std::ostream &os, const inventorySlot &x);
    void setItem(const item &x, int cnt);
    bool isEmpty() const;
    void changeCntItem(const int cnt);
    const item* getItem() const;
    int getCntItem() const;
};

#endif //OOP_INVENTORYSLOT_H