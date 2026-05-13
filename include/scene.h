//
// Created by matei on 5/12/2026.
//

#ifndef OOP_SCENE_H
#define OOP_SCENE_H

#include <SFML/Graphics.hpp>
class game;

class scene {
protected:
    game& _game;
    virtual void on_update(float)=0;
    virtual void on_render(sf::RenderTarget&)=0;
    virtual void on_event(const sf::Event&)=0;
public:
    explicit scene(game&);
    virtual ~scene();
    void update(float);
    void render(sf::RenderTarget&);
    void event_handler(const sf::Event&);
};


#endif //OOP_SCENE_H