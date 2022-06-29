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
	std::string print(int level = 0) const override {
		std::string res = std::string(level, '\t');

		std::vector<std::string>& mp_literals = GlobalLiteralTypeMap::getInstance().types;
		auto it = std::find(mp_literals.begin(), mp_literals.end(), type->value);
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

private:
	std::vector<VariableType*> types;
	Token* type;
};
