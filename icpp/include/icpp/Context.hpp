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

            template<typename T>
            bool create_value(const std::string& name,const T& val);

            template<typename T>
            bool change_value(const std::string& name,const T& val);
            

        private:
            friend class Driver;

            std::unordered_map<std::string,Value> values;
            Context* parent;
    };
}
#include <icpp/Context.tpl>
#endif
