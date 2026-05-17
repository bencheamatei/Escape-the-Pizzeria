//
// Created by matei on 5/17/2026.
//

#include "../../include/game_states/death_state.h"

#include "scenes/game_scene.h"
#include "game_states/respawn_state.h"
#include "../ResourceManager.hpp"

void death_state::on_enter(game_scene &ctx) {
    timer=duration;
    ctx.generate_death_background_drops();
}

void death_state::on_update(game_scene &ctx, float dt) {
    timer-=dt;
    if (timer<=0.f) {
        ctx.transition_to(std::make_unique<respawn_state>());
    }
}

void death_state::on_render(game_scene &ctx, sf::RenderTarget &t) {
    t.setView(ctx.get_game_view());
    t.draw(ctx.get_current_room());
    ctx.get_player_render().draw(t);
    for (const auto& e : ctx.get_enemies())
        if (e.room_id == ctx.get_room_idx()) e.render->draw(t);

    t.setView(ctx.get_hud_view());

    float progress = 1.f - (timer / duration);
    sf::Uint8 bg_a = static_cast<sf::Uint8>(std::min(255.f, progress * 2.f * 255.f));

    sf::RectangleShape bg({960.f, 640.f});
    bg.setFillColor(sf::Color(0, 0, 0, bg_a));
    t.draw(bg);

    for (auto drop : ctx.blood_drops) {
        sf::Color c = drop.getFillColor();
        c.a = static_cast<sf::Uint8>((c.a * std::min(1.f, progress * 2.5f)));
        drop.setFillColor(c);
        t.draw(drop);
    }

    if (progress > 0.45f) {
        auto& font = ResourceManager::Instance().getFont("FiraSans-Regular.ttf");
        float ta = std::min(255.f, (progress - 0.45f) / 0.3f * 255.f);

        sf::Text died;
        died.setFont(font);
        died.setString("You died.");
        died.setCharacterSize(72);
        died.setStyle(sf::Text::Bold);
        died.setFillColor(sf::Color(200, 20, 20, static_cast<sf::Uint8>(ta)));
        sf::FloatRect b = died.getLocalBounds();
        died.setOrigin(b.width/2.f, b.height/2.f);
        died.setPosition(480.f, 280.f);
        t.draw(died);
    }
}

std::string death_state::get_name() const {
    return "dying";
}
