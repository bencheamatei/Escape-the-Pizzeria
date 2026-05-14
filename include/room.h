#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

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
    int lin,col;
    int room_id;
    sf::Vector2f spawn;
};

class room : public sf::Drawable {
private:
    std::vector<std::vector<int>> map_grid;
    sf::Texture* tileset=nullptr;
    int tile_size=32;
    std::vector<door> doors;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    sf::Vector2f spawn_point;

    room()=default;
    room(const std::vector<std::vector<int>>& grid, sf::Texture& tex, int t_size);

    [[nodiscard]] bool collide(sf::FloatRect bounds) const;
    [[nodiscard]] sf::Vector2f get_size() const;

    // [[nodiscard]] int get_tile(int x, int y) const;
    void add_door(int x,int y,int care_camera, sf::Vector2f target_spawn);
    [[nodiscard]] const door* check_door(sf::Vector2f pos) const;
};