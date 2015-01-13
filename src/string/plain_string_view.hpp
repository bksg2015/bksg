#pragma once
#include "string_view_interface.hpp"
#include "char.hpp"
#include <cstddef>
#include <string>

namespace bksg
{
    struct plain_string_view;
    
    template <>
    struct string_view_trait<plain_string_view>
    {
        using char_type = char;
    };

    struct plain_string_view : public string_view_interface<plain_string_view>
    {
    private:
        using observe_char_ptr = char const *;
        observe_char_ptr first;
        observe_char_ptr last;
        using trait = string_view_trait<plain_string_view>;
    public:
        using char_type = typename trait::char_type;

        constexpr plain_string_view () noexcept 
          : first(nullptr), last(nullptr)
        {}
    
        constexpr plain_string_view (observe_char_ptr first, observe_char_ptr last) noexcept 
          : first(first), last(last) 
        {}

        template <std::size_t Length>
        constexpr plain_string_view (char_type arr[Length]) noexcept
          : first(arr), last(arr + Length) 
        {}

        constexpr plain_string_view (observe_char_ptr c_style_char_ptr) noexcept 
          : first(c_style_char_ptr), last(c_style_char_ptr) 
        { while(*last != '\0') { ++last; } }

        constexpr plain_string_view (observe_char_ptr first, std::ptrdiff_t size) noexcept 
          : first(first), last(first) 
        { last += size; } 

        constexpr char_type const & front () const noexcept { return *first; }

        constexpr plain_string_view & pop () noexcept { ++first; return *this;}
        constexpr bool empty() const noexcept { return first >= last; }
        constexpr std::size_t size()  const noexcept { return last - first;  }
    
        constexpr void begin (plain_string_view const & other) noexcept { first = other.first; }
        constexpr void end (plain_string_view const & other) noexcept { last = other.first; }

        constexpr observe_char_ptr begin () const noexcept { return first; }
        constexpr observe_char_ptr end () const noexcept { return last; }

        constexpr bool operator>= (plain_string_view const & other) noexcept { return first >= other.first; } 

        std::string to_string () const noexcept { return std::string(begin(), end()); }
    };

}
