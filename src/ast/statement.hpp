#pragma once
// #include "identifier.hpp"
// #include "type.hpp"
#include "expression.hpp"
#include "declaration.hpp"
#include "../string/string_iterator.hpp"
#include <vector>
#include <cstddef>
#include <iostream>

namespace bksg
{
    struct ast_statement;

    enum class statement_kind
    {
        DeclarationStatement
      , BlockStatement
      , Num
    };

    char const * statement_kind_name[std::size_t(statement_kind::Num)] =
    {
        "DeclarationStatement"
      , "BlockStatement"
    };

    struct ast_statement
    {
        statement_kind kind;
        ast_statement (statement_kind kind) noexcept : kind(kind) {}

        void print (int level = 0) noexcept
        {
            for (int i = 0; i < level; ++i) { std::cout << "  "; }
            std::cout << statement_kind_name[int(kind)] << " : ";
            print_sub(level);
        }

        virtual void print_sub (int level) noexcept { std::cout << std::endl; }
        
        virtual ~ast_statement () noexcept = default;
    };

    struct ast_declaration_statement : ast_statement
    {
        std::unique_ptr<ast_declaration> declaration;

        ast_declaration_statement () noexcept : ast_statement(statement_kind::DeclarationStatement) {} 

        void print_sub (int level) noexcept 
        {
            std::cout << std::endl;
            if (bool(declaration)) { declaration->print(level + 1); }
        }

        virtual ~ast_declaration_statement () noexcept = default;
    };

    struct ast_block_statement : ast_statement
    {
        std::vector<std::unique_ptr<ast_statement>> statements;

        ast_block_statement () noexcept : ast_statement(statement_kind::BlockStatement) {} 

        void print_sub (int level) noexcept 
        {
            std::cout << std::endl;
            for (auto & p : statements) {
                if (bool(p)) { p->print(level + 1); }
            }
        }

        virtual ~ast_block_statement () noexcept = default;
    };

}
