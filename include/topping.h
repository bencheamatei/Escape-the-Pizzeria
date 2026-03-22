//
// Created by matei on 3/22/2026.
//

#ifndef OOP_TOPPING_H
#define OOP_TOPPING_H
#include "item.h"

class topping : public item {
private:
    std::string nume;
    int damage; // in cazul in care este de tip posison damageul se va lua drep dmg/secunda
                // in caz contrar va fi doar damageul instantaneu

    float timp; // pentru damage instantaneu va fi 0
public:
    topping();
    topping(const std::string &nume, int damage, float timp);
    ~topping();
    std::string get_nume() const;
    int get_damage() const;
    float get_timp() const;
    void set_damage(int damage);
    void set_timp(float timp);
    void set_nume(const std::string &nume);
    int calculate_overall_damage();
    int calculate_damage(float time);
    friend std::ostream &operator<<(std::ostream &os, const topping &topping);
};

#endif //OOP_TOPPING_H