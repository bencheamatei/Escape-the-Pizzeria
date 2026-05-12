//
// Created by matei on 5/12/2026.
//

#include "../include/scene.h"
#include <SFML/Graphics.hpp>

class game;

scene::scene(game &_game) : _game(_game) {}
scene::~scene() = default;

void scene::update(float dt) {
    on_update(dt);
}

void scene::render(sf::RenderWindow &window) {
    on_render(window);
}

void scene::event_handler(const sf::Event &event) {
    on_event(event);
}
