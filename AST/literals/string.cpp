#include "string.h"

LiteralString::LiteralString(Token* value_)
	: value(value_)
{
}

void* LiteralString::execute() {
	return new std::string(value->value);
}

std::string LiteralString::toString() const {
	return value->value;
}

std::string LiteralString::print(int level) const {
	return std::string(level, '\t') + "STRING(\"" + value->print() + "\")\n";
}
