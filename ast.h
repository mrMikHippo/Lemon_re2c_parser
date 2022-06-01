#pragma once

#include "AST/token.h"
// #include "AST/variable_type.h"
// #include "AST/expression.h"
#include "AST/literal.h"




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
		res += " ";
		res += id.value;
		res += " ";
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
};
    
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
};