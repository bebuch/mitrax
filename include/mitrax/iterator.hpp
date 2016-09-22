//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__iterator__hpp_INCLUDED_
#define _mitrax__iterator__hpp_INCLUDED_

#include "iterator/move_iterator.hpp"
#include "iterator/flat_iterator.hpp"
#include "iterator/convert_iterator.hpp"


namespace mitrax{


	template < typename C >
	constexpr auto begin(C& c){
		return c.begin();
	}

	template < typename C >
	constexpr auto begin(C const& c){
		return c.begin();
	}

	template < typename T, size_t N >
	constexpr T* begin(T(&array)[N])noexcept{
		return array;
	}

	template < typename C >
	constexpr auto cbegin(C const& c)noexcept(noexcept(mitrax::begin(c))){
		return mitrax::begin(c);
	}


	template < typename C >
	constexpr auto end(C& c){
		return c.end();
	}

	template < typename C >
	constexpr auto end(C const& c){
		return c.end();
	}

	template < typename T, size_t N >
	constexpr T* end(T(&array)[N])noexcept{
		return array + N;
	}

	template < typename C >
	constexpr auto cend(C const& c)noexcept(noexcept(mitrax::end(c))){
		return mitrax::end(c);
	}


}


#endif
