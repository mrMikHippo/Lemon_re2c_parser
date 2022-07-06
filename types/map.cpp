#include "map.h"

#include <iostream>

void Map::insert(std::pair<Base*, Base*> value) {
    content.insert(value);
}

std::map<Base*, Base*> Map::get() const {
    return content;
}

int Map::size() const
{
    return content.size();
}

void Map::print() const {
    using std::cout;
    using std::endl;

    cout << "[";
    bool first = true;
    for (const auto& el : content) {
        if (first)
            first = false;
        else {
            cout << ", ";
        }
        cout << "{";
        el.first->print();
        cout << " : ";
        el.second->print();
        cout << "}";
    }
    cout << "]";
}
