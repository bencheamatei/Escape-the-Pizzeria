//
// Created by matei on 5/12/2026.
//

#include "../include/menu_scene.h"
#include "game.h"
#include "../ResourceManager.hpp"
#include "game_scene.h"

menu_scene::menu_scene(game &game) : scene(game) {
    auto& res_man=ResourceManager::Instance();
    auto& texture=res_man.getTexture("podea-fin.png");
    auto& font=res_man.getFont("FiraSans-Regular.ttf");

    background.setTexture(texture);
    sf::Vector2u ts = texture.getSize();
    background.setScale(960.f / ts.x, 640.f / ts.y);

    overlay.setSize({960.f, 640.f});
    overlay.setFillColor(sf::Color(8, 6, 16, 210));

    title.setFont(font);
    title.setString("Escape the Pizzeria");
    title.setCharacterSize(80);
    title.setFillColor(sf::Color(215, 55, 45));
    title.setStyle(sf::Text::Bold);
    sf::FloatRect tb = title.getLocalBounds();
    title.setOrigin(tb.width / 2.f, tb.height / 2.f);
    title.setPosition(480.f, 185.f);

    subtitle.setFont(font);
    subtitle.setString("A FNAF-inspired survival explorer");
    subtitle.setCharacterSize(18);
    subtitle.setFillColor(sf::Color(150, 130, 170));
    sf::FloatRect sb = subtitle.getLocalBounds();
    subtitle.setOrigin(sb.width / 2.f, 0.f);
    subtitle.setPosition(480.f, 270.f);

    build_items();
    refresh();
}

void menu_scene::build_items() {
    auto& font = ResourceManager::Instance().getFont("FiraSans-Regular.ttf");
    const float startY = 350.f;
    const float gap    = 62.f;

    int i=0;
    for (const auto &label:{"Start", "Quit"}) {
        menu_item item;
        item.label.setFont(font);
        item.label.setString(label);
        item.label.setCharacterSize(28);

        sf::FloatRect b = item.label.getLocalBounds();
        item.label.setOrigin(b.width / 2.f, b.height / 2.f);
        item.label.setPosition(480.f, startY + i * gap);

        item.box.setSize({b.width + 48.f, 46.f});
        item.box.setOrigin(item.box.getSize() / 2.f);
        item.box.setPosition(480.f, startY + i * gap + 4.f);
        item.box.setOutlineThickness(1.f);

        v.push_back(std::move(item));
        i++;
    }
}

void menu_scene::refresh() {
    for (int i = 0; i < (int)v.size(); i++) {
        bool sel = (i == curr_index);
        v[i].label.setFillColor(
            sel ? sf::Color(255, 215, 70) : sf::Color(200, 190, 220));
        v[i].box.setFillColor(
            sel ? sf::Color(55, 44, 75, 200) : sf::Color::Transparent);
        v[i].box.setOutlineColor(
            sel ? sf::Color(255, 200, 55) : sf::Color(70, 58, 90));
    }
}

void menu_scene::confirm() {
    if (curr_index == 0)
        _game.add_scene(std::make_unique<game_scene>(_game));
    else
        _game.get_window().close();
}

void menu_scene::on_update(float dt) {
    blink_timer+=dt;
    if (blink_timer>=0.45f) {
        blink_timer=0.0f;
        show_cursor=!show_cursor;
    }
}

void menu_scene::on_render(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(overlay);
    window.draw(title);
    window.draw(subtitle);

    for (auto& item : v) {
        window.draw(item.box);
        window.draw(item.label);
    }

    // blinking arrow cursor
    if (show_cursor && !v.empty()) {
        sf::ConvexShape arrow(3);
        float y = v[curr_index].label.getPosition().y;
        arrow.setPoint(0, {388.f, y - 10.f});
        arrow.setPoint(1, {388.f, y + 10.f});
        arrow.setPoint(2, {404.f, y});
        arrow.setFillColor(sf::Color(255, 210, 60));
        window.draw(arrow);
    }
}

void menu_scene::on_event(const sf::Event& event) {
    if (event.type != sf::Event::KeyPressed) return;
    switch (event.key.code) {
        case sf::Keyboard::W:
        case sf::Keyboard::Up:
            curr_index =
                (curr_index - 1 + (int)v.size()) % (int)v.size();
            refresh();
            break;
        case sf::Keyboard::S:
        case sf::Keyboard::Down:
            curr_index = (curr_index + 1) % (int)v.size();
            refresh();
            break;
        case sf::Keyboard::Return:
        case sf::Keyboard::Space:
            confirm();
            break;
        case sf::Keyboard::Escape:
            _game.get_window().close();
            break;
        default: break;
    }
}




