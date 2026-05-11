#include <iostream>
#include <SFML/Graphics.hpp> // Libraria grafica
#include "player.h"
#include "inventory.h"
#include "inventorySlot.h"
#include "item.h"
#include "pizza.h"
#include "topping.h"
#include "exceptions.h"

int main() {
    // ==========================================================
    // 1. TESTUL TAU OOP (Rămâne neschimbat, rulează în consolă)
    // ==========================================================
    std::cout << "===================Billy intra in pizzerie===================\n";
    player eu(100, 100, 4);

    try {
        std::cout << "\n[ ETAPA 1: Explorare & Polimorfism ]\n";
        topping cheese("Cheese", 10);
        topping pepperoni("Pepperoni", 15);

        eu.addItem(inventorySlot(cheese, 1));
        eu.addItem(inventorySlot(pepperoni, 2));

        std::cout << "Inventarul lui Billy:\n" << eu.get_inventory() << "\n";

        std::cout << "\n[ ETAPA 2: Testare Exceptii - Crafting ]\n";
        std::cout << "Billy incearca sa crafteze o pizza din aer...\n";
        eu.craftPizza();

    } catch (const game_exception& e) {
        std::cerr << ">>> [Game Error prins]: " << e.what() << "\n";
    }

    try {
        std::cout << "\n[ ETAPA 3: Testare Exceptii - Inventar Plin ]\n";
        topping random_junk("Scrap", 0);

        eu.addItem(inventorySlot(random_junk, 1));
        eu.addItem(inventorySlot(random_junk, 1));
        eu.addItem(inventorySlot(random_junk, 1));

        std::cout << "Incearca sa indese inca un item...\n";
        eu.addItem(inventorySlot(random_junk, 1));

    } catch (const game_exception& e) {
        std::cerr << ">>> [Game Error prins]: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << ">>> [Standard Error]: " << e.what() << "\n";
    }

    // ==========================================================
    // 2. TESTUL SFML (Fereastra grafica)
    // ==========================================================
    std::cout << "\n>>> PORNIRE INTERFATA GRAFICA SFML...\n";

    // Creăm fereastra
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test SFML - FNAF Pizzeria");
    window.setFramerateLimit(60); // Limităm la 60 cadre pe secundă

    // Creăm un obiect de test grafic (un cerc roșu reprezentând o pizza)
    sf::CircleShape pizzaShape(50.f);
    pizzaShape.setFillColor(sf::Color::Red);
    pizzaShape.setPosition(350.f, 250.f); // Îl punem pe centrul ecranului aproximativ

    // Bucla infinită de joc (Game Loop)
    while (window.isOpen()) {

        // A. Procesăm Evenimentele (input de la utilizator)
        sf::Event event;
        while (window.pollEvent(event)) {
            // Dacă utilizatorul apasă pe 'X' sau pe tasta Escape
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // B. Update logic (Momentan nu avem nimic care se mișcă singur pe ecran)

        // C. Render (Desenăm cadrul nou)
        window.clear(sf::Color(30, 30, 30)); // Fundal gri închis

        window.draw(pizzaShape);             // Desenăm cercul roșu creat mai sus

        window.display();                    // Trimitem imaginea pe monitor
    }

    std::cout << "\n===================Fereastra inchisa. Sfarsit===================\n";
    return 0;
}