#include <cctype>
#include <iostream>

enum class token_kind
{
    empty
  , identifier
  , space
  , alternative
  , zero_or_more
  , one_or_more
  , zero_or_one
  , and_pred
  , not_pred
  , unknown    
};

struct parser
{
    using iterator = char *;
    iterator begin;
    iterator end;

    iterator token_begin;
    iterator token_end;

    bool empty () noexcept { return begin >= end; }

    token_kind parse_token () noexcept
    {
        if (empty()) { return token_kind::empty; }
        token_begin = begin;
        if (std::isalpha(*begin)) {
            ++begin;
            while (!empty() && std::isalpha(*begin)) { ++begin; }
            token_end = begin;
            return token_kind::identifier;
        } 

        if (std::isspace(*begin)) {
            ++begin;
            while (!empty() && std::isspace(*begin)) { ++begin; }
            token_end = begin;
            return token_kind::space;
        }

        if (*begin == '|') { ++begin; return token_kind::alternative; }
        if (*begin == '*') { ++begin; return token_kind::zero_or_more; }
        if (*begin == '+') { ++begin; return token_kind::one_or_more; }
        if (*begin == '?') { ++begin; return token_kind::zero_or_one; }
        if (*begin == '&') { ++begin; return token_kind::and_pred; }
        if (*begin == '!') { ++begin; return token_kind::not_pred; }
        ++begin;
        return token_kind::unknown;
    }    
};

int main()
{
    std::string buffer;
    std::string line;
    while (std::getline(std::cin, line)) {buffer += (line += '\n');}
    parser ps;
    ps.begin = &*buffer.begin();
    ps.end = &*buffer.end();
    
    while (!ps.empty()) {
        auto t = ps.parse_token();
    }
    
}
