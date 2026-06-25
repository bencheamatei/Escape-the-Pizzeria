//
// Created by matei on 6/22/2026.
//

#include "../../include/scenes/scene_manager.h"

#include "scenes/menu_scene.h"

void scene_manager::add_scene(std::unique_ptr<scene> scene) {
    to_push = std::move(scene);
}

void scene_manager::rm_scene() {
    to_pop++;
}

void scene_manager::apply_lazy() {
    while (to_pop > 0 && !d.empty()) {
        d.pop();
        to_pop--;
    }

    if (to_push) {
        d.push(std::move(to_push));
        to_push = nullptr;
    }
}

void scene_manager::update(float dt) {
    if (!d.empty()) {
        d.top()->update(dt);
    }
}

void scene_manager::render(sf::RenderWindow& window) {
    if (!d.empty()) {
        d.top()->render(window);
    }
}

void scene_manager::process_event(const sf::Event& event) {
    if (!d.empty()) {
        d.top()->event_handler(event);
    }
}

void scene_manager::clear() {
    to_pop=0;
    to_push=nullptr;
    while (!d.empty()) {
        d.pop();
    }
    add_scene(std::make_unique<menu_scene>(false));
}
