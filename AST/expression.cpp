#include "expression.h"

#include "literal.h"
#include "variable_type.h"

#include <iostream>

// ExpressionsId
ExpressionId::ExpressionId(Token* id_)
	: id(id_)
{
	// Do nothing
}

Token* ExpressionId::getToken() const
{
	return id;
}

std::string ExpressionId::toString() const
{
	return id->value;
}

std::string ExpressionId::print(int level) const {
	std::string res = std::string(level, '\t') + "ExpressionId(\"" + this->toString() + "\")\n";
	res += std::string(level+1, '\t') + "ID(\"" + id->value + "\")\n";
	return res;
}

// ExpressionAssign
ExpressionAssign::ExpressionAssign(Expression* left_, Expression* right_)
	: left(left_), right(right_)
{
	// Do nothing
}

std::string ExpressionAssign::toString() const
{
	return left->toString() + " = " + right->toString();
}

std::string ExpressionAssign::print(int level) const {
	std::string res = std::string(level, '\t') + "ExpressionAssign(\"" + this->toString() + "\")\n";
	res += left->print(level+1);
	res += right->print(level+1);
	return res;
}

// ExpressionDot
ExpressionDot::ExpressionDot(Token* id_, Expression* caller_)
	: id(id_), caller(caller_)
{
	// Do nothing
}

Expression* ExpressionDot::getCaller() const
{
	return caller;
}

Token* ExpressionDot::getId() const
{
	return id;
}

std::string ExpressionDot::toString() const
{
	return caller->toString() + "." + id->value;
}

std::string ExpressionDot::print(int level) const {
	std::string res = std::string(level, '\t') + "ExpressionDot(\"" + this->toString() + "\")\n";
	res += caller->print(level+1);
	res += std::string(level+1, '\t') + "ID(\"" + id->value + "\")\n";
	return res;
}

// ExpressionCall
ExpressionCall::ExpressionCall(Expression* callee_, Expression* args_)
	: callee(callee_), args(args_)
{
	// Do nothing
}

std::string ExpressionCall::toString() const
{
	std::string res;
	if (callee)
		res += callee->toString();
	// };
	res += args->toString();
	// res += "(";
	// bool first = true;
	// for (const auto& el : args) {
	// 	if (first) {
	// 		first = false;
	// 	} else
	// 		res += ", ";
	// 	res += el->toString();
	// }
	// res += ")";
	return res;
}

std::string ExpressionCall::print(int level) const {
	std::string res = std::string(level, '\t') + "ExpressionCall(\"" + this->toString() + "\")\n";
	res += callee->print(level+1);
	res += args->print(level+1);
	return res;
}

// ExpressionCallOrdered
ExpressionCallOrdered::ExpressionCallOrdered(std::vector<Expression*> args_)
	: args(args_)
{
	// Do nothing
}

void ExpressionCallOrdered::addArg(Expression* arg_)
{
	args.push_back(arg_);
}

std::string ExpressionCallOrdered::toString() const
{
	std::string res = "(";
	bool first = true;
	for (const auto& el : args) {
		if (first) {
			first = false;
		} else
			res += ", ";
		res += el->toString();
	}
	res += ")";
	return res;
}

std::string ExpressionCallOrdered::print(int level) const {
	std::string res = std::string(level, '\t') + "ExpressionCallOrdered(\"" + this->toString() + "\")\n";
	for (const auto& arg : args)
		res += arg->print(level+1);
	return res;
}

// ExpressionCallNamed
ExpressionCallNamed::ExpressionCallNamed(ArgsType args_)
	: args(args_)
{
	// Do nothing
}

std::string ExpressionCallNamed::toString() const
{
	std::string res = "(";
	bool first = true;
	for (const auto& el : args) {
		if (first) {
			first = false;
		} else
			res += ", ";
		res += el.first->value;
		res += " = ";
		res += el.second->toString();
	}
	res += ")";
	return res;
}

// ExpressionAt
ExpressionAt::ExpressionAt(Expression* caller_, Expression* key_)
	: caller(caller_), key(key_)
{
	// Do nothing
}

Expression* ExpressionAt::getCaller()
{
	return caller;
}

std::string ExpressionAt::toString() const
{
	return caller->toString() + "[" + key->toString() + "]";
}

std::string ExpressionAt::print(int level) const {
	std::string res = std::string(level, '\t') + "ExpressionAt(\"" + this->toString() + "\")\n";
	res += caller->print(level+1);
	res += key->print(level+1);
	return res;
}

// ExpressionLiteral
ExpressionLiteral::ExpressionLiteral(Literal* literal_)
	: literal(literal_)
{
	// Do nothing
}

std::string ExpressionLiteral::toString() const
{
	return literal->toString();
}

std::string ExpressionLiteral::print(int level) const {
	std::string res = std::string(level, '\t') + "ExpressionLiteral(\"" + this->toString() + "\")\n";
	res += literal->print(level+1);
	return res;
}

// ExpressionType
ExpressionType::ExpressionType(VariableType* type_)
	: type(type_)
{
	// Do nothing
}

std::string ExpressionType::toString() const
{
	return type->toString();
}

std::string ExpressionType::print(int level) const {
	std::string res = std::string(level, '\t') + "ExpressionType(\"" + this->toString() + "\")\n";
	res += type->print(level+1);
	return res;
}

// ExpressionEqual
ExpressionEqual::ExpressionEqual(Expression* left_, Expression* right_)
	: left(left_), right(right_)
{
	// Do nothing
}

std::string ExpressionEqual::toString() const
{
	return left->toString() + " == " + right->toString();
}

std::string ExpressionEqual::print(int level) const {
	std::string res = std::string(level, '\t') + "ExpressionEqual(\"" + this->toString() + "\")\n";
	res += left->print(level+1);
	res += right->print(level+1);
	return res;
}
