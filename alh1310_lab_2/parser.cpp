/*
Name: Anne Marie Heidebreicht
NetID: alh1310
Course: CSE 4714
Lab: 02 - Parsing
Purpose: Create a recursive descent parser for a subset of English sentences.
*/

#include <stdio.h>
#include <iostream>
#include "lexer.h"
#include "parser.h"

using namespace std;

extern "C"
{
  extern int   yylex();      // the generated lexical analyzer
  extern char *yytext;       // text of current lexeme
}

// Initialize nextToken and sentence phrase counters
int nextToken = 0;
int verbPhrase = 0;
int nounPhrase = 0;
int adjectivePhrase = 0;

// Production functions
bool firstOf_sentence();
void noun_phrase();
void adjective_phrase();
void verb_phrase();

//*****************************************************************************
// Get the next lexeme (word in sentence)
int lex() {
  nextToken = yylex();
  if( nextToken == TOK_EOF ) {
    yytext[0] = 'E'; yytext[1] = 'O'; yytext[2] = 'F'; yytext[3] = 0;   
  }

  printf("Next token: %d, lexeme: |%s|\n", nextToken, yytext);
  return nextToken;
}
//*****************************************************************************
// Report what we found
void output( string what ) {
  cout << "===> Accepted " << what << ": |" << yytext << "| <===" << endl;
}
//*****************************************************************************
// <sentence> -> <noun phrase> <verb phrase> <noun phrase>
// <sentence> -> <adjective phrase> NOUN <verb phrase> <adjective phrase> NOUN
// <sentence> -> (ARTICLE | POSSESSIVE) ADJECTIVE NOUN <verb phrase> etc etc
void sentence() 
{
  if( firstOf_sentence() == false )
  {
    throw("<sentence> did not start with an article or possessive.");
  }
  cout << "Enter <sentence>" << endl;
  noun_phrase();
  verb_phrase();
  noun_phrase();
  cout << "Exit <sentence>" << endl;
} 
//*****************************************************************************
bool firstOf_sentence() {
  if (nextToken == ARTICLE || nextToken == POSSESSIVE)
  {
    return true;    
  }
  else
  {
    return false;
  }
}
//*****************************************************************************
// <noun phrase> -> <adjective phrase> NOUN
void noun_phrase()
{
  if (nextToken == ARTICLE || nextToken == POSSESSIVE)
  {
    nounPhrase++;
    for (int i = 0; i < nounPhrase; i++)
    {
      cout << "  ";
    }
    cout << "Enter <noun phrase> " << nounPhrase << endl;
  }
  else
  {
    throw("<noun phrase> did not start with an article or possessive.");
  }    
  adjective_phrase();
  if (nextToken == NOUN)
  {
    output("NOUN");
    lex();   
  }  
  else
  {
    throw("<noun phrase> did not have a noun");
  }  
  for (int i = 0; i < nounPhrase; i++)
  {
    cout << "  ";
  }
    cout << "Exit <noun phrase> " << nounPhrase << endl;    
}
//*****************************************************************************
// <adjective phrase> -> (ARTICLE | POSSESSIVE) ADJECTIVE
void adjective_phrase()
{
  if (nextToken == ARTICLE || nextToken == POSSESSIVE)
  {
    adjectivePhrase++;
    for (int i = 0; i < adjectivePhrase; i++)
    {
      cout << "  ";
    }  
    cout << "Enter <adjective phrase> " << adjectivePhrase << endl;
  }
    else
    {
      throw("<adjective phrase> did not start with an article or possessive.");
    }
    if (nextToken == ARTICLE)
    {
      output("ARTICLE"); // check for an article
    }
    if (nextToken == POSSESSIVE) // check for a possessive
    {
      output("POSSESSIVE");
    }
    lex();
    if (nextToken == ADJECTIVE) // check for an adjective
    {
      output("ADJECTIVE");
      lex();
      for (int i = 0; i < adjectivePhrase; i++)
      {
        cout << "  ";
      }    
      cout << "Exit <adjective phrase> " << adjectivePhrase << endl;        
    }
    else
    {
      throw("<adjective phrase> did not have an adjective.");      
    }
}
//*****************************************************************************
// <verb phrase> -> VERB | ADVERB <verb phrase>
void verb_phrase()
{
  if (nextToken == VERB || nextToken == ADVERB)
  {
    verbPhrase++;    
    for (int i = 0; i < verbPhrase; i++)
    {
      cout << "  ";    
    }
    cout << "Enter <verb phrase> " << verbPhrase << endl;      
    if (nextToken == ADVERB) // check for an adverb
    {
      output("ADVERB");
      lex();
      verb_phrase(); // recursive call to verb_phrase
      verbPhrase--;
      for (int i = 0; i < verbPhrase; i++)
      {
        cout << "  ";    
      }
      cout << "Exit <verb phrase> " << verbPhrase << endl;
    }    
    if (nextToken == VERB) // check for a verb
    {
      output("VERB");
      lex();
      for (int i = 0; i < verbPhrase; i++)
      {
        cout << "  ";    
      }
      cout << "Exit <verb phrase> " << verbPhrase << endl;
    }    

  }
  else
  {
    throw("<verb phrase> did not start with a verb or an adverb.");
  }
}
//*****************************************************************************