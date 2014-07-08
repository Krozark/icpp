
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
            utils::log::error("Icpp","Value of name",name,"already exist in context");
        }
        return res;
    }

    template<typename T>
    bool Context::change_value(const std::string& name,const T& val)
    {
        bool res = false;
        auto f = values.find(name);
        if(f != values.end())
        {
            //res = true;
            utils::log::todo("Icpp","fonctionalaty not implemanted");
        }
        else
        {
            utils::log::error("Icpp","Name",name,"is not defined");
        }
        return res;
    }
}
