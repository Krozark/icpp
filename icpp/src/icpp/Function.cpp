#include <icpp/Function.hpp>

namespace icpp
{
    /** VFunction **/
    VFunction::VFunction() : func(nullptr)
    {
    }

    VFunction::~VFunction()
    {
    }

    void VFunction::setf(void* f)
    {
        func = f;
    }
    
    void VFunction::bind_param(const Value& param,av_alist& p)
    {
        switch(param.type)
        {
            case Value::Type::BOOL:
                av_char(p,param.v_bool);break;
            case Value::Type::CHAR:
                av_char(p,param.v_char);break;
            case Value::Type::INT:
                av_int(p,param.v_int);break;
            case Value::Type::FLOAT:
                av_double(p,param.v_float);break;
            case Value::Type::STRING:
                av_ptr(p,std::string*,param.v_string);break;
            default:
                utils::log::error("Function","Unknow param type");
        }
    }

    template<>
    void Function<bool>::bind_ret(void* f,av_alist& p,bool& res)
    {
        av_start_char(p,f,&res);
    }

    template<>
    void Function<char>::bind_ret(void* f,av_alist& p,char& res)
    {
        av_start_char(p,f,&res);
    }

    template<>
    void Function<int>::bind_ret(void* f,av_alist& p,int& res)
    {
        av_start_int(p,f,&res);
    }

    template<>
    void Function<double>::bind_ret(void* f,av_alist& p,double& res)
    {
        av_start_double(p,f,&res);
    }

    template<>
    void Function<std::string>::bind_ret(void* f,av_alist& p,std::string& res)
    {
        av_start_struct(p,f,std::string,0,&res);
    }

    template<>
    std::ostream& Function<bool>::print(std::ostream& out)const
    {
        out<<"bool";
        return out;
    }

    template<>
    std::ostream& Function<char>::print(std::ostream& out)const
    {
        out<<"char";
        return out;
    }

    template<>
    std::ostream& Function<int>::print(std::ostream& out)const
    {
        out<<"int";
        return out;
    }

    template<>
    std::ostream& Function<double>::print(std::ostream& out)const
    {
        out<<"float";
        return out;
    }

    template<>
    std::ostream& Function<std::string>::print(std::ostream& out)const
    {
        out<<"string";
        return out;
    }
}
