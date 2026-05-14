//
// Created by matei on 5/12/2026.
//

#include "../include/player_render.h"
#include "../include/game.h"

player_render::player_render(player &p, sf::Texture &texture, sf::Vector2f init_pos) :
                    player_data(p), position(init_pos) {

    sprite.setTexture(texture);
    sprite.setOrigin(FRAME_W/2.0f, FRAME_H/2.0f);
    update_sprite_rect();
    sprite.setPosition(position);
}

// daca implementez un sistem de spawnpoint
void player_render::set_position(sf::Vector2f pos) {
    position=pos;
    sprite.setPosition(pos);
}

void player_render::handle_input() {
    velocity={0.0f,0.0f};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        velocity.y-=0.1f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        velocity.y+=0.1f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        velocity.x-=0.1f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        velocity.x+=0.1f;
    }

    // normalizez si pe diagonala fmm de supersonic
    if (velocity.x!=0.f && velocity.y!=0.f) {
        velocity.x*=0.7071f;
        velocity.y*=0.7071f;
    }

    if (velocity.y<0.0f) {
        facing=Dir::Up;
    }
    else if (velocity.y>0.0f) {
        facing=Dir::Down;
    }
    else if (velocity.x<0.0f) {
        facing=Dir::Left;
    }
    else if (velocity.x>0.0f) {
        facing=Dir::Right;
    }

    if (velocity.x!=0.0f || velocity.y!=0.0f) {
        moving=true;
    }
    else {
        moving=false;
    }
}

bool player_render::overlap_solid(sf::FloatRect rect, const room &room) const {
    return room.collide(rect);
}

void player_render::resolve_collision(sf::Vector2f delta, const room &room) {
    sf::FloatRect pe_x(position.x-BOX_W/2.0f+delta.x,position.y-BOX_H/2.0f,
                        BOX_W,BOX_H);

    if (!overlap_solid(pe_x,room)) {
        position.x+=delta.x;
    }

    sf::FloatRect pe_y(position.x-BOX_W/2.0f,position.y-BOX_H/2.0f+delta.y,
                        BOX_W,BOX_H);

    if (!overlap_solid(pe_y,room)) {
        position.y+=delta.y;
    }
}

// in viitor o sa vreau ca sprite-ul pentru billy sa nu fie static cum este acum
// adica ca in jocurile vechi sa aduc ceva miscare sus-jos ca sa arat respiratia gen

// void player_render::update_animation(float dt) {
//     if (moving) {
//         frameTimer+=dt;
//         if (frameTimer>=FRAME_TIME) {
//             frameTimer=0.0f;
//             frame=(frame+1)%FRAME_COUNT;
//         }
//     }
//     else {
//         frame=0;
//         frameTimer=0.0f;
//     }
// }

void player_render::update_sprite_rect() {
    sprite.setTextureRect(sf::IntRect(frame*FRAME_W,
        (int)facing*FRAME_H,
        FRAME_W,FRAME_H
    ));
}

void player_render::draw(sf::RenderTarget &window) const {
    window.draw(sprite);
    if (game::is_debug_mode()) {
        sf::RectangleShape hitbox({BOX_W, BOX_H});
        hitbox.setOrigin(BOX_W / 2.0f, BOX_H / 2.0f);
        hitbox.setPosition(position);
        hitbox.setFillColor(sf::Color::Transparent);
        hitbox.setOutlineColor(sf::Color::Red);
        hitbox.setOutlineThickness(1.0f);
        window.draw(hitbox);
    }
}

void player_render::update(float dt, const room &room) {
    if (player_data.isAlive()) {
        resolve_collision(velocity*SPEED*dt,room);
    }

    // update_animation(dt);
    sprite.setPosition(position);
}

// bool player_render::is_moving() const {
//     return moving;
// }

sf::Vector2f player_render::get_position() const {
    return position;
}

sf::FloatRect player_render::get_bound() const {
    return sf::FloatRect(position.x - BOX_W / 2.0f, position.y - BOX_H / 2.0f, BOX_W, BOX_H);
}
