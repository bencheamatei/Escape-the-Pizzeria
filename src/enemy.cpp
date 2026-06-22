//
// Created by matei on 6/23/2026.
//

#include "../include/enemy.h"

enemy::enemy(std::unique_ptr<animatronic> data,
    std::unique_ptr<animatronic_render> render, int room_id) :
    data(std::move(data)), render(std::move(render)), room_id(room_id) {
}

int enemy::get_room_id() const {
    return room_id;
}

animatronic *enemy::get_data() const {
    return data.get();
}





