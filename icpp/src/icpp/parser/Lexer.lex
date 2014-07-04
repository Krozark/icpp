%{
    /* Implementation of yyFlexScanner */
    #include <icpp/parser/Scanner.hpp>
    #include <utils/log.hpp>

    /* typedef to make the returns for the tokens shorter */
    typedef icpp::Parser::token token;
    int icpp_line_no = 1;

    /* define yyterminate as this instead of NULL */
    //#define yyterminate() return token::T_END;

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

= {
    return T_EQUAL;
}
        /* separators */
"," {
    return T_COMA;
}

":" {
    return T_COLON;
}
        /* brackets */
"(" {
    return T_BRACKET_OPEN;
}

")" {
    return T_BRACKET_CLOSE;
}

"[" {
    return T_SQUARE_BRACKET_OPEN;
}

"]" {
    return T_SQUARE_BRACKET_CLOSE;
}

"{" {
    return T_CURLY_BRACKET_OPEN;
}

"}" {
    return T_CURLY_BRACKET_CLOSE;
}

        /* pointer */
"*" {
    return T_ASTERISK;
}

"&" {
    return T_AMPERSAND;
}

    /** KEYWORDS **/

exit {
    return T_EXIT;
}

        /* import */

from {
    return T_IMPORT_FROM;
}

import {
    return T_IMPORT_IMPORT;
}

        /* operators */
as {
    return T_OPERATOR_AS;
}

with {
    return T_OPERATOR_WITH;
}
        /* builtins */

help {
    return T_B_HELP;
}

print {
    return T_B_PRINT;
}

show {
    return T_B_SHOW;
}

delete {
    return T_B_DELETE;
}

wget {
    return T_B_WGET;
}

run {
    return T_B_RUN;
}

compile {
    return T_B_COMPILE;
}

source {
    return T_B_SOURCE;
}

        /* types */
char  {
    return T_TYPE_CHAR;
}

bool  {
    return T_TYPE_BOOL;
}

int {
    return T_TYPE_INT;
}

float {
    return T_TYPE_FLOAT;
}

    /*double {
        return T_TYPE_DOUBLE;
    }*/

string {
    return T_TYPE_STRING;
}

tuple {
    return T_TYPE_TUPLE;
}

tab {
    return T_TYPE_TAB;
}

dict {
    return T_TYPE_DICT;
}

auto {
    return T_TYPE_AUTO;
}
    /************** VALUES *****************/

\'.\' {
    yylval->v_char = yytext[1];
    return T_VALUE_CHAR;
}

true {
    yylval->v_bool = true;
    return token::T_VALUE_BOOL;
}

false {
    yylval->v_bool = false;
    return token::T_VALUE_BOOL;
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
    return token::T_NULL;
}

    /**************** KEYWORDS ****************/
    

    /************** NOT CATCHED ****************/

. {
    utils::log::error("Icpp Parser","line",icpp_line_no,": what is that <",yytext,"> ?");
}

