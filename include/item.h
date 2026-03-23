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
    explicit item(const std::string &nume);
    virtual ~item();
    virtual std::string get_nume() const;
    friend std::ostream &operator<<(std::ostream &os, const item &item);
    friend std::istream &operator>>(std::istream &is, item &item);
};

#endif //OOP_ITEM_H