#pragma once

#include "identifier.hpp"
#include "template_instance.hpp"
#include "../string/string_iterator.hpp"
#include <limits>
#include <memory>

namespace bksg
{
    enum class type_qualifier_kind
    {
        Const
      , LvalueRef
      , Num
    };
    
    struct type_qualifier
    {
        using value_type = unsigned int;
        static_assert(
            sizeof(value_type) * std::numeric_limits<value_type>::digits > int(type_qualifier_kind::Num)
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

    struct ast_type
    {
        std::unique_ptr<ast_template_instance> basic_type;
        std::vector<std::unique_ptr<ast_template_instance>> basic_type_scope;
        type_qualifier qualifier;

        void print (int level = 0) noexcept
        {
            for (int i = 0; i < level; ++i) { std::cout << "  "; }
            std::cout << "ast_type : " << std::endl;
            basic_type->print(level + 1);
            for (auto & v : basic_type_scope) { v->print(level + 1); }
        }
    };

}
