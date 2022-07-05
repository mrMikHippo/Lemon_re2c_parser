CC = gcc
CXX = g++
PARSER_PATH=parser
LEXER_PATH=lexer

CXXFLAGS =
#-std=c++11

SRCS_AST   := variable_type.cpp literal.cpp expression.cpp statement.cpp content.cpp
SRCS_AST_LITERALS := dbbuffer.cpp integer.cpp float.cpp
SRCS_EXECS := literal_executor.cpp
SRCS_TESTS := test_all.cpp test_parser.cpp
SRCS_TYPES := dbbuffer.cpp vector.cpp integer.cpp float.cpp
SRCS_MAIN  := module.cpp main.cpp

SRCS := $(addprefix AST/,$(SRCS_AST))
SRCS += $(addprefix AST/literals/,$(SRCS_AST_LITERALS))
SRCS += $(addprefix executors/,$(SRCS_EXECS))
SRCS += $(addprefix types/,$(SRCS_TYPES))
# SRCS += $(addprefix tests/,$(SRCS_TESTS))
SRCS += $(SRCS_MAIN)

OBJ := $(SRCS:.cpp=.o)

OBJF=lre_test

.PHONY: all clean lexer parser

all: lexer parser comp

comp: $(OBJ)
	$(CXX) $(OBJ) -o $(OBJF)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

lexer:
	cd $(LEXER_PATH); re2c lexer.re -i --case-ranges -o lexer.h

parser:
	cd $(PARSER_PATH); lemon -s parser.y

clean:
	rm -fv $(OBJF) $(LEXER_PATH)/lexer.{cpp,h} $(PARSER_PATH)/parser.{h,out,c}
	find . -type f -name '*.o' | xargs -n1 rm -fv
