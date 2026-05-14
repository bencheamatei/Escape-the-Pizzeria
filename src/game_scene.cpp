//
// Created by matei on 5/12/2026.
//

#include "../include/game_scene.h"

#include "backpack.h"
#include "../ResourceManager.hpp"
#include "dough.h"
#include "game.h"
#include "pause_scene.h"
#include "topping.h"
#include "pizza.h"
#include "soda.h"
#include <cmath>

game_scene::game_scene(game& g)
    : scene(g)
    , player_data(70, 100, 5)
    , room_(buildRoom(ResourceManager::Instance().getTexture("tileset.png")))
    , player_render_(player_data,ResourceManager::Instance().getTexture("billy.png"),room_.spawn_point)
    , inventory_ui_(player_data,ResourceManager::Instance().getFont("FiraSans-Regular.ttf"))
{
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
    camera_pos = room_.spawn_point;

    auto& font = ResourceManager::Instance().getFont("FiraSans-Regular.ttf");

    hpBarBg.setSize({204.f, 16.f});
    hpBarBg.setFillColor(sf::Color(45, 12, 12));
    hpBarBg.setPosition(18.f, 18.f);

    hpBar.setPosition(20.f, 20.f);

    hpLabel.setFont(font);
    hpLabel.setCharacterSize(11);
    hpLabel.setFillColor(sf::Color(220, 210, 230));
    hpLabel.setPosition(20.f, 38.f);
}

room game_scene::buildRoom(sf::Texture& floorTex) {
    std::vector<std::vector<int>> level_map = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    room r(level_map, floorTex, 64);
    r.spawn_point = {200.f, 100.f};

    return r;
}

void game_scene::on_update(float dt) {
    if (!player_data.isAlive()) return;
    player_render_.handle_input();
    player_render_.update(dt, room_);
    updateCamera(dt);
}

void game_scene::updateCamera(float dt) {
    sf::Vector2f target = player_render_.get_position();
    camera_pos.x += (target.x - camera_pos.x) * CAM_LERP * dt;
    camera_pos.y += (target.y - camera_pos.y) * CAM_LERP * dt;

    float hw = game_view.getSize().x / 2.f;
    float hh = game_view.getSize().y / 2.f;
    camera_pos.x = std::clamp(camera_pos.x, hw, room_.get_size().x - hw);
    camera_pos.y = std::clamp(camera_pos.y, hh, room_.get_size().y - hh);
    game_view.setCenter(std::floor(camera_pos.x), std::floor(camera_pos.y));
}

void game_scene::on_render(sf::RenderTarget& window) {
    float windowRatio = (float)window.getSize().x / (float)window.getSize().y;
    float viewRatio = (float)game::BASE_W / (float)game::BASE_H;

    float sizeX = 1.0f, sizeY = 1.0f;
    float posX = 0.0f, posY = 0.0f;

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

    window.setView(game_view);
    window.draw(room_);
    player_render_.draw(window);

    window.setView(hud_view);
    drawHUD(window);
    inventory_ui_.draw(window);
}

void game_scene::drawHUD(sf::RenderTarget& window) {
    float frac = (float)player_data.getHp() / 100.f;
    hpBar.setSize({200.f * frac, 12.f});
    hpBar.setFillColor(
        frac > 0.5f  ? sf::Color(195, 50, 50) :
        frac > 0.25f ? sf::Color(215, 135, 25) :
                       sf::Color(255, 45, 45));

    hpLabel.setString("HP  " + std::to_string(player_data.getHp())
                      + " / 100");

    window.draw(hpBarBg);
    window.draw(hpBar);
    window.draw(hpLabel);
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