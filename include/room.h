#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <vector>
#include "items/item.h"

/*
*Run at the door
Anyone home?
Have I lost it all?
Struck me like a chord
I'm an ugly boy
Holdin' out the night
Lonely after light
You begged me not to go
Sinkin' like a stone
Use me like an oar
And get yourself to shore
 */


struct door {
    sf::FloatRect bounds;
    int room_id;
    sf::Vector2f spawn;
};

struct ground_item {
    std::unique_ptr<item> ce;
    sf::FloatRect hitbox;
    sf::Sprite sprite;
};

class room : public sf::Drawable {
private:
    std::vector<std::vector<int>> map_grid;
    sf::Texture* tileset=nullptr;
    int tile_size=32;
    std::vector<door> doors;

    sf::VertexArray vertices_;
    void build_geometry();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    static constexpr int WALL=0;
    static constexpr int FREE=3;
    static constexpr int DOOR=1;

    std::vector<ground_item> ground_items;

public:
    sf::Vector2f spawn_point;

    room()=default;
    room(const std::vector<std::vector<int>>& grid, sf::Texture& tex, int t_size);

    [[nodiscard]] bool collide(sf::FloatRect bounds) const;
    [[nodiscard]] sf::Vector2f get_size() const;

    // [[nodiscard]] int get_tile(int x, int y) const;
    void add_door(int x,int y,int care_camera, sf::Vector2f target_spawn);
    [[nodiscard]] const door* check_door(sf::Vector2f pos) const;

    [[nodiscard]] sf::Vector2i get_grid_size() const;
    [[nodiscard]] bool is_solid(int x,int y) const;

    static room from_tmj(const std::string& filepath,sf::Texture& tileset);

    void add_ground_item(std::unique_ptr<item> new_item, sf::Vector2f pos, const sf::Texture& texture,sf::Vector2f scale = sf::Vector2f(1.f, 1.f));
    std::vector<std::unique_ptr<item>> pickup_items(sf::FloatRect player_bounds);

    void try_pickup_items(player& p, sf::FloatRect player_bounds);
};