/*****************************************************************************
  Name: Anne Marie Heidebreicht             NetID: alh1310
  Course: CSE 4714                          Assignment: Part 2
  Programming Environment: VS Code
  Purpose of File: Using the rules.l file from Part 1, create a recursive
  descent parser for a subset of Ten Instruction Pascal Set (TIPS).
******************************************************************************/

#ifndef PRODUCTIONS_H
#define PRODUCTIONS_H

#include <iostream>
using namespace std;

extern set<string> symbolTable;
int nextToken = 0;  // token returned from yylex
int level = 0;  // used to indent output to approximate parse tree
int num = 0; // check number of identifier declarations
set<string>::iterator i; // used to iterate over the symbolTable set (Source: https://www.geeksforgeeks.org/different-ways-to-iterate-over-a-set-in-c/)
//*****************************************************************************
extern "C"
{
	// Instantiate global variables used by flex
	extern char* yytext;       // text of current lexeme
	extern int   yylex();      // the generated lexical analyzer
}
//*****************************************************************************
// Forward declarations of production parsing functions
void program();
void block();
void statement();
void assignment();
void compound();
void ifStatement();
void whileStatement();
void read();
void write();
void expression();
void simpleExpression();
void term();
void factor();
//*****************************************************************************
// Forward declarations of functions that check whether the current token is
// in the first set of a production rule
bool first_of_program(void);
bool first_of_block(void);
bool first_of_statement(void);
bool first_of_assignment(void);
bool first_of_compound(void);
bool first_of_if(void);
bool first_of_while(void);
bool first_of_read(void);
bool first_of_write(void);
bool first_of_expression(void);
bool first_of_simple_expression(void);
bool first_of_term(void);
bool first_of_factor(void);
//*****************************************************************************
inline void indent(){
    for (int i = 0; i<level; i++)
        cout << ("    ");
}

void output(){
    indent();
    cout << "-->found " << yytext << endl;
}
//*****************************************************************************
// <program> → TOK_PROGRAM TOK_IDENT TOK_SEMICOLON <block>
void program() {
    if (!first_of_program()) // Check for PROGRAM
    {
        throw "3: 'PROGRAM' expected";
    }
    cout << "enter <program>" << endl;
    indent();
    ++level;
    output();
    nextToken = yylex();
    output();
    if (nextToken != TOK_IDENT)
    {
        throw "2: identifier expected";
    }
    nextToken = yylex();
    if (nextToken != TOK_SEMICOLON)
    {
        throw "14: ';' expected";
    }
    output();
    nextToken = yylex();
    if (!first_of_block())
    {
        throw "18: error in declaration part OR 17: 'BEGIN' expected";
    }
    while (nextToken != TOK_END && nextToken != TOK_EOF)
    {
        block();
    }
    --level;
    indent();
    cout << "exit <program>" << endl;
    nextToken = yylex();
}

