//
// Created by matei on 5/13/2026.
//

#ifndef OOP_STATUS_EFFECT_H
#define OOP_STATUS_EFFECT_H

#include <string>

class player;

class status_effect {
private:
    std::string name;
protected:
    virtual void on_trigger(player &)=0;
public:
    virtual ~status_effect();
    explicit status_effect(const std::string &nume="efect_generic");
    void trigger(player &);
    [[nodiscard]] virtual status_effect* get_clone()=0;
};


#endif //OOP_STATUS_EFFECT_H