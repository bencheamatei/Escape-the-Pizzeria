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

player::player() : rucsac(5) {
    this->hp = 100;
    this->maxHp = 100;
}

player::player(const int hp, const int maxHp, const int maxInventoryCapacity) : rucsac(maxInventoryCapacity) {
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
    if (this->rucsac.isFull()) {
        throw craft_exception("must have an empty slot in order to craft");
    }

    int dough_idx = -1;
    for (int i = 0; i < this->rucsac.get_capacity(); i++) {
        if (this->rucsac.get_item_at_index(i).isEmpty()) {
            continue;
        }

        if (this->rucsac.get_item_at_index(i).is_dough()) {
            // if (dynamic_cast<const dough*>(this->rucsac.get_item_at_index(i).getItem())!=nullptr) {
            dough_idx = i;
            break;
        }
    }

    if (dough_idx == -1) {
        throw craft_exception("must have at least one piece of dough to craft pizza");
    }

    std::vector<topping> available_toppings;
    for (int i = 0; i < this->rucsac.get_capacity(); i++) {
        if (available_toppings.size() == 3) {
            break;
        }

        if (i == dough_idx) {
            continue;
        }

        if (this->rucsac.get_item_at_index(i).isEmpty()) {
            continue;
        }

        if (this->rucsac.get_item_at_index(i).is_topping()) {
            const auto *u = dynamic_cast<const topping *>(this->rucsac.get_at(i).getItem());
            available_toppings.push_back(*u);
            this->rucsac.decrease_at_pos(i, 1);
        }
    }
    this->rucsac.decrease_at_pos(dough_idx, 1);
    pizza x(available_toppings);
    rucsac.addItem({x, 1});
    this->rucsac.rearrangeItems();
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