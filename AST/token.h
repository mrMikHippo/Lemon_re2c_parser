#pragma once

#include <string>

// Token types
//  TOKEN_TYPE
//	TOKEN_ID

struct Token
{
	Token() {}
	Token(const std::string& value_) : value(value_) {}
	virtual ~Token() = default;
	std::string value;
};
