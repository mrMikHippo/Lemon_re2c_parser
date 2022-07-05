#include "float.h"

#include <iostream>

Float::Float(double _value)
    : value(_value)
{}

void Float::print() const {
    std::cout << value;
}
