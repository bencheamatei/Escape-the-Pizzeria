//
// Created by matei on 5/13/2026.
//

#ifndef OOP_ANIMATRONIC_H
#define OOP_ANIMATRONIC_H

#include <string>
#include "../player.h"

class animatronic {
protected:
    std::string name;
    int damage;
    float speed;
    bool active;

    float attack_cooldown;
    float attack_rate;
public:
    animatronic(std::string,int,float,bool,float);
    virtual ~animatronic()=default;

    virtual void on_attack(player &p)=0;
    [[nodiscard]] bool is_active() const;
    [[nodiscard]] float get_speed() const;

    void tick_timer(float);
    bool can_attack() const;
    void reset_cooldown();
};


#endif //OOP_ANIMATRONIC_H