//
// Created by matei on 5/12/2026.
//

#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>
#include "Scene.h"


class game {
private:
    sf::RenderWindow window;
    sf::Clock clock;
    std::stack<std::unique_ptr<scene> > d;
    bool to_pop=false;
    std::unique_ptr<scene> to_push=nullptr;
    void update(float);
    void render();
    void apply_lazy();
    void process_event();
public:
    game();
    void run();
    void add_scene(std::unique_ptr<scene>);
    void rm_scene();
    sf::RenderWindow& get_window();
};


#endif //OOP_GAME_H