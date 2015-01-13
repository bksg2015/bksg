#pragma once
#include "../string/string_view.hpp"
#include "./type.hpp"
#include "./scope_specifier.hpp"
#include <vector>
#include <memory>

namespace bksg
{
    struct parameter
    {
        type parameter_type;
        string_view_type parameter_name;
        scope_specifier scope;
    };
}
