//
// Created by matei on 5/17/2026.
//

#ifndef OOP_RESPAWN_STATE_H
#define OOP_RESPAWN_STATE_H
#include "game_state.h"


class respawn_state : public game_state{
private:
    void on_render(game_scene &ctx, sf::RenderTarget &t) override;
    void on_update(game_scene &ctx, float dt) override;
    void on_enter(game_scene &) override;
    [[nodiscard]] std::string get_name() const override;
public:
    float timer=0.f;
    float blink_timer=0.f;
    bool  visible=true;
    static constexpr float duration=2.5f;
    static constexpr float blink_duration=0.12f;
};


#endif //OOP_RESPAWN_STATE_H