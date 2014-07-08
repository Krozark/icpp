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
    #include <icpp/Value.hpp>

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

    #define DEBUG 1

    #define DEL(x) delete x; x=nullptr;

    #define OUT std::cout

/* tuple : T_BRACKET_OPEN T_BRACKET_CLOSE
      ;

dic : T_CURLY_BRACKET_OPEN T_CURLY_BRACKET_CLOSE
    ;

tab : T_SQUARE_BRACKET_OPEN T_SQUARE_BRACKET_CLOSE
    ;
 */

/*affectation_char : T_TYPE_CHAR T_INDENTIFIER T_EQUAL T_VALUE_CHAR {
                    bool p = driver.context().create_value(*$2,$4);
                    DEL($2);
                    if(not p)
                        YYERROR;
                 }
                 ;
*/
}



%union
{
    // "Pure" types
    bool            v_bool;
    char            v_char;
    int             v_int;
    double          v_float;
    std::string*    v_string;
    icpp::Value*    v_value;
    // Pointers to more complex classes
    /*
    utils::json::Object* v_object;
    utils::json::Array* v_array;
    utils::json::Value* v_value;
    */
} 

    
/** Declare tokens */
    /* specials */
%token      T_EOL                   "end of line"
%token      T_EQUAL                 "symbol ="
%token      T_COMA                  "symbol ,"
%token      T_COLON                 "symbol :"
%token      T_BRACKET_OPEN          "symbol ("
%token      T_BRACKET_CLOSE         "symbol )"
%token      T_SQUARE_BRACKET_OPEN   "symbol ["
%token      T_SQUARE_BRACKET_CLOSE  "symbol ]"
%token      T_CURLY_BRACKET_OPEN    "symbol {"
%token      T_CURLY_BRACKET_CLOSE   "symbol }"
    /* pointer */
%token      T_ASTERISK              "symbol *"
%token      T_AMPERSAND             "symbol &"
    /* kewords */
%token      T_EXIT                  "keyword exit"
    /* import */
%token      T_IMPORT_FROM           "keyword from"
%token      T_IMPORT_IMPORT         "keyword import"
    /* operators */

%token      T_OPERATOR_AS           "keyword as"
%token      T_OPERATOR_WITH         "keyword with"
    /* builtins */
%token      T_B_HELP                "builtin function help"
%token      T_B_PRINT               "builtin function print"
%token      T_B_SHOW                "builtin function show"
%token      T_B_DELETE              "builtin function delete"
%token      T_B_WGET                "builtin function wget"
%token      T_B_RUN                 "builtin function run"
%token      T_B_COMPILE             "builtin function compile"
%token      T_B_SOURCE              "builtin function source"
    /* type */
%token      T_TYPE_CHAR             "type char"
%token      T_TYPE_BOOL             "type bool"
%token      T_TYPE_INT              "type int"
%token      T_TYPE_FLOAT            "type float"
%token      T_TYPE_STRING           "type string"
%token      T_TYPE_TUPLE            "type tuple"
%token      T_TYPE_TAB              "type tab"
%token      T_TYPE_DICT             "type dict"
%token      T_TYPE_AUTO             "type auto"
    /* values*/
%token      T_VALUE_CHAR            "value char"
%token      T_VALUE_BOOL            "value bool"
%token      T_VALUE_INT             "value int"
%token      T_VALUE_FLOAT           "value float"
%token      T_VALUE_STRING          "value string"
%token      T_VALUE_NULL            "value null"
    /* identifier */
%token      T_INDENTIFIER           "identifier"
    


%start start
/** Define types for union values */
%type<v_char>   T_VALUE_CHAR
%type<v_bool>   T_VALUE_BOOL
%type<v_int>    T_VALUE_INT
%type<v_float>  T_VALUE_FLOAT
%type<v_string> T_VALUE_STRING
%type<v_string> T_INDENTIFIER

%type<v_value>  value_tmp;


%%

start:  statements T_EXIT {
        YYACCEPT;
     }
     ;


statements : statement {}
           | statements statement {}
           | error {error("Parse error");}
           ;

statement : T_EOL 
          | declaration T_EOL
          | affectation T_EOL
          | print T_EOL
          | show T_EOL
          ;

declaration : T_TYPE_CHAR T_INDENTIFIER {
                bool p = driver.context().create_value(*$2,'0');
                DEL($2);
                if(not p)
                    YYERROR;
            }
            | T_TYPE_BOOL T_INDENTIFIER {
                bool p = driver.context().create_value(*$2,false);
                DEL($2);
                if(not p)
                    YYERROR;
            }
            | T_TYPE_INT T_INDENTIFIER {
                bool p = driver.context().create_value(*$2,0);
                DEL($2);
                if(not p)
                    YYERROR;
            }
            | T_TYPE_FLOAT T_INDENTIFIER {
                bool p = driver.context().create_value(*$2,0.f);
                DEL($2);
                if(not p)
                    YYERROR;
            }
            | T_TYPE_STRING T_INDENTIFIER {
                bool p = driver.context().create_value(*$2,"");
                DEL($2);
                if(not p)
                    YYERROR;
            }
            ;

affectation : affectation_primitif
            /*affectation_char
            | affectation_bool
            | affectation_int
            | affectation_float
            | affectation_string
            | affectation_auto*/
            ;

affectation_primitif : T_INDENTIFIER T_EQUAL value_tmp {
                        bool p = driver.context().change_value(*$1,std::move(*$3));
                        DEL($1);
                        DEL($3);
                        if(not p)
                            YYERROR;
                    }
                    ;

value_tmp : T_VALUE_CHAR {$$=new icpp::Value($1);}
          | T_VALUE_BOOL {$$=new icpp::Value($1);}
          | T_VALUE_INT  {$$=new icpp::Value($1);}
          | T_VALUE_FLOAT {$$=new icpp::Value($1);}
          | T_VALUE_STRING {$$=new icpp::Value(std::move(*$1));DEL($1);}
          | T_VALUE_NULL  {$$=new icpp::Value();}


print : T_B_PRINT T_INDENTIFIER{
        bool p = driver.context().print(*$2,OUT);
        DEL($2);
        if(not p)
            YYERROR;
      } 
      | T_B_PRINT value_tmp {$2->print(OUT)<<std::endl;DEL($2);}
      | T_B_PRINT {driver.context().print(OUT);} /* context */
      ;

show : T_B_SHOW T_INDENTIFIER {
        bool p = driver.context().show(*$2,OUT);
        DEL($2);
        if(not p)
            YYERROR;
     }
     | T_B_SHOW value_tmp {$2->show(OUT)<<std::endl;DEL($2);}
     | T_B_SHOW {driver.context().show(OUT);} /* context */
     ;



%%

void icpp::Parser::error(const std::string &message)
{
   utils::log::error("Error","line",icpp_line_no,":",message);
}
 
/*Now that we have the Parser declared, we can declare the Scanner and implement the yylex function*/
#include <icpp/parser/Scanner.hpp>
#include <icpp/parser/Driver.hpp>
static int yylex(icpp::Parser::semantic_type *yylval,icpp::Scanner& scanner)
{
    return scanner.yylex(yylval);
}
