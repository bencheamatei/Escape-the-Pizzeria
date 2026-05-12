//
// Created by matei on 5/11/2026.
//

#include "dough.h"
#include "player.h"

dough::dough() : item("dough") {}

void dough::display(std::ostream &os) const {
    os << "Dough";
}

void dough::on_use(player &p) {
    p.heal(1); // not really worth eating plain dough
}

item *dough::get_clone() const {
    return new dough(*this);
}