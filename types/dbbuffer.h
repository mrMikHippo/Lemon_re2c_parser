#pragma once

#include "base.h"

#include <string>

class DBBuffer : public Base
{
public:
    DBBuffer();
    DBBuffer(int _address, int _size, const std::string& _description);

    void print() const override;

    void setParameters(int _addr, int _size, const std::string& _descr);

private:
    int address;
    int size;
    std::string description;
};
