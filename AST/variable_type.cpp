#include "variable_type.h"

#include <iostream>

VariableType::VariableType(Token* type_, const std::vector<VariableType*> types_)
	: type(type_), types(types_)
{
}

Token* VariableType::getType() const
{
	return type;
}

std::vector<VariableType*> VariableType::getSubTypes() const
{
	return types;
}

void VariableType::addSubType(VariableType* type_)
{
	types.push_back(type_);
}

std::string VariableType::toString()
{
	std::string res = type->value;
	if (!types.empty()) {
		res += "(";
		bool first = true;
		for (const auto& t : types) {
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

	switch(types.size()) {
		case 1:
			res += "_ONEPARAM";
			break;
		case 2:
			res += "_TWOPARAM";
			break;
	}
	res += "(\"" + type->print() + "\")\n";
	if (!types.empty()) {
		for (const auto& t : types) {
			res += t->print(level+1);
		}
	}
	return res;
}
