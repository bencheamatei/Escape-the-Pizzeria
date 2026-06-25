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
    void add(const T &x) {
        v.push_back(x);
    }

    T get_rnd() {
        if (v.empty()) {
            throw std::runtime_error("you have to have at least one element in order to get_rnd");
        }
        int idx=std::rand()%v.size();
        std::swap(v[(int)v.size()-1],v[idx]);
        T aux=v.back();
        v.pop_back();
        return aux;
    }
};


#endif //OOP_RANDOM_SELECTOR_H