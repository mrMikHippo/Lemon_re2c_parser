#pragma once

#include "base.h"

#include <string>

class String : public Base
{
public:
    String(const std::string& _value);

    void print() const override;

protected:
private:
    std::string value;
};
