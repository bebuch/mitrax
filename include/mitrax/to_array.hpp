//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__detail__to_array__hpp_INCLUDED_
#define _mitrax__detail__to_array__hpp_INCLUDED_

#include "dim.hpp"
#include "array_s.hpp"

#include <utility>


namespace mitrax{ namespace detail{


	template < typename Iter, size_t ... I >
	constexpr array_s< iter_type_t< Iter >, sizeof...(I) >
	to_array(Iter iter, std::index_sequence< I ... >){
		return {{ iter[I] ... }};
	}

	template < typename T >
	constexpr T const& nop(T const& v, size_t)noexcept{ return v; }

	template < typename T, size_t ... I >
	constexpr array_s< std::remove_cv_t< T >, sizeof...(I) >
	init_array(T const& v, std::index_sequence< I ... >){
		return {{ nop(v, I) ... }};
	}


	template < size_t N, typename Iter >
	constexpr auto to_array(Iter iter){
		return to_array(iter, std::make_index_sequence< N >());
	}

	template < size_t N, typename T >
	constexpr auto init_array(T const& v){
		return init_array(v, std::make_index_sequence< N >());
	}


} }


#endif
