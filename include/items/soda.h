//
// Created by matei on 5/13/2026.
//

#ifndef OOP_SODA_H
#define OOP_SODA_H

#include "item.h"

class soda : public item {
private:
    void display(std::ostream &os) const override;
    void on_use(player &p) override;
public:
    soda();
    ~soda() override=default;
    [[nodiscard]] item* get_clone() const override;
};


#endif //OOP_SODA_H