//
// Created by matei pe 5/12/2026.
//

#include "../include/game.h"
#include "../ResourceManager.hpp"
#include "../include/scenes/menu_scene.h"
#include <cmath>

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
    sm.add_scene(std::make_unique<menu_scene>());
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        if (dt > 0.05f) {
            dt = 0.05f;
        }

        sm.apply_lazy();
        process_event();
        sm.apply_lazy();

        sm.update(dt);

        window.clear(sf::Color::Black);
        sm.render(window);
        window.display();
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

        sm.process_event(event);
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

game &game::get_instance() {
    static game g;
    return g;
}

scene_manager &game::get_scene_manager() {
    return sm;
}
