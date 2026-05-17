//
// Created by matei on 5/12/2026.
//

#include "../../include/scenes/scene.h"
#include <SFML/Graphics.hpp>

class game;

scene::scene(game &_game) : _game(_game) {}
scene::~scene() = default;

void scene::update(float dt) {
    on_update(dt);
}

void scene::render(sf::RenderTarget &window) {
    on_render(window);
}

void scene::event_handler(const sf::Event &event) {
    on_event(event);
}
