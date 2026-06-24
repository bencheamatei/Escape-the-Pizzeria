//
// Created by matei on 5/14/2026.
//

#include "../../include/renders/animatronic_render.h"
#include "../../include/animatronic/animatronic.h"
#include "game.h"
#include <cmath>
#include "../../include/animatronic/animatronic_ai.h"

animatronic_render::animatronic_render(animatronic &a, sf::Texture &texture, sf::Vector2f init_pos, float scale)
    : data(a) {
    sprite.setTexture(texture);
    sprite.setOrigin(32.0f, 32.0f);
    sprite.setScale(scale,scale);
    data.set_position(init_pos);
    sprite.setPosition(init_pos);
}

void animatronic_render::draw(sf::RenderTarget &window) {
    if (!data.is_active()) return;

    sprite.setPosition(data.get_position());
    window.draw(sprite);

    if (game::get_instance().is_debug_mode()) {
        float BOX_W=data.get_bounds().width;
        float BOX_H=data.get_bounds().height;
        sf::RectangleShape hitbox({BOX_W, BOX_H});
        hitbox.setOrigin(BOX_W / 2.0f, BOX_H / 2.0f);
        hitbox.setPosition(data.get_position());
        hitbox.setFillColor(sf::Color::Transparent);
        hitbox.setOutlineColor(sf::Color::Magenta);
        hitbox.setOutlineThickness(1.0f);
        window.draw(hitbox);

        for (const auto &wp: data.get_path()) {
            sf::RectangleShape dot({6.f, 6.f});
            dot.setOrigin(3.f, 3.f);
            dot.setFillColor(sf::Color(255, 100, 255, 180));
            dot.setPosition(wp.x * 64.f + 64.f / 2.f,
                            wp.y * 64.f + 64.f / 2.f);
            window.draw(dot);
        }
    }
}
