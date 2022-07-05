#pragma once

#include "base.h"

#include <vector>
#include <iostream>

template<typename T>
class Vector : public Base
{
public:
    Vector() {}

    void pushBack(T value) {
        content.push_back(value);
    }
    std::vector<T> get() const {
        return content;
    }

    void print() const override {
        using std::cout;
        using std::endl;

        cout << "Vector content: ";
        for (const auto& el : content)
            cout << el << " ";
        cout << endl;
    }

private:
    std::vector<T> content;
};