// <block> → [ TOK_VAR TOK_IDENT TOK_COLON (TOK_INTEGER | TOK_REAL) TOK_SEMICOLON { TOK_IDENT TOK_COLON (TOK_INTEGER | TOK_REAL) TOK_SEMICOLON } ] <compound>
void block() {
    indent();
    cout << "enter <block>" << endl;
    ++level;
    if (nextToken == TOK_VAR)
    {
        output();
        nextToken = yylex();
        if (nextToken != TOK_IDENT)
        {
            throw "2: identifier expected";
        }
        // iterate over the symbolTable set (Source: https://www.geeksforgeeks.org/different-ways-to-iterate-over-a-set-in-c/)
        for (i = symbolTable.begin(); i != symbolTable.end(); ++i)
        {
            string t;
            t = string(*i);
            if (t == yytext)
            {
                throw "101: identifier declared twice";
            }
        }
        symbolTable.insert(yytext);
        output();
        nextToken = yylex();
        output();
        if (nextToken != TOK_COLON)
        {
            throw "5 : ':' expected";
        }
        nextToken = yylex();
        output();
        if (nextToken != TOK_INTEGER && nextToken != TOK_REAL)
        {
            throw "10: error in type";
        }
        nextToken = yylex();
        output();
        if (nextToken != TOK_SEMICOLON)
        {
            throw "14: ';' expected";
        }
        nextToken = yylex();
        while (nextToken != TOK_SEMICOLON && nextToken != TOK_BEGIN)
        {
            cout << endl;
            if (nextToken != TOK_IDENT)
            {
                throw "2: identifier expected";
            }
            for (i = symbolTable.begin(); i != symbolTable.end(); ++i)
            {
                string t;
                t = string(*i);
                if (t == yytext)
                {
                    throw "101: identifier declared twice";
                }
            }
            symbolTable.insert(yytext);
            output();            
            nextToken = yylex();
            output();
            if (nextToken != TOK_COLON)
            {
                throw "5 : ':' expected";
            }
            nextToken = yylex();
            output();
            if (nextToken != TOK_INTEGER && nextToken != TOK_REAL)
            {
                throw "10: error in type";
            }
            nextToken = yylex();
            output();
            if (nextToken != TOK_SEMICOLON)
            {
                throw "14: ';' expected";
            }
            nextToken = yylex();
        }
        cout << endl;
    }
    if (nextToken != TOK_BEGIN)
    {
        throw "18: error in declaration part OR 17: 'BEGIN' expected";
    }
    compound();
    while (nextToken != TOK_END && nextToken != TOK_EOF)
    {
        if (nextToken != TOK_SEMICOLON)
        {
            throw "14: ';' expected";
        }
        compound();
    }
    yylex();
    --level;
    indent();
    cout << "exit <block>" << endl;
}

// <statement> → <assignment> | <compound> | <if> | <while> | <read> | <write>
void statement() {
    indent();
    cout << "enter <statement>" << endl;
    ++level;
    if (nextToken == TOK_IDENT) 
    {
        assignment();
    } 
    else if (nextToken == TOK_BEGIN || nextToken == TOK_THEN)
    {
        compound();
    } 
    else if (nextToken == TOK_IF) 
    {
        ifStatement();
        if (nextToken == TOK_END)
        {
            nextToken = yylex();
        }
    } 
    else if (nextToken == TOK_WHILE) 
    {
        whileStatement();
    } 
    else if (nextToken == TOK_READ) 
    {
        read();
    } 
    else if (nextToken == TOK_WRITE) 
    {
        write();
    } 
    else 
    {
        if (nextToken != TOK_SEMICOLON) 
        {
            throw ("14: ';' expected");
        }
    }
    --level;
    indent();
    cout << "exit <statement>" << endl;
}

// <assignment> → TOK_IDENT TOK_ASSIGN <expression>
void assignment() {
    indent();
    cout << "enter <assignment>" << endl;
    ++level;
    output();
    symbolTable.insert(yytext);
    nextToken = yylex();
    output();
    if (nextToken != TOK_ASSIGN)
    {
        throw "51: ':=; expected";
    }
    nextToken = yylex();
    if (!first_of_expression())
    {
        throw "901: illegal type of simple expression";
    }
    expression();
    --level;
    indent();
    cout << "exit <assignment>" << endl;
}

// <compound> → TOK_BEGIN <statement> { TOK_SEMICOLON <statement> } TOK_END
void compound() {
    indent();
    cout << "enter <compound_statement>" << endl;
    ++level;
    output();
    nextToken = yylex();
    if (!first_of_statement())
    {
        throw "900: illegal type of statement";
    }
    statement();
    while (nextToken == TOK_SEMICOLON)
    {
        output();
        nextToken = yylex();
        if (!first_of_statement())
        {
            throw "900: illegal type of statement";
        }
        statement();
        if (nextToken == TOK_EOF)
        {
            indent();
            cout << "-->found END" << endl;
        }
    }
    if (nextToken != TOK_EOF)
    {
        output();       
    }
    --level;
    indent();
    cout << "exit <compound_statement>" << endl;
}

