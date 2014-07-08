#include <icpp/Context.hpp>

namespace icpp
{
    
    Context::Context() : parent(nullptr)
    {
    }

    Value* Context::get(const std::string& identifier)
    {
        Value* res = nullptr;
        Context* self = this;

        while(res == nullptr and self != nullptr)
        {
            auto f = self->values.find(identifier);

            if(f == self->values.end())
                self = self->parent;
            else
                res = &(f->second);
        }

        return res;
    }

    const Value* Context::get(const std::string& identifier)const
    {
        const Value* res = nullptr;
        const Context* self = this;

        while(res == nullptr and self != nullptr)
        {
            auto f = self->values.find(identifier);

            if(f == self->values.end())
                self = self->parent;
            else
                res = &(f->second);
        }

        return res;
    }

    void Context::print(const std::string& identifier,std::ostream& out)const
    {
        const Value* v = get(identifier);
        if(v != nullptr){
            v->print(out)<<std::endl;
        }
        else
            utils::log::error("Icpp","Name",identifier,"is not define");
    }

    void Context::show(const std::string& identifier,std::ostream& out)const
    {
        const Value* v = get(identifier);
        if(v != nullptr)
            v->show(out)<<std::endl;
        else
            utils::log::error("Icpp","Name",identifier,"is not define");
    }

    std::ostream& Context::print(std::ostream& out)const
    {
        for(auto& u : values)
        {
            out<<u.first<<" : ";
            u.second.print(out)<<"\n";
        }
        out<<std::flush;

        return out;
    }

    std::ostream& Context::show(std::ostream& out)const
    {
        for(auto& u : values)
        {
            out<<u.first<<" : ";
            u.second.show(out);
            out<<"\n";
        }
        out<<std::flush;

        return out;
    }
    
}
