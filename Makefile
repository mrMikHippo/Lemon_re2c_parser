CC = gcc
CXX = g++
PARSER_PATH=parser
LEXER_PATH=lexer

CXXFILES = main.cpp

OBJF=lre_test

all: $(OBJF)


$(OBJF): lexer.h parser.c
	$(CXX) $(CXXFILES) -o $(OBJF)

lexer.h: $(LEXER_PATH)/lexer.re
	re2c $(LEXER_PATH)/lexer.re -i --case-ranges -o $(LEXER_PATH)/lexer.h 

parser.c: $(PARSER_PATH)/parser.yy
	lemon $(PARSER_PATH)/parser.yy

clean:
	rm -rf $(OBJF) *.o $(LEXER_PATH)/lexer.{cpp,h} $(PARSER_PATH)/parser.{h,out,c}