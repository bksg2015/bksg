#pragma once

#include <cstddef>
#include <type_traits>

namespace bksg
{
    template <typename T>
    struct string_view_trait;
    
    template <typename Derived>
    struct string_view_interface
    {
    private:
        using trait = string_view_trait<Derived>;
    public:
        using char_type = typename trait::char_type;

        constexpr Derived & derived() noexcept { return *static_cast<Derived *>(this); }
        constexpr Derived const & derived() const noexcept { return *static_cast<Derived const *>(this); }

        // if front() is called when string_view is empty() == true, ill-formed
        constexpr char_type const & front () const noexcept { return derived().front(); }
        constexpr char_type const & operator* () const noexcept { return front(); }

        constexpr Derived & pop () noexcept { return derived().pop(); }
        constexpr bool empty () const noexcept { return derived().empty(); }
        constexpr std::size_t size () const noexcept { return derived().size(); }

        constexpr void begin (Derived const & other) { derived().begin(other); }
        constexpr void end (Derived const & other) { derived().end(other); }

        constexpr decltype(auto) begin () const noexcept { derived().begin(); }
        constexpr decltype(auto) end () const noexcept { derived().end(); }

        constexpr bool operator>= (Derived const & other) { return derived().operator>=(other); }
        constexpr bool operator<= (Derived const & other) { return other.operator<=(derived()); }
        constexpr bool operator> (Derived const & other) { return ! other <= *this; }
        constexpr bool operator< (Derived const & other) { return ! other >= *this; }
    };

    template <typename T>
    struct is_string_view : std::conditional<std::is_base_of<string_view_interface<T>, T>::value, std::true_type, std::false_type>::type {};

    template <typename T1, typename T2>
    using is_string_view_pair = typename std::conditional<is_string_view<T1>::value && is_string_view<T2>::value, std::true_type, std::false_type>::type;
}
