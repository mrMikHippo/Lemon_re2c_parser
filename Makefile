CC = gcc
CXX = g++
PARSER_PATH=lemon_p
LEXER_PATH=lexer

NEW_PARSER_PATH=parser
NEW_LEXER_PATH=lexer_v2

CXXFILES = main.cpp
CXXFILES_V2 = main_v2.cpp

all: lre_test_v2

old: lre_test

lre_test: scanner.h lemon.c
	$(CXX) $(LDFLAGS) -o lre_test $(CXXFILES)

lemon.c: $(PARSER_PATH)/parser.yy
	lemon $(PARSER_PATH)/parser.yy

scanner.h: $(LEXER_PATH)/test_scanner.re
	re2c $(LEXER_PATH)/test_scanner.re -i --case-ranges > $(LEXER_PATH)/test_scanner.h 

clean_old:
	rm -rf lre_test *.o $(PARSER_PATH)/{parser.h,parser.out,parser.c} $(LEXER_PATH)/test_scanner.h 



lre_test_v2: lexer.h parser.c
	$(CXX) $(CXXFILES_V2) -o lre_test_v2

lexer.h: $(NEW_LEXER_PATH)/lexer.re
	re2c $(NEW_LEXER_PATH)/lexer.re -i --case-ranges -o $(NEW_LEXER_PATH)/lexer.h 

parser.c: $(NEW_PARSER_PATH)/parser.yy
	lemon $(NEW_PARSER_PATH)/parser.yy

clean:
	rm -rf lre_test_v2 *.o $(NEW_LEXER_PATH)/lexer.{cpp,h}