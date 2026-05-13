//
// Created by matei on 5/13/2026.
//

#ifndef OOP_FOOD_POISONING_H
#define OOP_FOOD_POISONING_H
#include "status_effect.h"


class food_poisoning : public status_effect {
protected:
    void on_trigger(player &) override;
public:
    food_poisoning();
    status_effect *get_clone() override;
};


#endif //OOP_FOOD_POISONING_H