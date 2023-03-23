//*****************************************************************************
// purpose: driver file for CSE 4714 Lab 1
// version: Spring 2022
// author: Joe Crumpton / Ed Swan
//
// Speak to the TA or Instructor if you think that you need to modify this file.
//
//*****************************************************************************
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include "lexer.h"


extern "C"
{
// Instantiate global variables
extern FILE *yyin;         // input stream
extern FILE *yyout;        // output stream
extern int   yyleng;       // length of current lexeme
extern char *yytext;       // text of current lexeme
extern int   yylex();      // the generated lexical analyzer

extern int   line_number;
}


// Do the analysis
int main( int argc, char* argv[] )
{
  int token;   // hold each token code

  // Set the input stream
  if (argc > 1) {
    printf("INFO: Using the %s file for input\n", argv[1]);
    yyin = fopen(argv[1], "r"); 
  }
  else {
    printf("INFO: Using the sample.csv file for input\n");
    yyin = fopen("sample.csv", "r");
  }
  
  if (!yyin) {
    printf("ERROR: input file not found\n");
    return (-1);
  }

  // Set the output stream
  yyout = stdout;

  // Do the lexical parsing
  token = yylex();
  while( true ) 
  {
    if ( token == EOF_TOKEN ) {
      printf("Found end of file...\n");
      break;
    }

    // What did we find?
    printf("line: %d  lexeme: |%s|  length: %d  token: %d\n", line_number, yytext, yyleng, token);
    
    // Is it an error?
    if( token == UNKNOWN_TOKEN ) {
      printf("ERROR: unknown token\n");
      return(-2);
    }

    // Get the next token
    token = yylex();
  }

  return(0);
}
