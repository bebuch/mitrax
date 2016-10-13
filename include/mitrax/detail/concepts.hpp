//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// Based on a blog post from:
// https://foonathan.github.io/blog/2016/09/09/cpp14-concepts.html
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__concepts__hpp_INCLUDED_
#define _mitrax__concepts__hpp_INCLUDED_

#include <type_traits>


namespace mitrax{


	template < typename ... Ts >
	using void_t = void;

	template < typename T, template < typename > typename Expr,
		typename VoidT = void_t<> >
	struct compiles: std::false_type{};

	template < typename T, template < typename > typename Expr >
	struct compiles< T, Expr, void_t< Expr< T > > >: std::true_type{};


	template < typename ResultT, typename CheckT,
		template < typename > typename ... Concepts >
	using requires = std::enable_if_t< std::conjunction_v<
		Concepts< CheckT > ... >, ResultT >;

	template < typename ResultT, typename CheckT,
		template < typename > typename ... Concepts >
	using fallback = std::enable_if_t< std::negation_v< std::conjunction<
		Concepts< CheckT > ... > >, ResultT >;


	//--- Usage: Defining a concept
	// template < typename T >
	// using check_foo = decltype(std::declval< T >().foo());
	//
	// template < typename T >
	// using has_foo = compiles< T, check_foo >;
	//--- Usage end


}


#endif
