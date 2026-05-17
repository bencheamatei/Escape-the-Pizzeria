//
// Created by matei on 5/14/2026.
//

#ifndef OOP_FREDDY_H
#define OOP_FREDDY_H
#include "animatronic.h"


class freddy : public animatronic{
public:
    freddy();
    void on_attack(player &p) override;
};


#endif //OOP_FREDDY_H