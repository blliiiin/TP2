#ifndef INPUT_H
#define INPUT_H

#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

template <typename T>
T readNumber(const char* prompt)
{
    std::cout << prompt;
    char line[128];

    if (!std::cin.getline(line, sizeof line)) {
        if (std::cin.eof()) {
            throw std::runtime_error("Ввод завершён.");
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Слишком длинная строка.");
    }

    std::istringstream input(line);
    T value;
    char extra;

    if (!(input >> value) || (input >> extra) || !std::isfinite(value)) {
        throw std::invalid_argument("Введите одно корректное число.");
    }
    return value;
}

#endif
