//
// Created by matei on 5/30/2026.
//

#ifndef OOP_ANIMATRONIC_FACTORY_H
#define OOP_ANIMATRONIC_FACTORY_H

#include <animatronic/animatronic.h>
#include <memory>

enum class tipuri_animatronici {
    freddy,
    chica,
    foxy,
    nightmare
};

class animatronic_factory {
public:
    static std::shared_ptr<animatronic> create(const tipuri_animatronici &x);
};


#endif //OOP_ANIMATRONIC_FACTORY_H