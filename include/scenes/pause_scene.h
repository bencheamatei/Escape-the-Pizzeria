//
// Created by matei on 5/12/2026.
//

#ifndef OOP_PAUSE_SCENE_H
#define OOP_PAUSE_SCENE_H

#include "scene.h"
#include <vector>
#include <SFML/Graphics.hpp>

class pause_scene : public scene{
private:
    sf::RectangleShape overlay;

    struct menu_item {
        sf::Text label;
        sf::RectangleShape box;
    };

    std::vector<menu_item> v;
    int curr_index = 0;

    float blink_timer=0.0f;
    bool show_cursor=true;

    void build_items();
    void refresh();
    void confirm();

    void on_update(float dt) override;
    void on_render(sf::RenderTarget& target) override;
    void on_event(const sf::Event& event) override;
public:
    explicit pause_scene();
};


#endif //OOP_PAUSE_SCENE_H