#include "expression.hpp"

namespace bksg
{
    std::tuple<bool, std::unique_ptr<ast_expression>>  parse_expression (string_iterator_type & cursor) noexcept
    {
        assert(true, assert_kind::parse_expression, "parse_exprsesion", "enter", cursor.front_ptr());
        auto tmp = parse_expression_comma(cursor);
        if (!std::get<0>(tmp)) {
            assert(true, assert_kind::parse_expression, "parse_exprsesion", "fail", cursor.front_ptr());
            return std::make_tuple(false, std::unique_ptr<ast_expression>{});
        }
        assert(true, assert_kind::parse_expression, "parse_exprsesion", "ok", cursor.front_ptr());
        return std::make_tuple(true, std::move(std::get<1>(tmp)));
    }

    std::tuple<bool, std::unique_ptr<ast_expression>> parse_expression_comma (string_iterator_type & cursor)noexcept
    {
        assert(true, assert_kind::parse_expression, "parse_comma_exprsesion", "enetr", cursor.front_ptr());
        auto tmp = parse_expression_assign(cursor);
        if (!std::get<0>(tmp)) { 
            assert(true, assert_kind::parse_expression, "parse_comma_exprsesion", "fail1", cursor.front_ptr());
            return std::make_tuple(false, std::unique_ptr<ast_expression>{}); 
        }

        if (!parse_ascii(cursor, ',')) { 
            assert(true, assert_kind::parse_expression, "parse_comma_exprsesion", "ok1", cursor.front_ptr());
            return std::make_tuple(true, std::move(std::get<1>(tmp))); 
        }

        auto ptr = std::unique_ptr<ast_expression_operator_call>(new ast_expression_operator_call(operator_kind::Comma)); 
        ptr->add_argument(std::move(ptr)); 
        
        while(true)
        {
            parse_whitespaces(cursor);
            tmp = parse_expression_assign(cursor);
            if (!std::get<0>(tmp)) { 
                assert(true, assert_kind::parse_expression, "parse_comma_exprsesion", "fail2", cursor.front_ptr());
                return std::make_tuple(false, std::unique_ptr<ast_expression>{}); 
            }
            ptr->add_argument(std::move(std::get<1>(tmp)));
            if (!parse_ascii(cursor, ',')) { break; } 
        }
        assert(true, assert_kind::parse_expression, "parse_comma_exprsesion", "true", cursor.front_ptr());
        return std::make_tuple(true, std::move(ptr));
    }

    std::tuple<bool, std::unique_ptr<ast_expression>> parse_expression_assign (string_iterator_type & cursor) noexcept
    {
        assert(true, assert_kind::parse_expression, "parse_expression_assign", "enter", cursor.front_ptr());
        auto ret = parse_expression_primary(cursor);
        if (!std::get<0>(ret)) { 
            assert(true, assert_kind::parse_expression, "parse_expression_assign", "fail1", cursor.front_ptr());
            return std::make_tuple(false, std::unique_ptr<ast_expression>{}); 
        }

        auto op = parse_assign_operator(cursor);
        if (op == operator_kind::Unknown) {
            assert(true, assert_kind::parse_expression, "parse_expression_assign", "ok1", cursor.front_ptr());
            return std::make_tuple(true, std::move(std::get<1>(ret)));
        }

        auto head = std::unique_ptr<ast_expression_operator_call>(new ast_expression_operator_call(op));
        head->add_argument(std::move(std::get<1>(ret)));

        ast_expression_operator_call * target_ptr = head.get();
        
        while (true) 
        {
            auto ret = parse_expression_primary(cursor);
            if (!std::get<0>(ret)) {
                assert(true, assert_kind::parse_expression, "parse_expression_assign", "fail2", cursor.front_ptr());
                return std::make_tuple(false, std::unique_ptr<ast_expression>{});
            }

            auto op = parse_assign_operator(cursor);
            if (op == operator_kind::Unknown) { 
                target_ptr->add_argument(std::move(std::get<1>(ret)));
                assert(true, assert_kind::parse_expression, "parse_expression_assign", "ok2", cursor.front_ptr());
                return std::make_tuple(true, std::move(head));
            }
            target_ptr->add_argument(std::unique_ptr<ast_expression_operator_call>(new ast_expression_operator_call(op)));
            target_ptr = dynamic_cast<ast_expression_operator_call *>(target_ptr->arguments.back().get());
            target_ptr->add_argument(std::move(std::get<1>(ret))); 
        }
    }

    operator_kind parse_assign_operator (string_iterator_type & cursor) noexcept
    {
        if (parse_ascii(cursor,'=')) { parse_separator(cursor); return operator_kind::Equal; }
        return operator_kind::Unknown;
    }

    std::tuple<bool, std::unique_ptr<ast_expression>> parse_expression_primary (string_iterator_type & cursor) noexcept
    {
        assert(true, assert_kind::parse_expression, "parse_expression_assign", "enter", cursor.front_ptr());
        {
            auto res = parse_integer_literal(cursor);
            if (std::get<0>(res)) {
                auto ret = std::unique_ptr<ast_expression_integer>(new ast_expression_integer(std::move(std::get<1>(res)))); 
                assert(true, assert_kind::parse_expression, "parse_expression_assign", "ok", cursor.front_ptr());
                return std::make_tuple(true, std::move(ret));
            }
        }
        assert(true, assert_kind::parse_expression, "parse_expression_assign", "fail", cursor.front_ptr());
        return std::make_tuple(false, std::unique_ptr<ast_expression>{});
    }
}
