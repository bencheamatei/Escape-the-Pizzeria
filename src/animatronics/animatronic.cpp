//
// Created by matei on 5/13/2026.
//

#include "../../include/animatronic/animatronic.h"
#include <SFML/Graphics.hpp>
#include "player.h"
#include "room.h"

animatronic::animatronic(std::string nume, int dmg, float speed, bool active, float rate) : name(std::move(nume)),
    damage(dmg), speed(speed), active(active),
    attack_cooldown(0.0f), attack_rate(rate) {
}

bool animatronic::is_active() const {
    return active;
}

float animatronic::get_speed() const {
    return speed;
}

bool animatronic::can_attack() const {
    return attack_cooldown <= 0.f;
}

void animatronic::reset_cooldown() {
    attack_cooldown = attack_rate;
}

void animatronic::tick_timer(float dt) {
    if (attack_cooldown > 0) {
        attack_cooldown -= dt;
    }

    if (stun_timer>0) {
        stun_timer-=dt;
    }
}

bool animatronic::gets_hit() {
    pizza_hits++;
    if (pizza_hits>=max_pizza_hits) {
        active=false;
        return true;
    }
    return false;
}

bool animatronic::is_stunned() const {
    return stun_timer>0.f;
}

void animatronic::apply_stun(float dt) {
    stun_timer=dt;
}
