#include "integer.hpp"

namespace bksg
{
    std::tuple<bool, std::unique_ptr<ast_integer>> parse_binary_integer (string_iterator_type & cursor) noexcept
    {
        assert(true, assert_kind::parse_integer, "parse_binary_integer", "enter", cursor.front_ptr());
        if (!parse_string(cursor, "0b") && !parse_string(cursor, "0B")) { 
            assert(true, assert_kind::parse_integer, "parse_binary_integer", "failr", cursor.front_ptr());
            return std::make_tuple(false, std::unique_ptr<ast_integer>{}); 
        }

        auto begin = cursor;
        while (true) { if (!parse_ascii(cursor, '0') && !parse_ascii(cursor, '1') && !parse_ascii(cursor, '_')){ break; } }
        auto end = cursor;

        parse_separator(cursor);
        

        assert(true, assert_kind::parse_integer, "parse_binary_integer", "ok", std::string(begin.front_ptr(), end.front_ptr()), cursor.front_ptr());
        return std::make_tuple(true, make_binary_integer(string_iterator_type(begin.front_ptr()), string_iterator_type(end.front_ptr())));
    }

    std::tuple<bool, std::unique_ptr<ast_integer>> parse_hexadecimal_integer (string_iterator_type & cursor) noexcept
    {
        assert(true, assert_kind::parse_integer, "parse_hexadecimal_integer", "enter", cursor.front_ptr());
        if (!parse_string(cursor, "0x") && !parse_string(cursor, "0X")) { 
            assert(true, assert_kind::parse_integer, "parse_hexadecimal_integer", "fail", cursor.front_ptr());
            return std::make_tuple(false, std::unique_ptr<ast_integer>{}); 
        }

        auto begin = cursor;
        while (true) { if (!parse_digit(cursor) && !parse_one_of_char(cursor,"abcdefABCDEF") && !parse_ascii(cursor, '_')) { break; } }  
        auto end = cursor;

        parse_separator(cursor);

        assert(true, assert_kind::parse_integer, "parse_hexadecimal_integer", "ok", std::string(begin.front_ptr(), end.front_ptr()), cursor.front_ptr());
        return std::make_tuple(true, make_hexadecimal_integer(string_iterator_type(begin.front_ptr()), string_iterator_type(end.front_ptr())));
    }

    std::tuple<bool, std::unique_ptr<ast_integer>> parse_decimal_integer (string_iterator_type & cursor) noexcept
    {
        assert(true, assert_kind::parse_integer, "parse_decimal_integer", "enter", cursor.front_ptr());
        
        auto begin = cursor;
        if (parse_ascii(cursor, '0') || !parse_digit(cursor)) { 
            assert(true, assert_kind::parse_integer, "parse_decimal_integer", "fail", cursor.front_ptr());
            cursor = begin; 
            return std::make_tuple(false, std::unique_ptr<ast_integer>{}); 
        }
 
        while (true) { if (!parse_digit(cursor) && !parse_ascii(cursor, '_')) { break; } }  
        auto end = cursor;

        parse_separator(cursor);

        assert(true, assert_kind::parse_integer, "parse_decimal_integer", "ok", std::string(begin.front_ptr(), end.front_ptr()), cursor.front_ptr());
        return std::make_tuple(true, make_decimal_integer(string_iterator_type(begin.front_ptr()), string_iterator_type(end.front_ptr())));
    }
    
    std::tuple<bool, std::unique_ptr<ast_integer>> parse_integer_literal (string_iterator_type & cursor) noexcept 
    {
        assert(true, assert_kind::parse_integer, "parse_integer_literal", "enter", cursor.front_ptr());
        auto res =  parse_binary_integer(cursor);
        if (!std::get<0>(res)) { 
            res = parse_hexadecimal_integer(cursor);
            if (!std::get<0>(res)) {
                res = parse_decimal_integer(cursor);
                if (!std::get<0>(res)) {
                    assert(true, assert_kind::parse_integer, "parse_integer_literal", "fail", cursor.front_ptr());
                    return res; 
                }
            }
        }
        assert(true, assert_kind::parse_integer, "parse_integer_literal", "ok", cursor.front_ptr());
        return res;
    }
}
