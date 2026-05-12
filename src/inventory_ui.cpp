//
// Created by matei on 5/12/2026.
//

#include "../include/inventory_ui.h"
#include "exceptions.h"
#include "../ResourceManager.hpp"

inventory_ui::inventory_ui(const player &p, sf::Font &font) : player_data(p), font(font) {}

void inventory_ui::draw(sf::RenderWindow &window) const {
    const inventory &inv=player_data.get_inventory();
    int capacity=inv.get_capacity();

    float totalW=capacity*SLOT_SIZE+(capacity-1)*SLOT_GAP;
    float startX=(window.getView().getSize().x-totalW)/2.f;
    float y=window.getView().getSize().y-SLOT_SIZE-BOTTOM_PAD;

    sf::RectangleShape bg({totalW + 20.f, SLOT_SIZE + 20.f});
    bg.setFillColor(sf::Color(10, 8, 20, 190));
    bg.setPosition(startX - 10.f, y - 10.f);
    window.draw(bg);

    for (int i=0; i<capacity; i++) {
        float x=startX+i*(SLOT_SIZE+SLOT_GAP);
        draw_slot(window, i, {x,y}, i==slot_index);
    }

    sf::Text hint;
    hint.setFont(font);
    hint.setString("Q/E: left/right   F: eat   C: craft pizza");
    hint.setCharacterSize(10);
    hint.setFillColor(sf::Color(120, 110, 140));
    hint.setPosition(startX, y + SLOT_SIZE + 4.f);
    window.draw(hint);

}

void inventory_ui::draw_slot(sf::RenderWindow &window, int idx, sf::Vector2f pos, bool selectat) const {
    const inventory &inv=player_data.get_inventory();
    inventorySlot slot=inv.get_item_at_index(idx);

    sf::RectangleShape box({SLOT_SIZE, SLOT_SIZE});
    box.setPosition(pos);
    box.setFillColor(selectat
        ? sf::Color(65, 52, 88, 230)
        : sf::Color(22, 18, 32, 210));
    box.setOutlineThickness(selectat ? 2.f : 1.f);
    box.setOutlineColor(selectat
        ? sf::Color(255, 200, 60)
        : sf::Color(70, 58, 90));
    window.draw(box);

    if (!slot.isEmpty()) {
        sf::Sprite icon;
        std::string tex_name = get_texture_name(slot);
        const sf::Texture& tex = ResourceManager::Instance().getTexture(tex_name);
        icon.setTexture(tex);
        sf::Vector2u texSize = tex.getSize();
        float targetWH = SLOT_SIZE - 16.f;
        icon.setScale(targetWH / texSize.x, targetWH / texSize.y);

        icon.setPosition(pos.x + 8.f, pos.y + 8.f);
        window.draw(icon);

        if (slot.getCntItem() > 1) {
            sf::Text cnt;
            cnt.setFont(font);
            cnt.setString("x" + std::to_string(slot.getCntItem()));
            cnt.setCharacterSize(10);
            cnt.setFillColor(sf::Color(255, 220, 80));
            cnt.setPosition(pos.x + SLOT_SIZE - 18.f, pos.y + 2.f);
            window.draw(cnt);
        }
    }

    sf::Text num;
    num.setFont(font);
    num.setString(std::to_string(idx + 1));
    num.setCharacterSize(9);
    num.setFillColor(sf::Color(90, 78, 110));
    num.setPosition(pos.x + 3.f, pos.y + SLOT_SIZE - 14.f);
    window.draw(num);
}

void inventory_ui::event_handler(const sf::Event& event, player& p) {
    if (event.type != sf::Event::KeyPressed) return;
    int cap = p.get_inventory().get_capacity();

    switch (event.key.code) {
        case sf::Keyboard::Q:
            slot_index = (slot_index - 1 + cap) % cap;
            break;
        case sf::Keyboard::E:
            slot_index = (slot_index + 1) % cap;
            break;
        case sf::Keyboard::F:
            try { p.eat_item(slot_index); }
            catch (const player_exception&)   {}
            catch (const inventory_exception&) {}
            break;
        case sf::Keyboard::C:
            try { p.craftPizza(); }
            catch (const craft_exception&) {}
            break;
        case sf::Keyboard::X:
            try { p.drop_item(slot_index); }
            catch (const inventory_exception&) {}
            break;
        default: break;
    }
}

std::string inventory_ui::get_texture_name(const inventorySlot &slot) const {
    if (slot.isEmpty()) {
        return "";
    }

    if (slot.is_pizza()) {
        return "pizza.png";
    }

    if (slot.is_dough()) {
        return "dough.png";
    }

    std::string aux_name=slot.getItem()->get_nume();
    if (aux_name=="pepperoni") {
        return "pepperoni.png";
    }

    if (aux_name=="mushroom") {
        return "mushroom.png";
    }

    return "generic.png";
}
