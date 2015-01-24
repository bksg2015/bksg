#pragma once
#include "identifier.hpp"
#include "type.hpp"
#include "expression.hpp"
#include "../string/string_iterator.hpp"
#include <vector>
#include <cstddef>
#include <iostream>

namespace bksg
{
    struct ast_declaration;

    enum class declaration_kind
    {
        VariableDeclaration
      , Num
    };

    char const * declaration_kind_name[std::size_t(declaration_kind::Num)] =
    {
        "VariableDeclaration"
    };

    struct ast_declaration
    {
        declaration_kind kind;

        ast_declaration (declaration_kind kind) noexcept : kind(kind) {}

        void print (int level = 0) noexcept
        {
            for (int i = 0; i < level; ++i) { std::cout << "  "; }
            std::cout << declaration_kind_name[int(kind)] << " : ";
            print_sub(level);
        }

        virtual void print_sub (int level) noexcept { std::cout << std::endl; }
        virtual ~ast_declaration () noexcept = default;
    };

    struct ast_variable_declaration : ast_declaration
    {
        std::unique_ptr<ast_identifier> name;
        std::unique_ptr<ast_type> type;
        std::unique_ptr<ast_expression> initializer;
          
        ast_variable_declaration () noexcept : ast_declaration(declaration_kind::VariableDeclaration) {}

        void print_sub (int level) noexcept 
        {
            std::cout << std::string(&*name->name.begin(), &*name->name.end()) << " : " << std::endl;
            if (bool(type)) { type->print(level + 1); }
            if (bool(initializer)) { initializer->print(level + 1); }
        }

        virtual ~ast_variable_declaration () noexcept = default;
    };
}
