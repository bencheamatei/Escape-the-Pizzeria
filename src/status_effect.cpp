//
// Created by matei on 5/13/2026.
//

#include "../include/status_effect.h"

status_effect::~status_effect() = default;

status_effect::status_effect(const std::string &nume) : name(nume) {}

void status_effect::trigger(player &p) {
    on_trigger(p);
}
