#pragma once

#include <string>

struct Token
{
	Token() {}
	Token(const std::string& value_) : value(value_) {}
	virtual ~Token() = default;
	std::string value;
};
