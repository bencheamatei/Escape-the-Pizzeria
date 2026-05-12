//
// Created by matei on 5/12/2026.
//

#include "../../include/game.h"
#include "../ResourceManager.hpp"
#include "../../include/scenes/menu_scene.h"

game::game() : window(sf::VideoMode(960,640), "Escape the Pizzeria"
                , sf::Style::Close | sf::Style::Titlebar) {

    window.setFramerateLimit(60);
    ResourceManager::Instance();
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
    window.clear(sf::Color(12,10,18));
    if (!d.empty()) {
        d.top()->render(window);
    }
    window.display();
}

void game::add_scene(std::unique_ptr<scene> scene) {
    to_push=std::move(scene);
}

void game::rm_scene() {
    to_pop++;
}

void game::apply_lazy() {
    while (to_pop>0 && !d.empty()) {
        d.pop();
        to_pop--;
    }

    if (to_push) {
        d.push(std::move(to_push));
        to_push=nullptr;
    }
}

sf::RenderWindow &game::get_window() {
    return window;
}


