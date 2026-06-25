//
// Created by matei on 5/12/2026.
//

#ifndef OOP_GAME_SCENE_H
#define OOP_GAME_SCENE_H

#include <SFML/Graphics.hpp>
#include "../room.h"
#include "../renders/player_render.h"
#include "../inventory_ui.h"
#include "../player.h"
#include "scene.h"
#include "../animatronic/animatronic.h"
#include "game_states/game_state.h"
#include "../enemy.h"
#include "random_selector.h"

// shoutout domnului albert pentru ca a crezut in viziune

struct flying_pizza {
    sf::Vector2f pos;
    sf::Vector2f dir;
    float speed=550.f;
    bool active=true;
    sf::CircleShape shape;

    flying_pizza(sf::Vector2f pos, sf::Vector2f dir) : pos(pos), dir(dir) {
        shape.setRadius(10.f);
        shape.setOrigin(10.f, 10.f);
        shape.setFillColor(sf::Color(220, 170, 60));
        shape.setOutlineColor(sf::Color(160, 100, 20));
        shape.setOutlineThickness(2.f);
        shape.setPosition(pos);
    }

    bool update(float dt, const room& current_room, const std::vector<enemy>& enemies, int room_idx) {
        pos += dir * speed * dt;
        shape.setPosition(pos);

        sf::FloatRect proj_hitbox(pos.x - 10.f, pos.y - 10.f, 20.f, 20.f);

        if (current_room.collide(proj_hitbox)) {
            return false;
        }

        for (const auto &enemy : enemies) {
            if (enemy.get_room_id() != room_idx || !enemy.get_data()->is_active() || !enemy.get_data()->get_bounds().intersects(proj_hitbox))
                continue;
            enemy.get_data()->gets_hit();
            return false;
        }
        return true;
    }
};

class game_scene : public scene {
private:
    player player_data;
    player_render player_render_;
    inventory_ui inventory_ui_;

    sf::View game_view;
    sf::View hud_view;
    sf::Vector2f camera_pos;

    sf::RectangleShape hpBarBg;
    sf::RectangleShape hpBar;
    sf::Text hpLabel;

    static constexpr float CAM_LERP = 5.0f;
    void on_render(sf::RenderTarget& window) override;
    void on_event(const sf::Event& event) override;
    void door_transition();

    std::vector<room> rooms;
    int room_idx=0;
    float door_cooldown = 0.f;
    static constexpr float DOOR_COOLDOWN = 0.8f;

    room& current_room();

    std::vector<enemy> enemies;

    // float hit_flash_timer=0.0f;
    static constexpr float hit_duration=0.25f;

    std::vector<flying_pizza> flying_pizzas_;

    float pomana_timer;
    static constexpr float POMANA_COOLDOWN = 5.f;

public:
    explicit game_scene();

    player& get_player();
    player_render& get_player_render();
    room& get_current_room();
    std::vector<enemy>& get_enemies();
    int& get_room_idx();
    sf::View& get_game_view();
    sf::View& get_hud_view();
    inventory_ui& get_inventory_ui();
    sf::RectangleShape& get_hp_bar();
    sf::Text& get_hp_label();
    sf::RectangleShape& get_hp_bar_bg();
    sf::Vector2f& get_camera_pos();

    void transition_to(std::unique_ptr<game_state> new_state);
    std::unique_ptr<game_state> curr_state;

    std::vector<sf::CircleShape> blood_drops;
    void generate_death_background_drops();

    std::vector<sf::CircleShape> ballons;
    void generate_background_ballons();

    void updateCamera(float dt);
    void on_update(float dt) override;

    void throw_pizza();
    void update_flying_pizzas(float dt);
    void draw_pizzas(sf::RenderTarget &window) const;

    void reset_rooms();
};


#endif //OOP_GAME_SCENE_H