// <if> → TOK_IF <expression> TOK_THEN <statement> [ TOK_ELSE <statement> ]
void ifStatement() {
    indent();
    cout << "enter <if statement>" << endl;
    ++level;
    output();
    nextToken = yylex();
    if (!first_of_expression())
    {
        throw "144: illegal type of expression";
    }
    expression();
    if (nextToken != TOK_THEN)
    {
        throw "52: 'THEN' expected";
    }
    output();
    nextToken = yylex();
    if (!first_of_statement())
    {
        throw "900: illegal type of statement";
    }
    statement();
    if (nextToken != TOK_ELSE)
    {
        nextToken = yylex();
        if (nextToken == TOK_ELSE)
        {
            output();
            nextToken = yylex();
            if (!first_of_statement())
            {
                throw "900: illegal type of statement";
            }
            statement();            
        }
    }
    else
    {
        output();
        nextToken = yylex();
        if (!first_of_statement())
        {
            throw "900: illegal type of statement";
        }
        statement();
    }     
    --level;    
    indent();
    cout << "exit <if statement>" << endl;
}

// <while> → TOK_WHILE <expression> <statement>
void whileStatement() {
    indent();
    cout << "enter <while statement>" << endl;
    ++level;
    output();
    if (nextToken == TOK_WHILE)
    {
        nextToken = yylex();
        if (!first_of_expression())
        {
            throw "144: illegal type of expression";
        }
        expression();
        if(!first_of_statement())
        {
            throw "900: illegal type of statement";
        }
        statement();
    }
    nextToken = yylex();
    --level;
    indent();
    cout << "exit <while statement>" << endl;
}

// <read> → TOK_READ TOK_OPENPAREN TOK_IDENT TOK_CLOSEPAREN
void read() {
    indent();
    cout << "enter <read>" << endl;
    ++level;
    output();
    nextToken = yylex();
    if( nextToken == TOK_EOF )
    {
        yytext[0] = 'E'; 
        yytext[1] = 'O';
        yytext[2] = 'F'; 
        yytext[3] = 0; 
    } 
    else if (nextToken == TOK_IDENT) 
    {
        symbolTable.insert(yytext);
    } 
    if (nextToken != TOK_OPENPAREN)
    {
        throw "9: '(' expected";
    }
    output();
    nextToken = yylex();
    if( nextToken == TOK_EOF )
    {
        yytext[0] = 'E'; 
        yytext[1] = 'O';
        yytext[2] = 'F'; 
        yytext[3] = 0; 
    } 
    else if (nextToken == TOK_IDENT) 
    {
        symbolTable.insert(yytext);
    }
    if (nextToken != TOK_IDENT)
    {
        throw "2: identifier expected";
    }
    output();
    nextToken = yylex();
    if( nextToken == TOK_EOF )
    {
        yytext[0] = 'E'; 
        yytext[1] = 'O';
        yytext[2] = 'F'; 
        yytext[3] = 0; 
    } 
    else if (nextToken == TOK_IDENT) 
    {
        symbolTable.insert(yytext);
    }
    if (nextToken != TOK_CLOSEPAREN)
    {
        throw "4: ')' expected";
    }
    output();
    nextToken = yylex();
    if( nextToken == TOK_EOF )
    {
        yytext[0] = 'E'; 
        yytext[1] = 'O';
        yytext[2] = 'F'; 
        yytext[3] = 0; 
    } 
    else if (nextToken == TOK_IDENT) 
    {
        symbolTable.insert(yytext);
    }
    --level;
    indent();
    cout << "exit <read>" << endl;
}

