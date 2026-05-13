//
// Created by matei on 5/12/2026.
//

#include "../include/game.h"
#include "../ResourceManager.hpp"
#include "menu_scene.h"
#include <cmath>

game::game() {
    rebuild_window(false);
    render_tex.create(BASE_W,BASE_H);
    render_sprite.setTexture(render_tex.getTexture());
    render_tex.setSmooth(true);
    ResourceManager::Instance();
}


void game::rebuild_window(bool fullscreen) {
    is_fullscreen=fullscreen;
    if (fullscreen) {
        window.create(sf::VideoMode::getDesktopMode(), "Escape the Pizzeria", sf::Style::Fullscreen);
    }
    else {
        window.create(sf::VideoMode(BASE_W, BASE_H), "Escape the Pizzeria",
            sf::Style::Close|sf::Style::Titlebar);
    }
    window.setFramerateLimit(60);
}

void game::toggle_fullscreen() {
    rebuild_window(!is_fullscreen);
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

        if (event.type==sf::Event::KeyPressed) {
            if (event.key.code==sf::Keyboard::F11) {
                toggle_fullscreen();
            }
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
    render_tex.clear(sf::Color(12, 10, 18));
    if (!d.empty()) d.top()->render(render_tex);
    render_tex.display();

    float wx=(float)window.getSize().x;
    float wy=(float)window.getSize().y;
    float precise_scale=std::min(wx / BASE_W, wy / BASE_H);
    // float scale = std::max(1.0f, std::floor(precise_scale));

    render_sprite.setScale(precise_scale, precise_scale);
    render_sprite.setPosition(
        std::floor((wx - BASE_W * precise_scale) / 2.f),
        std::floor((wy - BASE_H * precise_scale) / 2.f));

    window.clear(sf::Color::Black);
    window.draw(render_sprite);
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

bool game::debug_mode=false;

bool game::is_debug_mode() {
    return debug_mode;
}

void game::toggle_debug_mode() {
    debug_mode=!debug_mode;
}


