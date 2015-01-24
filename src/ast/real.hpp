#pragma once 
#include "../string/string_iterator.hpp"
#include <gmpxx.h>
#include <string>

namespace bksg
{
    struct integer
    {
    private:
        mpz_class value;
    public:
        string_iterator_type location;

        integer (std::string str, int base, string_iterator_type location) noexcept
          : value(str, base), location(location) {}
    };

    integer make_binary_integer (string_iterator_type begin, string_iterator_type end) noexcept
    {
        std::string buffer;
        auto it = begin;
        while(begin != end) {
            if (!parse_char(begin, '_')) { 
                buffer.push_back(*begin); 
                begin.next(); 
            }
        }
        return integer(buffer, 2, it); 
    }

    integer make_hexadecimal_integer(string_iterator_type begin, string_iterator_type end) noexcept
    {
        std::string buffer;
        auto it = begin;
        while(begin != end) {
            if (!parse_char(begin, '_')) { 
                buffer.push_back(*begin); 
                begin.next(); 
            }
        }
        return integer(buffer, 16, it); 
    }

    integer make_decimal_integer(string_iterator_type begin, string_iterator_type end) noexcept
    {
        std::string buffer;
        auto it = begin;
        while(begin != end) {
            if (!parse_char(begin, '_')) {
                buffer.push_back(*begin); 
                begin.next(); 
            }
        }
        return integer(buffer, 10, it); 
    }

} 
