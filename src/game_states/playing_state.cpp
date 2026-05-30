//
// Created by matei on 5/17/2026.
//

#include "../../include/game_states/playing_state.h"

#include "game.h"
#include "../../include/game_states/death_state.h"
#include "scenes/game_scene.h"

void playing_state::on_update(game_scene &ctx, float dt) {
    auto &p = ctx.get_player();
    auto &player_render_ = ctx.get_player_render();

    player_render_.handle_input();
    player_render_.update(dt, ctx.get_current_room());

    if (update_enemies(ctx, dt)) {
        hit_flash_timer = hir_duration;
    }
    if (hit_flash_timer > 0.f) {
        hit_flash_timer -= dt;
    }

    if (!p.isAlive()) {
        ctx.transition_to(std::make_unique<death_state>());
        return;
    }

    ctx.update_flying_pizzas(dt);
}

bool playing_state::update_enemies(game_scene &ctx, float dt) {
    auto &p = ctx.get_player();
    auto &player_render_ = ctx.get_player_render();

    bool recieved_dmg = false;

    for (const auto &it: ctx.get_enemies()) {
        if (it.room_id != ctx.get_room_idx() || !it.data->is_active())
            continue;
        it.render->update(dt, ctx.get_current_room(), player_render_.get_position());
        it.data->tick_timer(dt);
        if (it.render->get_bounds().intersects(player_render_.get_bound())) {
            if (it.data->can_attack()) {
                it.data->on_attack(p);
                it.data->reset_cooldown();
                recieved_dmg = true;
            }
        }
    }
    return recieved_dmg;
}

void playing_state::on_render(game_scene &ctx, sf::RenderTarget &window) {
    window.setView(ctx.get_game_view());
    window.draw(ctx.get_current_room());
    ctx.get_player_render().draw(window);
    for (const auto &e: ctx.get_enemies()) {
        if (e.room_id == ctx.get_room_idx()) e.render->draw(window);
    }

    if (ctx.get_room_idx()==2) {
        draw_intuneric(ctx,window);
    }

    if (hit_flash_timer > 0.f) {
        float a = (hit_flash_timer / hir_duration) * 140.f;
        sf::RectangleShape flash(ctx.get_game_view().getSize());
        flash.setFillColor(sf::Color(220, 30, 30, (sf::Uint8) a));
        flash.setPosition(ctx.get_game_view().getCenter()
                          - ctx.get_game_view().getSize() / 2.f);
        window.draw(flash);
    }

    ctx.draw_pizzas(window);

    window.setView(ctx.get_hud_view());
    draw_hud(ctx, window);

    if (ctx.get_room_idx()==3) {
        sf::View compact_inv_view = ctx.get_hud_view();
        compact_inv_view.setViewport(sf::FloatRect(0.3f, 0.505f, 0.5f, 0.5f));
        window.setView(compact_inv_view);
        ctx.get_inventory_ui().draw(window);
        window.setView(ctx.get_hud_view());
        return ;
    }

    ctx.get_inventory_ui().draw(window);
}

void playing_state::draw_hud(game_scene &ctx, sf::RenderTarget &window) {
    auto &p = ctx.get_player();
    auto &hpBar = ctx.get_hp_bar();

    float frac = (float) p.getHp() / 100.f;
    hpBar.setSize({200.f * frac, 12.f});
    hpBar.setFillColor(
        frac > 0.5f ? sf::Color(195, 50, 50) : frac > 0.25f ? sf::Color(215, 135, 25) : sf::Color(255, 45, 45));

    ctx.get_hp_label().setString("HP  " + std::to_string(p.getHp())
                                 + " / 100");

    window.draw(ctx.get_hp_bar_bg());
    window.draw(hpBar);
    window.draw(ctx.get_hp_label());
}

bool playing_state::can_see_flying_pizzas() {
    return true;
}

void playing_state::draw_intuneric(game_scene &ctx, sf::RenderTarget &window) {
    if (!este_intuneric) {
        intuneric.create(game::BASE_W, game::BASE_H);
        intuneric.setSmooth(true);
        este_intuneric = true;
    }

    intuneric.clear(sf::Color(8, 8, 14, 252));

    intuneric.setView(ctx.get_game_view());

    sf::Vector2f ppos = ctx.get_player_render().get_position();
    float max_radius = 70.f;

    for (float r = max_radius; r > 0; r -= 4.f) {
        sf::CircleShape circle(r);
        circle.setOrigin(r, r);
        circle.setPosition(ppos);

        float ratio = r / max_radius;
        sf::Uint8 alpha = static_cast<sf::Uint8>(ratio * 252.f);

        circle.setFillColor(sf::Color(0, 0, 0, alpha));

        intuneric.draw(circle, sf::BlendNone);
    }
    intuneric.display();

    sf::Sprite light_sprite(intuneric.getTexture());

    window.setView(ctx.get_hud_view());
    window.draw(light_sprite);

    window.setView(ctx.get_game_view());
}
