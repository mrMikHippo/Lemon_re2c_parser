#pragma once

#include <string>
#include <cstring>
#include "parser/parser.h"
#include <iostream>

std::string tokenKindToString(int kind) {
	switch(kind) {
	case TOKEN_LEXEME_INTEGER:
		return "LEXEME_INTEGER";
	case TOKEN_NAME:
		return "TOKEN_NAME";
	case TOKEN_SEMICOLON:
		return "TOKEN_SEMICOLON";
	}
	return "Unknown";
}

struct Token {
	int kind;
	union {
		double num;
		char* str;
	} data;

	Token(int kind_) : kind(kind_) {}
	~Token() {
		std::cout << "Dtor [" << tokenKindToString(kind) << "], kind=" << kind;
		if (this->data.str) {
			std::cout << ", name=" << this->data.str;
			delete [] this->data.str;
			std::cout << ". char buffer freed";
		}
		std::cout << std::endl;
	}
};

Token* create_token(int kind) {
	return new Token(kind);
}

// Token* create_int_token(const std::string& value_) {
	// Token* token = create_token(TOKEN_LEXEME_INTEGER);
	// token->data.num = atoi(value_.c_str());
	// return token;
// }

Token* create_lex_integer_token(const std::string& lex_name_) {
	Token* token = create_token(TOKEN_LEXEME_INTEGER);
	token->data.str = new char[lex_name_.size()];
	strcpy(token->data.str, lex_name_.c_str());
	return token;
}

Token* create_name_token(const std::string& name_) {
	Token* token = create_token(TOKEN_NAME);
	// token->data.str = name_;
	token->data.str = new char[name_.size()];
	strcpy(token->data.str, name_.c_str());
	return token;
}