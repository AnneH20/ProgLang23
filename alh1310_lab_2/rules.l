/******************************************************************* 
purpose: CSE 4714 / 6714 flex rules file for Lab 2
version: Spring 2022
author: Joe Crumpton / Ed Swan
 *******************************************************************/
%option yylineno
%option noyywrap
%{
#include "lexer.h"
%}

%%

  /* Parts of speech */

(dog|trousers|daughter|nose|homework|time\ lord|pony)         { return NOUN; }             
(the|a|some|every|that)                                       { return ARTICLE; } 
(my|your|his|her)                                             { return POSSESSIVE; }
(friendly|furious|moist|green|severed|timey-wimey|little)     { return ADJECTIVE; }        
(ate|found|wrote|killed|mangled|saved|invented|broke)         { return VERB; }             
(squarely|incompetently|barely|sort\ of|awkwardly|totally)    { return ADVERB; }           

 /* Eat any whitespace */

[ \t\r\n]+             /* nop */

 /* Found an unknown character */

.         { return TOK_UNKNOWN; }

 /* Recognize end of file */

<<EOF>>   { return TOK_EOF; }


