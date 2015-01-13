#pragma once
#include "./scope.hpp"
#include <vector>
#include <memory>
#include <algorithm>

namespace bksg
{
    struct scope_module : scope
    {
        using scope_type = scope;
        using scope_observe_ptr = scope_type *;

        struct package_names
        {
            std::vector<string_view_type> names;
            void add_name (string_view_type const & name) noexcept { names.push_back(name); }

            bool operator== (package_names & pack) noexcept
            {
                if (names.size() != pack.names.size()) { return false; }
                for (int i = 0, e = names.size(); i < e; ++i) 
                {
                    if (!equal(names[i], pack.names[i])) { return false; }
                }
                return true;
            }
        };

        package_names package;

        scope_module () noexcept : scope_type(scope_kind::module,nullptr) {}
    };
}
