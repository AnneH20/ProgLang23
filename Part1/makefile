###############################################################################
# CSE 4714 / 6714 Project Part 1 - Lexical Analyzer (flex)
#
# 'make'        build executable file
# 'make clean'  removes all intermediate (lex.yy.c and *.o) and executable files
#
# This makefile purposely avoids macros to make the rules more clear.
# For more information about makefiles:
#      http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
#      http://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
#      http://www.gnu.org/software/make/manual/make.html
#
###############################################################################

tips_lex: lex.yy.o driver.o
	g++ -g -o tips_lex lex.yy.o driver.o

driver.o: driver.cpp lexer.h
	g++ -g -o driver.o -c driver.cpp

lex.yy.o: lex.yy.c lexer.h
	gcc -g -o lex.yy.o -c lex.yy.c

lex.yy.c: rules.l lexer.h
	flex -o lex.yy.c rules.l

clean: 
	$(RM) *.o lex.yy.c tips_lex

