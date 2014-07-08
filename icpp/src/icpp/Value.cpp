#include <icpp/Value.hpp>

namespace icpp
{
    
    Value::Value(): type(Type::NIL)
    {};

    Value::Value(bool b) : type(Type::BOOL),v_bool(b)
    {};

    Value::Value(char c) : type(Type::CHAR),v_char(c)
    {};

    Value::Value(int i) : type(Type::INT),v_int(i)
    {};

    Value::Value(double d) : type(Type::FLOAT), v_float(d)
    {};

    Value::Value(const std::string& s) : type(Type::STRING), v_string(new std::string(s))
    {};

    Value::Value(std::string&& s) : type(Type::STRING), v_string(new std::string(std::move(s)))
    {};

    Value::Value(const Value& other) : type(other.type)
    {
        switch(type)
        {
            case Type::BOOL:
                v_bool=other.v_bool;break;
            case Type::CHAR:
                v_char=other.v_char;break;
            case Type::INT:
                v_int=other.v_int;break;
            case Type::FLOAT:
                v_float=other.v_float;break;
            case Type::STRING:
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
            case Type::BOOL:
                v_bool=other.v_bool;break;
            case Type::CHAR:
                v_char=other.v_char;break;
            case Type::INT:
                v_int=other.v_int;break;
            case Type::FLOAT:
                v_float=other.v_float;break;
            case Type::STRING:
                v_string = new std::string(*other.v_string);break;
            default:break;
        }
        return *this;
    }

    Value::Value(Value&& other) : type(other.type)
    {
        switch(type)
        {
            case Type::BOOL:
                v_bool=other.v_bool;break;
            case Type::CHAR:
                v_char=other.v_char;break;
            case Type::INT:
                v_int=other.v_int;break;
            case Type::FLOAT:
                v_float=other.v_float;break;
            case Type::STRING:
                v_string = other.v_string;
                other.type=Type::UNDEFINE;break;
            default:break;
        }
    }

    Value& Value::operator=(Value&& other)
    {
        this->~Value();
        type = other.type;
        switch(type)
        {
            case Type::BOOL:
                v_bool=other.v_bool;break;
            case Type::CHAR:
                v_char=other.v_char;break;
            case Type::INT:
                v_int=other.v_int;break;
            case Type::FLOAT:
                v_float=other.v_float;break;
            case Type::STRING:
                v_string = other.v_string;
                other.type=Type::UNDEFINE;break;
            default:break;
        }
        return *this;
    }

    Value& Value::operator=(bool b)
    {
        if(type != Type::BOOL)
        {
            this->~Value();
            type = Type::BOOL;
        }
        v_bool = b;
        return *this;
    }

    Value& Value::operator=(char c)
    {
        if(type != Type::CHAR)
        {
            this->~Value();
            type = Type::CHAR;
        }
        v_char = c;
        return *this;
    }

    Value& Value::operator=(int i)
    {
        if(type != Type::INT)
        {
            this->~Value();
            type = Type::INT;
        }
        v_int = i;
        return *this;
    }

    Value& Value::operator=(double d)
    {
        if(type != Type::FLOAT)
        {
            this->~Value();
            type = Type::FLOAT;
        }
        v_float = d;
        return *this;
    }

    Value& Value::operator=(const std::string& s)
    {
        if(type != Type::STRING)
        {
            this->~Value();
            type = Type::STRING;
            v_string = new std::string(s);
        }
        else
            *v_string = s;
        return *this;
    }

    Value& Value::operator=(std::string&& s)
    {
        if(type != Type::STRING)
        {
            this->~Value();
            type = Type::STRING;
            v_string = new std::string(std::move(s));
        }
        else
            *v_string = std::move(s);
        return *this;
    }

    Value::~Value()
    {
        if(type==Type::STRING)
            delete v_string;
    }

    std::ostream& Value::print(std::ostream& out)const
    {
        switch(type)
        {
            case Type::BOOL:
                out<<(v_bool?"true":"false");break;
            case Type::CHAR:
                out<<v_char;break;
            case Type::INT:
                out<<v_int;break;
            case Type::FLOAT:
                out<<v_float;break;
            case Type::STRING:
                out<<*v_string;break;
            case Type::NIL:
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
            case Type::BOOL:
                out<<"bool, value: "<<(v_bool?"true":"false");break;
            case Type::CHAR:
                out<<"char, value: "<<v_char;break;
            case Type::INT:
                out<<"int, value: "<<v_int;break;
            case Type::FLOAT:
                out<<"float, value: "<<v_float;break;
            case Type::STRING:
                out<<"string, value: "<<*v_string;break;
            case Type::NIL:
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
            case Type::BOOL:
                return "bool";
            case Type::CHAR:
                return "char";
            case Type::INT:
                return "int";
            case Type::FLOAT:
                return "float";
            case Type::STRING:
                return "string";
            case Type::NIL:
                return "null";
            default:
                return "???";
        }
    }
}
