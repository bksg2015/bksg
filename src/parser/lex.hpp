#pragma once

#include "../string/string_iterator.hpp"
#include "../ast/identifier.hpp"
#include "../misc/three_value.hpp"
// #include "../error/error_handler.hpp"
#include <vector>
#include <tuple>
#include <memory>

namespace bksg
{
    bool parse_whitespaces (string_iterator_type & cursor) noexcept;
    bool parse_one_of_char (string_iterator_type & cursor, char const * char_set, bool skip_separator = true) noexcept;
    bool parse_string (string_iterator_type & cursor, char const * str, bool skip_separator = true) noexcept;
    bool parse_line_comment (string_iterator_type & cursor) noexcept;
    bool parse_block_comment (string_iterator_type & cursor) noexcept;
    bool parse_comment (string_iterator_type & cursor) noexcept;
    bool parse_separator (string_iterator_type & cursor) noexcept;
    std::tuple<bool, std::unique_ptr<ast_identifier>> parse_identifier (string_iterator_type & cursor) ;
    bool parse_escape_sequence (string_iterator_type & cursor) noexcept;

    bool parse_whitespaces (string_iterator_type & cursor) noexcept
    {
        if (!parse_whitespace(cursor)) { return false; }
        while (parse_whitespace(cursor)) {}
        return true; 
    }

    bool parse_one_of_char (string_iterator_type & cursor, char const * char_set, bool skip_separator) noexcept
    {
        auto it = cursor;
        if (parse_eof(cursor)) { return false; }
        while (*char_set != '\0') {
            if (parse_ascii(cursor,*char_set)) { 
                if (skip_separator) { parse_separator(cursor); };
                return true; 
            }
            ++char_set;
        }
        return false;
    }

    bool parse_string (string_iterator_type & cursor, char const * str, bool skip_separator) noexcept
    {
        auto it = cursor;
        while (*str != '\0') {
            if (!parse_ascii(cursor,*str)) { cursor = it; return false; }
            ++str;
        }
        if (skip_separator) { parse_separator(cursor); };
        return true;
    }

    bool parse_line_comment (string_iterator_type & cursor) noexcept
    {
        if (!parse_string(cursor, "//", false)) { return false; }
        while (!parse_eof(cursor) && !parse_eol(cursor)) { cursor.next(); }
        return true;
    }

    bool parse_block_comment (string_iterator_type & cursor) noexcept
    {
        if (!parse_string(cursor, "/*")) { return false; }
        while (!parse_eof(cursor) && !parse_string(cursor, "*/")) { cursor.next(); }
        return true;
    }

    bool parse_comment (string_iterator_type & cursor) noexcept
    {
        return parse_line_comment(cursor) || parse_block_comment(cursor);
    }

    bool parse_separator (string_iterator_type & cursor) noexcept
    {
        if (!parse_comment(cursor) && !parse_whitespaces(cursor)) { return false; }
        while (parse_comment(cursor) || parse_whitespaces(cursor)) {}
        return true;
    }

    std::tuple<bool, std::unique_ptr<ast_identifier>> parse_identifier (string_iterator_type & cursor) noexcept
    {
        auto begin = cursor;
        if (!parse_letter(cursor)) { return std::make_tuple(false, std::unique_ptr<ast_identifier>{}); }
        while (parse_letter(cursor) || parse_digit(cursor)) {}
        auto end = cursor;
        parse_separator(cursor);
        return std::make_tuple(true, std::unique_ptr<ast_identifier>(new ast_identifier(begin, end))); 
    }

    bool parse_escape_sequence (string_iterator_type & cursor) noexcept
    {
        if (!parse_ascii(cursor, '\\')) { return false; }
        cursor.next(); 
        return true;
    }
 
}
