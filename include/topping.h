//
// Created by matei on 3/22/2026.
//

#ifndef OOP_TOPPING_H
#define OOP_TOPPING_H
#include "item.h"

class topping : public item {
private:
    int damage; // in cazul in care este de tip posison damageul se va lua drep dmg/secunda
                // in caz contrar va fi doar damageul instantaneu

    int timp; // pentru damage instantaneu va fi 0
public:
    topping();
    topping(const std::string &nume, int damage, int timp);
    ~topping() override;
    [[nodiscard]] int get_damage() const;
    [[nodiscard]] int get_timp() const;
    void set_damage(int);
    void set_timp(int);
    int calculate_overall_damage();
    int calculate_damage(int time);
    friend std::ostream &operator<<(std::ostream &os, const topping &topping);
    friend std::istream &operator>>(std::istream &is, topping &topping);
};

#endif //OOP_TOPPING_H