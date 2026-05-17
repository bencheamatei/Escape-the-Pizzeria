//
// Created by matei on 5/12/2026.
//

#ifndef OOP_GAME_SCENE_H
#define OOP_GAME_SCENE_H

#include <SFML/Graphics.hpp>
#include "room.h"
#include "player_render.h"
#include "inventory_ui.h"
#include "player.h"
#include "scene.h"
#include "animatronic.h"
#include "animatronic_render.h"

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
    void drawHUD(sf::RenderTarget& window);
    void door_transition();

    // static room buildRoom(sf::Texture& floorTex);

    std::vector<room> rooms;
    int room_idx=0;
    float door_cooldown = 0.f;
    static constexpr float DOOR_COOLDOWN = 0.8f;

    room& current_room();

    static room buildPizzeriaMain(sf::Texture& tex);
    static room buildKitchen(sf::Texture& tex);

    std::vector<EnemyEntity> enemies;

    float hit_flash_timer=0.0f;
    static constexpr float hit_duration=0.25f;
public:
    explicit game_scene(game&);
};


#endif //OOP_GAME_SCENE_H