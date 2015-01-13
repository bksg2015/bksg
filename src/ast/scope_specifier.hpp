#pragma once
#include "../string/string_view.hpp"
#include <vector>
namespace bksg
{
    struct scope_specifier
    {
        std::vector<string_view_type> names;
    };
}
