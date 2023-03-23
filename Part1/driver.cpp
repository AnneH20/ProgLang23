//*****************************************************************************
// CSE 4714 / 6714 Project Part 1 - Lexical Analyzer Driver
// Spring 2023
//*****************************************************************************

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include "lexer.h"

// Instantiate global variables
extern "C"
{
extern FILE *yyin;         // input stream
extern FILE *yyout;        // output stream
extern int   yyleng;       // length of current lexeme
extern char *yytext;       // text of current lexeme
extern int   yylineno;     // line number for current lexeme
extern int   yylex();      // the generated lexical analyzer
}

// Do the analysis
int main( int argc, char* argv[] ) {
  int token;   // hold each token code

  // Set the input stream
  if (argc > 1) {
    printf("INFO: Using the %s file for input\n", argv[1]);
    yyin = fopen(argv[1], "r"); 
  }
  else {
    // printf("Using the input1.in file for input\n");
    // yyin = fopen("input1.in", "r");
    printf("Using stdin for input\n");
    yyin = stdin;
  }
  
  if (!yyin) {
    printf("ERROR: input file not found\n");
    return (-1);
  }

  // Set the output stream
  yyout = stdout;
  
  //***************************************************************************
  // Do the lexical parsing
  token = yylex();
  while( true ) 
  {
    char* token_str;

    if ( token == TOK_EOF) {
      printf("Found end of file...\n");
      break;
    }

    // Determine the logical name of the lexeme
    switch( token )
    {
        case TOK_BEGIN:       token_str = (char*)"TOK_BEGIN"; break;
        case TOK_BREAK:       token_str = (char*)"TOK_BREAK"; break;
        case TOK_CONTINUE:    token_str = (char*)"TOK_CONTINUE"; break;
        case TOK_DOWNTO:      token_str = (char*)"TOK_DOWNTO"; break;
        case TOK_ELSE:        token_str = (char*)"TOK_ELSE"; break;
        case TOK_END:         token_str = (char*)"TOK_END"; break;
        case TOK_FOR:         token_str = (char*)"TOK_FOR"; break;
        case TOK_IF:          token_str = (char*)"TOK_IF"; break;
        case TOK_LET:         token_str = (char*)"TOK_LET"; break;
        case TOK_PROGRAM:     token_str = (char*)"TOK_PROGRAM"; break;
        case TOK_READ:        token_str = (char*)"TOK_READ"; break;
        case TOK_THEN:        token_str = (char*)"TOK_THEN"; break;
        case TOK_TO:          token_str = (char*)"TOK_TO"; break;
        case TOK_VAR:         token_str = (char*)"TOK_VAR"; break;
        case TOK_WHILE:       token_str = (char*)"TOK_WHILE"; break;
        case TOK_WRITE:       token_str = (char*)"TOK_WRITE"; break;

        case TOK_INTEGER:     token_str = (char*)"TOK_INTEGER"; break;
        case TOK_REAL:        token_str = (char*)"TOK_REAL"; break;

        case TOK_SEMICOLON:   token_str = (char*)"TOK_SEMICOLON"; break;
        case TOK_COLON:       token_str = (char*)"TOK_COLON"; break;
        case TOK_OPENPAREN:   token_str = (char*)"TOK_OPENPAREN"; break;
        case TOK_CLOSEPAREN:  token_str = (char*)"TOK_CLOSEPAREN"; break;
        case TOK_OPENBRACE:   token_str = (char*)"TOK_OPENBRACE"; break;
        case TOK_CLOSEBRACE:  token_str = (char*)"TOK_CLOSEBRACE"; break;

        case TOK_PLUS:        token_str = (char*)"TOK_PLUS"; break;
        case TOK_MINUS:       token_str = (char*)"TOK_MINUS"; break;
        case TOK_MULTIPLY:    token_str = (char*)"TOK_MULTIPLY"; break;
        case TOK_DIVIDE:      token_str = (char*)"TOK_DIVIDE"; break;
        case TOK_ASSIGN:      token_str = (char*)"TOK_ASSIGN"; break;
        case TOK_EQUALTO:     token_str = (char*)"TOK_EQUALTO"; break;
        case TOK_LESSTHAN:    token_str = (char*)"TOK_LESSTHAN"; break;
        case TOK_GREATERTHAN: token_str = (char*)"TOK_GREATERTHAN"; break;
        case TOK_NOTEQUALTO:  token_str = (char*)"TOK_NOTEQUALTO"; break;
        case TOK_MOD:         token_str = (char*)"TOK_MOD"; break;
        case TOK_NOT:         token_str = (char*)"TOK_NOT"; break;
        case TOK_OR:          token_str = (char*)"TOK_OR"; break;
        case TOK_AND:         token_str = (char*)"TOK_AND"; break;

        case TOK_IDENT:       token_str = (char*)"TOK_IDENT"; break;
        case TOK_INTLIT:      token_str = (char*)"TOK_INTLIT"; break;
        case TOK_FLOATLIT:    token_str = (char*)"TOK_FLOATLIT"; break;
        case TOK_STRINGLIT:   token_str = (char*)"TOK_STRINGLIT"; break;

        case TOK_UNKNOWN:     token_str = (char*)"TOK_UNKNOWN"; break;

        default:              token_str = (char*)"=== unmapped token name ===";
    }

    // What did we find?
    fprintf(yyout, "line: %d, lexeme: |%s|, length: %d, token: %s\n", 
                        yylineno, yytext, yyleng, token_str);
    
    // Is it an error?
    if( token == TOK_UNKNOWN ) {
      fprintf(yyout,"   ERROR: unknown token\n");
      // return -1; // Ed says keep on running!
    }
    
    // Get the next token
    token = yylex();
  }
  return 0;
}
