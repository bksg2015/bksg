#pragma once
#include "../string/string_view.hpp"
#include "../ast/scope_specifier.hpp"
#include "../error/error_handler.hpp"
#include "token.hpp"
#include "manager.hpp"

namespace bksg
{
    // *ScopeSpecifier* <- (*NamespaceName* **.**)\+
    // *NamespaceName* <- *Identifier*
    bool parse_scope_specifier (parser_manager & parser, scope_specifier & s) noexcept
    {
        using parser_manager_type = parser_manager;
        s.names.clear();
        while (parser.token.last_token().kind == token_kind::identifier) {
            auto tmp = parser.token.last_token().string;
            parser.token.next_token();
            if (parser.token.last_token().detail != token_detail::period) {
                parser.token.back_token();
                parser.token.back_token();
                return true;
            }
            s.names.push_back(tmp);
        }
        return false;
    }
}
