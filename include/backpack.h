//
// Created by matei on 5/13/2026.
//

#ifndef OOP_BACKPACK_H
#define OOP_BACKPACK_H

#include "item.h"

class backpack : public item {
private:
    int sz_upgrade;
public:
    explicit backpack(int sz=8);
    ~backpack() override = default;
    void display(std::ostream &os) const override;
    void on_use(player &) override;
    [[nodiscard]] item* get_clone() const override;
};


#endif //OOP_BACKPACK_H