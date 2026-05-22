//
// Created by matei pe 5/12/2026.
//

#include "../include/game.h"
#include "../ResourceManager.hpp"
#include "../include/scenes/menu_scene.h"

game::game() {
    rebuild_window(false);
    ResourceManager::Instance();
}

void game::rebuild_window(bool fullscreen) {
    is_fullscreen = fullscreen;
    if (fullscreen) {
        window.create(sf::VideoMode::getDesktopMode(), "Escape the Pizzeria", sf::Style::Fullscreen);
    } else {
        window.create(sf::VideoMode(BASE_W, BASE_H), "Escape the Pizzeria",
                      sf::Style::Close | sf::Style::Titlebar);
    }
    window.setFramerateLimit(60);
}

void game::toggle_fullscreen() {
    rebuild_window(!is_fullscreen);
}

void game::run() {
    add_scene(std::make_unique<menu_scene>(*this));
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        if (dt > 0.05f) {
            dt = 0.05f;
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
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::F11) {
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
    // Curățăm ecranul cu negru (acestea vor deveni marginile negre la fullscreen)
    window.clear(sf::Color::Black);

    // Desenăm direct pe fereastră ce ne zice scena curentă
    if (!d.empty()) {
        d.top()->render(window);
    }

    window.display();
}

void game::add_scene(std::unique_ptr<scene> scene) {
    to_push = std::move(scene);
}

void game::rm_scene() {
    to_pop++;
}

void game::apply_lazy() {
    while (to_pop > 0 && !d.empty()) {
        d.pop();
        to_pop--;
    }

    if (to_push) {
        d.push(std::move(to_push));
        to_push = nullptr;
    }
}

sf::RenderWindow &game::get_window() {
    return window;
}

bool game::debug_mode = false;

bool game::is_debug_mode() {
    return debug_mode;
}

void game::toggle_debug_mode() {
    debug_mode = !debug_mode;
}