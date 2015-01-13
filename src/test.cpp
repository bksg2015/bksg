#include "string/plain_string_view.hpp"
#include "parser/module.hpp"
#include "parser/namespace.hpp"
#include "parser/function.hpp"
// #include "ast/ast.hpp"
#include <iostream>

int main()
{
    std::string input;
    std::string line;
    while (std::getline(std::cin, line)) { input += line + '\n'; }
    auto s = bksg::string_view_type(&*input.begin(), &*input.end());
    
    bksg::scope_module module{};

    bksg::parser_manager pm(s, module);
    pm.token.next_token();
    std::cout << bksg::parse_module_declaration(pm) << std::endl;
    for (auto it : module.package.names) {
        std::cout << it.to_string() << std::endl;
    }

    std::cout << module.name.to_string() << std::endl;
    std::cout << bksg::parse_namespace_declaration(pm) << std::endl;
//     pm.print_current_full_qualified_name();
    std::cout << bksg::parse_function_declaration(pm) << std::endl;
    std::cout << "-----" << std::endl;
    pm.error_handl.print(std::cout);
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
