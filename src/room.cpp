//
// Created by matei on 5/12/2026.
//

#include "../include/room.h"

#include <memory>
#include <vector>

room::room() = default;

room::room(sf::Vector2f room_sz, sf::Texture &texture) : room_sz(room_sz){
    floor.setTexture(texture);
    floor.setTextureRect(sf::IntRect(0, 0, (int)room_sz.x, (int)room_sz.y));
    floor.setPosition(0.f, 0.f);
    spawn_point=room_sz/2.0f;
}

void room::add_wall(float x, float y, float w, float h, sf::Color color) {
    wall wall;
    wall.bound={x,y,w,h};
    wall.shape.setPosition({x,y});
    wall.shape.setSize({w,h});
    wall.shape.setFillColor(color);
    wall.shape.setOutlineColor(sf::Color(30, 20, 12));
    wall.shape.setOutlineThickness(1.0f);
    walls.push_back(std::move(wall));
}

bool room::collide(sf::FloatRect rect) const {
    for (const auto &it:walls) {
        if (it.bound.intersects(rect)) {
            return true;
        }
    }
    return false;
}

sf::Vector2f room::get_size() const {
    return room_sz;
}

void room::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(floor, states);
    for (const auto &it:walls) {
        target.draw(it.shape,states);
    }
}
