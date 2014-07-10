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
    #include <list>
    #include <utils/sys.hpp>

    #include <icpp/Value.hpp>
    #include <icpp/Function.hpp>

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

    std::list<icpp::Value>* v_list_value;
    // Pointers to more complex classes
    /*
    utils::json::Object* v_object;
    utils::json::Array* v_array;
    utils::json::Value* v_value;
    */

    utils::sys::Compiler*   v_compiler;
    icpp::VFunction*        v_function;
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
    /* tokens */
%type<v_char>           T_VALUE_CHAR
%type<v_bool>           T_VALUE_BOOL
%type<v_int>            T_VALUE_INT
%type<v_float>          T_VALUE_FLOAT
%type<v_string>         T_VALUE_STRING
%type<v_string>         T_INDENTIFIER
%type<v_string>         func_name
    /* rules */
%type<v_value>          value_tmp
%type<v_value>          declaration
%type<v_value>          declaration_and_affectation
%type<v_value>          func_call

%type<v_list_value>     value_list

%type<v_compiler>       compile_cmd
%type<v_compiler>       compile_cmd_options
%type<v_compiler>       compile_cmd_or_options

%type<v_function>       func_return

%destructor {delete $$;} <v_string> <v_value> <v_list_value>


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
          | T_INDENTIFIER T_EOL {
            DEL($1);
            utils::log::info("Usless","Line",icpp_line_no-1,"as no effect");
          }
          | declaration T_EOL
          | declaration_and_affectation T_EOL
          | affectation T_EOL
          | bultins T_EOL
          | import T_EOL
          | from_import T_EOL
          | func_call T_EOL {DEL($1);}
          ;

declaration : T_TYPE_CHAR T_INDENTIFIER {
                bool p = driver.context().create_value(*$2,'0');
                if(not p)
                {
                    DEL($2);
                    YYERROR;
                }
                $$=driver.context().get(*$2);
                DEL($2);
            }
            | T_TYPE_BOOL T_INDENTIFIER {
                bool p = driver.context().create_value(*$2,false);
                if(not p)
                {
                    DEL($2);
                    YYERROR;
                }
                $$=driver.context().get(*$2);
                DEL($2);
            }
            | T_TYPE_INT T_INDENTIFIER {
                bool p = driver.context().create_value(*$2,0);
                if(not p)
                {
                    DEL($2);
                    YYERROR;
                }
                $$=driver.context().get(*$2);
                DEL($2);
            }
            | T_TYPE_FLOAT T_INDENTIFIER {
                bool p = driver.context().create_value(*$2,0.f);
                if(not p)
                {
                    DEL($2);
                    YYERROR;
                }
                $$=driver.context().get(*$2);
                DEL($2);
            }
            | T_TYPE_STRING T_INDENTIFIER {
                bool p = driver.context().create_value(*$2,std::string(""));
                if(not p)
                {
                    DEL($2);
                    YYERROR;
                }
                $$=driver.context().get(*$2);
                DEL($2);
            }
            ;

declaration_and_affectation : declaration T_EQUAL value_tmp {
                                $1->convert_to(*$3);
                                DEL($3);
                            }
                            | declaration T_EQUAL T_INDENTIFIER {
                                icpp::Value* v = driver.context().get(*$3);
                                DEL($3);
                                if(v)
                                {
                                    $1->convert_to(*v);
                                }
                            }
                            | T_TYPE_AUTO T_INDENTIFIER T_EQUAL value_tmp {
                                driver.context().create_or_change_value(*$2,std::move(*$4));
                                DEL($2);
                                DEL($4);
                            }
                            ;

