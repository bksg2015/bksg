#pragma once

#include <cstddef>
#include <type_traits>

namespace bksg
{
    template <typename T>
    struct string_iterator_trait;
    
    template <typename Derived>
    struct string_iterator_interface
    {
    private:
        using trait = string_iterator_trait<Derived>;
    public:

        Derived & derived() noexcept { return *static_cast<Derived *>(this); }
        Derived const & derived() const noexcept { return *static_cast<Derived const *>(this); }

        // if front() is called when string_view is empty() == true, ill-formed
        char const front_byte () const noexcept { return derived().front_byte(); }
        unsigned char const front_byte_unsigned () const noexcept { return derived().front_byte_unsigned(); }
        char const * front_ptr () const noexcept { return derived().front_ptr(); }

        Derived & next () noexcept { return derived().next(); }
        Derived & operator++ () noexcept { return next(); }
        Derived operator++ (int) noexcept { auto it = *this; next(); return it; }

        bool operator>= (Derived const & other) const noexcept { return derived().operator>=(other); }
        bool operator<= (Derived const & other) const noexcept  { return other.operator<=(derived()); }
        bool operator> (Derived const & other) const noexcept { return !(other <= derived()); }
        bool operator< (Derived const & other) const noexcept { return !(other >= derived()); }
        bool operator== (Derived const & other) const noexcept { return derived() >= other && other >= derived(); }
        bool operator!= (Derived const & other) const noexcept { return !(derived() == other); }

    };
}
