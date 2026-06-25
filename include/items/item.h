//
// Created by matei on 3/22/2026.
//

#ifndef OOP_ITEM_H
#define OOP_ITEM_H

#include <iostream>
#include <string>


class player;

class item {
protected:
    std::string nume;
    virtual void display(std::ostream &os) const;
    virtual void on_use(player &p)=0;
public:
    item();
    explicit item(const std::string &);
    virtual ~item();

    [[nodiscard]] virtual std::string get_nume() const;
    friend std::ostream &operator<<(std::ostream &, const item &);
    friend std::istream &operator>>(std::istream &, item &);
    [[nodiscard]] virtual item* get_clone() const=0;
    void use(player &p);
    // static int get_total_items();
};

#endif //OOP_ITEM_H