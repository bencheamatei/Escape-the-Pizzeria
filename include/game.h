//
// Created by matei on 5/12/2026.
//

#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>
#include "scene.h"


class game {
private:
    sf::RenderWindow window;
    sf::Clock clock;
    std::stack<std::unique_ptr<scene> > d;
    int to_pop=0;
    std::unique_ptr<scene> to_push=nullptr;
    void update(float);
    void render();
    void apply_lazy();
    void process_event();
    static bool debug_mode;

    sf::RenderTexture render_tex;
    sf::Sprite render_sprite;
    bool is_fullscreen = false;

public:
    game();
    void run();
    void add_scene(std::unique_ptr<scene>);
    void rm_scene();
    sf::RenderWindow& get_window();
    static void toggle_debug_mode();
    static bool is_debug_mode();

    void rebuild_window(bool fullscreen);

    static constexpr unsigned BASE_W = 960;
    static constexpr unsigned BASE_H = 640;

    void toggle_fullscreen();
};


#endif //OOP_GAME_H