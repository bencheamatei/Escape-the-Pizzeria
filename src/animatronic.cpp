//
// Created by matei on 5/13/2026.
//

#include "../include/animatronic.h"
#include <SFML/Graphics.hpp>
#include "player.h"
#include "room.h"

animatronic::animatronic(std::string nume, int dmg, float speed, bool active, float rate) :
    name(std::move(nume)), damage(dmg), speed(speed), active(active),
    attack_rate(rate), attack_cooldown(0.f) {}

bool animatronic::is_active() const {
    return active;
}

float animatronic::get_speed() const {
    return speed;
}

bool animatronic::can_attack() const {
    return attack_cooldown<=0.f;
}

void animatronic::reset_cooldown() {
    attack_cooldown=attack_rate;
}

void animatronic::tick_timer(float dt) {
    if (attack_cooldown>0) {
        attack_cooldown-=dt;
    }
}
