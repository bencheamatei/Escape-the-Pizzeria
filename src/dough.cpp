//
// Created by matei on 5/11/2026.
//

#include "dough.h"
#include "player.h"

dough::dough() = default;

void dough::display(std::ostream &os) const {
    os << "Dough";
}

void dough::apply_effect(player &p) {
    p.heal(1); // not really worth eating plain dough
}

item *dough::get_clone() const {
    return new dough(*this);
}