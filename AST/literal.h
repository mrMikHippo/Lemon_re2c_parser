#pragma once

#include "token.h"
#include "variable_type.h"

#include <string>
#include <vector>
#include <utility>


class Expression;

class Literal
{
public:
	virtual ~Literal() {};

	virtual std::string toString() const = 0;
};

//100500
class LiteralInteger : public Literal
{
public:
	LiteralInteger(Token value_);
	virtual ~LiteralInteger() {}

	std::string toString() const override;

private:
	Token value;
};

// Vector(Integer)[100500, id]
class LiteralOneParam : public Literal
{
public:
	LiteralOneParam(VariableType* type_, std::vector<Expression*> content_);

	std::string toString() const override;

private:
	VariableType* type;
	std::vector<Expression*> content;
};

//Map(Integer, Integer)[100500 : id, 42 : id2]
class LiteralTwoParam : public Literal
{
public:
	LiteralTwoParam(VariableType* type_, std::vector<std::pair<Expression*, Expression*>> content_);

	std::string toString() const override;

private:
    VariableType* type;
    std::vector<std::pair<Expression*, Expression*> > content;
};