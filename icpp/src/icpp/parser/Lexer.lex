%{
    /* Implementation of yyFlexScanner */
    #include <icpp/parser/Scanner.hpp>
    #include <utils/log.hpp>

    /* typedef to make the returns for the tokens shorter */
    typedef icpp::Parser::token token;
    int icpp_line_no = 1;

    /* define yyterminate as this instead of NULL */
    #define yyterminate() return token::T_EXIT;

    /* msvc2010 requires that we exclude this header file. */
    #define YY_NO_UNISTD_H
%}

%option c++
%option yyclass="Scanner"
%option nodefault
%option noyywrap
%option prefix="Icpp"

%%

    /*************** SPECIAL TOKEN *******************/
\n {
    ++icpp_line_no;
    return token::T_EOL;
}

\/\/.*$ {
}

= {
    return token::T_EQUAL;
}
        /* separators */
"," {
    return token::T_COMA;
}

":" {
    return token::T_COLON;
}
        /* brackets */
"(" {
    return token::T_BRACKET_OPEN;
}

")" {
    return token::T_BRACKET_CLOSE;
}

"[" {
    return token::T_SQUARE_BRACKET_OPEN;
}

"]" {
    return token::T_SQUARE_BRACKET_CLOSE;
}

"{" {
    return token::T_CURLY_BRACKET_OPEN;
}

"}" {
    return token::T_CURLY_BRACKET_CLOSE;
}

        /* pointer */
"*" {
    return token::T_ASTERISK;
}

"&" {
    return token::T_AMPERSAND;
}

    /** KEYWORDS **/

exit {
    return token::T_EXIT;
}

        /* import */

from {
    return token::T_IMPORT_FROM;
}

import {
    return token::T_IMPORT_IMPORT;
}

        /* operators */
as {
    return token::T_OPERATOR_AS;
}

with {
    return token::T_OPERATOR_WITH;
}
        /* builtins */

help {
    return token::T_B_HELP;
}

print {
    return token::T_B_PRINT;
}

show {
    return token::T_B_SHOW;
}

delete {
    return token::T_B_DELETE;
}

wget {
    return token::T_B_WGET;
}

run {
    return token::T_B_RUN;
}

compile {
    return token::T_B_COMPILE;
}

source {
    return token::T_B_SOURCE;
}

        /* types */
char  {
    return token::T_TYPE_CHAR;
}

bool  {
    return token::T_TYPE_BOOL;
}

int {
    return token::T_TYPE_INT;
}

float {
    return token::T_TYPE_FLOAT;
}

    /*double {
        return T_TYPE_DOUBLE;
    }*/

string {
    return token::T_TYPE_STRING;
}

tuple {
    return token::T_TYPE_TUPLE;
}

tab {
    return token::T_TYPE_TAB;
}

dict {
    return token::T_TYPE_DICT;
}

auto {
    return token::T_TYPE_AUTO;
}
    /************** VALUES *****************/

\'.\' {
    yylval->v_char = yytext[1];
    return token::T_VALUE_CHAR;
}

true {
    yylval->v_bool = true;
    //return token::T_VALUE_BOOL;
}

false {
    yylval->v_bool = false;
    //return token::T_VALUE_BOOL;
}

[-+]?[0-9]+  {
    yylval->v_int = ::atoi(yytext);
    return token::T_VALUE_INT;
}

[-+]?[0-9]*\.?[0-9]*([eE][-+]?[0-9]+)?  {
    yylval->v_float = ::atof(yytext);
    return token::T_VALUE_FLOAT;
}

\"[^\"]*\" { 
    yylval->v_string = new std::string(yytext+1,::strlen(yytext)-2);//remove "
    return token::T_VALUE_STRING;
}

null {
    return token::T_VALUE_NULL;
}

    /**************** identifier ****************/
[a-zA-Z_][a-zA-Z0-9_]* {
    yylval->v_string = new std::string(yytext);
    return token::T_INDENTIFIER;
}

    /************** NOT CATCHED ****************/

. {
    utils::log::error("Icpp Parser","line",icpp_line_no,": what is that <",yytext,"> ?");
}

