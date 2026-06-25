//
// Created by matei on 6/24/2026.
//

#include "../../include/items/key.h"

#include "player.h"

key::key() : item("key") {};

void key::on_use(player &p) {
    p.add_key();
}

item *key::get_clone() const {
    return new key(*this);
}
