//
// Created by matei on 5/17/2026.
//

#ifndef OOP_DEATH_STATE_H
#define OOP_DEATH_STATE_H
#include "game_state.h"
#include <string>

class death_state : public game_state {
private:
    float timer=0.f;
    static constexpr float duration=5.5f; // nu facem glume <3
public:
    void on_render(game_scene &ctx, sf::RenderTarget &t) override;
    void on_update(game_scene &ctx, float dt) override;
    void on_enter(game_scene &) override;
};


#endif //OOP_DEATH_STATE_H