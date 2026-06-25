//
// Created by matei on 3/22/2026.
//

#include <iostream>
#include <string>
#include "player.h"

#include "exceptions.h"
#include "inventory.h"
#include "../include/items/pizza.h"
#include "../include/items/topping.h"
#include "../include/items/item.h"
#include "../include/items/dough.h"


player::player() : rucsac(5), nr_keys(0) {
    this->hp = 100;
    this->maxHp = 100;
}

void player::add_key() {
    nr_keys++;
}

player::player(const int hp, const int maxHp, const int maxInventoryCapacity) : rucsac(maxInventoryCapacity), nr_keys(0) {
    if (hp <= 0) {
        throw player_exception("initial health must be > 0");
    }
    this->hp = hp;

    if (maxHp <= 0) {
        throw player_exception("max health must be > 0");
    }
    this->maxHp = maxHp;
}

player &player::operator=(const player &other) {
    if (this == &other)
        return *this;
    this->hp = other.hp;
    this->maxHp = other.maxHp;
    this->rucsac = other.rucsac;
    this->effects.clear();
    this->nr_keys=other.nr_keys;
    for (const auto &effect: other.effects) {
        if (effect != nullptr) {
            this->effects.push_back(std::unique_ptr<status_effect>(effect->get_clone()));
        }
    }
    return *this;
}

player::player(const player &other) {
    this->hp = other.hp;
    this->maxHp = other.maxHp;
    this->rucsac = other.rucsac;
    this->effects.clear();
    this->nr_keys=other.nr_keys;
    for (const auto &effect: other.effects) {
        if (effect != nullptr) {
            this->effects.push_back(std::unique_ptr<status_effect>(effect->get_clone()));
        }
    }
}

player::~player() = default;

const inventory &player::get_inventory() const {
    return this->rucsac;
}

std::ostream &operator<<(std::ostream &os, const player &p) {
    os << "Player\n";
    os << "Nume: " << p.nume << "\n";
    os << "Hp: " << p.hp << "\n";
    os << "Max Hp: " << p.maxHp << "\n";
    os << p.rucsac;
    return os;
}

void player::addItem(const inventorySlot &other) {
    for (int i = 0; i < this->rucsac.get_capacity(); i++) {
        if (this->rucsac.get_item_at_index(i).isEmpty()) {
            continue;
        }
        if (this->rucsac.get_item_at_index(i).getItem()->get_nume() == other.getItem()->get_nume()) {
            inventorySlot temp = this->rucsac.pop_from_pos(i);
            temp.changeCntItem(other.getCntItem());
            this->rucsac.addItem(temp);
            arrange();
            return;
        }
    }
    if (this->rucsac.isFull()) {
        return;
    }
    this->rucsac.addItem(other);
    arrange();
}

bool player::isAlive() const {
    return this->hp > 0;
}

int player::getHp() const {
    return this->hp;
}

void player::normalizeHp() {
    if (this->hp > this->maxHp) {
        this->hp = this->maxHp;
    }
    if (this->hp < 0) {
        this->hp = 0;
    }
}

// pentru cand adaug animatronicii

void player::receiveDmg(const int x) {
    if (x <= 0) {
        throw combat_exception("recieved damage must be > 0");
    }
    hp -= x;
    normalizeHp();
}

void player::heal(const int x) {
    if (x <= 0) {
        return;
    }
    hp += x;
    normalizeHp();
}

void player::craftPizza() {
    int dough_idx = -1;

    for (int i = 0; i < this->rucsac.get_capacity(); i++) {
        const auto& slot = this->rucsac.get_item_at_index(i);
        if (slot.isEmpty()) {
            continue;
        }

        if (dough_idx == -1 && slot.is_dough()) {
            dough_idx = i;
        }
    }

    if (count_specific_item<dough>()==0 || count_specific_item<topping>()<2) {
        throw craft_exception("you can't yet craft a pizza");
    }

    bool will_free_slot = false;
    if (this->rucsac.get_item_at_index(dough_idx).getCntItem() == 1) {
        will_free_slot = true;
    } else {
        int needed = 2;
        for (int i = 0; i < this->rucsac.get_capacity(); i++) {
            if (needed == 0) break;
            const auto& slot = this->rucsac.get_item_at_index(i);
            if (!slot.isEmpty() && slot.is_topping()) {
                int take = std::min(slot.getCntItem(), needed);
                if (take == slot.getCntItem()) {
                    will_free_slot = true;
                }
                needed -= take;
            }
        }
    }

    if (this->rucsac.isFull() && !will_free_slot) {
        throw craft_exception("must have an empty slot (or free one up) in order to craft");
    }

    std::vector<topping> available_toppings;
    int toppings_needed = 2;

    for (int i = 0; i < this->rucsac.get_capacity(); i++) {
        if (toppings_needed == 0) {
            break;
        }

        const auto& slot = this->rucsac.get_item_at_index(i);
        if (slot.isEmpty() || !slot.is_topping()) {
            continue;
        }

        int available_in_slot = slot.getCntItem();
        int amount_to_take = std::min(available_in_slot, toppings_needed);
        const auto *u = dynamic_cast<const topping *>(slot.getItem());

        for (int j = 0; j < amount_to_take; j++) {
            available_toppings.push_back(*u);
        }

        this->rucsac.decrease_at_pos(i, amount_to_take);
        toppings_needed -= amount_to_take;
    }

    this->rucsac.decrease_at_pos(dough_idx, 1);

    pizza x(available_toppings);
    rucsac.addItem({x, 1});
    arrange();
    this->rucsac.rearrangeItems();
}

void player::decpos(int pos) {
    if (pos < 0 || pos >= this->rucsac.get_capacity()) {
        throw inventory_exception("slot out of range");
    }
    this->rucsac.decrease_at_pos(pos,1);
}

void player::drop_item(const int pos) {
    if (pos < 0 || pos >= this->rucsac.get_capacity()) {
        throw inventory_exception("slot out of range");
    }
    this->rucsac.pop_from_pos(pos);
}

void player::arrange() {
    this->rucsac.merge_identic_slots();
}

void player::enlarge_inventory(int sz) {
    this->rucsac.resize_inventory(sz);
}

void player::eat_item(int pos) {
    if (pos < 0 || pos >= this->rucsac.get_capacity()) {
        throw inventory_exception("slot out of range");
    }

    if (this->rucsac.get_item_at_index(pos).isEmpty()) {
        throw player_exception("can't consume nothing");
    }

    if (this->rucsac.get_item_at_index(pos).is_key()) {
        return ;
    }

    item *curr = const_cast<item *>(this->rucsac.get_at(pos).getItem());
    if (curr != nullptr) {
        curr->use(*this);
        this->rucsac.decrease_at_pos(pos, 1);
    }
    this->process_effects();
}

void player::add_effect(std::unique_ptr<status_effect> effect) {
    effects.push_back(std::move(effect));
}

void player::process_effects() {
    for (auto &effect: effects) {
        effect->trigger(*this);
    }
    effects.clear();
}

int player::get_nr_keys() const {
    int count = 0;
    for (int i = 0; i < this->rucsac.get_capacity(); i++) {
        const auto& slot = this->rucsac.get_item_at_index(i);
        if (!slot.isEmpty() && slot.is_key()) {
            count += slot.getCntItem();
        }
    }
    return count;
}
