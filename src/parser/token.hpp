#pragma once

#include "../string/string_view.hpp"
#include "../string/char.hpp"
#include <iostream>
#include <type_traits>
#include <deque>
#include <bitset>

namespace bksg
{
    enum class token_kind 
    {
        empty
      , token_separator
      , identifier
      , string_literal
      , character_literal
      , integer_literal
      , special_character_sequence
      , unknown
      , num
    };

    char const * token_kind_name [int(token_kind::num)] = {
        "empty"
      , "token_separator"
      , "identifier"
      , "string_literal"
      , "character_literal"
      , "integer_literal"
      , "special_character_sequence"
      , "unknown" 
    };

    enum class token_detail
    {
        binary
      , hexadecimal
      , decimal 
      , comma
      , period
      , periodperiodperiod
      , semicolon
      , left_paren
      , right_paren
      , left_curved_bracket
      , right_curved_bracket
      , and_and
      , and_
      , or_or
      , or_
      , unknown
      , num
    };

    char const * token_detail_name [int(token_detail::num)] = {
        "binary"
      , "hexadecimal"
      , "decimal"
      , "comma"
      , "period"
      , "periodperiodperiod"
      , "semicolon"
      , "left_paren"
      , "right_paren"
      , "left_curved_bracket"
      , "right_curved_bracket"
      , "and_and"
      , "and"
      , "or_or"
      , "or"
      , "unknown"
    };

    struct token
    {
        token_kind kind;
        token_detail detail;
        string_view_type string;    
    };

    struct token_parser 
    {
        static constexpr std::size_t stack_size = 4;
        using string_view_iterator_type = typename std::remove_reference<decltype(std::declval<string_view_type>().begin())>::type;
        using char_type = typename string_view_type::char_type;

        string_view_type string_cursor; 
        std::array<token, stack_size> token_stack;
        std::bitset<stack_size> token_consumed;
        int stack_cursor;

        // default ctor of std::bitset : false filling
        token_parser (string_view_type string_view) noexcept : string_cursor(string_view), stack_cursor(0) { token_consumed.flip(); } 

        // assumption : stack_cursor == (stack_cursor % stack_size)
        token & last_token () noexcept { return token_stack[stack_cursor]; } 

        token next_token () noexcept
        {
            token_consumed[stack_cursor] = true;
            stack_cursor = (++stack_cursor) % stack_size;
            
            if (token_consumed[stack_cursor]) {
                parse_token();
                while(last_token().kind == token_kind::token_separator) { parse_token(); }
            } else {
                string_cursor.begin(last_token().string.end());
            }

            std::cout << "next token : " << token_kind_name[int(last_token().kind)] 
                      << " : " << token_detail_name[int(last_token().detail)] 
                      << " : " << last_token().string.to_string() 
                      << std::endl;

            return last_token();
        }

        token back_token () noexcept
        {
            token_consumed[stack_cursor] = false;
            stack_cursor = (stack_cursor + stack_size - 1) % stack_size;
            string_cursor.begin(last_token().string.end());
            return last_token();
        }

        bool parse_token () noexcept
        {
            if (string_cursor.empty()) { 
                last_token().kind = token_kind::empty;
                return false; 
            }

            last_token().string.begin(string_cursor);
            last_token().kind = token_kind::empty;
            last_token().detail = token_detail::unknown;

            if (parse_token_separator()) {
                last_token().kind = token_kind::token_separator;
            } else if (parse_string_literal()) {
                last_token().kind = token_kind::string_literal;
            } else if (parse_character_literal()) {
                last_token().kind = token_kind::character_literal;
            } else if (parse_integer_literal()) {
                last_token().kind = token_kind::integer_literal;
//             } else if (parse_keyword()){
//                 last_token().kind = token_kind::keyword;
            } else if (parse_identifier()){
                last_token().kind = token_kind::identifier;
            } else if (parse_special_character_sequence()){
                last_token().kind = token_kind::special_character_sequence;
            } else {
                last_token().kind = token_kind::unknown;
                return false; 
            }
            last_token().string.end(string_cursor);
            
//             std::cout << "token_kind : " << int(last_token_kind) << " : " << std::string(token_cursor.begin(), token_cursor.end()) << std::endl;
            return true;
        }

