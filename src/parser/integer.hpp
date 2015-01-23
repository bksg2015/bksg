#pragma once

#include "lex.hpp"
#include "../string/string_iterator.hpp"
#include "../ast/identifier.hpp"
#include "../ast/integer.hpp"
#include "../misc/optional.hpp"
#include "../debug/assert.hpp"
// #include "../error/error_handler.hpp"
#include <vector>
#include <tuple>

namespace bksg
{
    std::tuple<bool, std::unique_ptr<ast_integer>> parse_binary_integer (string_iterator_type & cursor) noexcept;
    std::tuple<bool, std::unique_ptr<ast_integer>> parse_hexadecimal_integer (string_iterator_type & cursor) noexcept;
    std::tuple<bool, std::unique_ptr<ast_integer>> parse_decimal_integer (string_iterator_type & cursor) noexcept;
    std::tuple<bool, std::unique_ptr<ast_integer>> parse_integer_literal (string_iterator_type & cursor) noexcept;

}
