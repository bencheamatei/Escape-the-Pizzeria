//
// Created by matei on 3/22/2026.
//

#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H
#include <string>
#include <vector>
#include <memory>
#include "inventory.h"
#include "status_effect.h"

class player {
private:
    const std::string nume="Billy";
    int hp;
    int maxHp;
    inventory rucsac;
    std::vector<std::unique_ptr<status_effect> > effects;
    void normalizeHp();

    int nr_keys;

public:
    player();
    player(int , int , int );
    ~player();
    player(const player &);
    player &operator=(const player &);
    friend std::ostream &operator<<(std::ostream &, const player &);
    [[nodiscard]] const inventory& get_inventory() const;
    void addItem(const inventorySlot &);
    [[nodiscard]] bool isAlive() const;
    [[nodiscard]] int getHp() const;
    void receiveDmg(int x);
    void heal(int x);
    void craftPizza();
    void drop_item(int);
    void arrange();
    void enlarge_inventory(int);
    void eat_item(int);
    void add_effect(std::unique_ptr<status_effect> effect);
    void process_effects();
    void add_key();
    [[nodiscard]] int get_nr_keys() const;

    void decpos(int pos);

    template <typename T>
    [[nodiscard]] int count_specific_item() const {
        int count = 0;
        for (int i = 0; i < this->rucsac.get_capacity(); i++) {
            const auto& slot = this->rucsac.get_item_at_index(i);
            if (!slot.isEmpty()) {
                if (dynamic_cast<const T*>(slot.getItem()) != nullptr) {
                    count += slot.getCntItem();
                }
            }
        }
        return count;
    }
};

#endif //OOP_PLAYER_H