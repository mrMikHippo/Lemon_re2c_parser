#pragma once

#include "token.h"
#include "variable_type.h"
#include "global_types_map.h"

#include <string>
#include <vector>
#include <utility>
#include <iostream>


class Expression;

class Literal : public Token
{
public:
	virtual ~Literal() {};

	virtual void* execute() { std::cout << "Literal execute" << std::endl; return nullptr; }

	virtual std::string toString() const = 0;
	virtual std::string print(int level = 0) const override { return "LITERAL"; }
};

//100500
class LiteralInteger : public Literal
{
public:
	LiteralInteger(Token* value_);

	void* execute();

	std::string toString() const override;
	std::string print(int level = 0) const override;

private:
	Token* value;
};

//10.5
class LiteralFloat : public Literal
{
public:
	LiteralFloat(Token* value_);

	void* execute();

	std::string toString() const override;
	std::string print(int level = 0) const override;

private:
	Token* value;
};

// "Some string"
class LiteralString : public Literal
{
public:
	LiteralString(Token* value_);

	void* execute();

	std::string toString() const override;
	std::string print(int level = 0) const override;

private:
	Token* value;
};
// Other primitives Literals ...

// class LiteralSimple : public Literal
// {
	// 	
	// }

// Integer or Type or Vector(Integer) etc.
class LiteralType : public Literal
{
public:
	LiteralType(VariableType* type_);

	std::string toString() const override;
	std::string print(int level = 0) const override;
private:
	VariableType* type;
};


// Vector(Integer)[100500, id]
class LiteralOneParam : public Literal
{
public:
	LiteralOneParam(VariableType* type_, std::vector<Expression*> content_);

	void* execute();

	std::string toString() const override;
	std::string print(int level = 0) const override;

private:
	VariableType* type;
	std::vector<Expression*> content;
};

//Map(Integer, Integer)[100500 : id, 42 : id2]
class LiteralTwoParam : public Literal
{
public:
	using ContentType = std::vector<std::pair<Token*, Expression*>>;
	// using ContentType = std::vector<std::pair<Expression*, Expression*>>;
	LiteralTwoParam(VariableType* type_, ContentType content_);

	std::string toString() const override;
	std::string print(int level = 0) const override;

private:
    VariableType* type;
    ContentType content;
};
