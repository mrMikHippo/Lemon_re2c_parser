#include "literal_integer.h"

// LiteralInteger
LiteralInteger::LiteralInteger(Token* value_)
	: value(value_)
{
}

void* LiteralInteger::execute() {
	int n = std::stoi(value->value);
	return new int(n);
}

std::string LiteralInteger::toString() const {
	return value->value;
}
std::string LiteralInteger::print(int level) const {
	return std::string(level, '\t') + "INTEGER(\"" + value->print() + "\")\n";
}
