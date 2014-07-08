#ifndef ICPP_CONTEXT_HPP
#define ICPP_CONTEXT_HPP

#include <string>
#include <unordered_map>
#include <utils/log.hpp>

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
            const Value* get(const std::string& identifier)const;

            template<typename T>
            bool create_value(const std::string& name,const T& val);

            template<typename T>
            bool change_value(const std::string& name,const T& val);


            void print(const std::string& identifier,std::ostream& out)const;
            void show(const std::string& identifier,std::ostream& out)const;

            std::ostream& print(std::ostream& out)const;
            std::ostream& show(std::ostream& out)const;

        private:
            friend class Driver;

            std::unordered_map<std::string,Value> values;
            Context* parent;
    };
}
#include <icpp/Context.tpl>
#endif
