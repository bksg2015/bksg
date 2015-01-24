#pragma once
#include <type_traits>
#include <iostream>

namespace bksg
{
    template <typename T>
    struct optional
    {
    private:
        bool is_engaged;
        using storage_type = typename std::aligned_storage<sizeof(T), alignof(T)>::type;
        storage_type storage;
        T * ptr () noexcept { return reinterpret_cast<T *>(&storage); }
        T const * ptr () const noexcept { return reinterpret_cast<T const *>(&storage); }
    public:
         
        optional () noexcept : is_engaged(false) {}
        optional (T const & t) noexcept : is_engaged(true) { new(ptr()) T(t); } 
        optional (T && t) noexcept : is_engaged(true) { new(ptr()) T(std::forward<T &&>(t)); }
        optional (bool condition, T const & t) noexcept : is_engaged(condition) { if(is_engaged){ new(ptr()) T(t);} }
        optional (bool condition, T && t) noexcept : is_engaged(condition) { if(is_engaged){ new(ptr()) T(std::move(t));} }
        optional (optional const & rhs) noexcept : optional(bool(rhs), *rhs) {}
        optional (optional && rhs) noexcept : optional(bool(rhs), std::move(*rhs)) {}
        
        optional & operator= (T const & t) noexcept 
        { 
            if (is_engaged) {
                *ptr() = t;
            } else {
                new(ptr()) T(t);
            }
            is_engaged = true;
            return *this;
        }

        optional & operator= (T && t) noexcept 
        { 
            if (is_engaged) {
                *ptr() = std::move(t);
            } else {
                new(ptr()) T(std::move(t));
            }
            is_engaged = true;
            return *this;
        }

        optional & operator= (optional const & rhs) noexcept 
        { 
            if (!is_engaged && !rhs) {
            } else if (is_engaged && !rhs){
                is_engaged = false; 
                ptr()->~T();
            } else if (!is_engaged && rhs) {
                is_engaged = true;
                new(ptr()) T(*rhs);
            } else {
                is_engaged = true;
                ptr() = *rhs;
            }
            return *this; 
        }

        optional & operator= (optional && rhs) noexcept 
        { 
            if (!is_engaged && !rhs) {
            } else if (is_engaged && !rhs){
                is_engaged = false; 
                ptr()->~T();
            } else if (!is_engaged && rhs) {
                is_engaged = true;
                new(ptr()) T(std::move(*rhs));
            } else {
                is_engaged = true;
                ptr() = std::move(*rhs);
            }
            return *this; 
        }

        explicit operator bool() const noexcept { return is_engaged; }
        bool operator! () const noexcept { return !is_engaged; }

        T const & operator* () const & { return *ptr(); }
        T & operator* () & { return *ptr(); }
        T && operator* () && { return std::move(*ptr()); }
        
        ~optional () noexcept
        {
            if (is_engaged) { ptr()->~T();}
        }
    };
}
