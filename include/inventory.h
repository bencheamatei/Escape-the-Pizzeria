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
    inventorySlot **items;
    int cntItems;
    int maxCapacity;
    int firstEmptySlot() const;
    void copy_inventory_from(const inventory &);
    bool is_valid_index(int) const;
public:

    inventory();
    explicit inventory(const int);
    inventory(const inventory &);
    inventory(std::initializer_list<inventorySlot>);
    inventory(std::initializer_list<inventorySlot>,int);
    inventory &operator=(const inventory &);
    ~inventory();
    friend std::ostream &operator<<(std::ostream &, const inventory &);

    int get_size() const;
    int get_capacity() const;
    void resize_inventory(const int );
    inventorySlot get_item_at_index(int) const;
    void insert_item_at_index(const inventorySlot &,int);
    void addItem(const inventorySlot &);
    inventorySlot pop_from_pos(int);
    bool isEmpty() const;
    bool isFull() const;
    void rearrangeItems();
    const inventorySlot& get_at(int) const;
};

#endif //OOP_INVENTORY_H
