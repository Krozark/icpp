#include <string>
#include <iostream>


/**
 * \brief DO NOT USE THIS FOR THE MOMENT
 */
class Value
{
    public:
        Value(const Value& other) : type(other.type)
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
                case DOUBLE:
                    v_double=other.v_double;break;
                case STRING:
                    v_string = new std::string(*other.v_string);break;
                default:break;
            }
        }

        Value& operator=(const Value& other)
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
                case DOUBLE:
                    v_double=other.v_double;break;
                case STRING:
                    v_string = new std::string(*other.v_string);break;
                default:break;
            }
            return *this;
        }

        Value(Value&& other) : type(other.type)
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
                case DOUBLE:
                    v_double=other.v_double;break;
                case STRING:
                    v_string = other.v_string;other.type=UNDEFINE;break;
                default:break;
            }
        }

        Value& operator=(Value&& other)
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
                case DOUBLE:
                    v_double=other.v_double;break;
                case STRING:
                    v_string = other.v_string;other.type=UNDEFINE;break;
                default:break;
            }
            return *this;
        }

        ~Value()
        {
            if(type==STRING)
                delete v_string;
        }
    
        Value(bool b) : type(BOOL),v_bool(b){};

        Value(char c) : type(CHAR),v_char(c){};

        Value(int i) : type(INT),v_int(i){};

        Value(float f) : type(FLOAT), v_float(f){};

        Value(double d) : type(DOUBLE), v_double(d){};

        Value(const char * s) : type(STRING), v_string(new std::string(s)){};
        Value(const std::string& s) : type(STRING), v_string(new std::string(s)){};
        Value(std::string&& s) : type(STRING), v_string(new std::string(std::move(s))){};

        Value(): type(NIL){};


        friend std::ostream& operator<<(std::ostream& out,const Value& self)
        {
            switch(self.type)
            {
                case BOOL:out<<(self.v_bool?"true":"false");break;
                case CHAR:out<<self.v_char;break;
                case INT:out<<self.v_int;break;
                case FLOAT:out<<self.v_float;break;
                case DOUBLE:out<<self.v_double;break;
                case STRING:out<<*self.v_string;break;
                case NIL:out<<"null";break;
                default:out<<"???";break;
            }
            return out;
        }

        std::ostream& show(std::ostream& out)const
        {
            out<<"type: ";
            switch(type)
            {
                case BOOL:out<<"bool, value: "<<(v_bool?"true":"false");break;
                case CHAR:out<<"char, value: "<<v_char;break;
                case INT:out<<"int, value: "<<v_int;break;
                case FLOAT:out<<"float, value: "<<v_float;break;
                case DOUBLE:out<<"double, value: "<<v_double;break;
                case STRING:out<<"string, value: "<<*v_string;break;
                case NIL:out<<"null";break;
                default:out<<"???";break;
            }
            return out;
        }

        std::string type_str()const
        {
            switch(type)
            {
                case BOOL:return "bool";
                case CHAR:return "char";
                case INT: return "int";
                case FLOAT: return "float";
                case DOUBLE: return "double";
                case STRING: return "string";
                case NIL: return "null";
                default: return "???";
            }
        }



    //private:

        enum Type {
            BOOL,
            CHAR,
            INT,
            FLOAT,
            DOUBLE,
            STRING,
            NIL,
            UNDEFINE
        } type;

        union {
            bool        v_bool;
            char        v_char;
            int         v_int;
            float       v_float;
            double      v_double;
            std::string* v_string;
        };
};
