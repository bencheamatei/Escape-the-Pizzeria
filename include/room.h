//
// Created by matei on 5/12/2026.
//

#ifndef OOP_ROOM_H
#define OOP_ROOM_H

#include <SFML/Graphics.hpp>
#include <vector>

class room : public sf::Drawable {
private:
    struct wall {
        sf::FloatRect bound;
        sf::RectangleShape shape;
    };
    sf::Sprite floor;
    sf::Vector2f room_sz;
    std::vector<wall> walls;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    room();
    room(sf::Vector2f, sf::Texture&);
    void add_wall(float , float , float , float, sf::Color=sf::Color(70, 50, 35));
    bool collide(sf::FloatRect) const;
    sf::Vector2f spawn_point;
    sf::Vector2f get_size() const;
};


#endif //OOP_ROOM_H