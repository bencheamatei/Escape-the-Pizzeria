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
#include "../../include/animatronic/foxy.h"
#include "animatronic/chica.h"
#include "animatronic/nightmare.h"

game_scene::game_scene(game &g)
    : scene(g)
      , player_data(70, 100, 5)
      , player_render_(player_data, ResourceManager::Instance().getTexture("billy.png"), {0.f, 0.f})
      , inventory_ui_(player_data, ResourceManager::Instance().getFont("FiraSans-Regular.ttf")) {
    auto &tileset = ResourceManager::Instance().getTexture("tileset.png");

    rooms.push_back(room::from_tmj("assets/maps/room1.tmj", tileset));
    rooms.push_back(room::from_tmj("assets/maps/room2.tmj", tileset));
    rooms.push_back(room::from_tmj("assets/maps/room3.tmj", tileset));
    rooms.push_back(room::from_tmj("assets/maps/room4.tmj", tileset));

    player_render_.set_position(current_room().spawn_point);
    camera_pos = current_room().spawn_point;

    try {
        player_data.addItem(inventorySlot(dough(), 10));
        player_data.addItem(inventorySlot(topping("pepperoni", 5), 10));
        player_data.addItem(inventorySlot(topping("mushroom", 3), 10));
        player_data.addItem(inventorySlot(backpack(8), 1));
        player_data.addItem(inventorySlot(soda(), 10));
    } catch (...) {
    }

    game_view.setSize(480.f, 320.f);
    hud_view.setSize(960.f, 640.f);
    hud_view.setCenter(480.f, 320.f);

    auto &font = ResourceManager::Instance().getFont("FiraSans-Regular.ttf");

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

    auto foxy_ = std::make_unique<foxy>();
    auto foxy_render_ = std::make_unique<animatronic_render>(
        *foxy_,
        ResourceManager::Instance().getTexture("foxy.png"),
        sf::Vector2f(490.f, 300.f)
    );

    auto chica_ = std::make_unique<chica>();
    auto chica_render_ = std::make_unique<animatronic_render>(
        *chica_,
        ResourceManager::Instance().getTexture("chica.png"),
        sf::Vector2f(600.f, 600.f)
    );

    auto nightmare_ = std::make_unique<nightmare>();
    auto nightmare_render_ = std::make_unique<animatronic_render>(
        *nightmare_,
        ResourceManager::Instance().getTexture("nightmare.png"),
        sf::Vector2f(600.f, 600.f), 3
    );

    enemies.push_back({std::move(freddy_), std::move(freddy_render_), 0});
    enemies.push_back({std::move(foxy_), std::move(foxy_render_), 1});
    enemies.push_back({std::move(chica_), std::move(chica_render_), 2});
    enemies.push_back({std::move(nightmare_), std::move(nightmare_render_), 3});

    curr_state = std::make_unique<playing_state>();
    curr_state->on_enter(*this);
}

void game_scene::transition_to(std::unique_ptr<game_state> new_state) {
    if (curr_state) {
        curr_state->on_exit(*this);
    }

    curr_state = std::move(new_state);
    curr_state->on_enter(*this);
}

room &game_scene::current_room() {
    return rooms[room_idx];
}

void game_scene::door_transition() {
    const door *usa = current_room().check_door(player_render_.get_position());
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
    } else {
        door_transition();
    }
}

void game_scene::on_render(sf::RenderTarget &window) {
    float windowRatio = (float) window.getSize().x / (float) window.getSize().y;
    float viewRatio = (float) game::BASE_W / (float) game::BASE_H;
    float sizeX = 1.0f, sizeY = 1.0f, posX = 0.0f, posY = 0.0f;

    if (windowRatio >= viewRatio) {
        sizeX = viewRatio / windowRatio;
        posX = (1.0f - sizeX) / 2.0f;
    } else {
        sizeY = windowRatio / viewRatio;
        posY = (1.0f - sizeY) / 2.0f;
    }

    sf::FloatRect viewport(posX, posY, sizeX, sizeY);
    game_view.setViewport(viewport);
    hud_view.setViewport(viewport);

    if (curr_state) {
        curr_state->on_render(*this, window);
    }
}


