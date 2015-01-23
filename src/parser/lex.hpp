#pragma once

#include "../string/string_iterator.hpp"
#include "../ast/identifier.hpp"
// #include "../error/error_handler.hpp"
#include <vector>
#include <tuple>
#include <memory>

namespace bksg
{
    bool parse_whitespaces (string_iterator_type & cursor) noexcept;
    bool parse_one_of_char (string_iterator_type & cursor, char const * char_set, bool skip_separator = true) noexcept;
    bool parse_string (string_iterator_type & cursor, char const * str, bool skip_separator = true) noexcept;
    bool parse_line_comment (string_iterator_type & cursor) noexcept;
    bool parse_block_comment (string_iterator_type & cursor) noexcept;
    bool parse_comment (string_iterator_type & cursor) noexcept;
    bool parse_separator (string_iterator_type & cursor) noexcept;
    std::tuple<bool, std::unique_ptr<ast_identifier>> parse_identifier (string_iterator_type & cursor) noexcept;
    bool parse_escape_sequence (string_iterator_type & cursor) noexcept;
}
