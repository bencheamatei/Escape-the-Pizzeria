//
// Created by matei on 5/11/2026.
//

#ifndef OOP_DOUGH_H
#define OOP_DOUGH_H

#include "../item.h"

class dough : public item {
public:
    dough();
    [[nodiscard]] item* get_clone() const override;
    void apply_effect(player &p) override;
    void display(std::ostream &os) const override;
};

#endif //OOP_DOUGH_H