// <write> → TOK_WRITE TOK_OPENPAREN ( TOK_IDENT | TOK_STRINGLIT ) TOK_CLOSEPAREN
void write() {
    indent();
    cout << "enter <write>" << endl;
    ++level;
    output();
    nextToken = yylex();
    if( nextToken == TOK_EOF )
    {
        yytext[0] = 'E'; 
        yytext[1] = 'O';
        yytext[2] = 'F'; 
        yytext[3] = 0; 
    } 
    else if (nextToken == TOK_IDENT) 
    {
        symbolTable.insert(yytext);
    } 
    if (nextToken != TOK_OPENPAREN)
    {
        throw "9: '(' expected";
    }
    output();
    nextToken = yylex();
    if( nextToken == TOK_EOF )
    {
        yytext[0] = 'E'; 
        yytext[1] = 'O';
        yytext[2] = 'F'; 
        yytext[3] = 0; 
    } 
    else if (nextToken == TOK_IDENT) 
    {
        symbolTable.insert(yytext);
    }
    if (nextToken != TOK_IDENT && nextToken != TOK_STRINGLIT)
    {
        throw "134: illegal type of operand(s)";
    }
    output();
    nextToken = yylex();
    if( nextToken == TOK_EOF )
    {
        yytext[0] = 'E'; 
        yytext[1] = 'O';
        yytext[2] = 'F'; 
        yytext[3] = 0; 
    } 
    else if (nextToken == TOK_IDENT) 
    {
        symbolTable.insert(yytext);
    }
    if (nextToken != TOK_CLOSEPAREN)
    {
        throw "4: ')' expected";
    }
    output();
    nextToken = yylex();
    if( nextToken == TOK_EOF )
    {
        yytext[0] = 'E'; 
        yytext[1] = 'O';
        yytext[2] = 'F'; 
        yytext[3] = 0; 
    } 
    else if (nextToken == TOK_IDENT) 
    {
        symbolTable.insert(yytext);
    } 
    --level;
    indent();
    cout << "exit <write>" << endl;
}

// <expression> → <simple expression>  [ ( TOK_EQUALTO | TOK_LESSTHAN | TOK_GREATERTHAN | TOK_NOTEQUALTO ) <simple expression> ]
void expression() {
    indent();
    cout << "enter <expression>" << endl;
    ++level;
    if (!first_of_simple_expression())
    {
        throw "144: illegal type of expression";
    }
    simpleExpression();
    switch (nextToken)
    {
        case TOK_EQUALTO:
        {
            output();
            nextToken = yylex();
            if( nextToken == TOK_EOF )
            {
                yytext[0] = 'E'; 
                yytext[1] = 'O';
                yytext[2] = 'F'; 
                yytext[3] = 0; 
            } 
            else if (nextToken == TOK_IDENT) 
            {
                symbolTable.insert(yytext);
            }
            if (!first_of_simple_expression())
            {
                throw "901: illegal type of simple expression";
            }
            simpleExpression();
            break;
        }
        case TOK_LESSTHAN:
        {
            output();
            nextToken = yylex();
            if( nextToken == TOK_EOF )
            {
                yytext[0] = 'E'; 
                yytext[1] = 'O';
                yytext[2] = 'F'; 
                yytext[3] = 0; 
            } 
            else if (nextToken == TOK_IDENT) 
            {
                symbolTable.insert(yytext);
            }
            if (!first_of_simple_expression())
            {
                throw "901: illegal type of simple expression";
            }
            simpleExpression();
            break;
        }
        case TOK_GREATERTHAN:
        {
            output();
            nextToken = yylex();
            if( nextToken == TOK_EOF )
            {
                yytext[0] = 'E'; 
                yytext[1] = 'O';
                yytext[2] = 'F'; 
                yytext[3] = 0; 
            } 
            else if (nextToken == TOK_IDENT) 
            {
                symbolTable.insert(yytext);
            }
            if (!first_of_simple_expression())
            {
                throw "901: illegal type of simple expression";
            }
            simpleExpression();
            break;
        }
        case TOK_NOTEQUALTO:
        {
            output();
            nextToken = yylex();
            if( nextToken == TOK_EOF )
            {
                yytext[0] = 'E'; 
                yytext[1] = 'O';
                yytext[2] = 'F'; 
                yytext[3] = 0; 
            } 
            else if (nextToken == TOK_IDENT) 
            {
                symbolTable.insert(yytext);
            }
            if (!first_of_simple_expression())
            {
                throw "901: illegal type of simple expression";
            }
            simpleExpression();
            break;
        }
        default:
        {
            break;
        }
    }
    --level;
    indent();
    cout << "exit <expression>" << endl;
}

