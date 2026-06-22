//
// Created by matei on 5/23/2026.
//

#include "../../include/animatronic/foxy.h"

foxy::foxy() : animatronic("Foxy", 20, 70.f, true, 1.0f) {
    max_pizza_hits=2;
}

void foxy::on_attack(player &p) {
    p.receiveDmg(damage);
}