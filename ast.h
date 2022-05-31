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

	std::string toString() {
		std::string result = type.value;
		res += "("s;
		bool first = true;
		for (const auto& t : types) {
			if (first) {
				res += t->type.value;
				first = false;
			} else
				res += ", "s + t->type.value;
		}
		res += ")"s;
		return res;
	}

private:
	std::vector<VariableType*> types;
	Token type;
};

class Literal
{
public:
	Literal() {}
	virtual ~Literal() {}

	virtual std::string toString() const = 0;
};

//100500
class LiteralInteger : public Literal
{
public:
	LiteralInteger(Token& value_) 
		: value(value_) {}

	Token getValue() const {
		return value;
	}

	std::string toString() const override {
		return value.value;
	}

private:
	Token value;
};

//Vector(Integer)[100500, id]
class LiteralVector : public Literal
{
public:
	LiteralVector(VariableType* type_, std::vector<Expression*> content_) 
		: type(type_), content(content_) {}

	void setVariableType(VariableType* type_) {
		type = type_;
	}

	void addSubType(Expression* expr) {
		content.push_back(expr);
	}

	std::string toString() const override {
		std::string result = type->toString();
		result += "["s;
		bool first = true;
		for (const auto& el : content) {
			if (first) {
				first = false;
			} else
				result += ", "s;

			result += el->toString();
		}
		result += "]"s;
		return result;
	}

private:
	VariableType* type;
	std::vector<Expression*> content;
};

//Map(Integer, Integer)[100500 : id, 42 : id2]
class LiteralMap : public Literal
{
public:
	using ContentType = std::vector<std::pair<Expression*, Expression*>>;

	LiteralMap(VariableType* type_, ContentType content_) 
		: type(type_), content(content_) {}

	void setVariableType(VariableType* type_) {
		type = type_;
	}

	void addKeyValue(Expression* key_, Expression* value_) {
		body.push_back(std::make_pair<Expression*, Expression*>(key_, value_));
	}

	std::string toString() const override {
		std::string res = type->toString();
		res += "["s;
		bool first = true;
		for (const auto& el : content) {
			if (first)
				first = false;
			else
				res += ", "s;
			res += el.first->toString();
			res += " : "s;
			res += el.second->toString();
		}
		res += "]"s;
		return res;
	}

private:
    VariableType* type
    ContentType content;
};



class Expression
{
public:
	Expression() {}
	virtual ~Expression() = default;

	virtual std::string toString() const = 0;
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

	std::string toString() const override {
		return id.value;
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

	std::string toString() const override {
		return id.value + "."s + caller->toString();
	}

private:
    Expression* caller;
    Token id;
};

//id.some(arg1, arg2)
class ExpressionCallOrdered : public Expression
{
public:
	ExpressionCallOrdered(Expression* callee_, std::vector<Expression*> args_)
		: callee(callee_), args(args_) {}

	void addArg(Expression* arg_) {
		args.push_back(arg_);
	}

	std::string toString() const override {
		std::string res = callee->toString();
		res += "(";
		bool first = true;
		for (const auto& el : args) {
			if (first) {
				first = false;
			} else
				result += ", "s;
			result += el->toString();
		}
		res += ")";
		return res;
	}

private:
    Expression* callee;
    std::vector<Expression*> args;
};
    
//id.some(key = arg1, key2 = arg2)
class ExpressionCallNamed : public Expression
{
public:
	using ArgsType = std::vector<std::pair<Token*, Expression*>>; 
	ExpressionCallNamed(Expression* callee_, ArgsType args_) 
		: callee(callee_), args(args_) {}

	void addArg(Token* arg_, Expression* value_) {
		args.push_back(std::make_pair<Token*, Expression*>(arg_, value_));
	}

	std::string toString() const override {
		std::string res = callee->toString();
		res += "(";
		bool first = true;
		for (const auto& el : args) {
			if (first) {	
				first = false;
			} else
				result += ", "s;
			result += el.first->value;
			result += " = "s;
			result += el.second->toString();
		}
		res += ")";
		return res;
	}

private:
	Expression* callee;
    ArgsType args;
};

//id[key]
class ExpressionAt : public Expression
{
public:
	ExpressionAt(Expression* caller_, Expression* key_) 
		: caller(caller_), key(key_) {}

	Expression* getCaller() {
		return caller;
	}

	std::string toString() const override {
		return caller->toString() + "["s + key->toString() + "]"s;
	}

private:
    Expression* caller
    Expression* key
};

class ExpressionLiteral : public Expression
{ 
public:
	ExpressionLiteral(Literal* literal_) 
		: literal(literal_) {}

	Literal* getLiteral() const {
		return literal;
	}

	std::string toString() const override {
		return literal->toString();
	}

private:
    Literal* literal;
};


class Statement
{
public:
	virtual std::string toString() const = 0;
};

//Integer a = 100500
class StatementDefinition : public Statement
{
public:
	StatementDefinition(VariableType* type_, Token id_, Expression* value_ = nullptr) 
		: type(type_), id(id_), value(value_) {}

	std::string toString() const override {
		std::string res = type->toString();
		res += " "s;
		res += id.value;
		res += " "s;
		if (value) {
			res += " = ";
			res += value->toString();
		}
		return res;
	}

private:
    VariableType* type;
    Token id;
    Expression* value;
};

class StatementExpression : public Statement
{
public:
	StatementExpression(Expression* expr_) 
		: expr(expr_) {}

	std::string toString() const override {
		return expr->toString();
	}

private:
    Expression* expr;
}
    
class StatementList : public Statement
{
public:
	StatementList(std::vector<Statement*> statements_)
		: statements(statements_) {}

	void addStatement(Statement* statement_) {
		statements.push_back(statement_);
	}

	std::string toString() const override {
		std::string res;
		for (const auto& st : statements) {
			res += st->toString();
		}
		return res;
	}

private:
    std::vector<Statement*> statements;
}