        bool parse_whitespaces () noexcept
        {
            if (!is_whitespace(*string_cursor)) { return false; }
            string_cursor.pop();
            while (!string_cursor.empty() && is_whitespace(*string_cursor)) { string_cursor.pop(); }
            return true;
        }

        bool parse_token_separator () noexcept
        {
            if (!parse_whitespaces() && !parse_comment()) { return false; }
            while (!string_cursor.empty() && (parse_whitespaces() || parse_comment())) {}
            return true;
        }

        bool parse_comment () noexcept 
        {
            return parse_block_comment() || parse_line_comment(); 
        }

        bool parse_block_comment () noexcept 
        {
            auto it = string_cursor.begin();
            if (!is_slash(*string_cursor)) { return false; }
            string_cursor.pop();
            if (string_cursor.empty() || !is_star(*string_cursor)) { string_cursor.begin(it); return false; }
            string_cursor.pop();
            while (!string_cursor.empty())
            {
                if (is_star(*string_cursor)) {
                    string_cursor.pop();
                    if (!string_cursor.empty() && is_slash(*string_cursor)) { string_cursor.pop(); return true; }
                }
                string_cursor.pop();
            }
            string_cursor.begin(it);
            return false;
        }

        bool parse_line_comment () noexcept
        {
            auto it = string_cursor.begin();
            if (!is_slash(*string_cursor)) { return false; }
            string_cursor.pop();
            if (!is_slash(*string_cursor)) { string_cursor.begin(it); return false;}
            while (!string_cursor.empty())
            {
                if (is_eol(*string_cursor)) { string_cursor.pop(); return true; }
                string_cursor.pop();
            }
            return true;
        }

        bool parse_identifier () noexcept
        {
            if (is_digit(*string_cursor) || !is_letter(*string_cursor)) { return false; }
            auto it = string_cursor.begin();
            do {
                string_cursor.pop();
            } while (!string_cursor.empty() && (is_letter(*string_cursor) || is_digit(*string_cursor)));
            return true;
        }

        bool parse_string_literal () noexcept
        {
            if (!is_double_quote(*string_cursor)) { return false; }
            auto it = string_cursor.begin();
            string_cursor.pop();
            while (!string_cursor.empty() && !is_double_quote(*string_cursor) ) {
                if (!parse_escape_sequence()) { string_cursor.pop(); }
            }
            if (string_cursor.empty()) { string_cursor.begin(it); return false; }
            string_cursor.pop();
            return true;
        }

        bool parse_character_literal () noexcept
        {
            if (!is_single_quote(*string_cursor)) { return false; }
            auto it = string_cursor.begin();
            string_cursor.pop();
            if (string_cursor.empty()) { string_cursor.begin(it); return false; }
            if (!parse_escape_sequence()) { string_cursor.pop(); }
            if (string_cursor.empty() || !is_single_quote(*string_cursor)) { string_cursor.begin(it); return false; }
            string_cursor.pop();
            return true;
        }

        bool parse_escape_sequence () noexcept
        {
            if (!is_backslash(*string_cursor)) { return false; }
            auto it = string_cursor.begin();
            string_cursor.pop();
            if (string_cursor.empty()) { string_cursor.begin(it); return false; }
            string_cursor.pop();
            return true;
        }

        bool parse_integer_literal () noexcept 
        {
            if (parse_binary_integer()) {
                last_token().detail = token_detail::binary;
            } else if (parse_hexadecimal_integer()) {
                last_token().detail = token_detail::hexadecimal;
            } else if (parse_decimal_integer()) {
                last_token().detail = token_detail::decimal;
            } else { 
                return false; 
            }
            return true; 
        }

