//
// Created by matei on 5/12/2026.
//

#include "../../include/scenes/game_scene.h"
#include "../../include/items/backpack.h"
#include "../../ResourceManager.hpp"
#include "../../include/items/dough.h"
#include "game.h"
#include "../../include/scenes/pause_scene.h"
#include "../../include/items/topping.h"
#include "../../include/items/pizza.h"
#include "../../include/items/soda.h"
#include <cmath>
#include "../../include/animatronic/freddy.h"
#include "game_states/playing_state.h"

game_scene::game_scene(game& g)
    : scene(g)
    , player_data(70, 100, 5)
    , player_render_(player_data,ResourceManager::Instance().getTexture("billy.png"),{0.f,0.f})
    , inventory_ui_(player_data,ResourceManager::Instance().getFont("FiraSans-Regular.ttf"))
{
    auto& tileset = ResourceManager::Instance().getTexture("tileset.png");

    rooms.push_back(buildPizzeriaMain(tileset));
    rooms.push_back(buildKitchen(tileset));

    player_render_.set_position(current_room().spawn_point);
    camera_pos = current_room().spawn_point;

    try {
        player_data.addItem(inventorySlot(dough(), 2));
        player_data.addItem(inventorySlot(topping("pepperoni", 5), 3));
        player_data.addItem(inventorySlot(topping("mushroom", 3), 2));
        player_data.addItem(inventorySlot(backpack(8), 1));
        player_data.addItem(inventorySlot(soda(),1));
    } catch (...) {}

    game_view.setSize(480.f, 320.f);
    hud_view.setSize(960.f, 640.f);
    hud_view.setCenter(480.f, 320.f);

    auto& font = ResourceManager::Instance().getFont("FiraSans-Regular.ttf");

    hpBarBg.setSize({204.f, 16.f});
    hpBarBg.setFillColor(sf::Color(45, 12, 12));
    hpBarBg.setPosition(18.f, 18.f);

    hpBar.setPosition(20.f, 20.f);

    hpLabel.setFont(font);
    hpLabel.setCharacterSize(11);
    hpLabel.setFillColor(sf::Color(220, 210, 230));
    hpLabel.setPosition(20.f, 38.f);

    auto freddy_ = std::make_unique<freddy>();
    auto freddy_render_ = std::make_unique<animatronic_render>(
        *freddy_,
        ResourceManager::Instance().getTexture("freddy.png"),
        sf::Vector2f(400.f, 200.f)
    );
    enemies.push_back({std::move(freddy_), std::move(freddy_render_), 0});

    curr_state=std::make_unique<playing_state>();
    curr_state->on_enter(*this);
}

void game_scene::transition_to(std::unique_ptr<game_state> new_state) {
    if (curr_state) {
        curr_state->on_exit(*this);
    }

    curr_state=std::move(new_state);
    curr_state->on_enter(*this);
}

room &game_scene::current_room() {
    return rooms[room_idx];
}

// room game_scene::buildRoom(sf::Texture& floorTex) {
//     std::vector<std::vector<int>> level_map = {
//         {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//         {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//         {1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
//         {1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
//         {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//         {1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
//         {1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
//         {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//         {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
//     };
//
//     room r(level_map, floorTex, 64);
//     r.spawn_point = {200.f, 100.f};
//
//     return r;
// }

room game_scene::buildPizzeriaMain(sf::Texture& tex) {
    std::vector<std::vector<int>> grid = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1},
    };

    room r(grid, tex, 64);
    r.spawn_point = {3 * 64.f + 32.f, 4 * 64.f + 32.f};

    r.add_door(7, 8, 1, {7 * 64.f + 32.f, 1 * 64.f + 32.f});

    return r;
}

