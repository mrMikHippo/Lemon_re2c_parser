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
std::string LiteralInteger::print(int level) const {
	return std::string(level, '\t') + "INTEGER(\"" + value->print() + "\")\n";
}

// LiteralFloat
LiteralFloat::LiteralFloat(Token* value_)
	: value(value_)
{
}

std::string LiteralFloat::toString() const {
	return value->value;
}
std::string LiteralFloat::print(int level) const {
	return std::string(level, '\t') + "FLOAT(\"" + value->print() + "\")\n";
}

// LiteralString
LiteralString::LiteralString(Token* value_)
	: value(value_)
{
}

std::string LiteralString::toString() const {
	return value->value;
}

std::string LiteralString::print(int level) const {
	return std::string(level, '\t') + "STRING(\"" + value->print() + "\")\n";
}

// LiteralType
LiteralType::LiteralType(VariableType* type_)
	: type(type_)
{
}

std::string LiteralType::toString() const {
	return type->toString();
	// return "TYPE(\"" + type->toString() + "\")";
}
std::string LiteralType::print(int level) const {
	std::string res = std::string(level, '\t') + "LiteralType\n";
	res += type->print(level+1);
	return res;
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

std::string LiteralOneParam::print(int level) const {
	std::string res = std::string(level, '\t') + "LiteralOneParam\n";
	res += type->print(level+1);
	for (const auto& el : content)
		res += el->print(level+2);
	return res;
}

// LiteralTwoParam
LiteralTwoParam::LiteralTwoParam(VariableType* type_, LiteralTwoParam::ContentType content_)
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
		auto key = static_cast<Expression*>(el.first);
		auto& val = el.second;
		res += key->toString();
		// res += el.first->toString();
		res += " : ";
		res += val->toString();
		// res += el.second->toString();
	}
	res += "]";
	return res;
}

std::string LiteralTwoParam::print(int level) const {
	std::string res = std::string(level, '\t') + "LiteralTwoParam\n";
	res += type->print(level+1);
	for (const auto& el : content) {
		res += el.first->print(level+2);
		res += el.second->print(level+2);
	}
	return res;
}
