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
#include "../renders/animatronic_render.h"
#include "game_states/game_state.h"

struct EnemyEntity {
    std::unique_ptr<animatronic> data;
    std::unique_ptr<animatronic_render> render;
    int room_id=0;
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

    void on_update(float dt) override;
    void on_render(sf::RenderTarget& window) override;
    void on_event(const sf::Event& event) override;

    void updateCamera(float dt);
    // void drawHUD(sf::RenderTarget& window);
    void door_transition();

    std::vector<room> rooms;
    int room_idx=0;
    float door_cooldown = 0.f;
    static constexpr float DOOR_COOLDOWN = 0.8f;

    room& current_room();

    static room buildPizzeriaMain(sf::Texture& tex);
    static room buildKitchen(sf::Texture& tex);

    std::vector<EnemyEntity> enemies;

    // float hit_flash_timer=0.0f;
    static constexpr float hit_duration=0.25f;
public:
    explicit game_scene(game&);

    player& get_player();
    player_render& get_player_render();
    room& get_current_room();
    std::vector<EnemyEntity>& get_enemies();
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
};


#endif //OOP_GAME_SCENE_H