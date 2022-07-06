#pragma once

#include "../literal.h"

#include <string>

class LiteralString : public Literal
{
public:
	LiteralString(Token* value_);

	void* execute() override;

	std::string toString() const override;
	std::string print(int level = 0) const override;

private:
	Token* value;
};
