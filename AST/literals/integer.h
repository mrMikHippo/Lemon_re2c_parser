#pragma once

#include "../literal.h"

#include <string>

class LiteralInteger : public Literal
{
public:
	LiteralInteger(Token* value_);

	void* execute() override;

	std::string toString() const override;
	std::string print(int level = 0) const override;

private:
	Token* value;
};
