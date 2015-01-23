#pragma once
#include "lex.hpp"
#include "../string/string_iterator.hpp"
#include "../ast/template_instance.hpp"
#include "../debug/assert.hpp"
#include <tuple>
#include <memory>

namespace bksg
{
    std::tuple<bool, std::unique_ptr<ast_template_instance>> parse_template_instance (string_iterator_type & cursor) noexcept;
}
