#include "string.h"

#include <iostream>

String::String(const std::string& _value)
    : value(_value)
{}

void String::print() const {
    std::cout << value;
}
