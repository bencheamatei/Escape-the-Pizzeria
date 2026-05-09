#include <iostream>
#include "player.h"
#include "inventory.h"
#include "inventorySlot.h"
#include "item.h"
#include "pizza.h"
#include "topping.h"
#include "exceptions.h"

int main() {
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

        // Umplem inventarul pana la refuz
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

    std::cout << "\n[ ETAPA 4: Atac Animatronic & Interfata Virtuala ]\n";
    std::cout << "Un animatronic il loveste pe Billy cu 45 damage!\n";
    eu.receiveDmg(45);
    std::cout << "HP Billy: " << eu.getHp() << "\n";

    if (eu.isAlive()) {
        std::cout << "Billy supravietuieste si foloseste un item!\n";
        std::cout << "HP Billy dupa heal: " << eu.getHp() << "\n";
    } else {
        std::cout << "S-a dus saracul...\n";
    }

    std::cout << "\n===================Sfarsit===================\n";
    return 0;
}