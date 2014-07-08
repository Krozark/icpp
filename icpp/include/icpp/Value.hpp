#ifndef ICPP_VALUE_HPP
#define ICPP_VALUE_HPP

#include <string>
#include <iostream>
#include <memory>

#include <utils/sys.hpp>

namespace icpp
{
    class Value
    {
        public:
            explicit Value();
            explicit Value(bool b);
            explicit Value(char c);
            explicit Value(int i);
            explicit Value(double d);
            explicit Value(const std::string& s);
            explicit Value(std::string&& s);
            
            explicit Value(utils::sys::Library* lib);

            Value(const Value& other);
            Value& operator=(const Value& other);

            Value(Value&& other);
            Value& operator=(Value&& other);

            Value& operator=(bool b);
            Value& operator=(char c);
            Value& operator=(int i);
            Value& operator=(double d);
            Value& operator=(const std::string& s);
            Value& operator=(std::string&& s);

            ~Value();

            bool convert_to(const Value& value);
            bool convert_to(Value&& value);

            std::ostream& print(std::ostream& out)const;
            std::ostream& show(std::ostream& out)const;

            friend std::ostream& operator<<(std::ostream& out,const Value& self);


            inline bool is_bool()const;
            inline bool is_char()const;
            inline bool is_int()const;
            inline bool is_float()const;
            inline bool is_string()const;
            inline bool is_null()const;

            inline bool as_bool()const;
            inline char as_char()const;
            inline int as_int()const;
            inline double as_float()const;
            inline const std::string& as_string()const;

            enum class Type {
                BOOL,
                CHAR,
                INT,
                FLOAT,
                STRING,
                //FUNCTION
                LIBRARY,
                NIL,
                UNDEFINE
            };

            std::string type_str()const;

            inline Type get_type()const;

        private:

            Type type;

            union {
                bool                    v_bool;
                char                    v_char;
                int                     v_int;
                double                  v_float;
                std::string*            v_string;

                std::shared_ptr<utils::sys::Library>    v_library;
            };
    };
}
#include <icpp/Value.tpl>
#endif
