#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class room : public sf::Drawable {
private:
    std::vector<std::vector<int>> map_grid;
    
    sf::Texture& tileset;
    
    int tile_size=32;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    sf::Vector2f spawn_point;

    room(const std::vector<std::vector<int>>& grid, sf::Texture& tex, int t_size);

    bool collide(sf::FloatRect bounds) const;
    
    sf::Vector2f get_size() const;
};