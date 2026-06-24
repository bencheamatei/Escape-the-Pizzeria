//
// Created by matei on 6/23/2026.
//

#ifndef OOP_ENEMY_H
#define OOP_ENEMY_H

#include "animatronic/animatronic.h"
#include "renders/animatronic_render.h"
#include <memory>

struct enemy {
    std::unique_ptr<animatronic> data;
    std::unique_ptr<animatronic_render> render;
    int room_id;
    enemy(std::unique_ptr<animatronic> data, std::unique_ptr<animatronic_render> render, int room_id);
    [[nodiscard]] int get_room_id() const;
    [[nodiscard]] animatronic* get_data() const;
    // [[nodiscard]] animatronic_render* get_render() const;
};


#endif //OOP_ENEMY_H