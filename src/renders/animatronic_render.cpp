//
// Created by matei on 5/14/2026.
//

#include "../../include/renders/animatronic_render.h"
#include "../../include/animatronic/animatronic.h"
#include "game.h"
#include <cmath>
#include "../../include/animatronic/animatronic_ai.h"

animatronic_render::animatronic_render(animatronic &a, sf::Texture &texture, sf::Vector2f init_pos)
    : data(a), pos(init_pos) {
    sprite.setTexture(texture);
    sprite.setOrigin(32.0f, 32.0f);
    sprite.setPosition(pos);
}

bool animatronic_render::overlap_solid(sf::FloatRect rect, const room &room) const {
    return room.collide(rect);
}

void animatronic_render::resolve_collision(sf::Vector2f delta, const room &room) {
    sf::FloatRect pe_x(pos.x - BOX_W / 2.0f + delta.x, pos.y - BOX_H / 2.0f, BOX_W, BOX_H);
    if (!overlap_solid(pe_x, room)) {
        pos.x += delta.x;
    }

    sf::FloatRect pe_y(pos.x - BOX_W / 2.0f, pos.y - BOX_H / 2.0f + delta.y, BOX_W, BOX_H);
    if (!overlap_solid(pe_y, room)) {
        pos.y += delta.y;
    }
}

void animatronic_render::update(float dt, const room &room, sf::Vector2f target_pos) {
    if (!data.is_active()) return;
    if (data.is_stunned()) return;

    path_timer -= dt;
    if (path_timer <= 0.f) {
        recalc_path(room, target_pos);
        path_timer = path_refresh;
    }

    if (!follow_path(dt, room)) {
        sf::Vector2f dir = target_pos - pos;
        float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);

        if (dist > 0.5f) {
            dir.x /= dist;
            dir.y /= dist;
            resolve_collision(dir * data.get_speed() * dt, room);
        }
    }
    sprite.setPosition(pos);
}

void animatronic_render::draw(sf::RenderTarget &window) const {
    if (!data.is_active()) return;

    window.draw(sprite);

    if (game::is_debug_mode()) {
        sf::RectangleShape hitbox({BOX_W, BOX_H});
        hitbox.setOrigin(BOX_W / 2.0f, BOX_H / 2.0f);
        hitbox.setPosition(pos);
        hitbox.setFillColor(sf::Color::Transparent);
        hitbox.setOutlineColor(sf::Color::Magenta);
        hitbox.setOutlineThickness(1.0f);
        window.draw(hitbox);

        for (const auto &wp: path) {
            sf::RectangleShape dot({6.f, 6.f});
            dot.setOrigin(3.f, 3.f);
            dot.setFillColor(sf::Color(255, 100, 255, 180));
            dot.setPosition(wp.x * 64.f + 64.f / 2.f,
                            wp.y * 64.f + 64.f / 2.f);
            window.draw(dot);
        }
    }
}

sf::FloatRect animatronic_render::get_bounds() const {
    return sf::FloatRect(pos.x - BOX_W / 2.f, pos.y - BOX_H / 2.f, BOX_W, BOX_H);
}

sf::Vector2f animatronic_render::get_position() const {
    return pos;
}

bool animatronic_render::follow_path(float dt, const room &r) {
    if (path.empty()) return false;

    sf::Vector2f waypoint{
            path.front().x * 64.f + 64.f / 2.f,
            path.front().y * 64.f + 64.f / 2.f
    };

    sf::Vector2f dir = waypoint - pos;
    float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);

    if (dist < 4.f) {
        path.erase(path.begin());
        return true;
    }

    dir.x /= dist;
    dir.y /= dist;

    resolve_collision(dir * data.get_speed() * dt, r);
    return true;
}

void animatronic_render::recalc_path(const room &r, sf::Vector2f target_world) {
    sf::Vector2i start{(int) (pos.x / 64.f), (int) (pos.y / 64.f)};
    sf::Vector2i goal{
            (int) (target_world.x / 64.f),
            (int) (target_world.y / 64.f)
    };
    path = animatronic_ai::find(r, start, goal);
}