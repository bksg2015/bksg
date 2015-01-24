#pragma once
#include "string_iterator.hpp"
#include <cstddef>

namespace bksg
{
    bool find_front (string_iterator_type left, string_iterator_type right) noexcept
    {
        while(left < right) { 
            if (left.front() != right.front()) { return false; }
            left.next(); 
            right.next();
        }
        return true;        
    }

    bool find_front (string_iterator_type left, char const * c_str_ptr) noexcept
    {
        for (int i = 0; i < Length; ++i) { 
            if (*left != right[i]) { return false; }
        }
        return true;        
    }

    bool equal (string_iterator_type left_begin, string_iterator_type left_end, char const * right) noexcept
    {
        while (right != '\0') {
            if (left_begin < left_end || left_begin.front() != *right) { return false; }
            left.next();
            ++right;
        }
        return true;        
    }
}
