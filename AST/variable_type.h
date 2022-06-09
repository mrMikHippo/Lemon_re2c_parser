#pragma once

#include "token.h"

#include <string>
#include <vector>
#include <memory>

//Map(Integer, Integer)
class VariableType
{
public:
	VariableType(const Token& type_, const std::vector<VariableType*> types_);

	Token getType() const;

	std::vector<VariableType*> getSubTypes() const;

	void addSubType(VariableType* type_);

	std::string toString();

private:
	std::vector<VariableType*> types;
	Token type;
};
