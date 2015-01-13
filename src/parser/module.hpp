#pragma once
#include "../string/string_view.hpp"
#include "../ast/module.hpp"
#include "../error/error_handler.hpp"
#include "token.hpp"
#include "manager.hpp"

namespace bksg
{
    bool parse_module_declaration (parser_manager & parser) noexcept;
    bool parse_module_fully_qualified_name (parser_manager & parser) noexcept;

    // *ModuleDeclaration* <- **Module** *ModuleFullyQualifiedName**
    bool parse_module_declaration (parser_manager & parser) noexcept
    {
        if (!parser.module_ptr->name.empty()) {
            parser.issue_error(parse_error::module_declaration_more_than_once, error_category::syntax_error);
            return false;
        }

        if (!equal(parser.token.last_token().string,"module")) { return false; }

        parser.token.next_token();
        parser.current_scope_ptr = parser.module_ptr;

        if (!parse_module_fully_qualified_name(parser)) {
            parser.issue_error(parse_error::module_declaration_invalid, error_category::syntax_error);
            return false;
        }

        if (parser.token.last_token().detail != token_detail::semicolon) {
            parser.issue_error(parse_error::module_semicolon_missing, error_category::syntax_error);
        }
        parser.token.next_token();
        parser.current_scope_ptr->kind = scope_kind::module;
        return true;
    }

    // *ModuleFullyQualifiedName* <- *PackageNames* *ModuleName*
    // *PackageNames* <- (*PakageName* **.**)\*
    // *PackageName* <- *Identifier*
    // *ModuleName* <- *Identifier*
    bool parse_module_fully_qualified_name (parser_manager & parser) noexcept
    {
        while (parser.token.last_token().kind == token_kind::identifier) {
            auto tmp = parser.token.last_token().string;
            parser.token.next_token();
            if (parser.token.last_token().detail != token_detail::period) {
                parser.module_ptr->name = parser.token.back_token().string;
                parser.token.next_token();
                return true;
            }
            parser.module_ptr->package.add_name(tmp);
            parser.token.next_token();
        }
        parser.issue_error(parse_error::token_invalid_where_identifier_expectd, error_category::token_error);
        return false;
    }
}
