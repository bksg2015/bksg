#pragma once
#include <limits>

namespace bksg
{
    enum class type_kind 
    {
        Void
      , Bool
      , Char
      , Class 
    };

    enum class type_qualifier_kind
    {
        Const
      , LvalueRef
      , num
    };
    
    struct type_qualifier
    {
        using value_type = unsigned int;
        static_assert(
            sizeof(value_type) * std::numeric_limits<value_type>::digits > int(type_qualifier_kind::num)
          , "change type of value in type_qualifier struct."
        ); 
    private:
        value_type value;
    public:
        type_qualifier () noexcept { value = 0; }
        bool get (type_qualifier_kind kind) const noexcept
        {
            return ((value & (1 << value_type(kind))) >> value_type(kind)) == 1;
        }
    
        void set (type_qualifier_kind kind, bool flg) noexcept
        {
            value = value | (flg << value_type(kind));
        }
    };

    struct type
    {
        type_kind kind;
        type_qualifier qualifier;
    };

}
