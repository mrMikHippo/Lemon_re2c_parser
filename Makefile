CC = gcc
CXX = g++
PARSER_PATH=parser
LEXER_PATH=lexer

CXXFLAGS =
#-std=c++11

SRCS := AST/variable_type.cpp \
		AST/literal.cpp \
		AST/expression.cpp \
		AST/statement.cpp \
		AST/content.cpp \
		module.cpp \
		tests/test_all.cpp \
		tests/test_parser.cpp \
		main.cpp

OBJF=lre_test

# all: $(OBJF)
.PHONY: all clean lexer parser

all: lexer parser
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(OBJF)

lexer: $(LEXER_PATH)/lexer.re
	re2c $(LEXER_PATH)/lexer.re -i --case-ranges -o $(LEXER_PATH)/lexer.h

parser: $(PARSER_PATH)/parser.y
	lemon -s $(PARSER_PATH)/parser.y

clean:
	rm -rf $(OBJF) *.o $(LEXER_PATH)/lexer.{cpp,h} $(PARSER_PATH)/parser.{h,out,c}
