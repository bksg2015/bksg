#pragma once
#include "../string/string_view.hpp"
#include <vector>
#include <iostream>

namespace bksg
{
    enum class parse_error
    {
        invalid_ast_cursor 
      , module_declaration_invalid
      , module_fully_qualifiedname_invalid
      , module_declaration_more_than_once
      , module_semicolon_missing
      , namespace_name_missing
      , namespace_left_bracket_missing
      , function_name_missing
      , function_parameters_missing
      , function_body_left_bracket_missing
      , parameters_right_paren_missing
      , parameters_parameter_missing
      , token_invalid_where_identifier_expectd
    };

    char const * parse_error_name [] = {
        "invalid_ast_cursor" 
      , "module_declaration_invalid"
      , "module_fully_qualifiedname_invalid"
      , "module_declaration_more_than_once"
      , "module_semicolon_missing"
      , "namespace_name_missing"
      , "namespace_left_bracket_missing"
      , "function_name_missing"
      , "function_parameters_missing"
      , "function_body_left_bracket_missing"
      , "parameters_right_paren_missing"
      , "parameters_parameter_missing"
      , "token_invalid_where_identifier_expectd"
    };

    enum class error_category
    {
        internal_error
      , token_error
      , token_warning
      , syntax_error
      , syntax_warning
      , semantic_error
      , semantic_warning
    };

    char const * error_category_name [] = {
        "internal_error"
      , "token_error"
      , "token_warning"
      , "syntax_error"
      , "syntax_warning"
      , "semantic_error"
      , "semantic_warning"
    };

    struct error_ticket
    {
        using error_kind_type = parse_error;

        string_view_type string_position;
        error_kind_type kind;
        error_category category;

        error_ticket (string_view_type string_position, error_kind_type kind, error_category category) noexcept
          : string_position(string_position), kind(kind), category(category) {}
    };

    struct error_handler
    {
        using error_kind_type = parse_error;
        using error_ticket_type = error_ticket;
        using error_cursor_type = int;

        std::vector<error_ticket_type> tickets;
        error_category category;
        error_cursor_type error_cursor = -1;

        error_ticket_type & last_error () noexcept { return tickets[error_cursor]; }

        void fall_back (error_cursor_type cursor) { error_cursor = cursor; }

        void issue (string_view_type string_position, error_kind_type kind, error_category category) noexcept
        { 
            std::cout << "error : " << parse_error_name[int(kind)] << ", " << error_category_name[int(category)] << std::endl;
            ++error_cursor;
            if (tickets.size() == error_cursor) { 
                tickets.push_back(error_ticket_type(string_position, kind, category)); 
            } else {
                auto & t = tickets[error_cursor];
                t.string_position = string_position;
                t.kind = kind;
                t.category = category;
            }
        }

        template <typename Ostream>
        void print (Ostream & ost) noexcept
        {
            for (auto & t : tickets) {
                ost << "error : " << parse_error_name[int(t.kind)] << ", " << error_category_name[int(t.category)] << std::endl;
                ost << std::string(t.string_position.begin(), t.string_position.end()) << std::endl;
            }
        }
    };
}
