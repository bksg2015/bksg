#pragma once
#include "./scope.hpp"
#include "./type.hpp"
#include "./parameter.hpp"
#include <vector>
#include <memory>
#include <algorithm>

namespace bksg
{
    enum class function_qualifier_kind
    {
        num
    };
    
    struct function_qualifier
    {
        using value_type = unsigned int;
        static_assert(
            sizeof(value_type) * std::numeric_limits<value_type>::digits > int(type_qualifier_kind::num)
          , "change type of value in function_qualifier struct."
        ); 
    private:
        value_type value;
    public:
        function_qualifier () noexcept { value = 0; }

        bool get (function_qualifier_kind kind) const noexcept
        {
            return ((value & (1 << value_type(kind))) >> value_type(kind)) == 1;
        }
    
        void set (function_qualifier_kind kind, bool flg) noexcept
        {
            value = value | (flg << value_type(kind));
        }
    };

    struct scope_function : scope
    {
        using scope_type = scope;
        using scope_observe_ptr = scope_type *;
        using type_type = type;
        using parameter_type = parameter;
    
        type_type return_type;
        std::vector<parameter_type> parameters;
        function_qualifier qualifier;

        scope_function (scope_observe_ptr parent = nullptr) noexcept 
          : scope_type(scope_kind::function, parent) {}

        std::size_t num_parameters () const noexcept { return parameters.size(); }
    };
}
