//
// Created by matei on 5/12/2026.
//

#ifndef OOP_INVENTORY_UI_H
#define OOP_INVENTORY_UI_H

#include <SFML/Graphics.hpp>
#include "player.h"

class inventory_ui {
private:
    const player& player_data;
    sf::Font& font;
    int slot_index=0;

    static constexpr float SLOT_SIZE  = 52.f;
    static constexpr float SLOT_GAP   =  6.f;
    static constexpr float BOTTOM_PAD = 14.f;

    void draw_slot(sf::RenderWindow&,int idx,sf::Vector2f,bool) const;
    sf::Color slot_item_color(const inventorySlot& s) const;
    std::string slot_item_label(const inventorySlot& s) const;
public:
    inventory_ui(const player&, sf::Font&);
    void draw(sf::RenderWindow&) const;
    void event_handler(const sf::Event&,player&);
    int get_slot() const;
};


#endif //OOP_INVENTORY_UI_H