#pragma once

#include "../string/string_view_interface.hpp"
#include "../string/string_algorithm.hpp"
#include "../ast/scope.hpp"
#include "../ast/function.hpp"
#include "../error/error_handler.hpp"
#include "token.hpp"
#include "parameter.hpp"
#include "manager.hpp"

namespace bksg
{
    bool parse_function_declaration (parser_manager & parser) noexcept;

    // **function** *FunctionName* *TemplateParameterList*? *Parameters* *FunctionReturnType* *FunctionBody*
    bool parse_function_declaration (parser_manager & parser) noexcept
    {
        if (!equal(parser.token.last_token().string, "function")) { return false; }
        parser.token.next_token();
        auto func_ptr = static_cast<scope_function *>(&(parser.current_scope_ptr->add_children<scope_function>()));
        parser.current_scope_ptr = func_ptr;

        if (parser.token.last_token().kind != token_kind::identifier) {
            parser.issue_error(parse_error::function_name_missing, error_category::syntax_error);
            return false;
        }
        
        func_ptr->name = parser.token.last_token().string;
        parser.token.next_token();
 
        if (!parse_parameters(parser, func_ptr->parameters)) {
            parser.issue_error(parse_error::function_parameters_missing, error_category::syntax_error);
            return false;
        }

        if (parser.token.last_token().detail != token_detail::left_curved_bracket) {
            parser.issue_error(parse_error::function_body_left_bracket_missing, error_category::syntax_error);
            return false;
        }

        return true;
    }
}
 
