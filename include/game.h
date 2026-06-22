//
// Created by matei pe 5/12/2026.
//

#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>
#include "scenes/scene.h"

class game {
private:
    sf::RenderWindow window;
    sf::Clock clock;
    std::stack<std::unique_ptr<scene>> d;
    int to_pop = 0;
    std::unique_ptr<scene> to_push = nullptr;

    void update(float);
    void render();
    void apply_lazy();
    void process_event();

    static bool debug_mode;
    bool is_fullscreen = false;

    sf::RenderTexture render_texture_;
    sf::Sprite render_sprite_;

public:
    game();
    void run();
    void add_scene(std::unique_ptr<scene>);
    void rm_scene();
    sf::RenderWindow& get_window();
    static void toggle_debug_mode();
    static bool is_debug_mode();

    void rebuild_window(bool fullscreen);
    void toggle_fullscreen();

    static constexpr unsigned BASE_W = 960;
    static constexpr unsigned BASE_H = 640;
};

#endif //OOP_GAME_H