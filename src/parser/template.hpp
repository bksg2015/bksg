#pragma once

#include "../string/string_view_interface.hpp"
#include "../string/string_algorithm.hpp"
#include "../ast/ast.hpp"
#include "../error/error_handler.hpp"
#include "token.hpp"
#include "manager.hpp"

namespace bksg
{
    template <typename StringView>
    struct parser_template_declaration
    {
        using parser_manager_type = parser_manager<StringView>;

        // **Module** *ModuleFullyQualifiedName* *TemplateParameterList*
        bool parse_template_parameter_list (parser_manager_type & parser) noexcept
        {
            if (parser.token.last_token_detail != token_detail::left_paren) { return false; }
            parser.token.next_token();
            auto & module_decl_ast = ast_cast<ast_kind::module_declaration>(*parser.ast_cursor); 
            parser.ast_cursor = &(module_decl_ast.module_fully_qualified_name);
            if (!parse_module_fully_qualified_name(parser)) {
                parser.issue_error(parse_error::module_declaration_invalid, error_category::syntax_error);
                parser.ast_cursor = &module_decl_ast;
                return false;
            }
            parser.ast_cursor = &module_decl_ast;
            return true;
        }

        // *ModuleFullyQualifiedName* <- *PackageNames* *ModuleName*
        // *PackageNames* <- (*PakageName* **.**)\*
        // *PackageName* <- *Identifier*
        // *ModuleName* <- *Identifier*
        bool parse_module_fully_qualified_name (parser_manager_type & parser) noexcept
        {
            std::cout << "module_fully_qualified_name" << std::endl;
            auto & module_fulqul_ast = ast_cast<ast_kind::module_fully_qualified_name>(*parser.ast_cursor);
            if (parser.token.last_token_kind != token_kind::identifier) { 
                return false;
            }
            while (parser.token.last_token_kind == token_kind::identifier) {
                auto token_cursor = parser.token.token_cursor;
                parser.token.next_token();
                if (parser.token.last_token_detail != token_detail::period) {
                    module_fulqul_ast.module_name = token_cursor;
                    return true;
                }
                module_fulqul_ast.package_names.push_back(token_cursor);
                parser.token.next_token();
            }

            parser.issue_error(parse_error::token_invalid_where_identifier_expectd, error_category::token_error);
            return false;
        }
    };
 

}
