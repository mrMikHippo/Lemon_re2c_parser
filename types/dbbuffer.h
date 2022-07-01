#pragma once

#include "base.h"

#include <string>

class DBBuffer : public Base
{
public:
    DBBuffer(int ival_ = 0, float fval_ = .0f, const std::string& sval_ = "");

    void print() const override;

private:
    int ival;
    float fval;
    std::string sval;
};
