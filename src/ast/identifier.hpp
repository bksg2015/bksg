#pragma once
#include "../string/string_iterator.hpp"
#include <vector>
#include <iterator>

namespace bksg
{
    struct ast_identifier
    {
        std::vector<char> name;

        ast_identifier () noexcept {}
 
        ast_identifier (string_iterator_type begin, string_iterator_type end) noexcept
          : name(begin.front_ptr(), end.front_ptr()) {}

        void set(string_iterator_type begin, string_iterator_type end) noexcept
        {
            name.clear();
            name.resize(end.front_ptr() - begin.front_ptr());
            std::copy(begin.front_ptr(), end.front_ptr(), name.begin()); 
        }
    };
}
