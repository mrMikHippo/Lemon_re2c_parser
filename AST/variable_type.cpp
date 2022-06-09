#include "variable_type.h"

VariableType::VariableType(const Token& type_, const std::vector<VariableType*> types_)
	: type(type_), types(types_)
{
}

Token VariableType::getType() const
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
	std::string res = type.value;
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
