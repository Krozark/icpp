#ifndef ICPP_VALUE_HPP
#define ICPP_VALUE_HPP

#include <string>
#include <iostream>

namespace icpp
{
    class Value
    {
        public:
            explicit Value();
            explicit Value(bool b);
            explicit Value(char c);
            explicit Value(int i);
            explicit Value(float f);
            explicit Value(double d);
            explicit Value(const std::string& s);
            explicit Value(std::string&& s);

            Value(const Value& other);

            Value& operator=(const Value& other);

            Value(Value&& other);

            Value& operator=(Value&& other);

            ~Value();

            friend std::ostream& operator<<(std::ostream& out,const Value& self);
            std::ostream& show(std::ostream& out)const;

            std::string type_str()const;

        private:

            enum Type {
                BOOL,
                CHAR,
                INT,
                FLOAT,
                STRING,
                //FUNCTION
                NIL,
                UNDEFINE
            } type;

            union {
                bool        v_bool;
                char        v_char;
                int         v_int;
                double      v_float;
                std::string* v_string;
            };
    };
}
#endif
