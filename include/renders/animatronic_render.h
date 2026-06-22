//
// Created by matei on 5/14/2026.
//

#ifndef OOP_ANIMATRONIC_RENDER_H
#define OOP_ANIMATRONIC_RENDER_H

#include "../animatronic/animatronic.h"
#include <SFML/Graphics.hpp>
#include "../room.h"

class animatronic_render {
private:
    animatronic& data;
    sf::Sprite sprite;
    sf::Vector2f pos;
    float BOX_W = 18.f;
    float BOX_H = 24.f;

    void resolve_collision(sf::Vector2f delta, const room& room);
    bool overlap_solid(sf::FloatRect rect, const room& room) const;

    std::vector<sf::Vector2i> path;
    float path_timer=0.f;
    static constexpr float path_refresh=0.3f;
    void recalc_path(const room& r, sf::Vector2f target_world);
    bool follow_path(float dt, const room& r);

public:
    animatronic_render(animatronic& a, sf::Texture& texture, sf::Vector2f init_pos, float scale=1.f);

    void update(float dt, const room& room, sf::Vector2f target_pos);
    void draw(sf::RenderTarget& window) const;

    sf::FloatRect get_bounds() const;
    sf::Vector2f get_position() const;
};


#endif //OOP_ANIMATRONIC_RENDER_H