        bool parse_binary_integer () noexcept
        {
            auto it = string_cursor.begin();
            if (!is_zero(*string_cursor)) {return false; }
            string_cursor.pop();
            if (string_cursor.empty() || !is_binary_prefix(*string_cursor)) { string_cursor.begin(it); return false; }
            string_cursor.pop();
            if (string_cursor.empty() || !is_binary_digit(*string_cursor)) { string_cursor.begin(it); return false; }
            string_cursor.pop();
            while (!string_cursor.empty() && is_binary_digit(*string_cursor)) {
                string_cursor.pop();
            }
            return true; 
        }

        bool parse_hexadecimal_integer () noexcept
        {
            auto it = string_cursor.begin();
            if (!is_zero(*string_cursor)) {return false; }
            string_cursor.pop();
            if (string_cursor.empty() || !is_hexadecimal_prefix(*string_cursor)) { string_cursor.begin(it); return false; }
            string_cursor.pop();
            if (string_cursor.empty() || !is_hexadecimal_digit(*string_cursor)) { string_cursor.begin(it); return false; }
            string_cursor.pop();
            while (!string_cursor.empty() && is_hexadecimal_digit(*string_cursor)) {
                string_cursor.pop();
            }
            return true; 
        }

        bool parse_decimal_integer () noexcept
        {
            if (is_digit(*string_cursor)) {
                string_cursor.pop();
                while (!string_cursor.empty() && (is_digit(*string_cursor) || is_underscore(*string_cursor))) { 
                    string_cursor.pop();
                }
                return true;
            }
            return false;
        }

        bool parse_special_character_sequence () noexcept
        {
            if (equal(string_cursor,"(")) {
                last_token().detail = token_detail::left_paren;
            } else if (equal(string_cursor,")")) {
                last_token().detail = token_detail::right_paren;
            } else if (equal(string_cursor,",")) {
                last_token().detail = token_detail::comma;    
            } else if (equal(string_cursor,"...")) {
                last_token().detail = token_detail::periodperiodperiod;
            } else if (equal(string_cursor,".")) {
                last_token().detail = token_detail::period;    
            } else if (equal(string_cursor,";")) {
                last_token().detail = token_detail::semicolon;    
            } else if (equal(string_cursor,"{")) {
                last_token().detail = token_detail::left_curved_bracket;    
            } else if (equal(string_cursor,"}")) {
                last_token().detail = token_detail::right_curved_bracket;    
            } else if (equal(string_cursor,"&&")) {
                last_token().detail = token_detail::and_and;    
            } else if (equal(string_cursor,"&")) {
                last_token().detail = token_detail::and_;    
            } else if (equal(string_cursor,"||")) {
                last_token().detail = token_detail::or_or;
            } else if (equal(string_cursor,"|")) {
                last_token().detail = token_detail::or_;    
            } else if (!is_special_character(*string_cursor)) { 
                return false; 
            } else {
                string_cursor.pop();
                while (!string_cursor.empty() && is_special_character(*string_cursor)) { string_cursor.pop(); }
                last_token().detail = token_detail::unknown;
                return true;
            }
            string_cursor.pop();
            return true;
        }

//         bool parse_keyword_helper (char_type const * keyword, int size) noexcept
//         {
//             auto it = string_cursor.begin();
//             if (string_cursor.size() < size || !compare_with_ascii(*string_cursor, keyword[0])) { return false; }
//             string_cursor.pop();
//             for (int i = 1; i < size; ++i) {
//                 if (!compare_with_ascii(*string_cursor, keyword[i])) { string_cursor.begin(it); return false; }
//                 string_cursor.pop();
//             }
//             return true;
//         }
//
//         bool parse_keyword () noexcept
//         {
//             if (parse_keyword_helper("module", 6)) {
//                 last_token().detail = token_detail::keyword_module;
//             } else if (parse_keyword_helper("class", 5)) {
//                 last_token().detail = token_detail::keyword_class;
//             } else if (parse_keyword_helper("namespace", 9)) {
//                 last_token().detail = token_detail::keyword_namespace;
//             } else if (parse_keyword_helper("function", 8)) {
//                 last_token().detail = token_detail::keyword_function;
//             } else {
//                 return false;
//             }
//             return true;
//         }
    };
}
