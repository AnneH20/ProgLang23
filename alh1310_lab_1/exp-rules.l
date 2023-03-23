 /*********************************************************************
  Name: Anne Marie Heidebreicht             NetID: alh1310
  Course: CSE 4714              
  Lab: 01 - Lexical Analyzer 
  Purpose of File: Use flex to generate a lexical analyzer using the
  "language specification" in the given table.

 This is the file that you should modify for Lab 1.
 **********************************************************************/

%option noyywrap
%{
#include "lexer.h"

// global variable to hold current line number being read
int line_number = 1;
%}

%%

 /* Separator */
\,                                                                                       { return SEPARATOR; }

 /* Date */
[0-9]{4}\/[0-9]{2}\/[0-9]{2}                                                             { return DATE; }

 /* Yes */
[Yy]es                                                                                   { return YES; }

 /* No */
[Nn]o                                                                                    { return NO; }

 /* Unknown Value */
[Uu]nknown                                                                               { return UNKNOWN_VALUE; }

 /* Missing */
[Mm]issing                                                                               { return MISSING; }

 /* Laboratory */
[Ll]aboratory\-[Cc]onfirmed\ [Cc]ase                                                           { return LABORATORY; }

 /* Probable */
[Pp]robable\ [Cc]ase                                                                        { return PROBABLE; }

 /* Male */
[Mm]ale                                                                                  { return MALE; }

 /* Female */
[Ff]emale                                                                                { return FEMALE; }

 /* Other */
[Oo]ther                                                                                 { return OTHER; }

 /* Age 0X */
0\ \-\ 9\ [Yy]ears                                                                       { return AGE_0X; }

 /* Age 1X */
10\ \-\ 19\ [Yy]ears                                                                     { return AGE_1X; }

 /* Age 2X */
20\ \-\ 39\ [Yy]ears                                                                     { return AGE_2X; }

 /* Age 4X */
40\ \-\ 49\ [Yy]ears                                                                     { return AGE_4X; }

 /* Age 5X */
50\ \-\ 59\ [Yy]ears                                                                     { return AGE_5X; }

 /* Age 6X */
60\ \-\ 69\ [Yy]ears                                                                     { return AGE_6X; }

 /* Age 7X */
70\ \-\ 79\ [Yy]ears                                                                     { return AGE_7X; }

 /* Age 8X */
80\+\ [Yy]ears                                                                           { return AGE_8X; }

 /* Hispanic */
\"[Hh]ispanic\/[Ll]atino\"                                                               { return HISPANIC; }

 /* Native American */
\"[Aa]merican\ [Ii]ndian\ \/\ [Aa]laska\ [Nn]ative\,\ [Nn]on\-[Hh]ispanic\"                              { return NATIVE_AMERICAN; }

 /* Asian */
\"[Aa]sian\,\ [Nn]on\-[Hh]ispanic\"                                                            { return ASIAN; }

 /* Black */
\"[Bb]lack\,\ [Nn]on\-[Hh]ispanic\"                                                            { return BLACK; }

 /* Pacific Islander */
\"[Nn]ative\ [Hh]awaiian\ \/\ [Oo]ther\ [Pp]acific\ [Ii]slander\,\ [Nn]on\-[Hh]ispanic\"                    { return PACIFIC_ISLANDER; }

 /* White */
\"[Ww]hite\,\ [Nn]on\-[Hh]ispanic\"                                                            { return WHITE; }

 /* Multiple Other */
\"[Mm]ultiple\/[Oo]ther\,\ [Nn]on\-[Hh]ispanic\"                                                  { return MULTIPLE_OTHER; }

 /* Eat any whitespace, will need to be modified to count lines */

[ \t\r]+            /* nop */ 
\n                                  { line_number++; }


 /* Found an unknown character */

.         { return UNKNOWN_TOKEN; }

 /* Recognize end of file */

<<EOF>>   { return EOF_TOKEN; }