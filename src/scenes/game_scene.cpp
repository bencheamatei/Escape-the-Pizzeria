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
#include "items/item_factory.h"
#include "scenes/everything_builder.h"
#include "items/item_factory.h"

game_scene::game_scene()
    : player_data(100, 100, 5)
    , player_render_(player_data, ResourceManager::Instance().getTexture("billy.png"), {0.f, 0.f})
    , inventory_ui_(player_data, ResourceManager::Instance().getFont("FiraSans-Regular.ttf")),
    rooms(everything_builder::build_rooms())
{
    everything_builder::setup_starting_inventory(player_data);
    everything_builder::build_enemies(enemies);

    player_render_.set_position(current_room().spawn_point);
    camera_pos = current_room().spawn_point;

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

    curr_state = std::make_unique<playing_state>();
    curr_state->on_enter(*this);

    pomana_timer=0.f;
}

void game_scene::transition_to(std::unique_ptr<game_state> new_state) {
    pending_state = std::move(new_state);
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

    if (pending_state) {
        if (curr_state) {
            curr_state->on_exit(*this);
        }
        curr_state = std::move(pending_state);
        curr_state->on_enter(*this);
    }

    if (door_cooldown > 0.0f) {
        door_cooldown -= dt;
    } else {
        door_transition();
    }

    pomana_timer += dt;
    if (pomana_timer >= POMANA_COOLDOWN) {
        pomana_timer = 0.0f;
        player_data.addItem({*item_factory::create(rand()%5), 1});
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
            game::get_instance().get_scene_manager().add_scene(std::make_unique<pause_scene>());
        }

        if (event.key.code == sf::Keyboard::F3) {
            game::get_instance().toggle_debug_mode();
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

void game_scene::generate_background_ballons() {
    ballons.clear();
    srand((unsigned) std::time(nullptr));
    for (int i = 0; i < 20; i++) {
        sf::CircleShape drop;
        float r = 8.f + (rand() % 38);
        drop.setRadius(r);
        drop.setOrigin(r, r);
        drop.setPosition((float) (rand() % 960), (float) (rand() % 640));
        drop.setFillColor(sf::Color(
            20, 180+rand()%50, 20,
            170 + rand() % 85));
        ballons.push_back(std::move(drop));
    }
}

room &game_scene::get_current_room() {
    return rooms[room_idx];
}

std::vector<enemy> &game_scene::get_enemies() {
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
            player_data.decpos(u);
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
        it.active=it.update(dt,current_room(),enemies,room_idx);
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

void game_scene::reset_rooms() {
    rooms.clear();
    rooms=everything_builder::build_rooms();
}
