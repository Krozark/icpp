#include <icpp/parser/Driver.hpp>

#include <utils/log.hpp>

namespace icpp
{
    Driver::Driver(std::istream& in) : scanner(in), parser(scanner,*this), _interactive(false),_finish(false)
    {
        context_current = new Context;
    }

    Driver::~Driver()
    {
        delete context_current;
    }


    void Driver::parse()
    {
        int res = parser.parse();
        if(res == 0)
            _finish = true;
        else if (res == STOP_RETURN)
        {
        }
        else
        {
            utils::log::error("icpp::Driver","Parse failed");
        }

    }

    bool Driver::finish()const
    {
        return _finish;
    }

    bool Driver::interactive()const
    {
        return _interactive;
    }

    void Driver::interactive(bool i)
    {
        _interactive = i;
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
