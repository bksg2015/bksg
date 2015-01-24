#pragma once
#include "lex.hpp"
#include "declaration.hpp"
#include "../string/string_iterator.hpp"
#include "../ast/statement.hpp"
#include "../ast/expression.hpp"
#include "../debug/assert.hpp"
#include <tuple>
#include <memory>

namespace bksg
{
    std::tuple<bool, std::unique_ptr<ast_statement>> parse_statement (string_iterator_type & cursor) noexcept;
    std::tuple<bool, std::unique_ptr<ast_statement>> parse_block_statement (string_iterator_type & cursor) noexcept;
    std::tuple<bool, std::unique_ptr<ast_statement>> parse_non_scope_statement (string_iterator_type & cursor) noexcept;
    std::tuple<bool, std::unique_ptr<ast_statement>> parse_declaration_statement (string_iterator_type & cursor) noexcept;

    std::tuple<bool, std::unique_ptr<ast_statement>> parse_statement (string_iterator_type & cursor) noexcept
    {
        assert(true, assert_kind::parse_statement, "parse_statement", "enter", cursor.front_ptr());
        auto block_stat = parse_block_statement(cursor);

        if (std::get<0>(block_stat)) {
            assert(true, assert_kind::parse_statement, "parse_statement", "ok1", cursor.front_ptr());
            return std::make_tuple(true, std::move(std::get<1>(block_stat))); 
        }

        auto non_block_stat = parse_non_scope_statement(cursor);
        if (std::get<0>(non_block_stat)) {
            assert(true, assert_kind::parse_statement, "parse_statement", "ok2", cursor.front_ptr());
            return std::make_tuple(true, std::move(std::get<1>(non_block_stat))); 
        }

        assert(true, assert_kind::parse_statement, "parse_statement", "fail", cursor.front_ptr());
        return std::make_tuple(false, std::unique_ptr<ast_statement>{});
    }

    std::tuple<bool, std::unique_ptr<ast_statement>> parse_block_statement (string_iterator_type & cursor) noexcept
    {
        assert(true, assert_kind::parse_statement, "parse_block_statement", "enter", cursor.front_ptr());
        if (!parse_ascii(cursor, '{')) {
            assert(true, assert_kind::parse_statement, "parse_block_statement", "fail1", cursor.front_ptr());
            return std::make_tuple(false, std::unique_ptr<ast_statement>{});
        } 
        
        parse_separator(cursor);        

        std::unique_ptr<ast_block_statement> block(new ast_block_statement{}); 
        while (true) {
            auto stat = parse_statement(cursor);
            if (!std::get<0>(stat)) { break; }
            block->statements.push_back(std::move(std::get<1>(stat))); 
        }

        if (!parse_ascii(cursor, '}')) {
            assert(true, assert_kind::parse_statement, "parse_block_statement", "fail2", cursor.front_ptr());
            return std::make_tuple(false, std::unique_ptr<ast_statement>{});
        }

        parse_separator(cursor);        
        
        assert(true, assert_kind::parse_statement, "parse_block_statement", "ok", cursor.front_ptr());
        return std::make_tuple(true, std::move(block));
    }

    std::tuple<bool, std::unique_ptr<ast_statement>> parse_non_scope_statement (string_iterator_type & cursor) noexcept
    {
        assert(true, assert_kind::parse_statement, "parse_non_scope_statement", "enter", cursor.front_ptr());
        auto decl_stat = parse_declaration_statement(cursor);
        if (std::get<0>(decl_stat)) {
            assert(true, assert_kind::parse_statement, "parse_non_scope_statement", "ok1", cursor.front_ptr());
            return std::make_tuple(true, std::move(std::get<1>(decl_stat)));  
        }
        assert(true, assert_kind::parse_statement, "parse_non_scope_statement", "fail", cursor.front_ptr());
        return std::make_tuple(false, std::unique_ptr<ast_statement>{});
    }

    std::tuple<bool, std::unique_ptr<ast_statement>> parse_declaration_statement (string_iterator_type & cursor) noexcept
    {
        assert(true, assert_kind::parse_statement, "parse_declaration_statement", "enter", cursor.front_ptr());
        auto decl = parse_declaration(cursor);
        if (!std::get<0>(decl)) {
            assert(true, assert_kind::parse_statement, "parse_declaration_statement", "fail", cursor.front_ptr());
            return std::make_tuple(false, std::unique_ptr<ast_statement>{}); 
        }
        auto decl_stat = std::unique_ptr<ast_declaration_statement>(new ast_declaration_statement{});
        decl_stat->declaration = std::move(std::get<1>(decl));
        assert(true, assert_kind::parse_statement, "parse_declaration_statement", "ok", cursor.front_ptr());
        return std::make_tuple(true, std::move(decl_stat));        
    }
}
