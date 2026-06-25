#include "room.h"
#include <cmath>
#include <fstream>
#include "exceptions.h"
#include <nlohmann/json.hpp>

#include "inventorySlot.h"
#include "player.h"
using json = nlohmann::json;

room::room(const std::vector<std::vector<int> > &grid, sf::Texture &tex, int t_size)
    : map_grid(grid), tileset(&tex), tile_size(t_size) {
    build_geometry();
}

void room::build_geometry() {
    if (map_grid.empty() || map_grid[0].empty() || !tileset) return;

    vertices_.setPrimitiveType(sf::Quads);

    int width = (int)map_grid[0].size();
    int height = (int)map_grid.size();

    int columns = tileset->getSize().x / tile_size;

    vertices_.resize(width * height * 4);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int tile_id = map_grid[y][x];

            sf::Vertex* quad = &vertices_[(x + y * width) * 4];

            if (tile_id < 0) {
                quad[0].position = quad[1].position = quad[2].position = quad[3].position = sf::Vector2f(0.f, 0.f);
                continue;
            }

            quad[0].position = sf::Vector2f((float)(x * tile_size),       (float)(y * tile_size));
            quad[1].position = sf::Vector2f((float)((x + 1) * tile_size), (float)(y * tile_size));
            quad[2].position = sf::Vector2f((float)((x + 1) * tile_size), (float)((y + 1) * tile_size));
            quad[3].position = sf::Vector2f((float)(x * tile_size),       (float)((y + 1) * tile_size));

            int texture_index = tile_id;

            int tu = texture_index % columns;
            int tv = texture_index / columns;

            quad[0].texCoords = sf::Vector2f((float)(tu * tile_size),       (float)(tv * tile_size));
            quad[1].texCoords = sf::Vector2f((float)((tu + 1) * tile_size), (float)(tv * tile_size));
            quad[2].texCoords = sf::Vector2f((float)((tu + 1) * tile_size), (float)((tv + 1) * tile_size));
            quad[3].texCoords = sf::Vector2f((float)(tu * tile_size),       (float)((tv + 1) * tile_size));
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

    states.texture = nullptr;
    for (const auto& gi : ground_items) {
        target.draw(gi.sprite, states);
    }
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
            if (map_grid[y][x] == WALL) {
                return true;
            }
        }
    }
    return false;
}

const door *room::check_door(sf::Vector2f pos) const {
    for (const auto& d : doors) {
        if (d.bounds.contains(pos))
            return &d;
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
    sf::FloatRect bounds(
        (float)(x * tile_size),
        (float)(y * tile_size),
        (float)tile_size,
        (float)tile_size);
    doors.push_back({bounds, care_camera, target_spawn});
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
    return map_grid[y][x] == WALL;
}

room room::from_tmj(const std::string &filepath, sf::Texture &tileset) {
    std::ifstream fin(filepath);
    if (!fin.is_open()) {
        throw game_exception("nu a mers sa dau fetch la harta");
    }

    json j=json::parse(fin);
    int width=j["width"];
    int height=j["height"];
    int tileW=j["tilewidth"];

    int first_gid = 1;
    if (j.contains("tilesets") && !j["tilesets"].empty()) {
        first_gid = j["tilesets"][0]["firstgid"];
    }

    std::vector<std::vector<int>> grid(
        height, std::vector<int>(width, -1));  // -1 = empty

    for (const auto& layer : j["layers"]) {
        std::string type = layer["type"];
        std::string name = layer["name"];

        if (type == "tilelayer" && (name == "Tiles" || name == "Ground")) {
            std::vector<int> data = layer["data"];
            for (int row = 0; row < height; row++)
                for (int col = 0; col < width; col++) {
                    int gid = data[row * width + col];
                    grid[row][col] = (gid == 0) ? -1 : (gid-first_gid);
                }
        }
    }

    room r(grid, tileset, tileW);
    for (const auto& layer : j["layers"]) {
        if (layer["type"] != "objectgroup") continue;

        for (const auto& obj : layer["objects"]) {
            std::string cls = obj.value("class",
                             obj.value("type", std::string("")));
            float ox = obj["x"];
            float oy = obj["y"];

            if (cls == "spawn") {
                r.spawn_point = {ox, oy};
            }
            else if (cls == "door") {
                float w = obj.value("width",  (double)tileW);
                float h = obj.value("height", (double)tileW);

                int   target_id = 0;
                float target_x  = ox;
                float target_y  = oy;

                if (obj.contains("properties")) {
                    for (const auto& prop : obj["properties"]) {
                        std::string pname = prop["name"];
                        if (pname == "target_room_id")
                            target_id = prop["value"].get<int>();
                        else if (pname == "target_x")
                            target_x = prop["value"].get<float>();
                        else if (pname == "target_y")
                            target_y = prop["value"].get<float>();
                    }
                }

                r.doors.push_back({
                    sf::FloatRect(ox, oy, w, h),
                    target_id,
                    {target_x, target_y}
                });
            }
        }
    }

    return r;
}

void room::add_ground_item(std::unique_ptr<item> new_item, sf::Vector2f pos, const sf::Texture& texture,sf::Vector2f scale) {
    ground_item gi;
    gi.ce = std::move(new_item);

    gi.sprite.setTexture(texture);
    gi.sprite.setPosition(pos);

    gi.sprite.setScale(scale);

    gi.hitbox = sf::FloatRect(pos.x, pos.y,
                              (float)texture.getSize().x * scale.x,
                              (float)texture.getSize().y * scale.y);

    ground_items.push_back(std::move(gi));
}

std::vector<std::unique_ptr<item> > room::pickup_items(sf::FloatRect player_bounds) {
    std::vector<std::unique_ptr<item>> picked_up;
    for (auto it = ground_items.begin(); it != ground_items.end();) {
        if (it->hitbox.intersects(player_bounds)) {
            picked_up.push_back(std::move(it->ce));
            it = ground_items.erase(it);
        } else {
            ++it;
        }
    }
    return picked_up;
}

void room::try_pickup_items(player& p, sf::FloatRect player_bounds) {
    for (auto it = ground_items.begin(); it != ground_items.end(); ) {
        if (it->hitbox.intersects(player_bounds)) {
            bool can_pickup = false;
            for(int i = 0; i < p.get_inventory().get_capacity(); i++) {
                if(!p.get_inventory().get_item_at_index(i).isEmpty() &&
                   p.get_inventory().get_item_at_index(i).getItem()->get_nume() == it->ce->get_nume()) {
                    can_pickup = true;
                    break;
                   }
            }

            if(!can_pickup && !p.get_inventory().isFull()) {
                can_pickup = true;
            }

            if (can_pickup) {
                p.addItem(inventorySlot(*it->ce, 1));
                it = ground_items.erase(it);
                continue;
            }
        }
        ++it;
    }
}