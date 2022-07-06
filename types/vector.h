#pragma once

#include "base.h"

#include <vector>
#include <iostream>

// template<typename T>
class Vector : public Base
{
public:

    template<typename ...Args>
	static Vector* create(Args && ... _args) {
		return new Vector(std::forward<Args>...);
	}

    void pushBack(Base* value);
    std::vector<Base*> get() const;

    void print() const override;

    int size() const;

protected:
    Vector() {}
private:
    std::vector<Base*> content;
};
