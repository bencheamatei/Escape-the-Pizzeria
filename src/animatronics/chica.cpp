//
// Created by matei on 5/30/2026.
//

#include "../../include/animatronic/chica.h"

chica::chica() : animatronic("Chica", 40, 60.f, true, 1.3f) {
    max_pizza_hits=1;
}

void chica::on_attack(player &p) {
    p.receiveDmg(damage);
}
