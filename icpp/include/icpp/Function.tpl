namespace icpp
{
    /** Function **/
    template<typename Ret>
    Function<Ret>::Function(void* f)  : VFunction(f)
    {}

    template<typename Ret>
    Function<Ret>::~Function()
    {}

    template<typename Ret>
    Value Function<Ret>::call(const std::list<Value>& params)const
    {
        av_alist p;
        //return type
        Ret res;
        bind_ret(func,p,res);

        //values
        for(const Value& v : params)
            bind_param(v,p);

        //run
        av_call(p);

        return {std::move(res)};
    }

    template<typename Ret>
    void Function<Ret>::bind_ret(void* f,av_alist& p,Ret& res)
    {
        utils::log::error("Function","Unknow return type");
    }

    /** Special void case **/
    template<>
    class Function<void> : public VFunction
    {
        public:
            Function(const Function&) = delete;
            Function& operator=(const Function&) = delete;

            Function(void* f) : VFunction(f){};
            virtual ~Function(){};

            virtual Value call(const std::list<Value>& params)const
            {
                av_alist p;
                //return type
                av_start_void(p,func);

                //values
                for(const Value& v : params)
                    bind_param(v,p);

                //run
                av_call(p);

                return Value();
            }
    };
}
