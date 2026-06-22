//
// Created by matei on 5/11/2026.
//

#include "../../include/items/dough.h"
#include "player.h"
#include <memory>

#include "food_poisoning.h"

dough::dough() : item("dough") {
}

void dough::display(std::ostream &os) const {
    os << "Dough";
}

void dough::on_use(player &p) {
    // not really worth eating plain dough
    p.add_effect(std::make_unique<food_poisoning>());
}

item *dough::get_clone() const {
    return new dough(*this);
}