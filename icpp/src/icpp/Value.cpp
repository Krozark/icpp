#include <icpp/Value.hpp>

#include <icpp/Function.hpp>

#include <stdlib.h>
#include <functional>

#include <utils/log.hpp>

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

    Value::Value(utils::sys::Library* lib) : type(Type::LIBRARY)
    {
        new(&v_library) std::shared_ptr<utils::sys::Library>(lib);
    }

    Value::Value(VFunction* func) : type(Type::FUNCTION)
    {
        new(&v_function) std::shared_ptr<VFunction>(func);
    }

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
            case Type::LIBRARY:
            {
                new(&v_library) std::shared_ptr<utils::sys::Library>;
                v_library = other.v_library;
            }break;
            case Type::FUNCTION:
            {
                new(&v_function) std::shared_ptr<VFunction>;
                v_function = other.v_function;
            }break;
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
            case Type::LIBRARY:
            {
                new(&v_library) std::shared_ptr<utils::sys::Library>;
                v_library = other.v_library;
            }break;
            case Type::FUNCTION:
            {
                new(&v_function) std::shared_ptr<VFunction>;
                v_function = other.v_function;
            }break;
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
            case Type::LIBRARY:
            {
                new(&v_library) std::shared_ptr<utils::sys::Library>;
                v_library = std::move(other.v_library);
                other.type=Type::UNDEFINE;
            }break;
            case Type::FUNCTION:
            {
                new(&v_function) std::shared_ptr<VFunction>;
                v_function = std::move(other.v_function);
                other.type=Type::UNDEFINE;
            }break;
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
            case Type::LIBRARY:
            {
                new(&v_library) std::shared_ptr<utils::sys::Library>;
                v_library = std::move(other.v_library);
                other.type=Type::UNDEFINE;
            }break;
            case Type::FUNCTION:
            {
                new(&v_function) std::shared_ptr<VFunction>;
                v_function = std::move(other.v_function);
                other.type=Type::UNDEFINE;
            }break;
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

    Value& Value::operator=(utils::sys::Library* lib)
    {
        if(type != Type::LIBRARY)
        {
            this->~Value();
            type = Type::LIBRARY;
            new(&v_library) std::shared_ptr<utils::sys::Library>(lib);
        }
        else
            v_library.reset(lib);
        return *this;
    }

    Value& Value::operator=(VFunction* func)
    {
        if(type != Type::FUNCTION)
        {
            this->~Value();
            type = Type::FUNCTION;
            new(&v_function) std::shared_ptr<VFunction>(func);
        }
        else
            v_function.reset(func);
        return *this;
    }

    Value::~Value()
    {
        switch(type)
        {
            case Type::STRING:
                delete v_string;
            break;
            case Type::LIBRARY:
                v_library.~shared_ptr();
            break;
            case Type::FUNCTION:
                v_function.~shared_ptr();
            break;
            default:
                break;
        }
    }

    bool Value::convert_to(const Value& other)
    {
        bool res = true;
        if(type == other.type)
            *this=other;
        else
        {
            switch(type)
            {
                case Type::BOOL:
                {
                    switch(other.type)
                    {
                        case Type::CHAR:
                            v_bool=other.v_char;break;
                        case Type::INT:
                            v_bool = other.v_int;break;
                        case Type::FLOAT:
                            v_bool = other.v_float;break;
                        case Type::STRING:
                            v_bool = ::atoi(other.v_string->c_str());break;
                        case Type::NIL:
                            v_bool = false;break;
                        default:
                            res = false;break;
                    }
                }break;
                case Type::CHAR:
                {
                    switch(other.type)
                    {
                        case Type::INT:
                            v_char = other.v_int;break;
                        case Type::STRING:
                        {
                            if(other.v_string->size()>0)
                                v_char = (*other.v_string)[0];
                        }break;
                        default:
                            res = false;break;
                    }
                }break;
                case Type::INT:
                {
                    switch(other.type)
                    {
                        case Type::BOOL:
                            v_int = other.v_bool;break;
                        case Type::CHAR:
                            v_int=other.v_char;break;
                        case Type::FLOAT:
                            v_int = other.v_float;break;
                        case Type::STRING:
                            v_int = ::atoi(other.v_string->c_str());break;
                        case Type::NIL:
                            v_bool = 0;break;
                        default:
                            res = false;break;
                    }
                }break;
                case Type::FLOAT:
                {
                    switch(other.type)
                    {
                        case Type::BOOL:
                            v_float = other.v_bool;break;
                        case Type::CHAR:
                            v_float=other.v_char;break;
                        case Type::INT:
                            v_float = other.v_int;break;
                        case Type::STRING:
                            v_float = ::atof(other.v_string->c_str());break;
                        case Type::NIL:
                            v_bool = false;break;
                        default:
                            res = false;break;
                    }
                }break;
                case Type::STRING:
                {
                    switch(other.type)
                    {
                        case Type::BOOL:
                            *v_string = other.v_bool?"true":"false";break;
                        case Type::CHAR:
                            *v_string = other.v_char;break;
                        case Type::INT:
                            *v_string = std::to_string(other.v_int);break;
                        case Type::FLOAT:
                            *v_string = std::to_string(other.v_float);break;
                        case Type::NIL:
                            *v_string = "";break;
                        default:
                            res = false;break;
                    }
                }break;
                default:
                {
                    res = false;
                }break;
            }
        }
        if(not res)
            utils::log::warning("Icpp","Type",type_str(),"is not convertible with type",other.type_str());

        return res;
    }

    bool Value::convert_to(Value&& other)
    {
        bool res;
        if(type == Type::STRING and other.type == Type::STRING)
        {
            *this=std::move(other);
            res = true;
        }
        else
            res = convert_to(std::ref(other));
        return res;
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
            case Type::LIBRARY:
                out<<v_library->name();break;
            case Type::FUNCTION:
                out<<"function";break;
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
                out<<"string, value: \""<<*v_string<<"\"";break;
            case Type::LIBRARY:
                out<<"library, value: "<<v_library->name();break;
            case Type::FUNCTION:
                out<<"function, return: ";v_function->show(out);break;
            case Type::NIL:
                out<<"null";break;
            default:
                out<<"???";break;
        }
        return out;
    }

    std::ostream& operator<<(std::ostream& out,const Value& self)
    {
        self.print(out);
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
            case Type::LIBRARY:
                return "library";
            case Type::FUNCTION:
                return "function";
            case Type::NIL:
                return "null";
            default:
                return "???";
        }
    }
}
