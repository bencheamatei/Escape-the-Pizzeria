//
// Created by matei on 5/23/2026.
//

#ifndef OOP_FOXY_H
#define OOP_FOXY_H
#include "animatronic.h"


class foxy : public animatronic{
public:
    foxy();
    void on_attack(player &p) override;
};


#endif //OOP_FOXY_H