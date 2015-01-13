#pragma once
#include "../string/string_view.hpp"
#include "../ast/namespace.hpp"
#include "../error/error_handler.hpp"
#include "token.hpp"
#include "manager.hpp"

namespace bksg
{
    // **namespace** *NamespaceName* **{** *Declarations* **}**
    bool parse_namespace_declaration (parser_manager & parser) noexcept
    {
        using namespace_observe_ptr = scope_namespace *;
        if (!equal(parser.token.last_token().string, "namespace")) { return false; }

        parser.token.next_token();
        auto ns_ptr = static_cast<namespace_observe_ptr>(&(parser.current_scope_ptr->add_children<scope_namespace>()));

        if (parser.token.last_token().kind != token_kind::identifier) {
            parser.issue_error(parse_error::namespace_name_missing, error_category::syntax_error);
            return false;
        }
        
        parser.current_scope_ptr = ns_ptr;
        parser.current_scope_ptr->name = parser.token.last_token().string; 
        parser.token.next_token();
        
        if (parser.token.last_token().detail != token_detail::left_curved_bracket) {
            parser.current_scope_ptr = parser.current_scope_ptr->parent; 
            parser.issue_error(parse_error::namespace_left_bracket_missing, error_category::syntax_error);
            return false;
        }

        parser.token.next_token();
        return true;
    }
}
