###############################################################################
# purpose: makefile for Lab 3
# author:  Joe Crumpton
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

# variables used in the following rules
CXX      = g++
RM       = rm
# generate debug information for gdb
CXXFLAGS = -g


lab3: nodes.h driver.o
	$(CXX) $(CXXFLAGS) -o lab3 driver.o

#     -o flag specifies the output file
#
#     The above rule could be written with macros as
#        $(CXX) $(CXXFLAGS) -o $@ $^

driver.o: driver.cpp nodes.h 
	$(CXX) $(CXXFLAGS) -o driver.o -c driver.cpp 

#      -c flag specifies stop after compiling, do not link


clean: 
	$(RM) *.o lab3

