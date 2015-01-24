#pragma once
#include "../string/string_view.hpp"
#include <vector>
#include <iostream>

namespace bksg
{
    enum class error_kind
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
      , token_invalid_where_identifier_expected
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
      , "end_of_file"
    };

    struct error_ticket
    {
        using error_kind_type = parse_error;

        string_view_type string_position;
        error_kind_type kind;

        error_ticket (string_view_type string_position, error_kind_type kind) noexcept
          : string_position(string_position), kind(kind)  {}
    };

    struct error_handler
    {
        using error_cursor_type = int;

        std::vector<error_ticket> tickets;
        error_category category;

        error_ticket_type & last_error () noexcept { return tickets[error_cursor]; }

        void fall_back (error_cursor_type cursor) { error_cursor = cursor; }

        void issue (string_view_type string_position, error_kind_type kind) noexcept
        { 
            ++error_cursor;
            tickets.push_back(error_ticket(string_position, kind)); 
        }

        void flush () noexcept
        {
            tickets.clear();
        }

        template <typename Ostream>
        void print (Ostream & ost) noexcept
        {
            for (auto & t : tickets) {
                ost << "error : " << parse_error_name[int(t.kind)] << std::endl;
                ost << std::string(t.string_position.begin(), t.string_position.end()) << std::endl;
            }
        }
    };
}
