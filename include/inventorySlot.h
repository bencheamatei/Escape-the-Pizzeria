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

    void clear();

public:
    inventorySlot();
    inventorySlot(const item &, int);
    inventorySlot(const inventorySlot &);
    inventorySlot &operator=(inventorySlot);
    ~inventorySlot();
    friend std::ostream &operator<<(std::ostream &, const inventorySlot &);
    [[nodiscard]] bool isEmpty() const;
    void changeCntItem(int cnt);
    [[nodiscard]] const item* getItem() const;
    [[nodiscard]] int getCntItem() const;

    [[nodiscard]] bool is_pizza() const;
    [[nodiscard]] bool is_topping() const;
    [[nodiscard]] bool is_dough() const;
    [[nodiscard]] bool is_backpack() const;
    [[nodiscard]] bool is_soda() const;

    friend void swap(inventorySlot &x, inventorySlot &y) noexcept;
};

#endif //OOP_INVENTORYSLOT_H