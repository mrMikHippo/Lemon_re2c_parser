#pragma once

#include "token.h"

#include <string>
#include <vector>
#include <memory>


class Literal;
class VariableType;

class Expression : public Token
{
public:
	Expression() {}
	virtual ~Expression() = default;
	virtual void setCallee(Expression* callee_) {}

	virtual std::string toString() const = 0;
};

//id
class ExpressionId : public Expression
{
public:
	ExpressionId(Token* id_);
	Token* getToken() const;
	std::string toString() const override;

private:
    Token* id;
};

//id1 = id2
class ExpressionAssign : public Expression
{
public:
	ExpressionAssign(Expression* left_, Expression* right_);

	std::string toString() const override;

private:
	Expression* left;
	Expression* right;
};

//id.some
class ExpressionDot : public Expression
{
public:
	ExpressionDot(Token* id_, Expression* caller_);

	Expression* getCaller() const;
	Token* getId() const;
	std::string toString() const override;

private:
    Expression* caller;
    Token* id;
};

class ExpressionCall : public Expression
{
public:
	ExpressionCall(Expression* caller_, Expression* args_);

	// virtual void setCallee(Expression* callee_) {
	// 	callee = callee_;
	// }

	std::string toString() const override;

private:
	Expression* callee;
	Expression* args;
};

//id.some(arg1, arg2)
class ExpressionCallOrdered : public Expression
{
public:
	ExpressionCallOrdered(Expression* callee_, std::vector<Expression*> args_);

	void addArg(Expression* arg_);
	std::string toString() const override;

private:
    Expression* callee;
    std::vector<Expression*> args;
};

//id.some(key = arg1, key2 = arg2)
class ExpressionCallNamed : public Expression
{
public:
	using ArgsType = std::vector<std::pair<Token*, Expression*>>;
	ExpressionCallNamed(Expression* callee_, ArgsType args_);

	std::string toString() const override;

private:
	Expression* callee;
    ArgsType args;
};

//id[key]
class ExpressionAt : public Expression
{
public:
	ExpressionAt(Expression* caller_, Expression* key_);

	Expression* getCaller();

	std::string toString() const override;

private:
    Expression* caller;
    Expression* key;
};


class ExpressionLiteral : public Expression
{
public:
	ExpressionLiteral(Literal* literal_);

	std::string toString() const override;

private:
    Literal* literal;
};

class ExpressionType : public Expression
{
public:
	ExpressionType(VariableType* type_);

	std::string toString() const override;

private:
    VariableType* type;
};

// a == b
class ExpressionEqual : public Expression
{
public:
	ExpressionEqual(Expression* left_, Expression* right_);

	std::string toString() const override;

private:
	Expression* left;
	Expression* right;
};
