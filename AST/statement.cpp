
#include "statement.h"

// StatementDefinition
StatementDefinition::StatementDefinition(VariableType* type_, Token id_, Expression* value_) 
	: type(type_), id(id_), value(value_)
{
	// Do nothing
}

std::string StatementDefinition::toString() const
{
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

// StatementExpression
StatementExpression::StatementExpression(Expression* expr_) 
	: expr(expr_)
{
	// Do nothing
}

std::string StatementExpression::toString() const
{
	return expr->toString();
}


// StatementList
StatementList::StatementList(std::vector<Statement*> statements_)
	: statements(statements_)
{
	// Do nothing
}

void StatementList::addStatement(Statement* statement_)
{
	statements.push_back(statement_);
}

std::string StatementList::toString() const
{
	std::string res;
	for (const auto& st : statements) {
		res += st->toString();
	}
	return res;
}
