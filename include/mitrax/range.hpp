//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__range__hpp_INCLUDED_
#define _mitrax__range__hpp_INCLUDED_

#include "detail/concepts.hpp"


namespace mitrax{


	template < typename T >
	using use_subscript_operator =
		decltype(std::declval< T const& >()[std::size_t()]);

	template < typename T >
	using has_subscript_operator = compiles< T, use_subscript_operator >;


	template < typename T >
	constexpr bool is_range_v = has_subscript_operator< T >::value;


}


#endif
