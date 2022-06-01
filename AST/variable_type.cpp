#include "variable_type.h"


VariableType::VariableType(const Token& type_) 
	: type(type_)
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
	res += "(";
	bool first = true;
	for (const auto& t : types) {
		if (first) {
			res += t->type.value;
			first = false;
		} else
			res += ", " + t->type.value;
	}
	res += ")";
	return res;
}