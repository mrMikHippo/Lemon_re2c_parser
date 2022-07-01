#include "literal.h"

#include "expression.h"
#include "../executors/literal_executor.h"

#include <iostream>
#include <string>

using std::cout;
using std::endl;

// LiteralInteger
LiteralInteger::LiteralInteger(Token* value_)
	: value(value_)
{
}

void* LiteralInteger::execute() {
	int n = std::stoi(value->value);
	return new int(n);
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

void* LiteralFloat::execute() {
	double n = std::stod(value->value);
	return new double(n);
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

void* LiteralString::execute() {
	return new std::string(value->value);
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
	std::string res = std::string(level, '\t') + "LiteralType(\"" + this->toString() + "\")\n";
	res += type->print(level+1);
	return res;
}

// LiteralOneParam
LiteralOneParam::LiteralOneParam(VariableType* type_, std::vector<Expression*> content_)
	: type(type_), content(content_)
{
}

void* LiteralOneParam::execute() {
	using std::cout;
	using std::endl;
   cout << "LiteralOneParam execute " << endl;
   cout << "Looking for '"<< type->getType()->value << "'" << endl;

   auto& mp_literals = GlobalLiteralTypeMap::getInstance().getStorage();
   auto it = mp_literals.find(type->getType()->value);
   if (it != mp_literals.end()) {
	   cout << it->first << " Found!" << endl;
	   auto& literal_executor = it->second;
	   return literal_executor->call(content);
   } else
	   cout << "Not found" << endl;
   return nullptr;
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
	std::string res = std::string(level, '\t') + "LiteralOneParam(\"" + this->toString() + "\")\n";
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
	std::string res = std::string(level, '\t') + "LiteralTwoParam(\"" + this->toString() + "\")\n";
	res += type->print(level+1);
	for (const auto& el : content) {
		res += el.first->print(level+2);
		res += el.second->print(level+2);
	}
	return res;
}
