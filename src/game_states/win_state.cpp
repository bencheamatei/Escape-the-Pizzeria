//
// Created by matei on 6/25/2026.
//

#include "../../include/game_states/win_state.h"
#include "scenes/game_scene.h"
#include <memory>

#include "game.h"
#include "../../ResourceManager.hpp"

void win_state::on_enter(game_scene &ctx) {
    timer = duration;
    ctx.generate_background_ballons();
}

void win_state::on_update(game_scene &, float dt) {
    timer -= dt;
    if (timer <= 0.f) {
        game::get_instance().get_scene_manager().clear();
    }
}

void win_state::on_render(game_scene &ctx, sf::RenderTarget &t) {
    t.setView(ctx.get_game_view());
    t.draw(ctx.get_current_room());
    ctx.get_player_render().draw(t);
    for (const auto &e: ctx.get_enemies())
        if (e.room_id == ctx.get_room_idx()) e.render->draw(t);

    t.setView(ctx.get_hud_view());

    float progress = 1.f - (timer / duration);
    sf::Uint8 bg_a = static_cast<sf::Uint8>(std::min(255.f, progress * 2.f * 255.f));

    sf::RectangleShape bg({960.f, 640.f});
    bg.setFillColor(sf::Color(0, 0, 0, bg_a));
    t.draw(bg);

    for (auto drop: ctx.ballons) {
        sf::Color c = drop.getFillColor();
        c.a = static_cast<sf::Uint8>((c.a * std::min(1.f, progress * 2.5f)));
        drop.setFillColor(c);
        t.draw(drop);
    }

    if (progress > 0.45f) {
        auto &font = ResourceManager::Instance().getFont("FiraSans-Regular.ttf");
        float ta = std::min(255.f, (progress - 0.45f) / 0.3f * 255.f);

        sf::Text win_text;
        win_text.setFont(font);

        win_text.setString("You Escaped!");
        win_text.setCharacterSize(72);
        win_text.setStyle(sf::Text::Bold);

        win_text.setFillColor(sf::Color(20, 200, 20, static_cast<sf::Uint8>(ta)));

        sf::FloatRect b = win_text.getLocalBounds();
        win_text.setOrigin(b.width / 2.f, b.height / 2.f);
        win_text.setPosition(480.f, 280.f);
        t.draw(win_text);
    }
}