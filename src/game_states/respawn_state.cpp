//
// Created by matei on 5/17/2026.
//

#include "../../include/game_states/respawn_state.h"
#include "game_states/playing_state.h"
#include "scenes/game_scene.h"

void respawn_state::on_enter(game_scene &ctx) {
    timer = duration;
    visible = true;
    blink_timer = blink_duration;

    for (int i = ctx.get_player().get_inventory().get_capacity() - 1; i >= 0; i--) {
        try {
            ctx.get_player().drop_item(i);
        } catch (...) {
        }
    }

    ctx.get_player().heal(999);

    sf::Vector2f spawn = ctx.get_current_room().spawn_point;
    ctx.get_player_render().set_position(spawn);
    ctx.get_camera_pos() = spawn;
}

void respawn_state::on_update(game_scene &ctx, float dt) {
    ctx.get_player_render().handle_input();
    ctx.get_player_render().update(dt, ctx.get_current_room());
    ctx.updateCamera(dt);

    blink_timer -= dt;
    if (blink_timer <= 0.f) {
        blink_timer = blink_duration;
        visible = !visible;
    }

    for (auto &e: ctx.get_enemies()) {
        if (e.room_id != ctx.get_room_idx())
            continue;
        e.data->update(dt, ctx.get_current_room(), ctx.get_player_render().get_position());
        e.data->tick_timer(dt);
    }

    timer -= dt;
    if (timer <= 0.f) {
        ctx.transition_to(std::make_unique<playing_state>());
    }
}

void respawn_state::on_render(game_scene &ctx, sf::RenderTarget &window) {
    window.setView(ctx.get_game_view());
    window.draw(ctx.get_current_room());
    if (visible) ctx.get_player_render().draw(window);
    for (const auto &e: ctx.get_enemies())
        if (e.room_id == ctx.get_room_idx()) e.render->draw(window);

    window.setView(ctx.get_hud_view());
    ctx.get_inventory_ui().draw(window);
}