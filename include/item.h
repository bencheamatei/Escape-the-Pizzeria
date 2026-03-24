//
// Created by matei on 3/22/2026.
//

#ifndef OOP_ITEM_H
#define OOP_ITEM_H

#include <iostream>
#include <string>

class item {
private:

protected:
    std::string nume;
public:
    item();
    explicit item(const std::string &);
    virtual ~item();
    virtual std::string get_nume() const;
    friend std::ostream &operator<<(std::ostream &, const item &);
    friend std::istream &operator>>(std::istream &, item &);
    virtual item* get_clone() const;
};

#endif //OOP_ITEM_H