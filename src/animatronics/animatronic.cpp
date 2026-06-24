//
// Created by matei on 5/13/2026.
//

#include "../../include/animatronic/animatronic.h"
#include <SFML/Graphics.hpp>
#include "player.h"
#include "room.h"
#include <cmath>

#include "animatronic/animatronic_ai.h"

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

void animatronic::set_position(sf::Vector2f new_pos) {
    pos=new_pos;
}

sf::Vector2f animatronic::get_position() const {
    return pos;
}

sf::FloatRect animatronic::get_bounds() const {
    return {pos.x - box_w / 2.f, pos.y - box_h / 2.f, box_w, box_h};
}

const std::vector<sf::Vector2i> &animatronic::get_path() const {
    return path;
}

void animatronic::update(float dt, const room &room, sf::Vector2f target_pos) {
    if (!is_active()) return;
    if (is_stunned()) return;

    path_timer -= dt;
    if (path_timer <= 0.f) {
        recalc_path(room, target_pos);
        path_timer = path_refresh;
    }

    if (!follow_path(dt, room)) {
        sf::Vector2f dir = target_pos - get_position();
        float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);

        if (dist > 0.5f) {
            dir.x /= dist;
            dir.y /= dist;
            resolve_collision(dir * get_speed() * dt, room);
        }
    }
}

bool animatronic::overlap_solid(sf::FloatRect rect, const room &room) const {
    return room.collide(rect);
}

void animatronic::resolve_collision(sf::Vector2f delta, const room &room) {
    sf::FloatRect bounds = get_bounds();
    float bw = bounds.width;
    float bh = bounds.height;

    sf::FloatRect pe_x(pos.x - bw / 2.0f + delta.x, pos.y - bh / 2.0f, bw, bh);
    if (!overlap_solid(pe_x, room)) pos.x += delta.x;

    sf::FloatRect pe_y(pos.x - bw / 2.0f, pos.y - bh / 2.0f + delta.y, bw, bh);
    if (!overlap_solid(pe_y, room)) pos.y += delta.y;
}

bool animatronic::follow_path(float dt, const room &r) {
    if (path.empty()) return false;

    sf::Vector2f waypoint{
        path.front().x * 64.f + 64.f / 2.f,
        path.front().y * 64.f + 64.f / 2.f
};

    sf::Vector2f dir = waypoint - get_position();
    float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);

    if (dist < 4.f) {
        path.erase(path.begin());
        return true;
    }

    dir.x /= dist;
    dir.y /= dist;

    resolve_collision(dir * get_speed() * dt, r);
    return true;
}

void animatronic::recalc_path(const room &r, sf::Vector2f target_world) {
    sf::Vector2i start{(int) (get_position().x / 64.f), (int) (get_position().y / 64.f)};
    sf::Vector2i goal{
        (int) (target_world.x / 64.f),
        (int) (target_world.y / 64.f)
};
    path = animatronic_ai::find(r, start, goal);
}