// <simple expression> → <term> { ( TOK_PLUS | TOK_MINUS | TOK_OR ) <term> }
void simpleExpression() {
    indent();
    cout << "enter <simple expression>" << endl;
    ++level;
    if (!first_of_term())
    {
        throw "902: illegal type of tern";
    }
    term();
    while (nextToken != TOK_SEMICOLON && nextToken != TOK_END && nextToken != TOK_EOF && nextToken != TOK_EQUALTO && nextToken != TOK_GREATERTHAN && nextToken != TOK_LESSTHAN && nextToken != TOK_NOTEQUALTO && nextToken != TOK_THEN && nextToken != TOK_ELSE && nextToken != TOK_CLOSEPAREN && nextToken != TOK_BEGIN)
    {
        switch (nextToken)
        {
            case TOK_PLUS:
            {
                output();
                nextToken = yylex();
                if (!first_of_term())
                {
                    throw "902: illegal type of term";
                }
                term();
                break;
            }
            case TOK_MINUS:
            {
                output();
                nextToken = yylex();
                if (!first_of_term())
                {
                    throw "902: illegal type of term";
                }
                term();
                break;
            }
            case TOK_OR:
            {
                output();
                nextToken = yylex();
                if (!first_of_term())
                {
                    throw "902: illegal type of term";
                }
                term();
                break;
            }
            default:
            {
                break;
            }
        }
    }
    --level;
    indent();
    cout << "exit <simple expression>" << endl;
}

// <term> → <factor> { ( TOK_MULTIPLY | TOK_DIVIDE | TOK_AND ) <factor> }
void term() {
    indent();
    cout << "enter <term>" << endl;
     ++level;   
    if (!first_of_factor())
    {
        throw "903: illegal type of factor";
    }
    factor();
    while (nextToken != TOK_NOT && nextToken != TOK_MINUS && nextToken != TOK_SEMICOLON && nextToken != TOK_EOF && nextToken != TOK_GREATERTHAN && nextToken != TOK_LESSTHAN && nextToken != TOK_EQUALTO && nextToken != TOK_NOTEQUALTO && nextToken != TOK_THEN && nextToken != TOK_ELSE && nextToken != TOK_CLOSEPAREN && nextToken != TOK_BEGIN && nextToken != TOK_PLUS && nextToken != TOK_END)
    {
        switch (nextToken)
        {
            case TOK_MULTIPLY:
            {
                output();
                nextToken = yylex();
                if (!first_of_factor())
                {
                    throw "903: illegal type of factor";
                }
                factor();
                break;
            }
            case TOK_DIVIDE:
            {
                output();
                nextToken = yylex();
                if (!first_of_factor())
                {
                    throw "903: illegal type of factor";
                }
                factor();
                break;
            }
            case TOK_AND:
            {
                output();
                nextToken = yylex();
                if (!first_of_factor())
                {
                    throw "903: illegal type of factor";
                }
                factor();
                break;
            }
            default:
            {
                break;
            }
        }
    }
    --level;
    indent();
    cout << "exit <term>" << endl;
}

