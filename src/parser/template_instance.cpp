#include "template_instance.hpp"

namespace bksg
{
    std::tuple<bool, std::unique_ptr<ast_template_instance>> parse_template_instance (string_iterator_type & cursor) noexcept
    {
        assert(true, assert_kind::parse_template_instance, "parse_template_instance", "enter", cursor.front_ptr());
        auto id = parse_identifier(cursor);
        if (!std::get<0>(id)) { 
            assert(true, assert_kind::parse_template_instance, "parse_template_instance", "fail1", cursor.front_ptr());
            return std::make_tuple(false, std::unique_ptr<ast_template_instance>{}); 
        }

        std::unique_ptr<ast_template_instance> tmp_inst{new ast_template_instance{}};

        tmp_inst->name = std::move(std::get<1>(id));
        if (!parse_string(cursor, "!(")) { 
            assert(true, assert_kind::parse_template_instance, "parse_template_instance", "ok1", cursor.front_ptr());
            return std::make_tuple(true, std::move(tmp_inst)); 
        }

        id = std::move(parse_identifier(cursor));
        if (!std::get<0>(id) && parse_ascii(cursor,')')) { 
            assert(true, assert_kind::parse_template_instance, "parse_template_instance", "ok2", cursor.front_ptr());
            return std::make_tuple(true, std::move(tmp_inst)); 
        }
        
        while (true) {
            tmp_inst->parameters.push_back(std::move(std::get<1>(id)));

            if (parse_ascii(cursor, ')')) {
                assert(true, assert_kind::parse_template_instance, "parse_template_instance", "ok3", cursor.front_ptr());
                return std::make_tuple(true, std::move(tmp_inst)); 
            }

            if (!parse_ascii(cursor, ',')) { 
                assert(true, assert_kind::parse_template_instance, "parse_template_instance", "fail2", cursor.front_ptr());
                return std::make_tuple(false, std::unique_ptr<ast_template_instance>{}); 
            }

            parse_separator(cursor);
            id = std::move(parse_identifier(cursor));
            if (!std::get<0>(id)) {
                assert(true, assert_kind::parse_template_instance, "parse_template_instance", "fail3", cursor.front_ptr());
                return std::make_tuple(false, std::unique_ptr<ast_template_instance>{}); 
            }
        }
    };
}
