#ifndef ICPP_DRIVER_HPP
#define ICPP_DRIVER_HPP

#include <iostream>

#include <icpp/parser/Scanner.hpp>
#include <icpp/Context.hpp>

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
             */
            void parse();

            /**
             * \return true if the stream is a valid format, else, false.
             */
            bool isValid()const;

        protected:
            friend class Parser;

            Context& context();
            void push_context();
            bool pop_context();
            
            
             
        private:
                
            Scanner scanner; ///< The lexer
            Parser parser; ///< The parser

            bool validity;//< is valid

            Context* context_current;


    };
}
#endif
