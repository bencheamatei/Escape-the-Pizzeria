#include <iostream>
#include <SFML/Graphics.hpp>

#include "player.h"
#include "inventory.h"
#include "inventorySlot.h"
#include "item.h"
#include "pizza.h"
#include "topping.h"
#include "dough.h"
#include "exceptions.h"
#include "ResourceManager.hpp"

int main() {
    std::cout << "\n=== Pornire Fereastra SFML ===\n";
    sf::RenderWindow window(sf::VideoMode(800, 600), "Escape The Pizzeria");
    window.setFramerateLimit(60);

    sf::Sprite backgroundSprite;

    try {
        sf::Texture& podea=ResourceManager::Instance().getTexture("podea-fin.png");
        podea.setRepeated(true);
        backgroundSprite.setTexture(podea);
        backgroundSprite.setTextureRect(sf::IntRect(0, 0, 800, 600));
    } catch (const std::exception& e) {
        std::cerr << "Eroare fatala la incarcarea resurselor: " << e.what() << '\n';
        return -1;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        window.clear();
        window.draw(backgroundSprite);
        window.display();
    }
    return 0;
}