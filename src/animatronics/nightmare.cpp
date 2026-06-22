//
// Created by matei on 5/30/2026.
//

#include "../../include/animatronic/nightmare.h"

nightmare::nightmare() : animatronic("Nightmare", 70, 55.f,true, 2.f) {
    max_pizza_hits=99999;
}

void nightmare::on_attack(player &p) {
    p.receiveDmg(damage);
}

bool nightmare::gets_hit() {
    apply_stun(3.0f);
    speed+=8.f;
    return false;
}
