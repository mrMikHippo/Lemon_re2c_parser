#include "literal.h"


LiteralInteger::LiteralInteger(Token value_)
	: value(value_) 
{
}

std::string LiteralInteger::toString() const {
	return value.value;
}

LiteralVector::LiteralVector(VariableType* type_, std::vector<Expression*> content_) 
	: type(type_), content(content_)
{

}

std::string LiteralVector::toString() const {
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


LiteralMap::LiteralMap(VariableType* type_, std::vector<std::pair<Expression*, Expression*> > content_) 
	: type(type_), content(content_) {}


std::string LiteralMap::toString() const {
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

