//
// Created by matei on 5/13/2026.
//

#include "../include/food_poisoning.h"
#include "player.h"

void food_poisoning::on_trigger(player &p) {
    p.receiveDmg(7);
}

food_poisoning::food_poisoning() : status_effect("Food poisoning") {}

status_effect *food_poisoning::get_clone() {
    return new food_poisoning(*this);
}
