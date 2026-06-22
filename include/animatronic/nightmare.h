//
// Created by matei on 5/30/2026.
//

#ifndef OOP_NIGHTMARE_H
#define OOP_NIGHTMARE_H
#include "animatronic.h"


class nightmare : public animatronic{
public:
    nightmare();
    void on_attack(player &p) override;
    bool gets_hit() override;
};


#endif //OOP_NIGHTMARE_H