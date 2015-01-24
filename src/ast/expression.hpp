#pragma once
#include "identifier.hpp"
#include "type.hpp"
#include "integer.hpp"
#include "../string/string_iterator.hpp"
#include <vector>
#include <cstddef>
#include <iostream>

namespace bksg
{
    enum class expression_kind
    {
        IntegerLiteral
      , FunctionCall
      , OperatorCall
      , NonOperatorCall
      , Unknown
      , Num
    };

    char const * expression_kind_name [std::size_t(expression_kind::Num)] =
    {
        "IntegerLiteral"
      , "FunctionCall"
      , "OperatorCall"
      , "NonOperatorCall"
      , "Unknown"
    };

    enum class operator_kind
    {
        Comma
      , AssignOperatorBegin
      , Equal
      , AssignOperatorEnd
      , Unknown
      , Num 
    };

    char const * operator_kind_name [std::size_t(operator_kind::Num)] =
    {
        "Comma"
      , "AssignOperatorBegin"
      , "Equal"
      , "AssignOperatorEnd"
      , "Unknown"
    };

    struct ast_expression;
    struct ast_expression_function_call;
    struct ast_expression_operator_call;
    struct ast_expression_non_operator_call;

    struct ast_expression
    {
        expression_kind kind;
        ast_type type;

        ast_expression (expression_kind kind) noexcept : kind(kind) {}

        void print (int level = 0) noexcept
        {
            for (int i = 0; i < level; ++i) { std::cout << "  "; }
            std::cout << expression_kind_name[int(kind)] << " : ";
            print_sub(level);
        }

        virtual void print_sub (int level) noexcept { std::cout << std::endl; }

        virtual ~ast_expression () noexcept = default; 
    };

    struct ast_expression_function_call : ast_expression
    {
        std::vector<std::unique_ptr<ast_expression>> arguments; 

        ast_expression_function_call (expression_kind kind) noexcept 
          : ast_expression(kind) {} 

        std::size_t num_arguments () const noexcept { return arguments.size(); }
        void add_argument (std::unique_ptr<ast_expression> && ptr) noexcept { arguments.push_back(std::move(ptr)); }


        void print_sub (int level) noexcept 
        { 
            for (auto & ptr : arguments) { 
                if (bool(ptr)) { ptr->print(level + 1); } 
            } 
        }
        
        virtual ~ast_expression_function_call () noexcept = default; 
    };

    struct ast_expression_operator_call : ast_expression_function_call
    {
        operator_kind kind;

        ast_expression_operator_call (operator_kind kind) noexcept
          : kind(kind), ast_expression_function_call(expression_kind::OperatorCall) {} 

        void print_sub (int level) noexcept
        {
            std::cout << operator_kind_name[std::size_t(kind)] << std::endl;
            ast_expression_function_call::print_sub(level);
        }

        bool is_comma_operator () const noexcept { return kind == operator_kind::Comma; }
        bool is_assign_operator () const noexcept { return operator_kind::AssignOperatorBegin < kind && kind < operator_kind::AssignOperatorEnd; }

        virtual ~ast_expression_operator_call () noexcept = default; 
    };

    struct ast_expression_non_operator_call : ast_expression_function_call
    {
        ast_identifier function_name;

        ast_expression_non_operator_call (string_iterator_type name_begin, string_iterator_type name_end) noexcept 
          : function_name(name_begin, name_end), ast_expression_function_call(expression_kind::FunctionCall) {} 

        void print_sub (int level) noexcept
        {
            std::cout << std::string(function_name.name.begin(), function_name.name.end()) << std::endl;
            ast_expression_function_call::print_sub(level);
        }

        virtual ~ast_expression_non_operator_call () noexcept = default; 
    };

    struct ast_expression_integer : ast_expression
    {
        std::unique_ptr<ast_integer> integer;

        ast_expression_integer (std::unique_ptr<ast_integer> && integer) noexcept
          :  integer(std::move(integer)), ast_expression(expression_kind::IntegerLiteral) {} 

        void print_sub (int level) noexcept
        {
            std::cout << integer->get() << std::endl;
        }

        virtual ~ast_expression_integer () noexcept = default;
    };
}
