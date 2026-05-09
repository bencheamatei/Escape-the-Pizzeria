//
// Created by matei on 3/22/2026.
//

#ifndef OOP_TOPPING_H
#define OOP_TOPPING_H
#include "item.h"
#include "player.h"

class topping : public item {
private:
    int damage;
protected:
    void display(std::ostream &os) const override;
public:
    topping();
    topping(const std::string &, int);
    ~topping() override;
    [[nodiscard]] item *get_clone() const override;

    [[nodiscard]] int get_damage() const;
    void set_damage(int);
    friend std::istream &operator>>(std::istream &, topping &);
    void apply_effect(player &p) override;
};

#endif //OOP_TOPPING_H