#pragma once

#include "string_view_interface.hpp"
#include <cstddef>

namespace bksg
{
    template <typename StringViewLeft, typename StringViewRight
            , typename std::enable_if<is_string_view_pair<StringViewLeft, StringViewRight>::value, void *>::type = nullptr>
    constexpr bool find_front (StringViewLeft left, StringViewRight right) noexcept
    {
        if (left.size() < right.size() ) { return false; }
        while(right.size() > 0) { 
            if (*left != *right) { return false; }
            left.pop(); 
            right.pop();
        }
        return true;        
    }

    template <typename StringViewLeft, std::size_t Length 
            , typename std::enable_if<is_string_view<StringViewLeft>::value, void *>::type = nullptr>
    constexpr bool find_front (StringViewLeft left, char right[Length]) noexcept
    {
        if (left.size() < Length ) { return false; }
        for (int i = 0; i < Length; ++i) { 
            if (*left != right[i]) { return false; }
        }
        return true;        
    }

    template <typename StringViewLeft, typename StringViewRight
            , typename std::enable_if<is_string_view_pair<StringViewLeft, StringViewRight>::value, void *>::type = nullptr>
    constexpr bool equal (StringViewLeft left, StringViewRight right) noexcept
    {
        if (left.size() != right.size() ) { return false; }
        while(right.size() > 0) { 
            if (*left != *right) { return false; }
            left.pop(); 
            right.pop();
        }
        return true;        
    }

    template <typename StringViewLeft 
            , typename std::enable_if<is_string_view<StringViewLeft>::value, void *>::type = nullptr>
    constexpr bool equal (StringViewLeft left, char const * right) noexcept
    {
        while (*right != '\0') {
            if (left.size() == 0 || *left != *right) { return false; }
            left.pop();
            ++right;
        }
        return true;        
    }

    template <typename StringView, typename std::enable_if<is_string_view<StringView>::value, void *>::type = nullptr>
    constexpr StringView diff (StringView left, StringView right) noexcept
    {
        left.end(right);
        return left;
    }

}
