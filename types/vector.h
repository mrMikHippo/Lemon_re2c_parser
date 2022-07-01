#pragma once

#include "base.h"

#include <vector>

class Vector : public Base
{
public:
    Vector();

    void pushBack(int value);
    std::vector<int> get() const;

    void print() const override;

private:
    std::vector<int> content;
};
