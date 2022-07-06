#include "variable_type.h"

#include <iostream>

VariableType::VariableType(Token* type_, const std::vector<VariableType*> sub_types_)
	: type(type_), sub_types(sub_types_)
{
}

std::string VariableType::getType() const
{
	return this->toString();
}

VariableType* VariableType::getTypeFull()
{
	return this;
}

std::string VariableType::getTokenType() const
{
	return type->value;
}

std::vector<VariableType*> VariableType::getSubTypes() const
{
	return sub_types;
}

void VariableType::addSubType(VariableType* type_)
{
	sub_types.push_back(type_);
}

std::string VariableType::toString() const
{
	std::string res = type->value;
	if (!sub_types.empty()) {
		res += "(";
		bool first = true;
		for (const auto& t : sub_types) {
			if (first) {
				first = false;
			} else
				res += ", ";
			res += t->toString();
		}
		res += ")";
	}
	return res;
}

std::string VariableType::print(int level) const {
	std::string res = std::string(level, '\t');

	auto& mp_literals = GlobalLiteralTypeMap::getInstance().getStorage();
	auto it = mp_literals.find(type->value);
	if (it != mp_literals.end()) {
		res += "LITERAL_";
	}

	res += "TYPE";

	switch(sub_types.size()) {
		case 1:
			res += "_ONEPARAM";
			break;
		case 2:
			res += "_TWOPARAM";
			break;
	}
	res += "(\"" + type->print() + "\")\n";
	if (!sub_types.empty()) {
		for (const auto& t : sub_types) {
			res += t->print(level+1);
		}
	}
	return res;
}
