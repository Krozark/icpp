#ifndef ICPP_CONTEXT_HPP
#define ICPP_CONTEXT_HPP

#include <string>
#include <unordered_map>

#include <icpp/Value.hpp>

namespace icpp
{
    class Context
    {
        public:
            Context();
            Context(const Context&) = delete;
            Context& operator=(const Context&) = delete;

            Value* get(const std::string& identifier);


        private:
            friend class Driver;

            std::unordered_map<std::string,Value> values;
            Context* parent;
    };
}
#endif
