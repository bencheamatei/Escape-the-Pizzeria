//
// Created by matei on 5/13/2026.
//

#ifndef OOP_ANIMATRONIC_H
#define OOP_ANIMATRONIC_H

#include <string>
#include "../player.h"
#include <SFML/Graphics.hpp>

class animatronic {
protected:
    std::string name;
    int damage;
    float speed;
    bool active;

    float attack_cooldown;
    float attack_rate;

    int max_pizza_hits=1;
    int pizza_hits=0;

    float stun_timer=0.f;

    sf::Vector2f pos;
    float box_w = 18.f;
    float box_h = 24.f;

public:
    animatronic(std::string,int,float,bool,float);
    virtual ~animatronic()=default;

    virtual void on_attack(player &p)=0;
    [[nodiscard]] bool is_active() const;
    [[nodiscard]] float get_speed() const;

    virtual void tick_timer(float);
    [[nodiscard]] bool can_attack() const;
    void reset_cooldown();

    virtual bool gets_hit();
    void apply_stun(float dt);
    [[nodiscard]] bool is_stunned() const;

    void set_position(sf::Vector2f new_pos);
    [[nodiscard]] sf::Vector2f get_position() const;
    [[nodiscard]] sf::FloatRect get_bounds() const;
};


#endif //OOP_ANIMATRONIC_H