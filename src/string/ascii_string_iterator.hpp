#pragma once
#include "string_iterator_interface.hpp"
#include <iterator>

namespace bksg
{
    struct ascii_string_iterator;
    
    template <>
    struct string_iterator_trait<ascii_string_iterator>
    {
    };

    struct ascii_string_iterator : public string_iterator_interface<ascii_string_iterator>, std::iterator<std::forward_iterator_tag, char>
    {
    private:
        using trait = string_iterator_trait<ascii_string_iterator>;
        using observe_char_ptr = char const *;
        observe_char_ptr ptr;
    public:
        using char_type = typename trait::char_type;

        ascii_string_iterator () noexcept : ptr(nullptr) {}
        ascii_string_iterator (observe_char_ptr ptr) noexcept : ptr(ptr) {}

        char const front_byte () const noexcept { return *ptr; }
        unsigned char const front_byte_unsigned () const noexcept { return *ptr; }
        char const * front_ptr () const noexcept { return ptr; }

        ascii_string_iterator & next () noexcept { ++ptr; return *this; }

        bool operator>= (ascii_string_iterator const & other) const noexcept { return ptr >= other.ptr; } 
    };

    bool parse_eof (ascii_string_iterator & it) noexcept
    {
        if (*it != '\0') { return false; }
        return true;
    }

    bool parse_char (ascii_string_iterator & it, char const ch) noexcept
    {
        if (parse_eof(it)) { return false; }
        if (*it == ch) { it.next(); return true; }
        return false; 
    }
    
    bool parse_letter (ascii_string_iterator & it) noexcept
    {
        if (parse_eof(it)) { return false; }
        if (('a' <= *it && *it <= 'z') || ('A' <= *it && *it <= 'Z')) { it.next(); return true; }
        return false;
    }

    bool parse_eol (ascii_string_iterator & it) noexcept
    {
        if (parse_eof(it)) { return false; }
        if (*it != 0x0d && *it != 0x0a) { return false; }
        it.next();
        return true;
    }
 
    bool parse_whitespace (ascii_string_iterator & it) noexcept
    {
        if (parse_eof(it)) { return false; }
        if (*it != 0x20 && *it != 0x09 && *it != 0x0b && *it != 0x0c && *it != 0x0d && *it != 0x0a) { return false; }
        it.next();
        return true;
    }

    bool parse_digit (ascii_string_iterator & it) noexcept
    {
        if (parse_eof(it)) { return false; }
        if ('0' <= *it && *it <= '9') { it.next(); return true; }
        return false; 
    }

}
