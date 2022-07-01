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
		executors/literal_executor.cpp \
		tests/test_all.cpp \
		tests/test_parser.cpp \
		main.cpp

OBJ := $(SRCS:.cpp=.o)

OBJF=lre_test

.PHONY: all clean lexer parser

all: lexer parser comp

comp: $(OBJ)
	$(CXX) $(OBJ) -o test

%.o: %.cpp
	$(CXX) -c $< -o $@


lexer: $(LEXER_PATH)/lexer.re
	re2c $(LEXER_PATH)/lexer.re -i --case-ranges -o $(LEXER_PATH)/lexer.h

parser: $(PARSER_PATH)/parser.y
	lemon -s $(PARSER_PATH)/parser.y

clean:
	rm -f $(OBJF) $(LEXER_PATH)/lexer.{cpp,h} $(PARSER_PATH)/parser.{h,out,c}
	find . -type f -name '*.o' | xargs -n1 rm -fv
