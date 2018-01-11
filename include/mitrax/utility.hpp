//-----------------------------------------------------------------------------
// Copyright (c) 2015-2018 Benjamin Buch
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


	template < bool Condition >
	using enable_if_t = std::enable_if_t< Condition, int >;


	template< typename Result, typename T, typename = void >
	struct has_data: std::false_type{};

	template< typename Result, typename T >
	struct has_data< Result, T, decltype((void)
		static_cast< Result >(std::declval< T >().data())
	) >: std::true_type{};

	template< typename Result, typename T >
	constexpr auto has_data_v = has_data< Result, T >::value;


	template< typename T, typename = void >
	struct has_iterator_fn: std::false_type{};

	template< typename T >
	struct has_iterator_fn< T, decltype((void)(
		std::declval< T >().begin(),
		std::declval< T >().end()
	)) >: std::true_type{};

	template< typename T >
	constexpr auto has_iterator_fn_v = has_iterator_fn< T >::value;


	template< typename T, typename = void >
	struct iterator_fn{
		using type = decltype(std::declval< T >().data());
	};

	template< typename T >
	struct iterator_fn< T, std::enable_if_t< has_iterator_fn_v< T > > >{
		using type = decltype(std::declval< T >().begin());
	};

	template< typename T >
	using iterator_fn_t = typename iterator_fn< T >::type;


	template < template < typename, typename > typename checker,
		typename ... T >
	struct is_all: std::true_type{};

	template < template < typename, typename > typename checker,
		typename T0, typename T1, typename ... T >
	struct is_all< checker, T0, T1, T ... >: std::bool_constant<
		checker< T0, T1 >::value && is_all< checker, T0, T ... >::value >{};

	template < template < typename, typename > typename checker,
		typename ... T >
	constexpr bool is_all_v = is_all< checker, T ... >::value;

}


#endif