// <factor> → TOK_INTLIT | TOK_FLOATLIT | TOK_IDENT |
void factor() {
    indent();
    cout << "enter <factor>" << endl;
    ++level;
    if (nextToken == TOK_INTLIT || nextToken == TOK_FLOATLIT)
    {
        output();
        nextToken = yylex();
    } 
    else if (nextToken == TOK_IDENT)
    {
        // iterate over the symbolTable set (Source: https://www.geeksforgeeks.org/different-ways-to-iterate-over-a-set-in-c/)
        for (i = symbolTable.begin(); i != symbolTable.end(); ++i) 
        {
            string t;
            t = string(*i);
            if (t == yytext)
            {
                ++num;
            }
        }
        if (num == 0)
        {
            throw ("104: identifier not declared");
        }
        --num;
        if (num > 1)
        {
            throw ("101: identifier declared twice");
        }
        output();
        nextToken = yylex();
    } 
    else if (nextToken == TOK_OPENPAREN)
    {
        output();
        nextToken = yylex();
        if (!first_of_expression())
        {
            throw ("144: illegal type of expression");
        }
        expression();
        output();
        if (nextToken != TOK_CLOSEPAREN)
        {
            throw ("4: ')' expected");
        }
        nextToken = yylex();
    }
    else if (nextToken == TOK_NOT)
    {
        output();
        nextToken = yylex();
        if (!first_of_factor())
        {
            throw ("903: illegal type of factor");
        }
        for (i = symbolTable.begin(); i != symbolTable.end(); ++i) 
        {
            string t;
            t = string(*i);
            if (t == yytext)
            {
                ++num;
            }
        }
        if (num == 0)
        {
            throw ("104: identifier not declared");
        }
        --num;
        if (num > 1) 
        {
            throw ("101: identifier declared twice");
        }
        factor();
    } 
    else if (nextToken == TOK_MINUS) 
    {
        output();
        nextToken = yylex();
        if (!first_of_factor()) 
        {
            throw "903: illegal type of factor";
        }
        if (nextToken == TOK_IDENT) 
        {
	        for (i = symbolTable.begin(); i != symbolTable.end(); ++i) 
            {
	            string t;
	            t = string(*i);
	            if (t == yytext) 
                {
	                ++num;
	            }
	        }
	        if (num == 0) 
            {
	            throw ("104: identifier not declared");
            }
	        --num;
	        if (num > 1)
            {
	            throw "101: identifier declared twice";
            }
        }
        factor();
    } 
    else 
    {
        throw ("903: illegal type of factor");
    }
    --level;
    indent();
    cout << "exit <factor>" << endl;
}
//*****************************************************************************
bool first_of_program(void) {
    return nextToken = TOK_PROGRAM;
}
bool first_of_block(void) {
    return nextToken == TOK_VAR || nextToken == TOK_BEGIN;
}
bool first_of_statement(void) {
    return nextToken == TOK_IDENT || nextToken == TOK_BEGIN || nextToken == TOK_IF || nextToken == TOK_WHILE || nextToken == TOK_READ || nextToken == TOK_WRITE;
}
bool first_of_assignment(void) {
    return nextToken == TOK_IDENT;
}
bool first_of_compound(void) {
    return nextToken == TOK_BEGIN;
}
bool first_of_if(void) {
    return nextToken == TOK_IF;
}
bool first_of_while(void) {
    return nextToken == TOK_WHILE;
}
bool first_of_read(void) {
    return nextToken == TOK_READ;
}
bool first_of_write(void) {
    return nextToken == TOK_WRITE;
}
bool first_of_expression(void) {
    return nextToken == TOK_INTLIT || nextToken == TOK_FLOATLIT || nextToken == TOK_IDENT || nextToken == TOK_OPENPAREN || TOK_NOT || TOK_MINUS;
}
bool first_of_simple_expression(void) {
    return nextToken == TOK_INTLIT || nextToken == TOK_FLOATLIT || nextToken == TOK_IDENT || nextToken == TOK_OPENPAREN || TOK_NOT || TOK_MINUS;
}
bool first_of_term(void) {
    return nextToken == TOK_INTLIT || nextToken == TOK_FLOATLIT || nextToken == TOK_IDENT || nextToken == TOK_OPENPAREN || TOK_NOT || TOK_MINUS;
}
bool first_of_factor(void) {
    return nextToken == TOK_INTLIT || nextToken == TOK_FLOATLIT || nextToken == TOK_IDENT || nextToken == TOK_OPENPAREN || TOK_NOT || TOK_MINUS;
}
//*****************************************************************************

#endif
