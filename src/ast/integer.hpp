#pragma once 
#include "../string/string_iterator.hpp"
#include <gmpxx.h>
#include <string>
#include <memory>

namespace bksg
{
    struct ast_integer
    {
    private:
        mpz_class value;
    public:
        string_iterator_type location;

        ast_integer (std::string & str, int base, string_iterator_type location) noexcept
          : value(str, base), location(location) {}

        mpz_class const & get () noexcept { return value; }
    };

    std::unique_ptr<ast_integer> make_binary_integer (string_iterator_type begin, string_iterator_type end) noexcept
    {
        std::string buffer;
        auto it = begin;
        while(begin != end) {
            if (!parse_ascii(begin, '_')) { 
                buffer.push_back(begin.front_byte()); 
                begin.next(); 
            }
        }
       
        if (buffer.size() == 0) { buffer += '0'; }
        return std::unique_ptr<ast_integer>(new ast_integer(buffer, 2, it)); 
    }

    std::unique_ptr<ast_integer> make_hexadecimal_integer(string_iterator_type begin, string_iterator_type end) noexcept
    {
        std::string buffer;
        auto it = begin;
        while(begin != end) {
            if (!parse_ascii(begin, '_')) { 
                buffer.push_back(begin.front_byte()); 
                begin.next(); 
            }
        }
        
        if (buffer.size() == 0) { buffer += '0'; }
        return std::unique_ptr<ast_integer>(new ast_integer(buffer, 16, it)); 
    }

    std::unique_ptr<ast_integer> make_decimal_integer(string_iterator_type begin, string_iterator_type end) noexcept
    {
        std::string buffer;
        auto it = begin;
        while(begin != end) {
            if (!parse_ascii(begin, '_')) {
                buffer.push_back(begin.front_byte()); 
                begin.next(); 
            }
        }
        
        if (buffer.size() == 0) { buffer += '0'; }
        return std::unique_ptr<ast_integer>(new ast_integer(buffer, 10, it)); 
    }

} 
