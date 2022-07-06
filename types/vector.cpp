#include "vector.h"

#include <iostream>

void Vector::pushBack(Base* value) {
    content.push_back(value);
}

std::vector<Base*> Vector::get() const {
    return content;
}

int Vector::size() const
{
    return content.size();
}

void Vector::print() const {
    using std::cout;
    using std::endl;

    // cout << "Vector content: ";
    cout << "[";
    bool first = true;
    for (const auto& el : content) {
        if (first)
            first = false;
        else {
            cout << ", ";
        }
        el->print();
    }
    cout << "]";
}
