#pragma once

#include "../string/string_view_interface.hpp"
#include "../string/string_algorithm.hpp"
#include "../ast/declaration.hpp"
#include "../error/error_handler.hpp"
#include "token.hpp"
#include "manager.hpp"

namespace bksg
{
    template <typename StringView>
    struct parser_variable_declaration
    {
        using parser_manager_type = parser_manager<StringView>;

        // **namespace** *NamespaceName* **{** *Declarations* **}**
        bool parse_variable_declaration (parser_manager_type & parser) noexcept
        {
            if (parser.token.last_token_detail != token_detail::keyword_namespace) { return false; }

            parser.token.next_token();
            parser.current_decl_ptr = parser.module_ptr;

            if (parser.token.last_token_kind != token_kind::identifier) {
                parser.issue_error(parse_error::namespace_name_missing, error_category::syntax_error);
                return false;
            }

            parser.current_decl_ptr = &(parser.current_decl_ptr->add_children(decl_kind::namepsace));
            parser.current_decl_ptr->name = parser.token.token_cursor;           
            parser.token.next_token();
            
            if (parser.token.last_token_detail != token_detail::left_curved_bracket) {
                parser.current_decl_ptr = parser.current_decl_ptr->parent; 
                parser.issue_error(parse_error::namespace_left_bracket_missing, error_category::syntax_error);
            }

            parser.token.next_token();
             
            return true;
        }
    };
}