void game_scene::on_event(const sf::Event &event) {
    inventory_ui_.event_handler(event, player_data);
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            _game.add_scene(std::make_unique<pause_scene>(_game));
        }

        if (event.key.code == sf::Keyboard::F3) {
            game::toggle_debug_mode();
        }

        if (event.key.code==sf::Keyboard::Space) {
            if (curr_state!=nullptr && curr_state->can_see_flying_pizzas()) {
                throw_pizza();
            }
        }
    }
}

void game_scene::updateCamera(float dt) {
    if (room_idx==3) {
        sf::Vector2f r_size = current_room().get_size();

        float base_ratio = (float)game::BASE_W / game::BASE_H;
        float room_ratio = r_size.x / r_size.y;

        float view_w = r_size.x;
        float view_h = r_size.y;

        if (room_ratio > base_ratio) {
            view_h = r_size.x / base_ratio;
        } else {
            view_w = r_size.y * base_ratio;
        }

        game_view.setSize(view_w, view_h);
        game_view.setCenter(r_size.x / 2.f, r_size.y / 2.f);
        return ;
    }

    game_view.setSize(480.f, 320.f);

    sf::Vector2f target = player_render_.get_position();
    camera_pos.x += (target.x - camera_pos.x) * CAM_LERP * dt;
    camera_pos.y += (target.y - camera_pos.y) * CAM_LERP * dt;

    float hw = game_view.getSize().x / 2.f;
    float hh = game_view.getSize().y / 2.f;
    float max_x = std::max(hw, current_room().get_size().x - hw);
    float max_y = std::max(hh, current_room().get_size().y - hh);

    camera_pos.x = std::clamp(camera_pos.x, hw, max_x);
    camera_pos.y = std::clamp(camera_pos.y, hh, max_y);
    game_view.setCenter(camera_pos);
}

player &game_scene::get_player() {
    return player_data;
}

player_render &game_scene::get_player_render() {
    return player_render_;
}

void game_scene::generate_death_background_drops() {
    blood_drops.clear();
    srand((unsigned) std::time(nullptr));
    for (int i = 0; i < 20; i++) {
        sf::CircleShape drop;
        float r = 8.f + (rand() % 38);
        drop.setRadius(r);
        drop.setOrigin(r, r);
        drop.setPosition((float) (rand() % 960), (float) (rand() % 640));
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

void game_scene::throw_pizza() {
    auto inv=player_data.get_inventory();
    int u=inv.first_pizza_slot();

    if (u!=-1) {
        try {
            player_data.drop_item(u);
        }
        catch (...) {
            return;
        }
        flying_pizzas_.emplace_back(player_render_.get_position(),player_render_.get_dir());
    }
}

void game_scene::update_flying_pizzas(float dt) {
    for (auto &it:flying_pizzas_) {
        if (!it.active)
            continue;

        it.pos+=it.dir*it.speed*dt;
        it.shape.setPosition(it.pos);
        sf::FloatRect proj_hitbox(it.pos.x-10.f,it.pos.y-10.f,20.f,20.f);

        if (current_room().collide(proj_hitbox)) {
            it.active=false;
            continue;
        }

        for (auto &enemy:enemies) {
            if (enemy.room_id!=room_idx || !enemy.data->is_active() || !enemy.render->get_bounds().intersects(proj_hitbox))
                continue;
            enemy.data->gets_hit();
            it.active=false;
            break;
        }
    }

    flying_pizzas_.erase(std::remove_if(flying_pizzas_.begin(),flying_pizzas_.end(),
                    [](const flying_pizza &x) {return !x.active;})
                        ,flying_pizzas_.end());
}

void game_scene::draw_pizzas(sf::RenderTarget &window) const {
    for (const auto& it:flying_pizzas_) {
        if (!it.active)
            continue;
        window.draw(it.shape);
    }
}
