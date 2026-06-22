//
// Created by matei on 5/30/2026.
//

#include "../include/animatronic_factory.h"
#include "animatronic/freddy.h"
#include "animatronic/foxy.h"
#include "animatronic/chica.h"
#include "animatronic/nightmare.h"

std::shared_ptr<animatronic> animatronic_factory::create(const tipuri_animatronici &x) {
    if (x==tipuri_animatronici::freddy) {
        return std::make_shared<freddy>();
    }

    if (x==tipuri_animatronici::foxy) {
        return std::make_shared<foxy>();
    }

    if (x==tipuri_animatronici::chica) {
        return std::make_shared<chica>();
    }

    if (x==tipuri_animatronici::nightmare) {
        return std::make_shared<nightmare>();
    }
    return nullptr;
}
