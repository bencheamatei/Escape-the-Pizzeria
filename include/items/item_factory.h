//
// Created by matei on 6/25/2026.
//

#ifndef OOP_ITEM_FACTORY_H
#define OOP_ITEM_FACTORY_H

#include <memory>
#include "items/item.h"

class item_factory {
public:
    static std::unique_ptr<item> create(int tip);
};


#endif //OOP_ITEM_FACTORY_H