#ifndef ICPP_FUNCTION_HPP
#define ICPP_FUNCTION_HPP

#include <list>
#include <icpp/Value.hpp>

#include <avcall.h>

namespace icpp
{
    class VFunction
    {
        public:
            VFunction();
            virtual ~VFunction();

            virtual Value call(const std::list<Value>& params)const = 0;

            virtual std::ostream& show(std::ostream& out)const = 0;

            void set_f(void* func);

        protected:
            void* func;
            static void bind_param(const Value& param,av_alist& p);
    };

    template<typename Ret>
    class Function : public VFunction
    {
        public:
            Function(const Function&) = delete;
            Function& operator=(const Function&) = delete;

            Function();

            virtual ~Function();

            virtual Value call(const std::list<Value>& params)const;

            virtual std::ostream& show(std::ostream& out)const;

        protected:
            static void bind_ret(void* f,av_alist& p,Ret& res);
    };

}
#include <icpp/Function.tpl>
#endif
