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
}
