//
// Created by matei on 6/25/2026.
//

#ifndef OOP_RANDOM_SELECTOR_H
#define OOP_RANDOM_SELECTOR_H

#include <stdexcept>
#include <vector>
#include "exceptions.h"

template <typename T>
class random_selector {
private:
    std::vector<T> v;
public:
    void add(T &&x) {
        v.push_back(std::move(x));
    }

    T get_rnd() const {
        if (v.empty()) {
            throw std::runtime_error("Trebuie sa ai macar un element la alegere aleatorie");
        }
        return v[std::rand() % v.size()];
    }
};


#endif //OOP_RANDOM_SELECTOR_H