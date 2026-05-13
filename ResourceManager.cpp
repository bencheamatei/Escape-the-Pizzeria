//
// Created by bgd on 12/15/2024.
//

#include "ResourceManager.hpp"
#include "exceptions.h"

ResourceManager& ResourceManager::Instance()
{
    static ResourceManager instance;
    return instance;
}

ResourceManager::ResourceManager()
{
    loadTexture("images", "podea-fin.png");
    loadTexture("images", "billy.png");
    loadTexture("images", "dough.png");
    loadTexture("images", "generic.png");
    loadTexture("images", "pizza.png");
    loadTexture("images", "pepperoni.png");
    loadTexture("images", "mushroom.png");
    loadTexture("images", "backpack.png");
    loadTexture("images", "soda.png");

    loadFont("fonts", "FiraSans-Regular.ttf");
    m_textures["podea-fin.png"].setRepeated(true);
}

void ResourceManager::loadTexture(const std::string& path, const std::string& texture_name)
{
    sf::Texture texture;

    if(!texture.loadFromFile(path + '/' + texture_name))
    {
        throw resources_exception("Textura " + texture_name + " nu a putut fi incarcata.");
    }

    m_textures[texture_name] = texture;
}

void ResourceManager::loadFont(const std::string& path, const std::string& font_name)
{
    sf::Font font;

    if(!font.loadFromFile(path + '/' + font_name))
    {
        throw resources_exception("Fontul " + font_name + " nu a putut fi incarcat.");
    }

    m_fonts[font_name] = font;
}


sf::Texture& ResourceManager::getTexture(const std::string& texture_name)
{
    if(m_textures.find(texture_name) == m_textures.end())
    {
        throw resources_exception("Textura " + texture_name + " nu a fost gasita.");
    }

    return m_textures[texture_name];
}

sf::Font& ResourceManager::getFont(const std::string& font_name)
{
    if(m_fonts.find(font_name) == m_fonts.end())
    {
        throw resources_exception("Fontul " + font_name + " nu a fost gasita.");
    }

    return m_fonts[font_name];
}