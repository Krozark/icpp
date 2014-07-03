#include <icpp/parser/Driver.hpp>

#include <utils/log.hpp>

namespace icpp
{
    Driver::Driver(std::istream& in) : scanner(in), parser(scanner,*this), validity(true)
    {
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
}
