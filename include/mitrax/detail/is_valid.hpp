//-----------------------------------------------------------------------------
// Copyright (c) 2016-2018 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__is_valid__hpp_INCLUDED_
#define _mitrax__is_valid__hpp_INCLUDED_

#include <type_traits>


namespace mitrax{


	struct is_valid_t{
	private:
		template < typename F, typename ... T, typename = decltype(
			std::declval< F&& >()(std::declval< T&& ... >())
		) >
		static constexpr auto impl(int){ return std::true_type(); }

		template < typename F, typename ... T >
		static constexpr auto impl(...){ return std::false_type(); }

		template < typename F >
		struct fn{
			template < typename ... T >
			constexpr auto operator()(T&& ...)const
			{ return impl< F&&, T&& ... >(int()); }
		};

	public:
		template < typename F >
		constexpr auto operator()(F&&)const
		{ return fn< F&& >(); }
	};

	constexpr is_valid_t is_valid{};


}


#endif
