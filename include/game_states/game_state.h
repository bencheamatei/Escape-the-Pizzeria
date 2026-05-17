//
// Created by matei on 5/17/2026.
//

#ifndef OOP_GAME_STATE_H
#define OOP_GAME_STATE_H

#include <SFML/Graphics.hpp>

class game_scene;

class game_state {
public:
    virtual ~game_state()=default;

    virtual void on_enter(game_scene&) {};
    virtual void on_exit(game_scene&) {};

    virtual void on_update(game_scene& ctx, float dt)=0;
    virtual void on_render(game_scene& ctx, sf::RenderTarget& t)=0;

};


#endif //OOP_GAME_STATE_H