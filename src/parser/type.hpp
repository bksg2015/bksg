#pragma once
#include "lex.hpp"
#include "template_instance.hpp"
#include "../string/string_iterator.hpp"
#include "../ast/type.hpp"
// #include "../error/error_handler.hpp"
#include <tuple>
#include <memory>

namespace bksg
{
    std::tuple<bool, std::unique_ptr<ast_type>> parse_type (string_iterator_type & cursor) noexcept;
}
