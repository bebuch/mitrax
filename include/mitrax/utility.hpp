//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__utility__hpp_INCLUDED_
#define _mitrax__utility__hpp_INCLUDED_

#include <cstddef>
#include <iterator>
#include <type_traits>


namespace mitrax{


	using size_t = std::size_t;

	using ptrdiff_t = std::ptrdiff_t;


	template < typename T, typename Auto >
	using auto_t = std::conditional_t< std::is_void_v< T >, Auto, T >;

	template < typename T, typename Auto >
	constexpr auto auto_ref(Auto&& v)
	-> auto_t< T, decltype(static_cast< Auto&& >(v)) >{
		return static_cast< Auto&& >(v);
	}


	template < typename ... T >
	constexpr bool one_of(T ... v){ return (... || v); }

	template < typename ... T >
	constexpr bool all_of(T ... v){ return (... && v); }


	template < typename T >
	using value_type_t = typename T::value_type;

	template < bool I >
	using bool_t = std::integral_constant< bool, I >;

	template < typename Iter >
	using iter_type_t = typename std::iterator_traits< Iter >::value_type;


	template < size_t C, size_t R >
	struct is_static: std::true_type{};

	template < size_t R >
	struct is_static< 0, R >: std::false_type{};

	template < size_t C >
	struct is_static< C, 0 >: std::false_type{};

	template <>
	struct is_static< 0, 0 >: std::false_type{};


}


#endif
