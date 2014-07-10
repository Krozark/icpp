namespace icpp
{
    /** Function **/
    template<typename Ret>
    Function<Ret>::Function() : VFunction()
    {};

    template<typename Ret>
    Function<Ret>::~Function()
    {}

    template<typename Ret>
    Value Function<Ret>::call(const std::list<Value>& params)const
    {
        Ret res;
        if(func != nullptr)
        {
            av_alist p;
            //return type
            bind_ret(func,p,res);

            //values
            for(const Value& v : params)
                bind_param(v,p);

            //run
            av_call(p);
        }
        return Value(std::move(res));
    }

    template<typename Ret>
    std::ostream& Function<Ret>::show(std::ostream& out)const
    {
        out<<"???";
        return out;
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

            Function() : VFunction(){};

            virtual ~Function(){};

            virtual Value call(const std::list<Value>& params)const
            {
                if(func != nullptr)
                {
                    av_alist p;
                    //return type
                    av_start_void(p,func);

                    //values
                    for(const Value& v : params)
                        bind_param(v,p);

                    //run
                    av_call(p);
                }
                return Value();
            }

            virtual std::ostream& show(std::ostream& out)const
            {
                out<<"null";
                return out;
            }

    };
}
