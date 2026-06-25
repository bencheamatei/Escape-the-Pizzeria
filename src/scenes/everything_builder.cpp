//
// Created by matei on 6/23/2026.
//

#include "../../include/scenes/everything_builder.h"

#include "items/backpack.h"
#include "items/dough.h"
#include "items/soda.h"
#include "items/topping.h"
#include "../ResourceManager.hpp"
#include <animatronic/freddy.h>
#include <animatronic/chica.h>
#include <animatronic/foxy.h>
#include <animatronic/nightmare.h>
#include "items/key.h"

std::vector<room> everything_builder::build_rooms() {
    std::vector<room> rooms;
    auto &tileset = ResourceManager::Instance().getTexture("tileset.png");
    rooms.push_back(room::from_tmj("assets/maps/room1.tmj", tileset));
    rooms.push_back(room::from_tmj("assets/maps/room2.tmj", tileset));
    rooms.push_back(room::from_tmj("assets/maps/room3.tmj", tileset));
    rooms.push_back(room::from_tmj("assets/maps/room4.tmj", tileset));

    const auto& key_tex = ResourceManager::Instance().getTexture("key.png");

    rooms[1].add_ground_item(std::make_unique<key>(), sf::Vector2f(450.f, 1500.f), key_tex, sf::Vector2f(0.5,0.5));
    rooms[2].add_ground_item(std::make_unique<key>(), sf::Vector2f(450.f, 400.f), key_tex,sf::Vector2f(0.5,0.5));
    rooms[3].add_ground_item(std::make_unique<key>(), sf::Vector2f(600.f, 600.f), key_tex,sf::Vector2f(1.f,1.f));
    return rooms;
}

void everything_builder::setup_starting_inventory(player& p) {
    try {
        p.addItem(inventorySlot(dough(), 3));
        p.addItem(inventorySlot(backpack(8), 1));
        p.addItem(inventorySlot(soda(), 1));
    } catch (const std::exception &) {
        throw;
    }
}

void everything_builder::build_enemies(std::vector<enemy>& enemies) {
    auto freddy_ = std::make_unique<freddy>();
    auto freddy_render_ = std::make_unique<animatronic_render>(
        *freddy_, ResourceManager::Instance().getTexture("freddy.png"), sf::Vector2f(400.f, 200.f)
    );

    auto foxy_ = std::make_unique<foxy>();
    auto foxy_render_ = std::make_unique<animatronic_render>(
        *foxy_, ResourceManager::Instance().getTexture("foxy.png"), sf::Vector2f(490.f, 300.f)
    );

    auto chica_ = std::make_unique<chica>();
    auto chica_render_ = std::make_unique<animatronic_render>(
        *chica_, ResourceManager::Instance().getTexture("chica.png"), sf::Vector2f(600.f, 600.f)
    );

    auto nightmare_ = std::make_unique<nightmare>();
    auto nightmare_render_ = std::make_unique<animatronic_render>(
        *nightmare_, ResourceManager::Instance().getTexture("nightmare.png"), sf::Vector2f(600.f, 600.f), 3
    );

    enemies.emplace_back(std::move(freddy_), std::move(freddy_render_), 0);
    enemies.emplace_back(std::move(foxy_), std::move(foxy_render_), 1);
    enemies.emplace_back(std::move(chica_), std::move(chica_render_), 2);
    enemies.emplace_back(std::move(nightmare_), std::move(nightmare_render_), 3);
}