room game_scene::buildKitchen(sf::Texture& tex) {
    std::vector<std::vector<int>> grid = {
        {1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    room r(grid, tex, 64);
    r.spawn_point = {7 * 64.f + 32.f, 2 * 64.f + 32.f};

    r.add_door(7, 0, 0, {7 * 64.f + 32.f, 7 * 64.f + 32.f});

    return r;
}

void game_scene::door_transition() {
    const door* usa = current_room().check_door(player_render_.get_position());
    if (!usa) {
        return;
    }

    room_idx = usa->room_id;

    player_render_.set_position(usa->spawn);
    camera_pos = usa->spawn;

    door_cooldown = DOOR_COOLDOWN;
}


void game_scene::on_update(float dt) {
    if (curr_state) {
        curr_state->on_update(*this, dt);
    }
    if (door_cooldown > 0.0f) {
        door_cooldown -= dt;
    }
    else {
        door_transition();
    }
    updateCamera(dt);
}

void game_scene::on_render(sf::RenderTarget &window) {
    float wr = (float)window.getSize().x /(float) window.getSize().y;
    float vr = (float)game::BASE_W / game::BASE_H;
    float sx = 1.f, sy = 1.f, px = 0.f, py = 0.f;
    if (wr >= vr) {
        sx = vr/wr; px = (1.f-sx)/2.f;
    } else {
        sy = wr/vr; py = (1.f-sy)/2.f;
    }
    game_view.setViewport({px, py, sx, sy});
    hud_view.setViewport({px, py, sx, sy});
    if (curr_state) {
        curr_state->on_render(*this,window);
    }
}


void game_scene::on_event(const sf::Event& event) {
    inventory_ui_.event_handler(event, player_data);
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            _game.add_scene(std::make_unique<pause_scene>(_game));
        }

        if (event.key.code==sf::Keyboard::F3) {
            game::toggle_debug_mode();
        }
    }
}

void game_scene::updateCamera(float dt) {
    sf::Vector2f target = player_render_.get_position();
    camera_pos.x += (target.x - camera_pos.x) * CAM_LERP * dt;
    camera_pos.y += (target.y - camera_pos.y) * CAM_LERP * dt;

    float hw = game_view.getSize().x / 2.f;
    float hh = game_view.getSize().y / 2.f;
    camera_pos.x = std::clamp(camera_pos.x, hw, current_room().get_size().x - hw);
    camera_pos.y = std::clamp(camera_pos.y, hh, current_room().get_size().y - hh);
    game_view.setCenter(std::round(camera_pos.x), std::round(camera_pos.y));
}

// void game_scene::drawHUD(sf::RenderTarget& window) {
//     float frac = (float)player_data.getHp() / 100.f;
//     hpBar.setSize({200.f * frac, 12.f});
//     hpBar.setFillColor(
//         frac > 0.5f  ? sf::Color(195, 50, 50) :
//         frac > 0.25f ? sf::Color(215, 135, 25) :
//                        sf::Color(255, 45, 45));
//
//     hpLabel.setString("HP  " + std::to_string(player_data.getHp())
//                       + " / 100");
//
//     window.draw(hpBarBg);
//     window.draw(hpBar);
//     window.draw(hpLabel);
// }

player &game_scene::get_player() {
    return player_data;
}

player_render &game_scene::get_player_render() {
    return player_render_;
}

void game_scene::generate_death_background_drops() {
    blood_drops.clear();
    srand((unsigned)std::time(nullptr));
    for (int i = 0; i < 20; i++) {
        sf::CircleShape drop;
        float r = 8.f + (rand() % 38);
        drop.setRadius(r);
        drop.setOrigin(r, r);
        drop.setPosition((float)(rand() % 960), (float)(rand() % 640));
        drop.setFillColor(sf::Color(
            80 + rand() % 80, 0, 0,
            170 + rand() % 85));
        blood_drops.push_back(std::move(drop));
    }
}

room &game_scene::get_current_room() {
    return rooms[room_idx];
}

std::vector<EnemyEntity> &game_scene::get_enemies() {
    return enemies;
}

int &game_scene::get_room_idx() {
    return room_idx;
}

sf::View &game_scene::get_game_view() {
    return game_view;
}

sf::View &game_scene::get_hud_view() {
    return hud_view;
}

inventory_ui &game_scene::get_inventory_ui() {
    return inventory_ui_;
}

sf::RectangleShape &game_scene::get_hp_bar() {
    return hpBar;
}

sf::Text &game_scene::get_hp_label() {
    return hpLabel;
}

sf::RectangleShape &game_scene::get_hp_bar_bg() {
    return hpBarBg;
}

sf::Vector2f &game_scene::get_camera_pos() {
    return camera_pos;
}
