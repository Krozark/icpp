#ifndef ICPP_SCANNER_HPP
#define ICPP_SCANNER_HPP

#if ! defined(yyFlexLexerOnce)
#define yyFlexLexer IcppFlexLexer
#include <icpp/parser/FlexLexer.hpp>
#undef yyFlexLexer
#endif

// Override the interface for yylex since we namespaced it
#undef YY_DECL
#define YY_DECL int icpp::Scanner::yylex()

// Include Bison for types / tokens
//#if __WIN32
    //#include <icpp/parser/Win/Parser.hpp>
//#else
    #include <icpp/parser/Parser.hpp>
//#endif // __WIN32

namespace icpp
{
    class Parser;
    //typename Parser::semantic_type;

    /**
     * \brief The lexer that tokenize the input
     */
    class Scanner : public IcppFlexLexer
    {
        public:
            /**
             * \brief Construct from a input
             * \param in  imput
             */
            Scanner(std::istream& in);
            Scanner(const Scanner&) = delete;
            Scanner& operator=(const Scanner&) = delete;
            /**
             * \breif save the pointer to yylval so we can change it, and invoke scanner
             * \param lval For Lex/bison
             * \return 0 if all input is parse
             */
            int yylex(icpp::Parser::semantic_type *lval);

        protected:

        private:
            /**
             * \breif Scanning function created by Flex; make this private to force usage
             * of the overloaded method so we can get a pointer to Bison's yylval
             */
            int yylex();
            /* yyval ptr */
            icpp::Parser::semantic_type *yylval; ///< For Lex/bison
    };
}
#endif
