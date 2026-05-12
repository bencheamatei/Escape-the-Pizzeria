//
// Created by matei on 5/12/2026.
//

#include "../include/game.h"
#include "../ResourceManager.hpp"
#include "menu_scene.h"

game::game() : window(sf::VideoMode::getDesktopMode(), "Escape the Pizzeria", sf::Style::Fullscreen) {

    window.setFramerateLimit(60);
    ResourceManager::Instance();

    backbuffer.create(960,640);
}

void game::run() {
    add_scene(std::make_unique<menu_scene>(*this));
    while (window.isOpen()) {
        float dt=clock.restart().asSeconds();
        if (dt>0.05f) {
            dt=0.05f;
        }

        apply_lazy();
        process_event();
        apply_lazy();
        update(dt);
        render();
    }
}

void game::process_event() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type==sf::Event::Closed) {
            window.close();
        }

        if (!d.empty()) {
            d.top()->event_handler(event);
        }
    }
}

void game::update(float dt) {
    if (!d.empty()) {
        d.top()->update(dt);
    }
}

void game::render() {
    backbuffer.clear(sf::Color(12,10,18));
    if (!d.empty()) {
        d.top()->render(backbuffer);
    }
    backbuffer.display();

    backbuffer_sprite.setTexture(backbuffer.getTexture());
    sf::Vector2u winSize = window.getSize();
    float scale = std::min((float)winSize.x / 960.f, (float)winSize.y / 640.f);
    backbuffer_sprite.setScale(scale, scale);
    float posX = (winSize.x - 960.f * scale) / 2.f;
    float posY = (winSize.y - 640.f * scale) / 2.f;
    backbuffer_sprite.setPosition(posX, posY);
    window.clear(sf::Color::Black);
    window.draw(backbuffer_sprite);
    window.display();
}

void game::add_scene(std::unique_ptr<scene> scene) {
    to_push=std::move(scene);
}

void game::rm_scene() {
    to_pop=true;
}

void game::apply_lazy() {
    if (to_pop && !d.empty()) {
        d.pop();
        to_pop=false;
    }

    if (to_push) {
        d.push(std::move(to_push));
        to_push=nullptr;
    }
}

sf::RenderWindow &game::get_window() {
    return window;
}


