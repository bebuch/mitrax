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


namespace mitrax{


	template < typename C >
	constexpr auto begin(C& c)noexcept(noexcept(c.begin())){
		return c.begin();
	}

	template < typename C >
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

	template < typename C >
	constexpr auto cbegin(C const& c)noexcept(noexcept(mitrax::begin(c))){
		return mitrax::begin(c);
	}


	template < typename C >
	constexpr auto end(C& c)noexcept(noexcept(c.end())){
		return c.end();
	}

	template < typename C >
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

	template < typename C >
	constexpr auto cend(C const& c)noexcept(noexcept(mitrax::end(c))){
		return mitrax::end(c);
	}


}


#endif
