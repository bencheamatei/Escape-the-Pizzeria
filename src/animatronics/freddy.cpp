//
// Created by matei on 5/14/2026.
//

#include "../../include/animatronic/freddy.h"
#include "player.h"

freddy::freddy() : animatronic("Freddy", 40, 50.f, true, 3.0f) {
}

void freddy::on_attack(player &p) {
    p.receiveDmg(damage);
}