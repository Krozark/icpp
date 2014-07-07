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
}
