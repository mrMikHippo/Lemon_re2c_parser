#include "vector.h"

#include <iostream>

Vector::Vector()
{}

void Vector::pushBack(int value)
{
    content.push_back(value);
}

std::vector<int> Vector::get() const
{
    return content;
}

void Vector::print() const
{
    using std::cout;
    using std::endl;

    cout << "Vector content:" << endl;
    for (const auto& el : content)
        cout << "\t" << el << endl;
}
