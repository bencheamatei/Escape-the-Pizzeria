//
// Created by matei on 5/30/2026.
//

#ifndef OOP_CHICA_H
#define OOP_CHICA_H
#include "animatronic.h"


class chica : public animatronic{
public:
    chica();
    void on_attack(player &p) override;
};


#endif //OOP_CHICA_H