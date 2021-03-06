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

            /**
             * \brief search in all context stack
             */
            Value* get(const std::string& identifier,bool show_error =true);
            const Value* get(const std::string& identifier, bool show_error=true)const;

            /**
             * \brief search in current context only
             */
            Value* find(const std::string& identifier);
            const Value* find(const std::string& identifier)const;

            bool remove(const std::string& identifier,bool show_error=true);

            template<typename T>
            bool create_value(const std::string& name,const T& val);

            template<typename T>
            bool change_value(const std::string& name,const T& val);

            /**
             * \return true if created, false else but do not failed
             */
            template<typename T>
            bool create_or_change_value(const std::string& name,const T& val);


            bool print(const std::string& identifier,std::ostream& out)const;
            bool show(const std::string& identifier,std::ostream& out)const;

            std::ostream& print(std::ostream& out)const;
            std::ostream& show(std::ostream& out)const;

            void clear();

        private:
            friend class Driver;

            std::unordered_map<std::string,Value> values;
            Context* parent;
    };
}
#include <icpp/Context.tpl>
#endif
