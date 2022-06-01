CC = gcc
CXX = g++
PARSER_PATH=parser
LEXER_PATH=lexer

CXXFLAGS = 
#-std=c++11

CXXFILES = main.cpp AST/variable_type.cpp AST/literal.cpp AST/expression.cpp AST/statement.cpp

OBJF=lre_test

# all: $(OBJF)

HEADERS = lexer.h parser.c

all:
	$(CXX) $(CXXFLAGS) $(CXXFILES) -o $(OBJF)

lexer.h: $(LEXER_PATH)/lexer.re
	re2c $(LEXER_PATH)/lexer.re -i --case-ranges -o $(LEXER_PATH)/lexer.h 

parser.c: $(PARSER_PATH)/parser.yy
	lemon $(PARSER_PATH)/parser.yy

clean:
	rm -rf $(OBJF) *.o $(LEXER_PATH)/lexer.{cpp,h} $(PARSER_PATH)/parser.{h,out,c}