#pragma once
#include "string_iterator_interface.hpp"
#include <iterator>
#include <climits>

namespace bksg
{
    struct utf8_string_iterator;
   
    template <>
    struct string_iterator_trait<utf8_string_iterator>  
    {
        using char_type = char; 
    };
 
    struct utf8_string_iterator : public string_iterator_interface<utf8_string_iterator>, std::iterator<std::forward_iterator_tag, char>
    {
        static_assert(CHAR_BIT == 8, "assumes that CHAR_BIT == 8.");
    private :
        using trait = string_iterator_trait<utf8_string_iterator>;
        using observe_char_ptr = char const *;
        observe_char_ptr ptr;
    public :
        using char_type = typename trait::char_type;

        utf8_string_iterator () noexcept;
        utf8_string_iterator (observe_char_ptr ptr) noexcept;

        char const front_byte () const noexcept;
        unsigned char const front_byte_unsigned () const noexcept;
        char const * front_ptr () const noexcept;

        utf8_string_iterator & next () noexcept;
        utf8_string_iterator & back () noexcept;

        bool operator>= (utf8_string_iterator const & other) const noexcept;

        std::size_t num_bytes () noexcept;
         
        bool compare_char (char ch1) noexcept; 
        bool compare_char (char ch1, char ch2) noexcept; 
        bool compare_char (char ch1, char ch2, char ch3) noexcept; 
        bool compare_char (char ch1, char ch2, char ch3, char ch4) noexcept; 
        bool compare_char (char ch1, char ch2, char ch3, char ch4, char ch5) noexcept; 
        bool compare_char (char ch1, char ch2, char ch3, char ch4, char ch5, char ch6) noexcept; 
    };

    bool parse_eof (utf8_string_iterator & it) noexcept;
    bool parse_ascii (utf8_string_iterator & it, unsigned char const ch) noexcept;
    bool parse_letter (utf8_string_iterator & it) noexcept;
    bool parse_eol (utf8_string_iterator & it) noexcept;
    bool parse_whitespace (utf8_string_iterator & it) noexcept;
    bool parse_digit (utf8_string_iterator & it) noexcept;

    utf8_string_iterator::utf8_string_iterator () noexcept : ptr(nullptr) {}
    utf8_string_iterator::utf8_string_iterator (observe_char_ptr ptr) noexcept : ptr(ptr) {}

    char const utf8_string_iterator::front_byte () const noexcept { return *ptr; }
    unsigned char const utf8_string_iterator::front_byte_unsigned () const noexcept { return *ptr; }
    char const * utf8_string_iterator::front_ptr () const noexcept { return ptr; }

    utf8_string_iterator & utf8_string_iterator::next () noexcept { ptr += num_bytes(); return *this; }
    utf8_string_iterator & utf8_string_iterator::back () noexcept { --ptr; return *this; }

    bool utf8_string_iterator::operator>= (utf8_string_iterator const & other) const noexcept { return ptr >= other.ptr; } 

    std::size_t utf8_string_iterator::num_bytes () noexcept
    {
        if (front_byte_unsigned() < 0x80) { return 1; }
        if (front_byte_unsigned() < 0xE0) { return 2; }
        if (front_byte_unsigned() < 0xF0) { return 3; }
        if (front_byte_unsigned() < 0xF8) { return 4; }
        if (front_byte_unsigned() < 0xFC) { return 5; }
        return 6;
    }
     
    bool utf8_string_iterator::compare_char (char ch1) noexcept 
    { 
        return *front_ptr()  == ch1; 
    }

    bool utf8_string_iterator::compare_char (char ch1, char ch2) noexcept 
    { 
        return utf8_string_iterator::compare_char(ch1) && *(front_ptr() + 1) == ch2;
    }

    bool utf8_string_iterator::compare_char (char ch1, char ch2, char ch3) noexcept 
    { 
        return utf8_string_iterator::compare_char(ch1, ch2) && *(front_ptr() + 2) == ch3;
    }

    bool utf8_string_iterator::compare_char (char ch1, char ch2, char ch3, char ch4) noexcept 
    { 
        return utf8_string_iterator::compare_char(ch1, ch2, ch3) && *(front_ptr() + 3) == ch4;
    }

    bool utf8_string_iterator::compare_char (char ch1, char ch2, char ch3, char ch4, char ch5) noexcept 
    { 
        return utf8_string_iterator::compare_char(ch1, ch2, ch3, ch4) && *(front_ptr() + 4) == ch5;
    }

    bool utf8_string_iterator::compare_char (char ch1, char ch2, char ch3, char ch4, char ch5, char ch6) noexcept 
    { 
        return utf8_string_iterator::compare_char(ch1, ch2, ch3, ch4, ch5) && *(front_ptr() + 5) == ch6;
    }


    bool parse_eof (utf8_string_iterator & it) noexcept
    {
        // 0x00 NUL
        // 0x1a SUB
        return it.compare_char(0x00) || it.compare_char(0x1a);
    }

    bool parse_ascii (utf8_string_iterator & it, unsigned char const ch) noexcept
    {
        if (parse_eof(it)) { return false; }
        if (it.front_byte_unsigned() == ch) { it.next(); return true; }
        return false; 
    }
    
    bool parse_letter (utf8_string_iterator & it) noexcept
    {
        if (parse_eof(it)) { return false; }
        // 0x41 A, 0x5A Z, 0x61 a, 0x7a z
        if ((0x41 <= it.front_byte_unsigned() && it.front_byte_unsigned() <= 0x5A) 
         || (0x61 <= it.front_byte_unsigned() && it.front_byte_unsigned() <= 0x7a)) { it.next(); return true; }
        return false;
    }

    bool parse_eol (utf8_string_iterator & it) noexcept
    {
        if (parse_eof(it)) { return true; }
        // LF
        if (it.compare_char(0x0a)) { it.next(); return true; }
        // CR
        if (it.compare_char(0x0d)) { it.next(); return true; }
        // CR LF 
        if (it.compare_char(0x0d, 0x0a)) { it.next(); it.next(); return true; }

        // TODO see D lang. is this required?
        // LINE SEPARATOR
        if (it.compare_char(0xe2, 0x80, 0xa8)) { it.next(); return true; }
        if (it.compare_char(0xe2, 0x80, 0xa9)) { it.next(); return true; }
        return false;
    }
 
    bool parse_whitespace (utf8_string_iterator & it) noexcept
    {
        if (parse_eof(it)) { return false; }
        if (it.compare_char(0x20)) { it.next(); return true; }
        if (it.compare_char(0x09)) { it.next(); return true; }
        if (it.compare_char(0x0B)) { it.next(); return true; }
        if (it.compare_char(0x0C)) { it.next(); return true; }
        return false;
    }

    bool parse_digit (utf8_string_iterator & it) noexcept
    {
        if (parse_eof(it)) { return false; }
        // 0x30 0, 0x39 9
        if (0x30 <= it.front_byte_unsigned() && it.front_byte_unsigned() <= 0x39) { it.next(); return true; }
        return false; 
    }
}
