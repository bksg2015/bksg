#pragma once

#include "../string/string_view.hpp"
#include "../ast/scope.hpp"
#include "../ast/parameter.hpp"
#include "../error/error_handler.hpp"
#include "token.hpp"
#include "manager.hpp"
#include "type.hpp"
#include <vector>

namespace bksg
{
    bool parse_parameter (parser_manager & parser, std::vector<parameter>  & parameters) noexcept;
    bool parse_parameters (parser_manager & parser, std::vector<parameter>  & parameters) noexcept;

    // *Parameters* <- **(** (*Parameter* **,**)\* *Parameter* **)**
    bool parse_parameters (parser_manager & parser, std::vector<parameter> & parameters) noexcept
    {
        parameters.clear();

        if (parser.token.last_token().detail != token_detail::left_paren) { 
            return false; 
        }
        parser.token.next_token();

        while (parse_parameter(parser,parameters)) {
            if (parser.token.last_token().detail != token_detail::comma) {
                if (parser.token.last_token().detail == token_detail::right_paren) {
                    parser.token.next_token();
                    return true;
                } else {
                    parser.issue_error(parse_error::parameters_right_paren_missing, error_category::syntax_error);
                    return false; 
                }
            }
            parser.token.next_token();
        }
        
        parser.issue_error(parse_error::parameters_parameter_missing, error_category::syntax_error);
        return false; 
    }

    // *Parameter* <- *Type* *ParameterName*?    
    bool parse_parameter (parser_manager & parser, std::vector<parameter> & parameters) noexcept
    {
        parameters.push_back(parameter{});
        auto & p = parameters.back();
        if (!parse_type(parser,p.parameter_type)) { return false; }
        if (parser.token.last_token().kind == token_kind::identifier) {
            p.parameter_name = parser.token.last_token().string;
            parser.token.next_token();
        }
        return true;
    } 
}
