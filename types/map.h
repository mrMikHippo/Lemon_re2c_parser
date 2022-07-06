#pragma once

#include "base.h"

#include <map>

class Map : public Base
{
public:

    template<typename ...Args>
	static Map* create(Args && ... _args) {
		return new Map(std::forward<Args>...);
	}

    void insert(std::pair<Base*, Base*> value);
    std::map<Base*, Base*> get() const;

    void print() const override;

    int size() const;

protected:
    Map() {}
private:
    std::map<Base*, Base*> content;
};
