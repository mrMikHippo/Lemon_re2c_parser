#pragma once

#include "base.h"

class Float : public Base
{
public:
    void print() const override;
    Float(double _value);

protected:
private:
    double value;
};
