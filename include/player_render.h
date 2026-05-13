//
// Created by matei on 5/12/2026.
//

#ifndef OOP_PLAYER_RENDER_H
#define OOP_PLAYER_RENDER_H

#include <SFML/Graphics.hpp>
#include "player.h"
#include "room.h"

class player_render {
private:
    static constexpr int FRAME_W= 64;
    static constexpr int FRAME_H=64;
    static constexpr int FRAME_COUNT=1;
    static constexpr int DIR_COUNT=1;
    static constexpr float SPEED=1000.0f;
    static constexpr float BOX_W=18.f;
    static constexpr float BOX_H=24.f;
    static constexpr float FRAME_TIME=0.13f;

    player& player_data;
    sf::Sprite sprite;
    sf::Vector2f position;
    sf::Vector2f velocity;
    bool moving = false;

    enum class Dir {
        Down=0,
        Up=1,
        Left=2,
        Right=3
    };

    Dir facing=Dir::Down;
    int frame=0;
    // float frameTimer=0.0f;

    void resolve_collision(sf::Vector2f, const room&);
    bool overlap_solid(sf::FloatRect, const room&) const;
    // void update_animation(float);
    void update_sprite_rect();

public:
    player_render(player&, sf::Texture&, sf::Vector2f);

    void handle_input();
    void update(float, const room&);
    void draw(sf::RenderWindow&) const;

    // void set_position(sf::Vector2f);
    sf::Vector2f get_position() const;
    // bool is_moving() const;
};



#endif //OOP_PLAYER_RENDER_H