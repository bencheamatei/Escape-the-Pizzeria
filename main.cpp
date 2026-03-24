#include <iostream>
#include <fstream>
#include "player.h"
#include "inventory.h"
#include "inventorySlot.h"
#include "item.h"
#include "pizza.h"
#include "topping.h"

int main() {
    std::ifstream fin("tastatura.txt");

    // ok deci ce scenariu prezentam noi aici? in prima etapa de joc vreau sa las playerul sa exploreze putin
    // pizzeria, sa dea pick up la iteme, sa invete dmg si healing sistemul si mai ales cum sa crafteze pizza,
    // care o sa fie de altfel si singura lui arma impotriva animatronicilor.


    player eu(100,100,7);
    // Billy intra in pizzerie rn

    std::vector<item> chestii(10);
    std::vector<topping> tops(10);

    // Billy da pick up la chestii random
    for (int i=0; i<7; i++) {
        fin >> chestii[i];
        eu.addItem({chestii[i],1});
    }

    std::cout << eu << "\n";
    eu.enlarge_inventory(10);
    std::cout << eu.get_inventory().get_size() << "\n";

    eu.drop_item(0);
    eu.drop_item(4);
    eu.drop_item(5);
    eu.drop_item(1);
    inventory p=eu.get_inventory();
    eu.arrange();

    std::cout << eu << "-------------\n" << p << "\n";

    for (int i=0; i<3; i++) {
        fin >> tops[i];
        if (i==2) {
            tops[i].set_damage(1);
        }
        eu.addItem({tops[i],i+2});
    }

    inventorySlot pp;
    pp.setItem(item("dough"),1);

    eu.addItem(pp);
    eu.craftPizza();

    eu.receiveDmg(1000);
    if (!eu.isAlive()) {
        std::cout << "s-a dus saracul" << "\n";
        eu.heal(30);
    }
    std::cout << eu.getHp() << "\n";
    fin.close();
    return 0;
}