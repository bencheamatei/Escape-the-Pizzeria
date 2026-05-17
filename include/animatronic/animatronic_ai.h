//
// Created by matei on 5/17/2026.
//

#ifndef OOP_ANIMATRONIC_AI_H
#define OOP_ANIMATRONIC_AI_H

#include <SFML/Graphics.hpp>
#include <vector>

class room;

class animatronic_ai {
private:
    static int get_index(int,int,int);
    static bool in(int,int,int,int);
public:
    static std::vector<sf::Vector2i> find(const room& r, sf::Vector2i st, sf::Vector2i target);
};


#endif //OOP_ANIMATRONIC_AI_H