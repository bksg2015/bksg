#pragma once
#include "../string/string_iterator.hpp"
// #include "../ast/scope.hpp"
#include <vector>

namespace bksg
{
    struct parser_manager 
    {
//         using scope_type = scope; 
//         using scope_observe_ptr = scope_type *;
//         using module_type = scope_module; 
//         using module_observe_ptr = module_type *; 
//         using error_handler_type = error_handler;

//         error_handler_type error_handl;

//         module_observe_ptr module_ptr;
//         scope_observe_ptr current_scope_ptr;
        
        string_iterator_type cursor;

//         parser_manager (string_iterator_type cursor, module_type & module) noexcept
//           : cursor(cursor), module_ptr(&module) {}

        parser_manager (string_iterator_type cursor) noexcept
          : cursor(cursor)  {}

//         void issue_error (parse_error kind, error_category category) noexcept { error_handl.issue(token.last_token().string, kind, category); }
    
//         void print_current_full_qualified_name () noexcept
//         {
//             auto ptr = current_scope_ptr;
//             std::vector<scope_observe_ptr> vec;
//             vec.push_back(ptr);
//             while (ptr->parent != nullptr) { vec.push_back(ptr->parent); ptr = ptr->parent; }
//             for (int i = vec.size() - 1; i >= 0; --i) {
//                 std::cout << vec[i]->name.to_string();
//                 if ( i > 0 ) { std::cout << '.'; }
//             }
//             std::cout << std::endl;
//         }
    };
}
