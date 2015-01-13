#pragma once

#include <string>
#include <memory>

namespace ast
{
    enum class ast_tag
    {
        nonterminal
      , sequence
      , alternative
      , zero_or_more
      , one_or_more
      , zero_or_one
      , and_pred
      , or_pred
      , not_pred
    };

    struct ast
    {
        ast_tag tag;
        std::unique_ptr<ast> left;
        std::unique_ptr<ast> right;
        ast * parent;
        std::string name;
        ast (ast * parent = nullptr) : parent(parent), left(new ast()), right(new ast()) {}
    };

}

