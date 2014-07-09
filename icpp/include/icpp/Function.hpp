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
            VFunction(void* f);
            virtual ~VFunction();

            virtual Value call(const std::list<Value>& params)const = 0;

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

            Function(void* f);
            virtual ~Function();

            virtual Value call(const std::list<Value>& params)const;

        protected:
            static void bind_ret(void* f,av_alist& p,Ret& res);
    };

}
#include <icpp/Function.tpl>
#endif
