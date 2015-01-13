#pragma once
#include "../string/string_view.hpp"
#include <vector>
#include <memory>
#include <algorithm>

namespace bksg
{
    enum class scope_kind
    {
        module
      , namepsace
      , type
      , function
      , variable
      , scope_kind_number
    };

    char const * scope_kind_name [] = {"module", "namespace", "type", "function", "variable"};

    struct scope
    {
        using scope_type = scope;
        using scope_observe_ptr = scope_type *;

        scope_observe_ptr parent;
        string_view_type name;
        scope_kind kind;

        std::vector<std::unique_ptr<scope_type>> children;

        scope (scope_kind kind, scope_observe_ptr parent = nullptr) noexcept 
          : kind(kind), parent(parent) {}

        template <typename Iterator>
        auto find_name (Iterator first, Iterator last, string_view_type name) noexcept 
        { 
            return std::find_if(first, last, [&name](auto & n) { return equal(name, n); }); 
        }

        template <typename ScopeType>
        scope_type & add_children () noexcept
        {
            children.push_back(std::unique_ptr<ScopeType>{new ScopeType{}});
            children.back()->parent = this;
            return *(children.back());
        }

        virtual ~scope () = default;
    };
}
