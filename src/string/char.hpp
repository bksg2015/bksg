#pragma once
#include <cctype>
namespace bksg
{
    constexpr bool compare_with_ascii (char const & ch, char const & ch2) noexcept { return ch == ch2; }

    // Letter
    constexpr bool is_letter (char const & ch) noexcept { return (0x41 <= ch && ch <= 0x5A) || (0x61 <= ch && ch <= 0x7A); } 
    // SpecialCharacter
    constexpr bool is_special_character (char const & ch) noexcept { return (0x21 <= ch && ch <= 0x2f) || (0x3a <= ch && ch <= 0x40) 
                                                                         || (0x5b <= ch && ch <= 0x60) || (0x7b <= ch && ch <= 0x7e);
                                                                   }
    // EndOfLine
    constexpr bool is_eol (char const & ch) noexcept { return ch == 0x0d || ch == 0x0a; } 
    // WhiteSpace
    constexpr bool is_whitespace (char const & ch) noexcept { return (ch == 0x20) || (ch == 0x09) || (ch == 0x0b) || (ch == 0x0c) || is_eol(ch); }
    
    constexpr bool is_underscore (char const & ch) noexcept { return ch == '_'; }

    constexpr bool is_digit (char const & ch) noexcept { return 0x30 <= ch && ch <= 0x39; }
    constexpr bool is_zero (char const & ch) noexcept { return ch == 0x30; }

    constexpr bool is_long_suffix (char const & ch) noexcept { return ch == 0x4c; }
    constexpr bool is_unsigned_suffix (char const & ch) noexcept { return ch == 0x55 || ch == 0x75; }
  
    constexpr bool is_binary_prefix (char const & ch) noexcept { return ch == 0x62 || ch == 0x42; }
    constexpr bool is_binary_digit (char const & ch) noexcept { return ch == 0x30 || ch == 0x31; }

    constexpr bool is_hexadecimal_prefix (char const & ch) noexcept { return ch == 0x58 || ch == 0x78; }
    constexpr bool is_hexadecimal_digit (char const & ch) noexcept { return is_digit(ch) || (0x41 <= ch && ch <= 0x46) || (0x61 <= ch && ch <= 0x66); }

    constexpr bool is_star (char const & ch) noexcept { return ch == 0x2a; }
    constexpr bool is_slash (char const & ch) noexcept { return ch == 0x2f; }

    constexpr bool is_single_quote (char const & ch) noexcept { return ch == 0x27; }
    constexpr bool is_double_quote (char const & ch) noexcept { return ch == 0x22; }
       
    constexpr bool is_backslash (char const & ch) noexcept { return ch == 0x5c; }
    
    constexpr bool is_comma (char const & ch) noexcept { return ch == 0x2c; }
    constexpr bool is_period (char const & ch) noexcept { return ch == 0x2e; }

    constexpr bool is_semicolon (char const & ch) noexcept { return ch == 0x3b; }

    constexpr bool is_left_parenthesis (char const & ch) noexcept { return ch == 0x28; } 
    constexpr bool is_right_parenthesis (char const & ch) noexcept { return ch == 0x29; } 

    constexpr bool is_left_curved_bracket (char const & ch) noexcept { return ch == 0x7b; }
    constexpr bool is_right_curved_bracket (char const & ch) noexcept { return ch == 0x7d; }
   
}
