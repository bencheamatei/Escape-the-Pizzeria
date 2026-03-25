//
// Created by matei on 3/22/2026.
//

#include <iostream>
#include <string>
#include "player.h"
#include "inventory.h"
#include "pizza.h"
#include "topping.h"
#include "item.h"

player::player() : rucsac(5) {
    this->hp=100;
    this->maxHp=100;
}

player::player(const int hp, const int maxHp, const int maxInventoryCapacity) : rucsac(maxInventoryCapacity){
    this->hp=hp;
    this->maxHp=maxHp;
}

player &player::operator=(const player &other) {
    if (this==&other)
        return *this;
    this->hp=other.hp;
    this->maxHp=other.maxHp;
    this->rucsac=other.rucsac;
    return *this;
}

player::player(const player &other) {
    this->hp=other.hp;
    this->maxHp=other.maxHp;
    this->rucsac=other.rucsac;
}

player::~player() = default;

const inventory& player::get_inventory() const {
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
    return this->hp>0;
}

int player::getHp() const {
    return this->hp;
}

void player::normalizeHp() {
    if (this->hp>this->maxHp) {
        this->hp=this->maxHp;
    }
    if (this->hp<0) {
        this->hp=0;
    }
}

void player::receiveDmg(const int x) {
    if (x<=0) {
        return;
    }
    hp-=x;
    normalizeHp();
}

void player::heal(const int x) {
    if (x<=0) {
        return;
    }
    hp+=x;
    normalizeHp();
}

void player::craftPizza() {
    if (this->rucsac.isFull()) {
        std::cout << "Inventory is full, can't craft pizza\n";
        return;
    }

    int dough_idx=-1;
    for (int i=0; i<this->rucsac.get_capacity(); i++) {
        if (this->rucsac.get_item_at_index(i).isEmpty()) {
            continue;
        }
        if (this->rucsac.get_at(i).getItem()->get_nume()=="dough") {
            dough_idx=i;
            break;
        }
    }

    if (dough_idx==-1) {
        std::cout << "You need dough to craft pizza\n";
        return;
    }

    std::vector<topping> available_toppings;
    for (int i=0; i<this->rucsac.get_capacity(); i++) {
        if (available_toppings.size()==3) {
            break;
        }

        if (i==dough_idx) {
            continue;
        }

        if (this->rucsac.get_item_at_index(i).isEmpty()) {
            continue;
        }

        const auto *u=dynamic_cast<const topping*>(this->rucsac.get_at(i).getItem());
        if (u!=nullptr) {
            available_toppings.push_back(*u);
            this->rucsac.decrease_at_pos(i,1);
        }
    }
    this->rucsac.decrease_at_pos(dough_idx,1);
    pizza x(available_toppings);
    std::cout << "Dmg total al pizzei craftate este " << x.get_dmg() << "\n";
    std::cout << x << "\n";
    rucsac.addItem({x,1});
}

void player::drop_item(const int pos) {
    if (pos<0 || pos>=this->rucsac.get_capacity()) {
        throw std::out_of_range("Index out of range");
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
    if (pos<0 || pos>=this->rucsac.get_capacity()) {
        throw std::out_of_range("Index out of range");
    }

    if (this->rucsac.get_item_at_index(pos).isEmpty()) {
        return;
    }

    const auto curr=this->rucsac.get_at(pos).getItem();
    const auto aux=dynamic_cast<const pizza*>(curr);
    if (aux!=nullptr) {
        this->heal(aux->get_dmg());
        this->rucsac.decrease_at_pos(pos,1);
    }
}
