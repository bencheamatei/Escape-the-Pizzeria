//
// Created by matei on 5/12/2026.
//

#ifndef OOP_MENU_SCENE_H
#define OOP_MENU_SCENE_H

#include "scene.h"
#include <SFML/Graphics.hpp>
#include <vector>

class menu_scene : public scene {
private:
    sf::Sprite background;
    sf::RectangleShape overlay;
    sf::Text title;
    sf::Text subtitle;

    struct menu_item {
        sf::Text label;
        sf::RectangleShape box;
    };

    std::vector<menu_item> v;
    int curr_index=0;

    float blink_timer=0.0f;
    bool show_cursor=true;

    void on_update(float) override;
    void on_render(sf::RenderTarget &) override;
    void on_event(const sf::Event &) override;

    void build_items();
    void confirm();
    void refresh();

public:
    explicit menu_scene();
};


#endif //OOP_MENU_SCENE_H