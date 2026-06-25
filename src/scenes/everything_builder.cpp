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
#include "random_selector.h"

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
    random_selector<sf::Vector2f> rd_freddy;
    rd_freddy.add({400.f,200.f});
    rd_freddy.add({400.f,400.f});

    auto freddy_ = std::make_unique<freddy>();
    auto freddy_render_ = std::make_unique<animatronic_render>(
        *freddy_, ResourceManager::Instance().getTexture("freddy.png"), rd_freddy.get_rnd()
    );

    random_selector<sf::Vector2f> rd_foxy;
    rd_foxy.add({450.f,700.f});
    rd_foxy.add({450.f,1500.f});
    rd_foxy.add({450.f,1600.f});

    auto foxy1_ = std::make_unique<foxy>();
    auto foxy_render1_ = std::make_unique<animatronic_render>(
        *foxy1_, ResourceManager::Instance().getTexture("foxy.png"), rd_foxy.get_rnd()
    );

    auto foxy2_ = std::make_unique<foxy>();
    auto foxy_render2_ = std::make_unique<animatronic_render>(
        *foxy2_, ResourceManager::Instance().getTexture("foxy.png"), rd_foxy.get_rnd()
    );

    random_selector<sf::Vector2f> rd_chica;
    rd_chica.add({600.f,600.f});
    rd_chica.add({500.f,500.f});
    rd_chica.add({450.f,400.f});
    rd_chica.add({550.f,400.f});

    auto chica1_ = std::make_unique<chica>();
    auto chica_render1_ = std::make_unique<animatronic_render>(
        *chica1_, ResourceManager::Instance().getTexture("chica.png"), rd_chica.get_rnd()
    );

    auto chica2_ = std::make_unique<chica>();
    auto chica_render2_ = std::make_unique<animatronic_render>(
        *chica2_, ResourceManager::Instance().getTexture("chica.png"), rd_chica.get_rnd()
    );

    auto chica3_ = std::make_unique<chica>();
    auto chica_render3_ = std::make_unique<animatronic_render>(
        *chica3_, ResourceManager::Instance().getTexture("chica.png"), rd_chica.get_rnd()
    );

    auto nightmare_ = std::make_unique<nightmare>();
    auto nightmare_render_ = std::make_unique<animatronic_render>(
        *nightmare_, ResourceManager::Instance().getTexture("nightmare.png"), sf::Vector2f(600.f, 600.f), 3
    );

    enemies.emplace_back(std::move(freddy_), std::move(freddy_render_), 0);
    enemies.emplace_back(std::move(foxy1_), std::move(foxy_render1_), 1);
    enemies.emplace_back(std::move(foxy2_), std::move(foxy_render2_), 1);
    enemies.emplace_back(std::move(chica1_), std::move(chica_render1_), 2);
    enemies.emplace_back(std::move(chica2_), std::move(chica_render2_), 2);
    enemies.emplace_back(std::move(chica3_), std::move(chica_render3_), 2);
    enemies.emplace_back(std::move(nightmare_), std::move(nightmare_render_), 3);
}