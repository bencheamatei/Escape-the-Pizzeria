//
// Created by matei on 5/12/2026.
//

#include "../include/pause_scene.h"
#include "../ResourceManager.hpp"
#include "game.h"

pause_scene::pause_scene(game &game) : scene(game) {
    overlay.setSize({960.f, 640.f});
    overlay.setFillColor(sf::Color(8, 6, 18, 200));
    build_items();
    refresh();
}

void pause_scene::build_items() {
    auto& font = ResourceManager::Instance().getFont("FiraSans-Regular.ttf");
    const float startY=280.0f;
    const float gap=60.0f;
    int i = 0;
    for (const auto& label : {"Resume", "Main Menu", "Quit"}) {
        menu_item it;
        it.label.setFont(font);
        it.label.setString(label);
        it.label.setCharacterSize(28);

        sf::FloatRect b = it.label.getLocalBounds();
        it.label.setOrigin(b.width / 2.f, b.height / 2.f);
        it.label.setPosition(480.f, startY + i * gap);

        it.box.setSize({b.width + 48.f, 46.f});
        it.box.setOrigin(it.box.getSize() / 2.f);
        it.box.setPosition(480.f, startY + i * gap + 4.f);
        it.box.setOutlineThickness(1.f);

        v.push_back(std::move(it));
        i++;
    }
}

void pause_scene::refresh() {
    for (int i = 0; i < (int)v.size(); i++) {
        bool sel=(i==curr_index);
        v[i].label.setFillColor(
            sel ? sf::Color(255, 215, 70) : sf::Color(200, 190, 220));
        v[i].box.setFillColor(
            sel ? sf::Color(55, 44, 75, 200) : sf::Color::Transparent);
        v[i].box.setOutlineColor(
            sel ? sf::Color(255, 200, 55) : sf::Color(70, 58, 90));
    }
}

void pause_scene::confirm() {
    if (curr_index == 0) {
        _game.rm_scene();
    }
    else if (curr_index == 1) {
        _game.rm_scene();
        _game.rm_scene();
    }
    else {
        _game.get_window().close();
    }
}

void pause_scene::on_update(float dt) {
    blink_timer += dt;
    if (blink_timer >= 0.45f) {
        blink_timer = 0.f;
        show_cursor = !show_cursor;
    }
}


void pause_scene::on_render(sf::RenderTarget& target) {
    float windowRatio = (float)target.getSize().x / (float)target.getSize().y;
    float viewRatio = (float)game::BASE_W / (float)game::BASE_H;

    float sizeX = 1.0f, sizeY = 1.0f;
    float posX = 0.0f, posY = 0.0f;

    if (windowRatio >= viewRatio) {
        sizeX = viewRatio / windowRatio;
        posX = (1.0f - sizeX) / 2.0f;
    } else {
        sizeY = windowRatio / viewRatio;
        posY = (1.0f - sizeY) / 2.0f;
    }

    sf::View fixed({480.f, 320.f}, {960.f, 640.f}); // Assuming BASE_W=960, BASE_H=640
    fixed.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
    target.setView(fixed);

    target.draw(overlay);

    auto& font = ResourceManager::Instance().getFont("FiraSans-Regular.ttf");
    sf::Text title;
    title.setFont(font);
    title.setString("PAUSED");
    title.setCharacterSize(52);
    title.setFillColor(sf::Color(215, 55, 45));
    title.setStyle(sf::Text::Bold);
    sf::FloatRect tb = title.getLocalBounds();
    title.setOrigin(tb.width / 2.f, tb.height / 2.f);
    title.setPosition(480.f, 190.f);
    target.draw(title);

    for (auto& item : v) {
        target.draw(item.box);
        target.draw(item.label);
    }

    if (show_cursor && !v.empty()) {
        sf::ConvexShape arrow(3);
        float y = v[curr_index].label.getPosition().y;
        arrow.setPoint(0, {388.f, y - 10.f});
        arrow.setPoint(1, {388.f, y + 10.f});
        arrow.setPoint(2, {404.f, y});
        arrow.setFillColor(sf::Color(255, 210, 60));
        target.draw(arrow);
    }
}

void pause_scene::on_event(const sf::Event& event) {
    if (event.type != sf::Event::KeyPressed) return;
    switch (event.key.code) {
        case sf::Keyboard::W:
        case sf::Keyboard::Up:
            curr_index = (curr_index - 1 + (int)v.size()) % (int)v.size();
            refresh(); break;
        case sf::Keyboard::S:
        case sf::Keyboard::Down:
            curr_index = (curr_index + 1) % (int)v.size();
            refresh(); break;
        case sf::Keyboard::Return:
        case sf::Keyboard::Space:
            confirm(); break;
        case sf::Keyboard::Escape:
            _game.rm_scene();
            break;
        default: break;
    }
}