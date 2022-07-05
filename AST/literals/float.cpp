#include "float.h"

#include <iostream>

LiteralFloat::LiteralFloat(Token* value_)
	: value(value_)
{
}

void* LiteralFloat::execute() {
	double n = std::stod(value->value);
	return new double(n);
}

std::string LiteralFloat::toString() const {
	return value->value;
}
std::string LiteralFloat::print(int level) const {
	return std::string(level, '\t') + "FLOAT(\"" + value->print() + "\")\n";
}
