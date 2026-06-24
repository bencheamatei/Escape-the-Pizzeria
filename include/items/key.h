//
// Created by matei on 6/24/2026.
//

#ifndef OOP_KEY_H
#define OOP_KEY_H

#include "items/item.h"

class key : public item {
public:
    key();
    void on_use(player &p) override;
    [[nodiscard]] item* get_clone() const override;
};


#endif //OOP_KEY_H