#pragma once
#include <type_traits>

namespace bksg
{
    template <typename T>
    struct optional
    {
    private:
        bool is_engaged;
        using storage_type = typename std::aligned_storage<sizeof(T), alignof(T)>::type;
        storage_type storage;
        constexpr T * ptr () noexcept { return reinterpret_cast<T *>(&storage); }
        constexpr T const * ptr () const noexcept { return reinterpret_cast<T const *>(&storage); }
    public:
         
        constexpr optional () noexcept : is_engaged(false) {}
        constexpr optional (T const & t) noexcept : is_engaged(true) { new(ptr()) T(t); }
        constexpr optional (T && t) : is_engaged(true) { new(ptr()) T(std::forward<T &&>(t)); }
        constexpr optional (bool condition, T const & t) : is_engaged(condition) { if(is_engaged){ new(ptr()) T(t);} }
        constexpr optional (bool condition, T && t) : is_engaged(condition) { if(is_engaged){ new(ptr()) T(std::forward<T &&>(t));} }
        constexpr optional (optional const & rhs) : optional(bool(rhs), *rhs) {}
        constexpr optional (optional && rhs) : optional(bool(rhs), std::forward<T &&>(*rhs)) {}
        
        constexpr optional & operator= (T const & t) noexcept { is_engaged = true; (*ptr()) = t; return *this; }
        constexpr optional & operator= (T && t) noexcept { is_engaged = true; (*ptr()) = std::move(t); return *this; }
        constexpr optional & operator= (optional const & rhs) noexcept 
        { 
            is_engaged = bool(rhs); 
            if(is_engaged) { (*ptr()) = *rhs; }
            return *this; 
       }
        constexpr optional & operator= (optional && rhs) noexcept 
        { 
            is_engaged = bool(rhs); 
            if(is_engaged) { (*ptr()) = std::forward<T &&>(*rhs); } 
            return *this; 
        }

        constexpr explicit operator bool() const noexcept { return is_engaged; }
        constexpr bool operator! () const noexcept { return !is_engaged; }

        T const & operator* () const & { return *ptr(); }
        T & operator* () & { return *ptr(); }
        T && operator* () && { return std::move(*ptr()); }
        
        ~optional () noexcept
        {
            ptr()->~T();
        }
    };
}