affectation : T_INDENTIFIER T_EQUAL value_tmp {
                bool p = driver.context().change_value(*$1,std::move(*$3));
                DEL($1);
                DEL($3);
                if(not p)
                    YYERROR;
            }
            | T_INDENTIFIER T_EQUAL T_INDENTIFIER {
                icpp::Value* v2 = driver.context().get(*$3);
                if(v2 == nullptr)
                {
                    DEL($1);
                    DEL($3);
                    YYERROR;
                }
                bool p = driver.context().change_value(*$1,*v2);
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
          | func_call {$$=$1;$1=nullptr;}
          ;


value_list : value_tmp {
                $$=new std::list<icpp::Value>;
                $$->emplace_back(*$1);
                DEL($1);
           
           }| T_INDENTIFIER {
                icpp::Value* v = driver.context().get(*$1);
                DEL($1);
                if(v == nullptr)
                {
                    YYERROR;
                }
                $$=new std::list<icpp::Value>;
                $$->emplace_back(*v);
           }
           | value_list T_COMA value_tmp {
                $$ = $1;
                $1 = nullptr;
                $$->emplace_back(*$3);
                DEL($3);
           }
           | value_list T_COMA T_INDENTIFIER {
                $$ = $1;
                $1 = nullptr;
                icpp::Value* v = driver.context().get(*$3);
                if(v == nullptr)
                {
                    DEL($3);
                    YYERROR;
                }
                $$->emplace_back(*$3);
                DEL($3);
           }
           ;


bultins : help
        | print
        | show
        | delete
        | wget
        | run
        | compile
        | source
        ;

help : T_B_HELP {
        utils::log::todo("help","fonctionalaty not implemented");
     }
     ;

print : T_B_PRINT value_list {
        for(icpp::Value& v : *$2)
            v.print(OUT)<<" ";
        OUT<<std::endl;
        DEL($2);
      }
      | T_B_PRINT {driver.context().print(OUT);} /* context */
      ;

show : T_B_SHOW value_list {
        for(icpp::Value& v : *$2)
            v.show(OUT)<<std::endl;
        DEL($2);
     }
     | T_B_SHOW {driver.context().show(OUT);} /* context */
     ;

delete : T_B_DELETE T_INDENTIFIER {
            bool p = driver.context().remove(*$2);
            DEL($2);
            if(not p)
                YYERROR;
       }
       ;

wget : T_B_WGET T_VALUE_STRING {
        utils::log::todo("wget","fonctionalaty not implemented");
     }
     ;

run : T_B_RUN T_INDENTIFIER {
        utils::log::todo("run","fonctionalaty not implemented");
    }
    | T_B_RUN T_INDENTIFIER T_OPERATOR_AS T_INDENTIFIER {
        utils::log::todo("run","fonctionalaty not implemented");
    }
    ;

compile : compile_cmd_or_options T_OPERATOR_AS T_INDENTIFIER {
            Value* v = driver.context().find(*$3);
            if(v != nullptr)
            {
                utils::log::warning("Import","Name",*$3,"already exist in current context");
                DEL($3);
                DEL($1);
                YYERROR;
            }
            $1->output(*$3);

            try{
                utils::sys::Library* lib = new utils::sys::Library($1->get());
                DEL($1);
                bool er = not lib->load();
                if(not er)
                    er = not driver.context().create_value(*$3,lib);
                DEL($3);
                if(er)
                {
                    delete lib;
                    YYERROR;
                }
            } catch (std::runtime_error& e) {
                utils::log::error("compile",e.what());
                DEL($3);
                DEL($1);
                YYERROR;
            }
        }
        ;

compile_cmd_or_options : compile_cmd {
                            $$ = $1;
                            $1 = nullptr;
                       }
                       | compile_cmd_options {
                            $$ = $1;
                            $1 = nullptr;
                       }
                       ;


compile_cmd_options : compile_cmd T_OPERATOR_WITH {
                        $$ = $1;
                        $1 = nullptr;
                    }
                    | compile_cmd_options T_INDENTIFIER T_BRACKET_OPEN value_list T_BRACKET_CLOSE {
                        $$ = $1;
                        $1 = nullptr;
                        if(*$2 == "flags")
                        {
                            for(const icpp::Value& v : *$4)
                            {
                                if(v.is_string())
                                    $$->flags(v.as_string());
                                else
                                {
                                    utils::log::warning("compile","In flags, Value",v,"is not of type string");
                                    DEL($2);
                                    DEL($4);
                                    YYERROR;
                                }
                            }
                        }
                        else if(*$2 == "link")
                        {
                            for(const icpp::Value& v : *$4)
                            {
                                if(v.is_string())
                                    $$->link(v.as_string());
                                else
                                {
                                    utils::log::warning("compile","In link, Value",v,"is not of type string");
                                    DEL($2);
                                    DEL($4);
                                    YYERROR;
                                }
                            }
                        }
                        else
                        {
                            DEL($2);
                            DEL($4);
                            utils::log::warning("compile","Unknow param",*$2);
                            YYERROR;
                        }
                        DEL($2);
                        DEL($4);
                    }
                    ;

compile_cmd : T_B_COMPILE value_list {
            try {
                utils::sys::Compiler* comp = new utils::sys::Compiler();
                $$ = comp;
                for(const icpp::Value& v : *$2)
                {
                    if(v.is_string())
                        $$->input(v.as_string());
                    else
                    {
                        utils::log::warning("compile","Value",v,"is not of type string");
                        DEL($2);
                        YYERROR;
                    }
                }
            } catch (std::runtime_error& e){
                utils::log::error("compile",e.what());
                $$ = nullptr;
                DEL($2);
                YYERROR;
            }
            DEL($2);
        }
        ;

source : T_B_SOURCE T_VALUE_STRING {
       }
       | T_B_SOURCE T_INDENTIFIER {
       }
       ;

import : T_IMPORT_IMPORT T_VALUE_STRING T_OPERATOR_AS T_INDENTIFIER {
           Value* v = driver.context().find(*$4);
            if(v != nullptr)
            {
                utils::log::warning("Import","Name",*$4,"already exist in current context");
                DEL($2);
                DEL($4);
                YYERROR;
            }
            utils::sys::Library* lib = new utils::sys::Library(*$2);
            DEL($2);
            bool er = not lib->load();
            if(not er)
                er = not driver.context().create_value(*$4,lib);
            DEL($4);
            if(er)
            {
                delete lib;
                YYERROR;
            }
       }
       | T_IMPORT_IMPORT T_INDENTIFIER T_OPERATOR_AS T_INDENTIFIER {
            Value* id = driver.context().get(*$2);
            DEL($2);
            if(id == nullptr)
            {
                DEL($4);
                YYERROR;
            }
            if(not id->is_string())
            {
                utils::log::warning("compile","Value",*id,"is not of type string");
                DEL($4);
                YYERROR;
            }

            Value* v = driver.context().find(*$4);
            if(v != nullptr)
            {
                utils::log::warning("Import","Name",*$4,"already exist in current context");
                DEL($4);
                YYERROR;
            }
            utils::sys::Library* lib = new utils::sys::Library(id->as_string());
            bool er = not lib->load();
            if(not er)
                er = not driver.context().create_value(*$4,lib);
            DEL($4);
            if(er)
            {
                delete lib;
                YYERROR;
            }
       }


from_import : T_IMPORT_FROM T_INDENTIFIER T_IMPORT_IMPORT func_return func_name T_OPERATOR_AS T_INDENTIFIER {
                
                //lib
                Value* lib = driver.context().get(*$2);
                if(lib == nullptr or (not lib->is_library()))
                {
                    utils::log::warning("import","Value",*$2,"is not of type library");
                    DEL($2);//lib name
                    DEL($4);//func type
                    DEL($5);//func name
                    DEL($7);//dest
                    YYERROR;
                }
                DEL($2);//lib name
                //get func
                void* func = lib->as_library().get_f(*$5);
                DEL($5);//func name

                if(func == nullptr)
                {
                    DEL($4);//func type
                    DEL($7);//dest
                    YYERROR;
                }
                //store
                Value* dest = driver.context().find(*$7);
                if(dest != nullptr)
                {
                    utils::log::warning("Import","Name",*$7,"already exist in current context");
                    DEL($4);//func type
                    DEL($7);//dest
                    YYERROR;
                }
                $4->set_f(func);
                bool er = driver.context().create_value(*$7,$4);
                DEL($7);
                if (not er)
                    YYERROR;
          }
          ;

func_name : T_INDENTIFIER {
            Value* func_name = driver.context().find(*$1);
            if(func_name != nullptr)
            {
                if(not func_name->is_string())
                {
                    utils::log::warning("import","Value",*$1,"is not of type string");
                    DEL($1);
                    YYERROR;
                }
                $$ = new std::string(func_name->as_string());
            }
            else
                $$ = $1;
          }
          | T_VALUE_STRING {
            $$ = $1;
          }
          ;

func_return : /* void */{$$=new icpp::Function<void>();}
            | T_TYPE_CHAR {$$=new icpp::Function<char>();}
            | T_TYPE_BOOL {$$=new icpp::Function<bool>();}
            | T_TYPE_INT {$$=new icpp::Function<int>();}
            | T_TYPE_STRING {$$=new icpp::Function<std::string>();}
            ;

func_call   : T_INDENTIFIER T_BRACKET_OPEN value_list T_BRACKET_CLOSE {
                Value* func = driver.context().get(*$1);
                if(func == nullptr)
                {
                    DEL($3);//params
                    DEL($1);//func name
                    YYERROR;
                }
                if(not func->is_function())
                {
                    utils::log::warning("import","Value",*$1,"is not of type function");
                    DEL($1);//func name
                    DEL($3);//params
                    YYERROR;
                }
                DEL($1);//func name
                $$= new Value(std::move(func->as_function().call(*$3)));
                DEL($3);//params
            }
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
