namespace icpp
{
    template<typename T>
    bool Context::create_value(const std::string& name,const T& val)
    {
        bool res = false;
        auto f = values.find(name);
        if(f = values.end())
        {
            values.emplace(name,val);
            res = true;
        }
        return res;
    }
}
