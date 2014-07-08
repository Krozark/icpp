namespace icpp
{
    inline bool Value::is_bool()const
    {
        return type == Type::BOOL;
    }

    inline bool Value::is_char()const
    {
        return type == Type::CHAR;
    }

    inline bool Value::is_int()const
    {
        return type == Type::INT;
    }

    inline bool Value::is_float()const
    {
        return type == Type::FLOAT;
    }

    inline bool Value::is_string()const
    {
        return type == Type::STRING;
    }

    inline bool Value::is_null()const
    {
        return type == Type::NIL;
    }

    inline bool Value::is_lib()const
    {
        return type == Type::LIBRARY;
    }






    inline bool Value::as_bool()const
    {
        return v_bool;
    }

    inline char Value::as_char()const
    {
        return v_char;
    }

    inline int Value::as_int()const
    {
        return v_int;
    }

    inline double Value::as_float()const
    {
        return v_float;
    }

    inline const std::string& Value::as_string()const
    {
        return *v_string;
    }

    inline const utils::sys::Library& Value::as_library()const
    {
        return *v_library.get();
    }




    inline Value::Type Value::get_type()const
    {
        return type;
    }
}
