#include <iostream>
#include <SFML/Graphics.hpp>

// Include-urile claselor tale
#include "player.h"
#include "inventory.h"
#include "inventorySlot.h"
#include "item.h"
#include "pizza.h"
#include "topping.h"
#include "dough.h"
#include "exceptions.h"

int main() {
    // ==========================================================
    // 1. TESTARE LOGICĂ OOP (Consolă)
    // ==========================================================
    std::cout << "=== Testare Logica Joc: Billy la Pizzerie ===\n";

    try {
        // Cream jucatorul (Billy)
        player billy(80, 100, 5); // 80 HP, 100 MaxHP, 5 sloturi inventar

        // Cream ingredientele
        dough aluat;
        topping branza("Mozzarella", 20);
        topping salam("Salam Pepperoni", 30);

        // Adaugam ingrediente in inventar
        billy.addItem(inventorySlot(aluat, 1));
        billy.addItem(inventorySlot(branza, 1));
        billy.addItem(inventorySlot(salam, 1));

        std::cout << "\nInventar initial:\n" << billy.get_inventory() << "\n";

        // Testam Crafting-ul
        std::cout << "Billy gateste o pizza...\n";
        billy.craftPizza();
        std::cout << "Inventar dupa gatit:\n" << billy.get_inventory() << "\n";

        // Testam Polimorfismul (Metoda eat_item care apeleaza apply_effect)
        std::cout << "Billy mananca pizza (ar trebui sa primeasca heal)...\n";
        // Pizza rezultata este de obicei pe ultimul slot ocupat (sau primul liber)
        // In logica noastra, dupa craft, pizza este adaugata in inventar.
        billy.eat_item(0); // Billy mananca ce are pe primul slot (care ar trebui sa fie pizza acum)

        std::cout << "HP Billy dupa masa: " << billy.getHp() << " / 100\n";

    } catch (const game_exception& e) {
        std::cerr << "Eroare detectata: " << e.what() << "\n";
    }

    // ==========================================================
    // 2. TESTARE INTERFAȚĂ GRAFICĂ (SFML)
    // ==========================================================
    std::cout << "\n=== Pornire Fereastra SFML ===\n";

    // Cream fereastra jocului
    sf::RenderWindow window(sf::VideoMode(800, 600), "FNAF: Pizzeria Test");
    window.setFramerateLimit(60);

    // Cream un obiect grafic simplu pentru test (un dreptunghi pentru "masa")
    sf::RectangleShape table(sf::Vector2f(400.f, 200.f));
    table.setFillColor(sf::Color(100, 50, 0)); // Maro
    table.setOrigin(200.f, 100.f);
    table.setPosition(400.f, 400.f);

    // Un cerc galben care reprezinta o "pizza" pe masa
    sf::CircleShape pizzaGraphic(60.f);
    pizzaGraphic.setFillColor(sf::Color::Yellow);
    pizzaGraphic.setOutlineThickness(5);
    pizzaGraphic.setOutlineColor(sf::Color(200, 100, 0)); // Margine portocalie (crusta)
    pizzaGraphic.setOrigin(60.f, 60.f);
    pizzaGraphic.setPosition(400.f, 380.f);

    // Bucla principala a ferestrei
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Inchidere fereastra la apasarea 'X' sau Escape
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        // --- RENDER ---
        window.clear(sf::Color(20, 20, 25)); // Fundal foarte inchis (atmosfera FNAF)

        window.draw(table);         // Desenam masa
        window.draw(pizzaGraphic);  // Desenam pizza

        window.display();
    }

    std::cout << "Program incheiat cu succes.\n";
    return 0;
}