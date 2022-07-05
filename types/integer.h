#pragma once

#include "base.h"

class Integer : public Base
{
public:
    // template<typename ...Args>
	// static Integer* create(Args && ... _args) {
	// 	return new Integer(std::forward<Args>...);
	// }
    // static Integer* create(int val) {
    //     return new Integer(val);
    // }

    void print() const override;
    Integer(int _value);

protected:
private:
    int value;
};
