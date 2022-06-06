// #pragma once

// #include <string>
// #include <cstring>
// #include "parser/parser.h"
// #include <iostream>

// std::string tokenKindToString(int kind) {
// 	switch(kind) {
// 	// case TOKEN_LEXEME_INTEGER:
// 		// return "LEXEME_INTEGER";
// 	// case TOKEN_NAME:
// 		// return "TOKEN_NAME";
// 	// case TOKEN_SEMICOLON:
// 		// return "TOKEN_SEMICOLON";
// 	// case TOKEN_ID:
// 		// return "TOKEN_ID";
// 	// case TOKEN_INTEGER:
// 		// return "TOKEN_INTEGER";
// 	// case TOKEN_LITERAL:
// 		// return "TOKEN_LITERAL";
// 	// case TOKEN_ASSIGN:
// 		// return "TOKEN_ASSIGN";
// 	}
// 	return "Unknown";
// }

// struct Token {
// 	const std::string value;
// 	int type;
// 	Token(int type_, const std::string& value_)
// 		: type(type_), value(value_) {}
// };

// Token* create_token(int type, const std::string& value) {
// 	return new Token(type, value);
// }

// // struct Token {
// // 	int kind;
// // 	// union {
// // 	double num;
// // 	char* str = nullptr;
// // 	// } data;

// // 	Token(int kind_) : kind(kind_) {}
// // 	~Token() {
// // 		std::cout << "Dtor [" << tokenKindToString(kind) << "], kind=" << kind;
// // 		if (this->str) {
// // 			std::cout << ", name=" << this->str;
// // 			delete [] this->str;
// // 			std::cout << ". char buffer freed";
// // 		}
// // 		std::cout << std::endl;
// // 	}
// // };

// // Token* create_token(int kind) {
// // 	// std::cout << "Create Simple token kind[" << kind << "] token_type=" << tokenKindToString(kind) << std::endl;
// // 	return new Token(kind);
// // }

// // Token* create_int_token(const std::string& value_) {
// // 	Token* token = create_token(TOKEN_INTEGER);
// // 	// std::cout << "Create_int_token";
// // 	token->num = atoi(value_.c_str());
// // 	token->str = new char[value_.size()];
// // 	strcpy(token->str, value_.c_str());
// // 	// std::cout << ", value=" << token->num << std::endl;
// // 	return token;
// // }

// // // Token* create_lex_integer_token(const std::string& lex_name_) {
// // // 	Token* token = create_token(TOKEN_LEXEME_INTEGER);
// // // 	token->str = new char[lex_name_.size()];
// // // 	strcpy(token->str, lex_name_.c_str());
// // // 	return token;
// // // }

// // Token* create_name_token(const std::string& name_) {
// // 	// Token* token = create_token(TOKEN_NAME);
// // 	// token->str = name_;
// // 	// token->str = new char[name_.size()];
// // 	// strcpy(token->str, name_.c_str());
// // 	// return token;
// // 	return nullptr;
// // }

// // Token* create_id_token(const std::string& name_) {
// // 	Token* token = create_token(TOKEN_ID);
// // 	// std::cout << "Create_Id_token";
// // 	token->str = new char[name_.size()];
// // 	strcpy(token->str, name_.c_str());
// // 	// std::cout << ", name=" << token->str << std::endl;
// // 	return token;
// // } 