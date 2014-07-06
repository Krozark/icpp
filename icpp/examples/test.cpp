#include "test.hpp"
#include <utils/sys.hpp>
#include <utils/string.hpp>

#include <vector>
#include <regex>
#include <algorithm> // for copy

#include <avcall.h>

//#include <tuple>
//std::tuple_cat(tuple,std::make_tuple());
/*
#define av_start_void(LIST,FUNC)		__av_start(LIST,FUNC,0,    __AVvoid)
#define av_start_char(LIST,FUNC,RADDR)		__av_start(LIST,FUNC,RADDR,__AVchar)
#define av_start_schar(LIST,FUNC,RADDR)		__av_start(LIST,FUNC,RADDR,__AVschar)
#define av_start_uchar(LIST,FUNC,RADDR)		__av_start(LIST,FUNC,RADDR,__AVuchar)
#define av_start_short(LIST,FUNC,RADDR)		__av_start(LIST,FUNC,RADDR,__AVshort)
#define av_start_ushort(LIST,FUNC,RADDR)	__av_start(LIST,FUNC,RADDR,__AVushort)
#define av_start_int(LIST,FUNC,RADDR)		__av_start(LIST,FUNC,RADDR,__AVint)
#define av_start_uint(LIST,FUNC,RADDR)		__av_start(LIST,FUNC,RADDR,__AVuint)
#define av_start_long(LIST,FUNC,RADDR)		__av_start(LIST,FUNC,RADDR,__AVlong)
#define av_start_ulong(LIST,FUNC,RADDR)		__av_start(LIST,FUNC,RADDR,__AVulong)
#define av_start_longlong(LIST,FUNC,RADDR)	__av_start(LIST,FUNC,RADDR,__AVlonglong)
#define av_start_ulonglong(LIST,FUNC,RADDR)	__av_start(LIST,FUNC,RADDR,__AVulonglong)
#define av_start_float(LIST,FUNC,RADDR)		__av_start(LIST,FUNC,RADDR,__AVfloat)
#define av_start_double(LIST,FUNC,RADDR)	__av_start(LIST,FUNC,RADDR,__AVdouble)
#define av_start_ptr(LIST,FUNC,TYPE,RADDR)	__av_start(LIST,FUNC,RADDR,__AVvoidp)
*/

template<typename Ret>
void bind_ret(void* f,av_alist& p,Ret& res)
{
    utils::log::error("bind_start","Unknow type");
}

/*template<>
  void bind_ret<void>(void* f,av_alist& p,void* )
  {
  }*/

template<>
void bind_ret<bool>(void* f,av_alist& p,bool& res)
{
    av_start_char(p,f,&res);
}

template<>
void bind_ret<char>(void* f,av_alist& p,char& res)
{
    av_start_char(p,f,&res);
}

template<>
void bind_ret<int>(void* f,av_alist& p,int& res)
{
    av_start_int(p,f,&res);
}

template<>
void bind_ret<float>(void* f,av_alist& p,float& res)
{
    av_start_float(p,f,&res);
}

template<>
void bind_ret<double>(void* f,av_alist& p,double& res)
{
    av_start_double(p,f,&res);
}

template<>
void bind_ret<std::string>(void* f,av_alist& p,std::string& res)
{
    av_start_struct(p,f,std::string,0,&res);
}

void bind_param(void* f,const Value& param,av_alist& p)
{
    if(param.type == Value::BOOL)
        av_char(p,param.v_bool);

    else if(param.type == Value::CHAR)
        av_char(p,param.v_char);

    else if(param.type == Value::INT)
        av_int(p,param.v_int);

    else if(param.type == Value::FLOAT)
        av_float(p,param.v_float);

    else if(param.type == Value::DOUBLE)
        av_double(p,param.v_double);

    else if(param.type == Value::STRING)
        av_ptr(p,std::string*,param.v_string);

    else
        utils::log::error("bind","Unknow type");
}

template<typename Ret>
Ret call(void* f,const std::vector<Value>& params)
{
    av_alist p;
    //return type
    Ret res;
    bind_ret<Ret>(f,p,res);

    //values
    const unsigned int _size = params.size();
    for(unsigned int i=0;i<_size;++i)
        bind_param(f,params[i],p);

    //run
    av_call(p);

    return res;
}

template<>
void call<void>(void* f,const std::vector<Value>& params)
{
    av_alist p;
    //return type
    av_start_void(p,f);

    //values
    const unsigned int _size = params.size();
    for(unsigned int i=0;i<_size;++i)
        bind_param(f,params[i],p);

    //run
    av_call(p);
}

extern "C"
{
    int i_3i(int a,int b,int c)
    {
        std::cout<<a
            <<" "<<b
            <<" "<<c<<std::endl;
        return 42;
    }

    void v_3i(int a,int b,int c)
    {
        std::cout<<a
            <<" "<<b
            <<" "<<c<<std::endl;
    }

    void v_2is(int a,int b,std::string c)
    {
        std::cout<<a
            <<" "<<b
            <<" "<<c<<std::endl;
    }

}

int main(int argc,char* argv[])
{
    std::vector<Value> vec = {{2},{2.4},{"test"}};
    for(const Value& v : vec)
        v.show(std::cout)<<std::endl;

    /*utils::sys::Compiler comp = utils::sys::Compiler::getCompiler();
    utils::sys::Library libf = comp.input("f2.cpp")
        .output("f2")
        .flags("-o3","-Wall","-I../include","-std=c++0x")
        .get();

    if(libf.load())
    {
        if(libf.load_f<int,int>("print"))
            libf["print"]->call<int>(21);

        if(libf.load_f<void,const Value&>("show"))
            libf["show"]->call<void>(vec[2]);
        libf.close();
        
    }
    */




    std::cout<<call<int>((void*)i_3i,{{1},{2},{3}})<<std::endl;
    call<void>((void*)i_3i,{{1},{2},{3}});
    call<void>((void*)v_3i,{{42},{45},{68}});
    call<void>((void*)v_2is,{{42},{45},{"Blah"}});




    return 0;
}
