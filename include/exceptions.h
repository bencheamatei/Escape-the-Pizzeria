//
// Created by matei on 5/9/2026.
//

#ifndef OOP_EXCEPTIONS_H
#define OOP_EXCEPTIONS_H

#include <exception>
#include <string>

class game_exception : public std::exception {
protected:
    std::string message;
public:
    explicit game_exception(const std::string &);
    [[nodiscard]] const char* what() const noexcept override;
};

class inventory_exception : public game_exception {
public:
    explicit inventory_exception(const std::string &);
};

class craft_exception : public game_exception {
public:
    explicit craft_exception(const std::string &);
};

class combat_exception : public  game_exception {
public:
    explicit combat_exception(const std::string &);
};

#endif //OOP_EXCEPTIONS_H