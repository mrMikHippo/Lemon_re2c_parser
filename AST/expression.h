#pragma once

#include "token.h"

#include <string>
#include <vector>
#include <memory>

// #include "../types/string.h"

class Literal;
class VariableType;

class Expression : public Token
{
public:
	Expression() {}
	virtual ~Expression() = default;
	virtual void setCallee(Expression* callee_) {}

	virtual void* execute() { return nullptr; }

	virtual std::string toString() const = 0;
	virtual std::string print(int level = 0) const override { return "Expression\n"; }
};

//id
class ExpressionId : public Expression
{
public:
	ExpressionId(Token* id_);
	Token* getToken() const;

	void* execute() override {
		// String *val = new String(id->value);
		// return static_cast<void*>(val);
		return new std::string(id->value);
	}

	std::string toString() const override;
	std::string print(int level = 0) const override;

private:
    Token* id;
};

//id1 = id2
class ExpressionAssign : public Expression
{
public:
	ExpressionAssign(Expression* left_, Expression* right_);

	void* execute() override {
		left->execute();
		right->execute();
		return nullptr;
	}

	std::string toString() const override;
	std::string print(int level = 0) const override;

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
	std::string print(int level = 0) const override;

private:
    Expression* caller;
    Token* id;
};

class ExpressionCall : public Expression
{
public:
	ExpressionCall(Expression* caller_, Expression* args_);

	std::string toString() const override;
	std::string print(int level = 0) const override;

private:
	Expression* callee;
	Expression* args;
};

//id.some(arg1, arg2)
class ExpressionCallOrdered : public Expression
{
public:
	ExpressionCallOrdered() {}
	ExpressionCallOrdered(std::vector<Expression*> args_);

	void addArg(Expression* arg_);
	std::string toString() const override;
	std::string print(int level = 0) const override;

private:
    std::vector<Expression*> args;
};

//id.some(key = arg1, key2 = arg2)
class ExpressionCallNamed : public Expression
{
public:
	using ArgsType = std::vector<std::pair<Token*, Expression*>>;
	ExpressionCallNamed(ArgsType args_);

	std::string toString() const override;
	std::string print(int level = 0) const override;

private:
    ArgsType args;
};

//id[key]
class ExpressionAt : public Expression
{
public:
	ExpressionAt(Expression* caller_, Expression* key_);

	Expression* getCaller();

	std::string toString() const override;
	std::string print(int level = 0) const override;

private:
    Expression* caller;
    Expression* key;
};


class ExpressionLiteral : public Expression
{
public:
	ExpressionLiteral(Literal* literal_);

	void* execute() override;

	std::string toString() const override;
	std::string print(int level = 0) const override;

private:
    Literal* literal;
};

// Integer
class ExpressionType : public Expression
{
public:
	ExpressionType(VariableType* type_);

	std::string toString() const override;
	std::string print(int level = 0) const override;

private:
    VariableType* type;
};

// a == b
class ExpressionEqual : public Expression
{
public:
	ExpressionEqual(Expression* left_, Expression* right_);

	std::string toString() const override;
	std::string print(int level = 0) const override;

private:
	Expression* left;
	Expression* right;
};
