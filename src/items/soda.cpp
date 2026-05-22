//
// Created by matei on 5/13/2026.
//

#include "../../include/items/soda.h"
#include "player.h"

soda::soda() : item("soda") {
}

item *soda::get_clone() const {
    return new soda(*this);
}

void soda::display(std::ostream &os) const {
    os << "Soda";
}

void soda::on_use(player &p) {
    p.heal(20);
}