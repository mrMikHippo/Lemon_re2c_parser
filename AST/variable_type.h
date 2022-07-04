#pragma once

#include "token.h"
#include "global_types_map.h"

#include <algorithm>
#include <string>
#include <vector>
#include <memory>

//Map(Integer, Integer)
class VariableType : public Token
{
public:
	VariableType(Token* type_, const std::vector<VariableType*> types_);

	Token* getType() const;

	std::vector<VariableType*> getSubTypes() const;

	void addSubType(VariableType* type_);

	std::string toString();
	std::string print(int level = 0) const override;

private:
	std::vector<VariableType*> types;
	Token* type;
};
