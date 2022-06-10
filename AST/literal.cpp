#include "literal.h"

#include "expression.h"

// LiteralInteger
LiteralInteger::LiteralInteger(Token* value_)
	: value(value_)
{
}

std::string LiteralInteger::toString() const {
	return value->value;
}
// LiteralFloat
LiteralFloat::LiteralFloat(Token* value_)
	: value(value_)
{
}

std::string LiteralFloat::toString() const {
	return value->value;
}
// LiteralString
LiteralString::LiteralString(Token* value_)
	: value(value_)
{
}

std::string LiteralString::toString() const {
	return value->value;
}

// LiteralType
LiteralType::LiteralType(VariableType* type_)
	: type(type_)
{
}

std::string LiteralType::toString() const {
	return type->toString();
}

// LiteralOneParam
LiteralOneParam::LiteralOneParam(VariableType* type_, std::vector<Expression*> content_)
	: type(type_), content(content_)
{
}

std::string LiteralOneParam::toString() const {
	std::string result = type->toString();
	result += "[";
	bool first = true;
	for (const auto& el : content) {
		if (first) {
			first = false;
		} else
			result += ", ";

		result += el->toString();
	}
	result += "]";
	return result;
}

// LiteralTwoParam
LiteralTwoParam::LiteralTwoParam(VariableType* type_, std::vector<std::pair<Expression*, Expression*> > content_)
	: type(type_), content(content_) {}


std::string LiteralTwoParam::toString() const {
	std::string res = type->toString();
	res += "[";
	bool first = true;
	for (const auto& el : content) {
		if (first)
			first = false;
		else
			res += ", ";
		res += el.first->toString();
		res += " : ";
		res += el.second->toString();
	}
	res += "]";
	return res;
}
