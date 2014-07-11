#ifndef ICPP_DRIVER_HPP
#define ICPP_DRIVER_HPP

#include <iostream>

#include <icpp/parser/Scanner.hpp>
#include <icpp/Context.hpp>

#define STOP_RETURN -3

namespace icpp
{
    /**
     * A class that have to be use to parse icpp input
     */
    class Driver
    {
        public:
            /**
             * \brief Construct a Driver from a stream
             * \param in input stream
             */
            Driver(std::istream& in);

            Driver(const Driver&) = delete;
            Driver& operator=(const Driver&) = delete;

            /**
             * \brief Destructor
             */
            ~Driver();

            /**
             * \brief Parse all the input (until \0)
             * on in interactive mod untile the end of statement
             */
            void parse();

            bool finish()const;
            bool interactive()const;
            void interactive(bool i);


        protected:
            friend class Parser;

            Context& context();
            void push_context();
            bool pop_context();
             
        private:
                
            Scanner scanner; ///< The lexer
            Parser parser; ///< The parser


            Context* context_current;

            bool _interactive;
            bool _finish;


    };
}
#endif
