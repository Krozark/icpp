#include <icpp/Value.hpp>

namespace icpp
{
    
    Value::Value(): type(NIL)
    {};

    Value::Value(bool b) : type(BOOL),v_bool(b)
    {};

    Value::Value(char c) : type(CHAR),v_char(c)
    {};

    Value::Value(int i) : type(INT),v_int(i)
    {};

    Value::Value(double d) : type(FLOAT), v_float(d)
    {};

    Value::Value(const std::string& s) : type(STRING), v_string(new std::string(s))
    {};

    Value::Value(std::string&& s) : type(STRING), v_string(new std::string(std::move(s)))
    {};

    Value::Value(const Value& other) : type(other.type)
    {
        switch(type)
        {
            case BOOL:
                v_bool=other.v_bool;break;
            case CHAR:
                v_char=other.v_char;break;
            case INT:
                v_int=other.v_int;break;
            case FLOAT:
                v_float=other.v_float;break;
            case STRING:
                v_string = new std::string(*other.v_string);break;
            default:break;
        }
    }

    Value& Value::operator=(const Value& other)
    {
        this->~Value();
        type = other.type;
        switch(type)
        {
            case BOOL:
                v_bool=other.v_bool;break;
            case CHAR:
                v_char=other.v_char;break;
            case INT:
                v_int=other.v_int;break;
            case FLOAT:
                v_float=other.v_float;break;
            case STRING:
                v_string = new std::string(*other.v_string);break;
            default:break;
        }
        return *this;
    }

    Value::Value(Value&& other) : type(other.type)
    {
        switch(type)
        {
            case BOOL:
                v_bool=other.v_bool;break;
            case CHAR:
                v_char=other.v_char;break;
            case INT:
                v_int=other.v_int;break;
            case FLOAT:
                v_float=other.v_float;break;
            case STRING:
                v_string = other.v_string;other.type=UNDEFINE;break;
            default:break;
        }
    }

    Value& Value::operator=(Value&& other)
    {
        this->~Value();
        type = other.type;
        switch(type)
        {
            case BOOL:
                v_bool=other.v_bool;break;
            case CHAR:
                v_char=other.v_char;break;
            case INT:
                v_int=other.v_int;break;
            case FLOAT:
                v_float=other.v_float;break;
            case STRING:
                v_string = other.v_string;other.type=UNDEFINE;break;
            default:break;
        }
        return *this;
    }

    Value::~Value()
    {
        if(type==STRING)
            delete v_string;
    }

    std::ostream& Value::print(std::ostream& out)const
    {
        switch(type)
        {
            case Value::BOOL:
                out<<(v_bool?"true":"false");break;
            case Value::CHAR:
                out<<v_char;break;
            case Value::INT:
                out<<v_int;break;
            case Value::FLOAT:
                out<<v_float;break;
            case Value::STRING:
                out<<*v_string;break;
            case Value::NIL:
                out<<"null";break;
            default:
                out<<"???";break;
        }
        return out;
    }

    std::ostream& Value::show(std::ostream& out)const
    {
        out<<"type: ";
        switch(type)
        {
            case Value::BOOL:
                out<<"bool, value: "<<(v_bool?"true":"false");break;
            case Value::CHAR:
                out<<"char, value: "<<v_char;break;
            case Value::INT:
                out<<"int, value: "<<v_int;break;
            case Value::FLOAT:
                out<<"float, value: "<<v_float;break;
            case Value::STRING:
                out<<"string, value: "<<*v_string;break;
            case Value::NIL:
                out<<"null";break;
            default:
                out<<"???";break;
        }
        return out;
    }

    std::string Value::type_str()const
    {
        switch(type)
        {
            case Value::BOOL:
                return "bool";
            case Value::CHAR:
                return "char";
            case Value::INT:
                return "int";
            case Value::FLOAT:
                return "float";
            case Value::STRING:
                return "string";
            case Value::NIL:
                return "null";
            default:
                return "???";
        }
    }


}
