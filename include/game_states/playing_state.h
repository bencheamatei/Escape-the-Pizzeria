//
// Created by matei on 5/17/2026.
//

#ifndef OOP_PLAYING_STATE_H
#define OOP_PLAYING_STATE_H

#include "game_state.h"
#include <string>

class playing_state : public game_state{
private:
    float hit_flash_timer = 0.f;
    static constexpr float hir_duration=0.3f;

    sf::RenderTexture intuneric;
    bool este_intuneric;
    void draw_intuneric(game_scene& ctx, sf::RenderTarget &window);

    bool update_enemies(game_scene&, float);
    void draw_hud(game_scene&, sf::RenderTarget&);
public:
    void on_update(game_scene&, float) override;
    void on_render(game_scene&, sf::RenderTarget&) override;
    bool can_see_flying_pizzas() override;
};


#endif //OOP_PLAYING_STATE_H