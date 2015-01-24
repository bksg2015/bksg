#pragma once
#include <cstddef>
#include <string>

namespace bksg
{
    enum class assert_kind 
    {
        parse_declaration
      , parse_expression
      , parse_statement
      , parse_template_instance
      , parse_type
      , parse_integer
      , num
    };

    bool assert_enabled[std::size_t(assert_kind::num)] = 
    {
        true // parse_declaration
      , true // parse_expression
      , true // parse_statement
      , true // parse_template_instance
      , true // parse_type
      , true // parse_integer
    };

    template <typename T>
    void assert (bool flg, assert_kind kind, T && t) 
    {
        if (assert_enabled[std::size_t(kind)]) { 
            std::cout << t << " : " << std::endl;
        }
    }

    template <typename T, typename ... Args>
    void assert (bool flg, assert_kind kind, T && t, Args && ... args) 
    {
        if (assert_enabled[std::size_t(kind)]) { 
            std::cout << t << " : ";
            assert(flg, kind, std::forward<Args>(args)...);
        }
    }

}
