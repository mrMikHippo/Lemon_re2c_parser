#pragma once

#include <string>

class DBBuffer
{
public:
    DBBuffer(int ival_ = 0, float fval_ = .0f, const std::string& sval_ = "");

    void print() const;

private:
    int ival;
    float fval;
    std::string sval;
};
