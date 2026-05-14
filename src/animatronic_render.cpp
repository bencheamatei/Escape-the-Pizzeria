//
// Created by matei on 5/14/2026.
//

#include "../include/animatronic_render.h"
#include "animatronic.h"
#include "game.h"
#include <cmath>

animatronic_render::animatronic_render(animatronic& a, sf::Texture& texture, sf::Vector2f init_pos)
    : data(a), pos(init_pos) {

    sprite.setTexture(texture);
    sprite.setOrigin(32.0f, 32.0f);
    sprite.setPosition(pos);
}

bool animatronic_render::overlap_solid(sf::FloatRect rect, const room& room) const {
    return room.collide(rect);
}

void animatronic_render::resolve_collision(sf::Vector2f delta, const room& room) {
    sf::FloatRect pe_x(pos.x - BOX_W/2.0f + delta.x, pos.y - BOX_H/2.0f, BOX_W, BOX_H);
    if (!overlap_solid(pe_x, room)) {
        pos.x += delta.x;
    }

    sf::FloatRect pe_y(pos.x - BOX_W/2.0f, pos.y - BOX_H/2.0f + delta.y, BOX_W, BOX_H);
    if (!overlap_solid(pe_y, room)) {
        pos.y += delta.y;
    }
}

void animatronic_render::update(float dt, const room& room, sf::Vector2f target_pos) {
    if (!data.is_active()) return;

    sf::Vector2f direction = target_pos - pos;

    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 0.5f) {
        direction.x /= distance;
        direction.y /= distance;

        sf::Vector2f velocity = direction * data.get_speed() * dt;

        resolve_collision(velocity, room);
    }

    sprite.setPosition(pos);
}

void animatronic_render::draw(sf::RenderTarget& window) const {
    if (!data.is_active()) return;

    window.draw(sprite);

    // Draw hitbox in debug mode (Matches your player logic)
    if (game::is_debug_mode()) {
        sf::RectangleShape hitbox({BOX_W, BOX_H});
        hitbox.setOrigin(BOX_W / 2.0f, BOX_H / 2.0f);
        hitbox.setPosition(pos);
        hitbox.setFillColor(sf::Color::Transparent);
        hitbox.setOutlineColor(sf::Color::Magenta); // Magenta to distinguish from player
        hitbox.setOutlineThickness(1.0f);
        window.draw(hitbox);
    }
}

sf::FloatRect animatronic_render::get_bounds() const {
    return sf::FloatRect(pos.x - BOX_W/2.f, pos.y - BOX_H/2.f, BOX_W, BOX_H);
}

sf::Vector2f animatronic_render::get_position() const {
    return pos;
}