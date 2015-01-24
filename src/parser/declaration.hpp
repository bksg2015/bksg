#pragma once
#include "lex.hpp"
#include "type.hpp"
#include "expression.hpp"
#include "../string/string_iterator.hpp"
#include "../ast/declaration.hpp"
#include "../debug/assert.hpp"
#include <tuple>
#include <memory>

namespace bksg
{
    std::tuple<bool, std::unique_ptr<ast_declaration>> parse_declaration (string_iterator_type & cursor) noexcept;
    std::tuple<bool, std::unique_ptr<ast_declaration>> parse_variable_declaration (string_iterator_type & cursor) noexcept;

    std::tuple<bool, std::unique_ptr<ast_declaration>> parse_declaration (string_iterator_type & cursor) noexcept
    {
        assert(true, assert_kind::parse_declaration, "parse_declaration", "enter", cursor.front_ptr());
        auto ret = parse_variable_declaration(cursor);
        if (std::get<0>(ret)) {
            assert(true, assert_kind::parse_declaration, "parse_declaration", "ok", cursor.front_ptr());
            return std::make_tuple(true, std::move(std::get<1>(ret))); 
        }
        return std::make_tuple(false, std::unique_ptr<ast_declaration>{});
    }

    std::tuple<bool, std::unique_ptr<ast_declaration>> parse_variable_declaration (string_iterator_type & cursor) noexcept
    {
        assert(true, assert_kind::parse_declaration, "parse_variable_declaration", "enter", cursor.front_ptr());
        if (!parse_string(cursor, "var")) { 
            assert(true, assert_kind::parse_declaration, "parse_variable_declaration", "fail1", cursor.front_ptr());
            return std::make_tuple(false, std::unique_ptr<ast_variable_declaration>{}); 
        }

        auto type = parse_type(cursor);
        if (!std::get<0>(type)) {
            assert(true, assert_kind::parse_declaration, "parse_variable_declaration", "fail2", cursor.front_ptr());
            return std::make_tuple(false, std::unique_ptr<ast_variable_declaration>{}); 
        }

        auto name = parse_identifier(cursor);
        if (!std::get<0>(name)) {
            assert(true, assert_kind::parse_declaration, "parse_variable_declaration", "fail3", cursor.front_ptr());
            return std::make_tuple(false, std::unique_ptr<ast_variable_declaration>{}); 
        }      
 
        std::unique_ptr<ast_expression> expr; 
        if (parse_ascii(cursor, '=')) {
            parse_separator(cursor);
            auto ret = parse_expression(cursor);
            if (!std::get<0>(ret)) {
                assert(true, assert_kind::parse_declaration, "parse_variable_declaration", "fail4", cursor.front_ptr());
                return std::make_tuple(false, std::unique_ptr<ast_variable_declaration>{}); 
            }
            expr = std::move(std::get<1>(ret));
            if (!parse_ascii(cursor, ';')) {
                assert(true, assert_kind::parse_declaration, "parse_variable_declaration", "fail5", cursor.front_ptr());
                return std::make_tuple(false, std::unique_ptr<ast_variable_declaration>{}); 
            }
            parse_separator(cursor);
        }

        std::unique_ptr<ast_variable_declaration> ptr(new ast_variable_declaration{});
        ptr->type = std::move(std::get<1>(type));
        ptr->name = std::move(std::get<1>(name));
        ptr->initializer = std::move(expr);
        return std::make_tuple(true, std::move(ptr)); 
    }

}
