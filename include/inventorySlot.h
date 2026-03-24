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
    inventorySlot(const item &, int);
    inventorySlot(const inventorySlot &);
    inventorySlot &operator=(const inventorySlot &);
    ~inventorySlot();
    friend std::ostream &operator<<(std::ostream &, const inventorySlot &);
    void setItem(const item &x, int cnt);
    [[nodiscard]] bool isEmpty() const;
    void changeCntItem(int cnt);
    [[nodiscard]] const item* getItem() const;
    [[nodiscard]] int getCntItem() const;
};

#endif //OOP_INVENTORYSLOT_H