//
// Created by matei on 3/22/2026.
//

#ifndef OOP_INVENTORY_H
#define OOP_INVENTORY_H

#include <iostream>
#include <string>
#include "items/item.h"
#include <memory>
#include <vector>
#include "inventorySlot.h"

class inventory {
private:
    std::vector<std::unique_ptr<inventorySlot> > items;
    int max_capacity;
    [[nodiscard]] int firstEmptySlot() const;
    void copy_inventory_from(const inventory &);
    [[nodiscard]] bool is_valid_index(int) const;
public:

    inventory();
    explicit inventory(int);
    inventory(const inventory &);
    inventory(std::initializer_list<inventorySlot>);
    inventory(std::initializer_list<inventorySlot>,int);
    inventory &operator=(inventory);
    ~inventory();
    friend std::ostream &operator<<(std::ostream &, const inventory &);

    [[nodiscard]] int get_size() const;
    [[nodiscard]] int get_capacity() const;
    void resize_inventory(int);
    [[nodiscard]] inventorySlot get_item_at_index(int) const;
    void addItem(const inventorySlot &);
    inventorySlot pop_from_pos(int);
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] bool isFull() const;
    void rearrangeItems();
    [[nodiscard]] const inventorySlot& get_at(int) const;
    void decrease_at_pos(int,int);
    void merge_identic_slots();
    friend void swap(inventory&,inventory&) noexcept;
};

#endif //OOP_INVENTORY_H
