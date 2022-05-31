#pragma once

#include <iostream>
#include <cstring>
#include <string>

struct Expression
{
	Token* token;

	Expression() : left(nullptr), right(nullptr) {}
	
	Expression* left;
	Expression* right;
};

// +, -, *, /, =, etc.
struct OperatorExpression : public Expression 
{
	OperatorExpression(Token* token_) {
		token = token_;
	}
	OperatorExpression(Token* token_, Expression* left_, Expression* right_) {
		token = token_;
		left = left_;
		right = right_;
	}
};

// Expression name
struct LiteralExpression : public Expression 
{
	LiteralExpression(Token* token_) {
		token = token_;
	}
};

// ID expression
struct IDExpression : public Expression
{
	IDExpression(Token* token_) {
		token = token_;
	}	
};

struct AST
{
	Expression* node;
};

struct Statement : public Expression {
	// virtual Token* evaluate(Token* left, Token* right) = 0;
};

struct Initialize : public Statement {
	// Token* evaluate(Token* left, Token* right) override {
	// 	std::cout << "evaluate Initialization" << std::endl;
	// 	return nullptr;
	// }
};

struct EvaluateToken : public Statement {
	// Token* evaluate(Token* left, Token* right) override {
	// 	std::cout << "evaluate Token" << std::endl;
	// 	return nullptr;
	// }
};

Expression* create_operator_expr(const std::string& value_) {
	// OperatorExpression* token = new OperatorExpression(value_);
	// token->type = TOKEN_ASSIGN;
	return nullptr;
}

Expression* create_literal_expr(const std::string& value_) {
	// LiteralExpression* token = new LiteralExpression(value_);
	// token->type = TOKEN_LITERAL;
	// return token;
	return nullptr;
}