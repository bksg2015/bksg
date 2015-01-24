#pragma once

#include "identifier.hpp"
#include "../string/string_iterator.hpp"
#include <limits>
#include <iostream>
#include <memory>

namespace bksg
{
    struct ast_template_instance
    {
        std::unique_ptr<ast_identifier> name;
        std::vector<std::unique_ptr<ast_identifier>> parameters;
    
        void print (int level = 0) noexcept
        {
            for (int i = 0; i < level; ++i) { std::cout << "  "; }
            std::cout << "ast_template_instance" << " : ";
            std::cout << std::string(&*name->name.begin(), &*name->name.end()) << " : ";
            for (auto & p : parameters) {
                std::cout << std::string(&*p->name.begin(), &*p->name.end()) << " : ";
            }
            std::cout << std::endl;
        }
    };    
}
