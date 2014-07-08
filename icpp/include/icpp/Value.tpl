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

    inline Value::Type Value::get_type()const
    {
        return type;
    }
}
