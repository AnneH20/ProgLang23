 /*********************************************************************
  Name: Anne Marie Heidebreicht             NetID: alh1310
  Course: CSE 4714                          Assignment: Part 1
  Programming Environment: VS Code
  Purpose of File: Use flex to generate a lexical analyzer using the
  language specification in the given tables.
 **********************************************************************/

%option yylineno
%option noyywrap

%{
#include "lexer.h"
int line_number = 1;
%}

%%

 /* Begin */
BEGIN          { return TOK_BEGIN; }

 /* Break */
BREAK          { return TOK_BREAK; }

 /* Continue */
CONTINUE       { return TOK_CONTINUE; }

 /* Downto */
DOWNTO         { return TOK_DOWNTO; }

 /* Else */
ELSE           { return TOK_ELSE; }

 /* End */
END            { return TOK_END; }

 /* For */
FOR            { return TOK_FOR; }

 /* If */
IF             { return TOK_IF; }

 /* Let */
LET            { return TOK_LET; }

 /* Program */
PROGRAM        { return TOK_PROGRAM; }

 /* Read */
READ           { return TOK_READ; }

 /* Then */
THEN           { return TOK_THEN; }

 /* To */
TO             { return TOK_TO; }
 
 /* Var */
VAR            { return TOK_VAR; }

 /* While */
WHILE          { return TOK_WHILE; }

 /* Write */
WRITE          { return TOK_WRITE; }

 /* Interger */
INTEGER        { return TOK_INTEGER; }

 /* Real */
REAL           { return TOK_REAL; }

 /* Assign */
\:\=           { return TOK_ASSIGN; }

 /* Semicolon */
\;             { return TOK_SEMICOLON; }

 /* Colon */
\:             { return TOK_COLON; }

 /* Open Parentheses */
\(             { return TOK_OPENPAREN; }

 /* Close Parentheses */
\)             { return TOK_CLOSEPAREN; }

 /* Open Curly Brace */
\{             { return TOK_OPENBRACE; }

 /* Close Curly Brace */
\}             { return TOK_CLOSEBRACE; }

 /* Plus */
\+             { return TOK_PLUS; }

 /* Minus */
\-             { return TOK_MINUS; }

 /* Multiply */
\*             { return TOK_MULTIPLY; }

 /* Divide */
\/             { return TOK_DIVIDE; }

 /* Equal To */
\=             { return TOK_EQUALTO; }

 /* Less Than */
\<             { return TOK_LESSTHAN; }

 /* Greater Than */
\>             { return TOK_GREATERTHAN; }

 /* Not Equal To */
\<\>           { return TOK_NOTEQUALTO; }

 /* Mod */
MOD            { return TOK_MOD; }

 /* Not */
NOT            { return TOK_NOT; }

 /* Or */
OR             { return TOK_OR; }

 /* And */
AND            { return TOK_AND; }

 /* Identifier */
[A-Z][0-9A-Z]{0,7}  {return TOK_IDENT;}

 /* Integer Literal */                  
[0-9]+              {return TOK_INTLIT;}

 /* Floating-Point Literal */
[0-9]+\.[0-9]+     {return TOK_FLOATLIT;}

 /* String Literal */                  
\'[^'^\n]{0,78}\'     {return TOK_STRINGLIT;}
 
 /* Eat any whitespace */

[ \t\r]+
\n                                  { line_number++; }

 /* Found an unknown character */

[A-Z][0-9A-Z]{8,}     {return TOK_UNKNOWN;} // more than 8 characters long
\'[^']{79,}\'         {return TOK_UNKNOWN;} // more than 80 characters long
.         { return TOK_UNKNOWN; }

 /* Recognize end of file */

<<EOF>>   { return TOK_EOF; }


