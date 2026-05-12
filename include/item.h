//
// Created by matei on 3/22/2026.
//

#ifndef OOP_ITEM_H
#define OOP_ITEM_H

#include <iostream>
#include <string>


class player;

class item {
private:
    // static int total_items;
protected:
    std::string nume;
    virtual void display(std::ostream &os) const;
public:
    item();
    explicit item(const std::string &);
    virtual ~item();

    virtual void print(std::ostream &os) const;
    [[nodiscard]] virtual std::string get_nume() const;
    friend std::ostream &operator<<(std::ostream &, const item &);
    friend std::istream &operator>>(std::istream &, item &);
    [[nodiscard]] virtual item* get_clone() const=0;
    virtual void apply_effect(player &p)=0;
    // static int get_total_items();
};

#endif //OOP_ITEM_H