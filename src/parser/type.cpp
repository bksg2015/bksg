#include "type.hpp"
namespace bksg
{
    std::tuple<bool, std::unique_ptr<ast_type>> parse_type (string_iterator_type & cursor) noexcept
    {
        std::unique_ptr<ast_type> ptr{new ast_type{}};

        assert(true, assert_kind::parse_type, "parse_type", "enter", cursor.front_ptr());
        
        while (true) {
            auto res = parse_template_instance(cursor);
            if (!std::get<0>(res)) {
                assert(true, assert_kind::parse_type, "parse_type", "fail1", cursor.front_ptr());
                return std::make_tuple(false, std::unique_ptr<ast_type>{});
            }

            if (!parse_ascii(cursor, '.')) { 
                ptr->basic_type = std::move(std::get<1>(res));
                assert(true, assert_kind::parse_type, "parse_type", "ok1", cursor.front_ptr());
                return std::make_tuple(true, std::move(ptr));
            }

            ptr->basic_type_scope.push_back(std::move(std::get<1>(res)));
            
        }
    }
}
