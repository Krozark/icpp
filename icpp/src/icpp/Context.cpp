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
        if(not res)
            utils::log::warning("Icpp","Name",identifier,"is not define");

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
        if(not res)
            utils::log::warning("Icpp","Name",identifier,"is not define");

        return res;
    }

    bool Context::remove(const std::string& identifier)
    {
        bool res = false;
        Context* self = this;

        while(self != nullptr)
        {
            auto f = self->values.find(identifier);

            if(f == self->values.end())
                self = self->parent;
            else
            {
                self->values.erase(f);
                res = true;
                break;
            }
        }
        if(not res)
            utils::log::warning("Icpp","Name",identifier,"is not define");
        
        return res;

    }

    bool Context::print(const std::string& identifier,std::ostream& out)const
    {
        const Value* v = get(identifier);
        if(v != nullptr)
        {
            v->print(out)<<std::endl;
            return true;
        }
        return false;
    }

    bool Context::show(const std::string& identifier,std::ostream& out)const
    {
        const Value* v = get(identifier);
        if(v != nullptr)
        {
            v->show(out)<<std::endl;
            return true;
        }
        return false;
    }

    std::ostream& Context::print(std::ostream& out)const
    {
        for(auto& u : values)
        {
            out<<u.first<<" : ";
            u.second.print(out)<<"\n";
        }
        if(parent)
            parent->print(out);
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
        if(parent)
            parent->show(out);
        out<<std::flush;

        return out;
    }

}
