//
// Created by matei pe 5/12/2026.
//

#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>
#include "scenes/scene.h"
#include <scenes/scene_manager.h>

class game {
private:
    sf::RenderWindow window;
    sf::Clock clock;

    void process_event();

    static bool debug_mode;
    bool is_fullscreen = false;
    scene_manager sm;

    sf::RenderTexture render_texture_;
    sf::Sprite render_sprite_;

    game();
public:

    static game& get_instance();
    game(const game&)=delete;
    game operator=(const game&)=delete;

    void run();
    [[nodiscard]] scene_manager& get_scene_manager();

    sf::RenderWindow& get_window();
    void toggle_debug_mode();
    bool is_debug_mode();

    void rebuild_window(bool fullscreen);
    void toggle_fullscreen();

    static constexpr unsigned BASE_W = 960;
    static constexpr unsigned BASE_H = 640;
};

#endif //OOP_GAME_H