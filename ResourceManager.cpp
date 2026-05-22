//
// Created by bgd on 12/15/2024.
//

#include "ResourceManager.hpp"
#include "exceptions.h"

ResourceManager &ResourceManager::Instance() {
    static ResourceManager instance;
    return instance;
}

ResourceManager::ResourceManager() {
    loadTexture("images", "podea-fin.png");
    loadTexture("images", "billy.png");
    loadTexture("images", "dough.png");
    loadTexture("images", "generic.png");
    loadTexture("images", "pizza.png");
    loadTexture("images", "pepperoni.png");
    loadTexture("images", "mushroom.png");
    loadTexture("images", "backpack.png");
    loadTexture("images", "soda.png");
    loadTexture("images", "freddy.png");

    loadFont("fonts", "FiraSans-Regular.ttf");
    m_textures["podea-fin.png"].setRepeated(true);

    sf::Texture tileset;
    tileset.loadFromImage(generate_tileset(64));
    m_textures["tileset.png"] = tileset;
}

void ResourceManager::loadTexture(const std::string &path, const std::string &texture_name) {
    sf::Texture texture;

    if (!texture.loadFromFile(path + '/' + texture_name)) {
        throw resources_exception("Textura " + texture_name + " nu a putut fi incarcata.");
    }

    m_textures[texture_name] = texture;
}

void ResourceManager::loadFont(const std::string &path, const std::string &font_name) {
    sf::Font font;

    if (!font.loadFromFile(path + '/' + font_name)) {
        throw resources_exception("Fontul " + font_name + " nu a putut fi incarcat.");
    }

    m_fonts[font_name] = font;
}


sf::Texture &ResourceManager::getTexture(const std::string &texture_name) {
    if (m_textures.find(texture_name) == m_textures.end()) {
        throw resources_exception("Textura " + texture_name + " nu a fost gasita.");
    }

    return m_textures[texture_name];
}

sf::Font &ResourceManager::getFont(const std::string &font_name) {
    if (m_fonts.find(font_name) == m_fonts.end()) {
        throw resources_exception("Fontul " + font_name + " nu a fost gasita.");
    }

    return m_fonts[font_name];
}

sf::Image ResourceManager::generate_tileset(int ts) {
    sf::Image img;
    img.create(3 * ts, ts, sf::Color::Transparent);

    for (int x = 0; x < ts; x++)
        for (int y = 0; y < ts; y++)
            img.setPixel(x, y, sf::Color(55, 50, 70));

    for (int i = 0; i < ts; i++) {
        img.setPixel(i, 0, sf::Color(45, 40, 58));
        img.setPixel(0, i, sf::Color(45, 40, 58));
        img.setPixel(i, ts - 1, sf::Color(45, 40, 58));
        img.setPixel(ts - 1, i, sf::Color(45, 40, 58));
    }

    for (int x = ts; x < 2 * ts; x++)
        for (int y = 0; y < ts; y++)
            img.setPixel(x, y, sf::Color(90, 60, 40));

    bool offset = false;
    for (int y = 0; y < ts; y += ts / 4) {
        int bx = offset ? ts / 3 : 0;
        for (int x = ts; x < 2 * ts; x++)
            img.setPixel(x, y, sf::Color(60, 38, 22));
        for (int x = ts + bx; x < 2 * ts; x += ts / 3)
            for (int yy = y; yy < std::min(y + ts / 4, ts); yy++)
                img.setPixel(x, yy, sf::Color(60, 38, 22));
        offset = !offset;
    }

    for (int x = 2 * ts; x < 3 * ts; x++)
        for (int y = 0; y < ts; y++)
            img.setPixel(x, y, sf::Color(180, 140, 60));

    for (int i = 0; i < ts; i++) {
        img.setPixel(2 * ts + i, 0, sf::Color(220, 180, 80));
        img.setPixel(2 * ts + i, ts - 1, sf::Color(220, 180, 80));
        img.setPixel(2 * ts, i, sf::Color(220, 180, 80));
        img.setPixel(2 * ts + ts - 1, i, sf::Color(220, 180, 80));
    }

    return img;
}