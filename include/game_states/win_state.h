//
// Created by matei on 6/25/2026.
//

#ifndef OOP_WIN_STATE_H
#define OOP_WIN_STATE_H

#include "game_states/game_state.h"

class win_state : public game_state {
private:
    float timer=0.f;
    static constexpr float duration=6.f; // nu facem glume <3
public:
    void on_render(game_scene &ctx, sf::RenderTarget &t) override;
    void on_update(game_scene &ctx, float dt) override;
    void on_enter(game_scene &) override;
};


#endif //OOP_WIN_STATE_H