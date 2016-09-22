//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__iterator__value_iterator__hpp_INCLUDED_
#define _mitrax__iterator__value_iterator__hpp_INCLUDED_

#include <iterator>


namespace mitrax{


	template < typename T >
	class value_iterator{
	public:
		using difference_type = std::ptrdiff_t;

		using pointer = T*;

		using value_type = T;

		using iterator_category = std::random_access_iterator_tag;

		using reference = T&;


		constexpr value_iterator() = default;

		constexpr explicit value_iterator(T v): value_(v) {}

		template < typename U >
		constexpr value_iterator(value_iterator< U > const& u): value_(*u) {}


		template < typename U >
		constexpr value_iterator& operator=(value_iterator< U > const& u){
			value_ = *u;
			return *this;
		}


		constexpr reference operator*()const{
			return value_;
		}

		constexpr pointer operator->()const{
			return &value_;
		}

		constexpr reference operator[](difference_type)const{
			return value_;
		}



		constexpr value_iterator& operator++()noexcept{
			return *this;
		}

		constexpr value_iterator operator++(int)noexcept{
			return *this;
		}

		constexpr value_iterator& operator--()noexcept{
			return *this;
		}

		constexpr value_iterator operator--(int)noexcept{
			return *this;
		}


		constexpr value_iterator operator+(difference_type)const noexcept{
			return *this;
		}

		constexpr value_iterator& operator+=(difference_type)noexcept{
			return *this;
		}

		constexpr value_iterator operator-(difference_type)const noexcept{
			return *this;
		}

		constexpr value_iterator& operator-=(difference_type)noexcept{
			return *this;
		}


	private:
		T value_;
	};


	template < typename T1, typename T2 >
	constexpr bool operator==(
		value_iterator< T1 > const&, value_iterator< T2 > const&
	)noexcept{
		return true;
	}

	template < typename T1, typename T2 >
	constexpr bool operator!=(
		value_iterator< T1 > const&, value_iterator< T2 > const&
	)noexcept{
		return false;
	}

	template < typename T1, typename T2 >
	constexpr bool operator<(
		value_iterator< T1 > const&, value_iterator< T2 > const&
	)noexcept{
		return false;
	}

	template < typename T1, typename T2 >
	constexpr bool operator<=(
		value_iterator< T1 > const&, value_iterator< T2 > const&
	)noexcept{
		return true;
	}

	template < typename T1, typename T2 >
	constexpr bool operator>(
		value_iterator< T1 > const&, value_iterator< T2 > const&
	)noexcept{
		return false;
	}

	template < typename T1, typename T2 >
	constexpr bool operator>=(
		value_iterator< T1 > const&, value_iterator< T2 > const&
	)noexcept{
		return true;
	}

	template < typename T >
	constexpr value_iterator< T > operator+(
		typename value_iterator< T >::difference_type,
		value_iterator< T > const& iter
	)noexcept{
		return iter;
	}

	template < typename T1, typename T2 >
	constexpr auto operator-(
		value_iterator< T1 > const& lhs, value_iterator< T2 > const&
	)noexcept{
		return lhs;
	}


	template < typename T >
	constexpr value_iterator< T > make_value_iterator(T const& v)noexcept{
		return value_iterator< T >(v);
	}


}


#endif
