//
// Created by matei on 5/13/2026.
//

#include "../include/backpack.h"
#include "../include/player.h"
#include "../include/exceptions.h"

backpack::backpack(int sz) : item("backpack"), sz_upgrade(sz) {}

void backpack::display(std::ostream &os) const {
    os << "Backpack: size=" << sz_upgrade;
}

item *backpack::get_clone() const {
    return new backpack(*this);
}

void backpack::on_use(player &p) {
    if (p.get_inventory().get_size()>=sz_upgrade) {
        throw player_exception("can't upgrade to a smaller backpack");
    }

    p.enlarge_inventory(sz_upgrade);
}
