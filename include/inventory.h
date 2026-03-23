//
// Created by matei on 3/22/2026.
//

#ifndef OOP_INVENTORY_H
#define OOP_INVENTORY_H

#include <iostream>
#include <string>
#include "item.h"
#include "inventorySlot.h"

class inventory {
private:
    inventorySlot *items;
    int cntItems;
    int maxCapacity;
    int firstEmptySlot() const;
    void putItem_at_pos(const inventorySlot &,int);
public:

    inventory();
    explicit inventory(const int);
    inventory(const inventory &);
    inventory &operator=(const inventory &);
    ~inventory();
    friend std::ostream &operator<<(std::ostream &os, const inventory &);

    int get_size() const;
    int get_capacity() const;
    void set_capacity(const int capacity);
    inventorySlot get_item_at_index(int index) const;
    void addItem(const inventorySlot &);
    inventorySlot pop_from_pos(int pos);
    bool isEmpty() const;
    bool isFull() const;
    void rearrangeItems();
};

#endif //OOP_INVENTORY_H
