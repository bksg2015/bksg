#include "string/string_iterator.hpp"
// #include "parser/manager.hpp"
#include "parser/lex.hpp"
#include "parser/type.hpp"
// #include "parser/namespace.hpp"
// #include "parser/function.hpp"
// #include "ast/ast.hpp"
#include "ast/expression.hpp"
#include "ast/integer.hpp"
#include "ast/type.hpp"
#include <iostream>
#include <tuple>
#include <string>

int main()
{
    std::string input;
    std::string line;
    while (std::getline(std::cin, line)) { input += line + '\n'; }

    auto s = bksg::string_iterator_type(input.c_str());
    auto ret = bksg::parse_type(s);
    if (std::get<0>(ret)) {
        auto & r = std::get<1>(ret)->template_name;
        std::cout << "type parse success : " << std::string(r.value.begin(), r.value.end()) << std::endl;
    } else {
        std::cout << "type parse failure" << std::endl;
    }
    while (!bksg::parse_eof(s)) {
        if (std::get<0>(bksg::parse_identifier(s))) {
            std::cout << "identifier" << std::endl;
        } else if (bksg::parse_separator(s)) {
            std::cout << "separator" << std::endl;
//         } else if (bksg::parse_character_literal(s)) {
//             std::cout << "character literal" << std::endl;
//         } else if (bksg::parse_string_literal(s)) {
//             std::cout << "string literal" << std::endl;
        } else if (std::get<0>(bksg::parse_binary_integer(s))) {
            std::cout << "binary integer" << std::endl;
        } else if (std::get<0>(bksg::parse_hexadecimal_integer(s))) {
            std::cout << "hexadecimal integer" << std::endl;
        } else if (std::get<0>(bksg::parse_decimal_integer(s))) {
            std::cout << "decimal integer" << std::endl;
        } else {
            std::cout << "unknown" << std::endl;
            s.next();
        }
    }
//     bksg::scope_module module{};

//     bksg::parser_manager pm(s);
//     pm.token.next_token();
//     std::cout << bksg::parse_module_declaration(pm) << std::endl;
//     for (auto it : module.package.names) {
//         std::cout << it.to_string() << std::endl;
//     }

//     std::cout << module.name.to_string() << std::endl;
//     std::cout << bksg::parse_namespace_declaration(pm) << std::endl;
//     pm.print_current_full_qualified_name();
//     std::cout << bksg::parse_function_declaration(pm) << std::endl;
//     std::cout << "-----" << std::endl;
//     pm.error_handl.print(std::cout);
//     bksg::token_parser<bksg::plain_string_view> ps{s};
//     while (ps.parse_token()) {}
//     std::cout << int(ps.last_token_kind) << std::endl;
//     std::cout << ps.parse_template_type_parameter() << std::endl;
//     std::cout << tobj.name_lookup(bksg::plain_string_view("aiueo"),ptr) << std::endl;

//     using namespace bksg;
//     ast_template_parameter_list<plain_string_view> a;    
//     ast<plain_string_view> * ptr = &a;
//     std::cout << sizeof(a) << std::endl;
}
