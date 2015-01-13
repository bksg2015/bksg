#pragma once

namespace bksg
{
    template <typename T>
    struct char_interface
    {
        static constexpr bool iswhitespace (T const & ch) noexcept { return ::bksg::iswhitespace(ch); }
    };
}
