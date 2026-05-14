#include "room.h"
#include <cmath>

room::room(const std::vector<std::vector<int>>& grid, sf::Texture& tex, int t_size)
    : map_grid(grid), tileset(tex), tile_size(t_size) {}

sf::Vector2f room::get_size() const {
    if (map_grid.empty()) return {0.f, 0.f};
    return { (float)(map_grid[0].size() * tile_size), (float)(map_grid.size() * tile_size) };
}

void room::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Sprite tile_sprite(tileset);
    
    for (size_t y = 0; y < map_grid.size(); ++y) {
        for (size_t x = 0; x < map_grid[y].size(); ++x) {
            int tile_id = map_grid[y][x];
            
            tile_sprite.setPosition((float)(x * tile_size), (float)(y * tile_size));
            
            tile_sprite.setTextureRect(sf::IntRect(tile_id * tile_size, 0, tile_size, tile_size));
            
            target.draw(tile_sprite, states);
        }
    }
}

bool room::collide(sf::FloatRect bounds) const {
    int left_tile   = std::floor(bounds.left / tile_size);
    int top_tile    = std::floor(bounds.top / tile_size);

    int right_tile  = std::floor((bounds.left + bounds.width - 0.01f) / tile_size);
    int bottom_tile = std::floor((bounds.top + bounds.height - 0.01f) / tile_size);

    if (left_tile < 0 || top_tile < 0 ||
        bottom_tile >= (int)map_grid.size() || 
        right_tile >= (int)map_grid[0].size()) {
        return true;
    }

    for (int y = top_tile; y <= bottom_tile; ++y) {
        for (int x = left_tile; x <= right_tile; ++x) {
            if (map_grid[y][x] != 0) {
                return true;
            }
        }
    }
    return false;
}