#include <icpp/parser/Driver.hpp>

#include <utils/log.hpp>

namespace icpp
{
    Driver::Driver(std::istream& in) : scanner(in), parser(scanner,*this), validity(true)
    {
        context_current = new Context;
    }

    Driver::~Driver()
    {
    }


    void Driver::parse()
    {
        validity=true;
        if(parser.parse() != 0)
        {
            utils::log::error("icpp::Driver","Parse failed");
            validity=false;
        }
    }

    bool Driver::isValid()const
    {
        return validity;
    }

    Context& Driver::context()
    {
        return *context_current;
    }

    void Driver::push_context()
    {
        Context* tmp = new Context;
        tmp->parent = context_current;
        context_current = tmp;
    }
    bool Driver::pop_context()
    {
        bool res = false;
        if(context_current->parent != nullptr)
        {
            res = true;
            Context* parent = context_current->parent;
            delete context_current;
            context_current = parent;
        }
        return res;
    }
}
