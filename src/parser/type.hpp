#pragma once

#include "../string/string_view.hpp"
#include "../ast/scope.hpp"
#include "../ast/type.hpp"
#include "../error/error_handler.hpp"
#include "token.hpp"
#include "manager.hpp"
#include <vector>

namespace bksg
{
    bool parse_type (parser_manager & parser, type t) noexcept;
    bool parse_basic_type (parser_manager & parser, type t) noexcept;
    bool parse_type_qualifier (parser_manager & parser, type t) noexcept;
    bool parse_type_qualifiers (parser_manager & parser, type t) noexcept;
    bool parse_core_type (parser_manager & parser, type t) noexcept;

    // *Type* <- *BasicType* *TypeQualifiers*
    bool parse_type (parser_manager & parser, type t) noexcept
    {
        if (!parse_basic_type(parser, t)) { return false; }
        if (!parse_type_qualifiers(parser, t)) { return false; }
        return true;
    }

    // *BasicType* <- *CoreType* | *ScopeSpecifier*? *TemplateInstance* 
    bool parse_basic_type (parser_manager & parser, type t) noexcept
    {
        if (parse_core_type(parser,t)) { return true; }
        return false;
    } 

    // *CoreType*
    bool parse_core_type (parser_manager & parser, type t) noexcept
    {
        if (parser.token.last_token().kind != token_kind::identifier) { return false; }
        if (equal(parser.token.last_token().string, "void")) {
            t.kind = type_kind::Void; 
        } else if (equal(parser.token.last_token().string, "bool")) {
            t.kind = type_kind::Bool; 
        } else if (equal(parser.token.last_token().string, "char")) {
            t.kind = type_kind::Char;
        } else { 
            return false; 
        }
   
        parser.token.next_token();
        return true;
    } 

    bool parse_type_qualifier (parser_manager & parser, type t) noexcept
    {
        if (parser.token.last_token().kind == token_kind::identifier) {
            if (equal(parser.token.last_token().string, "const")) { 
                t.qualifier.set(type_qualifier_kind::Const, true);
                return true;
            } else {
                return false;
            } 
        } else if (parser.token.last_token().detail == token_detail::and_) {
            t.qualifier.set(type_qualifier_kind::LvalueRef, true);
        } else {
            return false;
        }

        parser.token.next_token();
        return true;
    } 

    bool parse_type_qualifiers (parser_manager & parser, type t) noexcept
    {
        while (parse_type_qualifier(parser, t)){}
        return true;
    }
}
