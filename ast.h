#pragma once

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <utility>


struct Token
{
	std::string value;
};

//Map(Integer, Integer)
class VariableType
{
public:
	VariableType(const Token& type_) 
		: type(type_) {}

	Token getType() const {
		return type;
	}

	std::vector<VariableType*> getSubTypes() const {
		return types;
	}

	void addSubType(VariableType* type_) {
		types.push_back(type_);
	}

private:
	std::vector<VariableType*> types;
	Token type;
};

class Literal
{
	Token value;

public:
	Literal(const std::string& value_) 
		: value(value_) {}
	~Literal() = default;

	Token getValue() const {
		return value;
	}
};

//100500
class LiteralInteger : public Literal
{
public:
	LiteralInteger(const std::string& value_) 
		: Literal(value_) {}
};

//Vector(Integer)[100500, id]
class LiteralVector : public Literal
{
public:
	LiteralVector(const std::string& value_) 
		: Literal(value_) {}

	void setVariableType(VariableType* type_) {
		type = type_;
	}

	void addSubType(Expression* expr) {
		subTypes.push_back(expr);
	}

private:
	VariableType* type;
	std::vector<Expression*> subTypes;
};

//Map(Integer, Integer)[100500 : id, 42 : id2]
class LiteralMap : public Literal
{
public:
	LiteralMap(const std::string& value_) 
		: Literal(value_) {}

	void setVariableType(VariableType* type_) {
		type = type_;
	}

	void addKeyValue(	Expression* key_, Expression* value_) {
		body.push_back(std::make_pair<Expression*, Expression*>(key_, value_));
	}

private:
    VariableType* type
    std::vector<std::pair<Expression*, Expression*>> body;
};



class Expression
{
public:
	Expression() {}
	~Expression() = default;
};

//id
class ExpressionId : public Expression 
{
public:
	ExpressionId(const Token& id_) 
		: id(id_) {}

	Token getToken() const {
		return id;
	}

private:
    Token id;
};

//id.some
class ExpressionDot : public Expression
{
public:
	ExpressionDot(const Token& id_, Expression* caller_) 
		: id(id_), caller(caller_) {}

	Expression* getCaller() const {
		return caller;
	}

	Token getId() const {
		return id;
	}

private:
    Expression* caller;
    Token id;
};

//id.some(arg1, arg2)
class ExpressionCallOrdered : public Expression
{
public:
	ExpressionCallOrdered(Expression* callee_)
		: callee(callee_) {}

	void addArg(Expression* arg_) {
		args.push_back(arg_);
	}

private:
    Expression* callee;
    std::vector<Expression*> args;
};
    
//id.some(key = arg1, key2 = arg2)
class ExpressionCallNamed : public Expression
{
public:
	ExpressionCallNamed() {}

	void addArg(Token* arg_, Expression* value_) {
		args.push_back(std::make_pair<Token*, Expression*>(arg_, value_));
	}

private:
	Expression* callee;
    std::vector<std::pair<Token*, Expression*>> args;
};

//id[key]
class ExpressionAt : public Expression
{
public:
	ExpressionAt(Expression* caller_, Expression* key_) 
		: caller(caller_), key(key_) {}

private:
    Expression* caller
    Expression* key
};

class ExpressionLiteral : public Expression
{ 
public:
	ExpressionLiteral(Literal* literal_) 
		: literal(literal_) {}

private:
    Literal* literal;
};


class Statement
{

};

//Integer a = 100500
class StatementDefinition : public Statement
{
public:
	StatementDefinition(VariableType* type_, Token id_) 
		: type(type_) id(id_) {}

	void addExpression(Expression* expr_) {
		value = expr_;
	}

private:
    VariableType* type;
    Token id;
    Expression* value = nullptr;
};

class StatementExpression : public Statement
{
public:
	StatementExpression(Expression* expr_) 
		: expr(expr_) {}

private:
    Expression* expr;
}
    
class StatementList : public Statement
{
public:
	StatementList() {}

	void addStatement(Statement* statement_) {
		statements.push_back(statement_);
	}

private:
    std::vector<Statement*> statements;
}