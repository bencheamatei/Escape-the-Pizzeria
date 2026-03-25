//
// Created by matei on 3/24/2026.
//

#ifndef OOP_PIZZA_H
#define OOP_PIZZA_H
#include <string>
#include "item.h"
#include "topping.h"
#include <vector>

class pizza : public item{
private:

    int total_dmg;
    std::vector<topping> toppings;
    void calculate_total_dmg();
public:
    pizza();
    explicit pizza(const std::vector<topping>&);
    pizza(std::initializer_list<topping>);
    ~pizza() override;
    item *get_clone() const override;
    int get_dmg() const;
    const std::vector<topping>& get_toppings() const;
    friend std::ostream& operator<<(std::ostream& os, const pizza& p);
    void print(std::ostream &os) const override;
};

#endif //OOP_PIZZA_H