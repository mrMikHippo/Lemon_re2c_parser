#pragma once

#include "../literal.h"

#include <string>

class LiteralFloat : public Literal
{
public:
	LiteralFloat(Token* value_);

	void* execute() override;

	std::string toString() const override;
	std::string print(int level = 0) const override;

private:
	Token* value;
};
