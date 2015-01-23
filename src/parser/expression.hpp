#pragma once
#include "lex.hpp"
#include "integer.hpp"
#include "../string/string_iterator.hpp"
#include "../ast/expression.hpp"
#include "../debug/assert.hpp"
#include <tuple>
#include <memory>

namespace bksg
{
    std::tuple<bool, std::unique_ptr<ast_expression>> parse_expression (string_iterator_type & cursor) noexcept;
    std::tuple<bool, std::unique_ptr<ast_expression>> parse_expression_comma (string_iterator_type & cursor) noexcept;
    std::tuple<bool, std::unique_ptr<ast_expression>> parse_expression_assign (string_iterator_type & cursor) noexcept;
    operator_kind parse_assign_operator (string_iterator_type & cursor) noexcept;
    std::tuple<bool, std::unique_ptr<ast_expression>> parse_expression_primary (string_iterator_type & cursor) noexcept;
}
