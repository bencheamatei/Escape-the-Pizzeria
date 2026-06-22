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
public:
    animatronic_render(animatronic& a, sf::Texture& texture, sf::Vector2f init_pos, float scale=1.f);
    void draw(sf::RenderTarget& window);
};


#endif //OOP_ANIMATRONIC_RENDER_H