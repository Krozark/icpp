 /* use newer C++ skeleton file */
%skeleton "lalr1.cc"
/* Require bison version or later */
%require "3.0.2"
/* verbose error messages */
/*%error-verbose*/
/* namespace to enclose parser in */
%define api.namespace {icpp}
/* set the parser's class identifier */
%define parser_class_name {Parser}

%lex-param { icpp::Scanner& scanner }
%parse-param { icpp::Scanner& scanner }

%parse-param { icpp::Driver& driver }

%code requires {

    #include <utility>

    extern int icpp_line_no; 

    namespace icpp {
            class Scanner;
            class Driver;
        }
}

%code{
    #include <icpp/parser/Driver.hpp>
    #include <string>
	/*Prototype for the yylex function*/
	static int yylex(icpp::Parser::semantic_type* yylval, icpp::Scanner& scanner);

    #define DEL(x) delete x; x=nullptr;
}



%union
{
    // "Pure" types
    bool            v_bool;
    char            v_char;
    int             v_int;
    float           v_float;
    double          v_double;
    std::string*    v_string;
    // Pointers to more complex classes
    /*
    utils::json::Object* v_object;
    utils::json::Array* v_array;
    utils::json::Value* v_value;
    */
} 

    
/** Declare tokens */
%token      T_SQUARE_BRACKET_L        "square bracket left"
%token      T_SQUARE_BRACKET_R        "square bracket right"
%token      T_CURLY_BRACKET_L         "curry bracket left"
%token      T_CURLY_BRACKET_R         "curry bracket right"
%token      T_COMMA                   "coma"
%token      T_COLON                   "colon"

%token      T_NUMBER_I                "integer"
%token      T_NUMBER_F                "float"
%token      T_BOOLEAN                 "boolean"
%token      T_NULL                    "null"
%token      T_DOUBLE_QUOTED_STRING    "double quoted string"


%start start
/** Define types for union values */
%type<v_int>    T_NUMBER_I
%type<v_float>  T_NUMBER_F
%type<v_bool>   T_BOOLEAN
%type<v_string> T_DOUBLE_QUOTED_STRING str


%%

start:  {
     };

%%

void icpp::Parser::error(const std::string &message)
{
   std::cerr<<"Error line "<<icpp_line_no<<" : "<<message<<std::endl;; 
}
 
/*Now that we have the Parser declared, we can declare the Scanner and implement the yylex function*/
#include <icpp/parser/Scanner.hpp>
#include <icpp/parser/Driver.hpp>
static int yylex(icpp::Parser::semantic_type *yylval,icpp::Scanner& scanner)
{
    return scanner.yylex(yylval);
}
