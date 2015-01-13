#pragma once
#include "./scope.hpp"
#include <vector>
#include <memory>
#include <algorithm>

namespace bksg
{
    struct scope_namespace : scope
    {
        using scope_type = scope;
        using scope_observe_ptr = scope_type *;

        scope_namespace (scope_observe_ptr parent = nullptr) noexcept 
          : scope(scope_kind::namepsace, parent) {}
    };
}
