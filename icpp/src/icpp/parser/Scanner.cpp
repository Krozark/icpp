#include <icpp/parser/Scanner.hpp>

namespace icpp
{
    Scanner::Scanner(std::istream& in) : IcppFlexLexer(&in), yylval(nullptr)
    {
    }

    int Scanner::yylex(icpp::Parser::semantic_type *lval)
    {
        yylval = lval;
        return this->yylex();
    }
}
