
namespace icpp
{
    template<typename T>
    bool Context::create_value(const std::string& name,const T& val)
    {
        bool res = false;
        auto f = values.find(name);
        if(f == values.end())
        {
            values.emplace(name,Value(val));
            res = true;
        }
        else
        {
            utils::log::warning("Icpp","Value of name",name,"already exist in context");
        }
        return res;
    }
    
    template<typename T>
    bool Context::change_value(const std::string& name,const T& val)
    {
        Value* v = get(name);
        bool res = false;
        if(v)
            res = v->convert_to(val);
        return res;
    }

    template<typename T>
    bool Context::change_value(const std::string& name,T&& val)
    {
        Value* v = get(name);
        bool res = false;
        if(v)
            res = v->convert_to(std::move(val));
        return res;
    }

    template<typename T>
    bool Context::create_or_change_value(const std::string& name,const T& val)
    {
        bool res = false;
        Value* v = get(name,false);
        if(v == nullptr)
        {
            values.emplace(name,val);
            res = true;
        }
        else
            *v = val;
        return res;
    }

    template<typename T>
    bool Context::create_or_change_value(const std::string& name,T&& val)
    {
        bool res = false;
        Value* v = get(name,false);
        if(v == nullptr)
        {
            values.emplace(name,std::move(val));
            res = true;
        }
        else
            *v = std::move(val);
        return res;
    }
}
