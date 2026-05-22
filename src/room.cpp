#include "room.h"
#include <cmath>

room::room(const std::vector<std::vector<int> > &grid, sf::Texture &tex, int t_size)
    : map_grid(grid), tileset(&tex), tile_size(t_size) {

    build_geometry();
}

void room::build_geometry() {
    if (map_grid.empty() || map_grid[0].empty()) return;

    vertices_.setPrimitiveType(sf::Quads);

    int width = (int)map_grid[0].size();
    int height = (int)map_grid.size();

    vertices_.resize(width * height * 4);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int tile_id = map_grid[y][x];

            sf::Vertex* quad = &vertices_[(x + y * width) * 4];

            quad[0].position = sf::Vector2f((float)(x * tile_size),       (float)(y * tile_size));
            quad[1].position = sf::Vector2f((float)((x + 1) * tile_size), (float)(y * tile_size));
            quad[2].position = sf::Vector2f((float)((x + 1) * tile_size), (float)((y + 1) * tile_size));
            quad[3].position = sf::Vector2f((float)(x * tile_size),       (float)((y + 1) * tile_size));

            quad[0].texCoords = sf::Vector2f((float)(tile_id * tile_size),       0.f);
            quad[1].texCoords = sf::Vector2f((float)((tile_id + 1) * tile_size), 0.f);
            quad[2].texCoords = sf::Vector2f((float)((tile_id + 1) * tile_size), (float)tile_size);
            quad[3].texCoords = sf::Vector2f((float)(tile_id * tile_size),       (float)tile_size);
        }
    }
}

sf::Vector2f room::get_size() const {
    if (map_grid.empty()) return {0.f, 0.f};
    return {(float) (map_grid[0].size() * tile_size), (float) (map_grid.size() * tile_size)};
}

void room::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (!tileset)
        return;
    states.texture = tileset;
    target.draw(vertices_, states);
}

bool room::collide(sf::FloatRect bounds) const {
    int left_tile = std::floor(bounds.left / tile_size);
    int top_tile = std::floor(bounds.top / tile_size);

    int right_tile = std::floor((bounds.left + bounds.width - 0.01f) / tile_size);
    int bottom_tile = std::floor((bounds.top + bounds.height - 0.01f) / tile_size);

    if (left_tile < 0 || top_tile < 0 ||
        bottom_tile >= (int) map_grid.size() ||
        right_tile >= (int) map_grid[0].size()) {
        return true;
    }

    for (int y = top_tile; y <= bottom_tile; ++y) {
        for (int x = left_tile; x <= right_tile; ++x) {
            if (map_grid[y][x] == 1) {
                return true;
            }
        }
    }
    return false;
}

const door *room::check_door(sf::Vector2f pos) const {
    int gx = (int) (pos.x / tile_size);
    int gy = (int) (pos.y / tile_size);

    for (const auto &door: doors) {
        if (door.lin == gx && door.col == gy) {
            return &door;
        }
    }
    return nullptr;
}

// int room::get_tile(int x, int y) const {
//     if (x<0 || y<0 || x>=(int)map_grid.size() || y>=(int)map_grid[x].size()) {
//         return 1;
//     }
//     return map_grid[x][y];
// }

void room::add_door(int x, int y, int care_camera, sf::Vector2f target_spawn) {
    doors.push_back({x, y, care_camera, target_spawn});
}

sf::Vector2i room::get_grid_size() const {
    if (map_grid.empty())
        return {0, 0};
    return {(int) map_grid[0].size(), (int) map_grid.size()};
}

bool room::is_solid(int x, int y) const {
    if (x < 0 || x >= (int) map_grid[0].size())
        return true;
    if (y < 0 || y >= (int) map_grid.size())
        return true;
    return map_grid[y][x] == 1;
}