// Copyright Joe Coder 2015.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UTIL_OPTIONAL_ITERATOR_HPP
#define BOOST_UTIL_OPTIONAL_ITERATOR_HPP

#include <cstddef>
#include <iterator>
#include <utility>
#include <boost/optional.hpp>
#include <boost/range/has_range_iterator.hpp>

namespace optional_utility
{
    template <typename T>
    class optional_iterator
        : public std::iterator<std::forward_iterator_tag, T, std::ptrdiff_t, T const*, T const&>
    {
        boost::optional<T>* op_;
        bool used_;
    public:
        optional_iterator()
            : op_{nullptr}, used_{true}
        {
        }

        optional_iterator(optional_iterator const& that)
            : op_{that.op_}, used_{that.used_}
        {
        }

        explicit optional_iterator(boost::optional<T>& op)
            : op_{&op}, used_{!op}
        {
        }

        T const& operator*() const
        {
            return **op_;
        }

        T const& operator*()
        {
            return **op_;
        }

        optional_iterator& operator++()
        {
            used_ = true;
            return *this;
        }

        optional_iterator operator++(int)
        {
            auto temp = *this;
            ++*this;
            return temp;
        }

        friend bool operator==(optional_iterator const& left, optional_iterator const& right)
        {
            if (left.used_ && right.used_) {
                return true;
            }
            if (left.used_ || right.used_) {
                return false;
            }
            return left.op_ == right.op_;
        }

        friend bool operator!=(optional_iterator const& left, optional_iterator const& right)
        {
            return !(left == right);
        }
    };
    template <typename T>
    class const_optional_iterator
        : public std::iterator<std::forward_iterator_tag, T, std::ptrdiff_t, T const*, T const&>
    {
        boost::optional<T> const* op_;
        bool used_;
    public:
        const_optional_iterator()
            : op_{nullptr}, used_{true}
        {
        }

        const_optional_iterator(const_optional_iterator const& that)
            : op_{that.op_}, used_{that.used_}
        {
        }

        explicit const_optional_iterator(boost::optional<T> const& op)
            : op_{&op}, used_{!op}
        {
        }

        T const& operator*() const&
        {
            return **op_;
        }

        const_optional_iterator& operator++()
        {
            used_ = true;
            return *this;
        }

        const_optional_iterator operator++(int)
        {
            auto temp = *this;
            ++*this;
            return std::move(temp);
        }

        friend bool operator==(const_optional_iterator const& left, const_optional_iterator const& right)
        {
            if (left.used_ && right.used_) {
                return true;
            }
            if (left.used_ || right.used_) {
                return false;
            }
            return left.op_ == right.op_;
        }

        friend inline bool operator!=(const_optional_iterator const& left, const_optional_iterator const& right)
        {
            return !(left == right);
        }
    };

    template <typename T>
    inline const_optional_iterator<T> begin(boost::optional<T> const& op)
    {
        return const_optional_iterator<T>(op);
    }

    template <typename T>
    inline optional_iterator<T> begin(boost::optional<T>& op)
    {
        return optional_iterator<T>(op);
    }

    template <typename T>
    inline const_optional_iterator<T> end(boost::optional<T> const&)
    {
        return const_optional_iterator<T>();
    }

    template <typename T>
    inline optional_iterator<T> end(boost::optional<T>&)
    {
        return optional_iterator<T>();
    }
}

namespace boost
{

    template <typename T>
    struct range_iterator<boost::optional<T>>
    {
        using type = optional_utility::optional_iterator<T>;
    };

    template <typename T>
    struct range_iterator<boost::optional<T> const>
    {
        using type = optional_utility::const_optional_iterator<T>;
    };

    template <typename T>
    inline optional_utility::const_optional_iterator<T> range_begin(boost::optional<T> const& op)
    {
        return optional_utility::const_optional_iterator<T>(op);
    }

    template <typename T>
    inline optional_utility::optional_iterator<T> range_begin(boost::optional<T>& op)
    {
        return optional_utility::optional_iterator<T>(op);
    }

    template <typename T>
    inline optional_utility::const_optional_iterator<T> range_end(boost::optional<T> const&)
    {
        return optional_utility::const_optional_iterator<T>();
    }

    template <typename T>
    inline optional_utility::optional_iterator<T> range_end(boost::optional<T>&)
    {
        return optional_utility::optional_iterator<T>();
    }
}

#endif
