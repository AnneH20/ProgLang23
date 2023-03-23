//*****************************************************************************
// purpose: Driver for Lab 2
// version: Spring 2022
//  author: Joe Crumpton / Ed Swan
//*****************************************************************************
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <iostream>
#include "lexer.h"
#include "parser.h"

using namespace std;

extern "C"
{
  // Instantiate global variables
  extern FILE *yyin;         // input stream
  extern FILE *yyout;        // output stream
  extern int   yyleng;       // length of current lexeme
  extern char *yytext;       // text of current lexeme
  extern int   yylineno;     // line number for current lexeme
  extern int   yylex();      // the generated lexical analyzer
}

// Do the analysis
int main( int argc, char* argv[] ) {

  // Set the input stream
  if (argc > 1) {
    cout << "Using the " << argv[1] << " file for input" << endl;
    yyin = fopen(argv[1], "r"); 
  }
  else {
    yyin = stdin;
  }
  if (!yyin) {
    printf("ERROR: input file not found\n");
    return (-1);
  }

  // Set the output stream
  yyout = stdout;
  
  // Get the first token
  lex();

  // Fire up that parser!
  try {
        // Process <sentence> production
        sentence();

        if (nextToken != TOK_EOF)
            throw "end of file expected, but there is more here!";
        
    } catch (char const *errmsg) {
        cout << endl << "***ERROR near |" << yytext << "|" << endl;
        cout << "\t" << errmsg << endl;
        return EXIT_FAILURE;
    }

    cout << endl << "=== MAROON! WHITE! Your parse was successful! ===" << endl;
  
  return EXIT_SUCCESS;
}