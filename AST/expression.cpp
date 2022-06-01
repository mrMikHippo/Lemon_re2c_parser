#include "expression.h"

#include "literal.h"

// ExpressionsId
ExpressionId::ExpressionId(const Token& id_) 
	: id(id_)
{
	// Do nothing
}

Token ExpressionId::getToken() const
{
	return id;
}

std::string ExpressionId::toString() const
{
	return id.value;
}

// ExpressionDot
ExpressionDot::ExpressionDot(const Token& id_, Expression* caller_) 
	: id(id_), caller(caller_)
{
	// Do nothing
}

Expression* ExpressionDot::getCaller() const
{
	return caller;
}

Token ExpressionDot::getId() const
{
	return id;
}

std::string ExpressionDot::toString() const
{
	return caller->toString() + "." + id.value;
}

// ExpressionCallOrdered
ExpressionCallOrdered::ExpressionCallOrdered(Expression* callee_, std::vector<Expression*> args_)
	: callee(callee_), args(args_)
{
	// Do nothing
}

void ExpressionCallOrdered::addArg(Expression* arg_)
{
	args.push_back(arg_);
}

std::string ExpressionCallOrdered::toString() const
{
	std::string res = callee->toString();
	res += "(";
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

// ExpressionCallNamed
ExpressionCallNamed::ExpressionCallNamed(Expression* callee_, ArgsType args_) 
	: callee(callee_), args(args_)
{
	// Do nothing
}

// void addArg(Token arg_, Expression* value_) {
// 	args.push_back(std::make_pair<Token*, Expression*>(arg_, value_));
// }

std::string ExpressionCallNamed::toString() const
{
	std::string res = callee->toString();
	res += "(";
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
