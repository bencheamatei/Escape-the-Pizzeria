//
// Created by matei on 5/11/2026.
//

#ifndef OOP_DOUGH_H
#define OOP_DOUGH_H

#include "item.h"

class dough : public item {
private:
    void display(std::ostream &os) const override;
public:
    dough();
    ~dough() override = default;
    [[nodiscard]] item* get_clone() const override;
    void on_use(player &p) override;
};

#endif //OOP_DOUGH_H