//
// Created by matei on 3/22/2026.
//

#ifndef OOP_TOPPING_H
#define OOP_TOPPING_H
#include "item.h"

class topping : public item {
private:
    int damage;
public:
    topping();
    topping(const std::string &nume, int damage);
    ~topping() override;
    [[nodiscard]] int get_damage() const;
    void set_damage(int);
    friend std::ostream &operator<<(std::ostream &os, const topping &topping);
    friend std::istream &operator>>(std::istream &is, topping &topping);
    item *get_clone() const override;
    void print(std::ostream &os) const override;
};

#endif //OOP_TOPPING_H