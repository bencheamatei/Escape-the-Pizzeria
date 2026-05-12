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

class game_scene : public scene {
private:
    player player_data;
    room room_;
    player_render player_render_;
    inventory_ui inventory_ui_;

    sf::View game_view;
    sf::View hud_view;
    sf::Vector2f   camera_pos;

    sf::RectangleShape hpBarBg;
    sf::RectangleShape hpBar;
    sf::Text hpLabel;

    static constexpr float CAM_LERP = 5.0f;

    void on_update(float dt) override;
    void on_render(sf::RenderTarget& window) override;
    void on_event(const sf::Event& event) override;

    void updateCamera(float dt);
    void drawHUD(sf::RenderTarget& window);

    static room buildRoom(sf::Texture& floorTex);

public:
    explicit game_scene(game&);
};


#endif //OOP_GAME_SCENE_H