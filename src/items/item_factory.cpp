//
// Created by matei on 6/25/2026.
//

#include "../../include/items/item_factory.h"
#include "items/item.h"
#include "items/dough.h"
#include "items/soda.h"
#include "items/topping.h"
#include "exceptions.h"

std::unique_ptr<item> item_factory::create(int tip) {
    if (tip<0 || tip>4) {
        throw game_exception("invalid tip");
    }
    if (tip==0) {
        return std::make_unique<dough>();
    }
    if (tip==1) {
        return std::make_unique<soda>();
    }
    if (tip==2) {
        return std::make_unique<topping>("pepperoni",5);
    }
    if (tip==3) {
        return std::make_unique<topping>("mushroom",3);
    }
    if (tip==4) {
        return std::make_unique<topping>("ananas",4);
    }
    return nullptr;
}
