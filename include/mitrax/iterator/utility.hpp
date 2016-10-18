//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__iterator__utility__hpp_INCLUDED_
#define _mitrax__iterator__utility__hpp_INCLUDED_

#include "move.hpp"
#include "../detail/concepts.hpp"


namespace mitrax::detail{


	template < typename C >
	using has_begin = decltype(std::declval< C >().begin());

	template < typename C >
	using has_end = decltype(std::declval< C >().end());


}


namespace mitrax{


	template < typename C,
		enable_if_t< (bool)compiles< C&, detail::has_begin >() > = 0 >
	constexpr auto begin(C& c)noexcept(noexcept(c.begin())){
		return c.begin();
	}

	template < typename C,
		enable_if_t< (bool)compiles< C const&, detail::has_begin >() > = 0 >
	constexpr auto begin(C const& c)noexcept(noexcept(c.begin())){
		return c.begin();
	}

	template < typename T, size_t N >
	constexpr auto begin(T(&array)[N])noexcept{
		return static_cast< T* >(array);
	}

	template < typename T, size_t N >
	constexpr auto begin(T(&&array)[N])noexcept{
		return make_move_iterator(array);
	}


	template < typename C,
		enable_if_t< (bool)compiles< C&, detail::has_end >() > = 0 >
	constexpr auto end(C& c)noexcept(noexcept(c.end())){
		return c.end();
	}

	template < typename C,
		enable_if_t< (bool)compiles< C const&, detail::has_end >() > = 0 >
	constexpr auto end(C const& c)noexcept(noexcept(c.end())){
		return c.end();
	}

	template < typename T, size_t N >
	constexpr auto end(T(&array)[N])noexcept{
		return static_cast< T* >(array + N);
	}

	template < typename T, size_t N >
	constexpr auto end(T(&&array)[N])noexcept{
		return make_move_iterator(array + N);
	}


}


namespace mitrax::detail{


	template < typename C >
	using support_begin = decltype(mitrax::begin(std::declval< C >()));

	template < typename C >
	using support_end = decltype(mitrax::begin(std::declval< C >()));


}


namespace mitrax{


	template < typename C,
		enable_if_t< (bool)compiles< C const&, detail::support_begin >() > = 0 >
	constexpr auto cbegin(C const& c)noexcept(noexcept(mitrax::begin(c))){
		return mitrax::begin(c);
	}

	template < typename C,
		enable_if_t< (bool)compiles< C const&, detail::support_end >() > = 0 >
	constexpr auto cend(C const& c)noexcept(noexcept(mitrax::end(c))){
		return mitrax::end(c);
	}


}


#endif
