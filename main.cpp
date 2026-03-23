#include <iostream>
#include <fstream>
#include <vector>
#include "topping.h"
#include "include/player.h"
#include "include/topping.h"
#include "include/item.h"
#include "include/topping.h"

int main() {

    std::ifstream fin("tastatura.txt");

    std::vector<item> items(3);
    for (int i=0 ; i<3 ; i++) {
        fin >> items[i];
        std::cout << items[i] << "\n";;
    }

    std::vector<topping> toppings(2);
    for (int i=0 ; i<2; i++) {
        fin >> toppings[i];
        std::cout << toppings[i] << "\n" << toppings[i].calculate_damage(5) << "\n" << toppings[i].calculate_overall_damage() << "\n";
    }

    player eu(100,100,5);

    for (int i=0; i<3; i++) {
        inventorySlot aux={items[i],i+4};
        aux.changeCntItem(-2);
        aux.setItem(items[i],i+4);
        eu.addItem(aux);
    }
    std::cout << eu << "\n";
    inventory inv(eu.get_inventory());
    std::cout << inv.get_size() << "\n";
    inv.pop_from_pos(0);
    std::cout << inv << "\n";
    std::cout << inv.get_size() << "\n";
    inv.rearrangeItems();
    std::cout << inv << "\n";
    std::cout << "done\n";

    for (int i=0 ;i<5; i++) {
        topping aux;
        fin >> aux;
        inv.addItem({aux,5});
    }
    inv.pop_from_pos(0);
    inv.pop_from_pos(2);
    std::cout << inv << "\n" << "------------------\n";
    inv.rearrangeItems();
    std::cout << inv;
    inv.resize_inventory(10);
    std::cout << inv;

    std::cout << "----------------------\n";
    std::cout << eu.getHp() << "\n";
    eu.receiveDmg(50);

    if (eu.isDead()) {
        eu.heal(100);
    }
    else {
        eu.heal(10);
    }

    std::cout << eu.getHp() << "\n";
    topping top("mold",50,0);
    top.set_damage(25);
    top.set_timp(1);
    eu.pickItem({top,1},4);
    std::cout << eu<< "\n";

    eu.receiveDmg(100);
    if (eu.isALive()) {
        std::cout << "all good\n";
    }
    fin.close();
    return 0;
}
