#include "integer.h"

#include <iostream>

Integer::Integer(int _value)
    : value(_value)
{}

void Integer::print() const {
    std::cout << value;
    // std::cout << "Integer(" << value << ")";
}
