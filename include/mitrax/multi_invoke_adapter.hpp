//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__multi_invoke_adapter__hpp_INCLUDED_
#define _mitrax__multi_invoke_adapter__hpp_INCLUDED_

#include <tuple>
#include <utility>


namespace mitrax{


	template < typename F, typename S, typename ... T >
	struct multi_invoke_adapter{
		constexpr multi_invoke_adapter(F&& f, S&& single_call, T&& ... arg):
			f_(static_cast< F >(f)),
			single_call_(static_cast< S >(single_call)),
			arg_(static_cast< T >(arg) ...)
			{}

		F f_;
		S single_call_;
		std::tuple< T ... > arg_;

		template < typename ... A >
		constexpr auto operator()(A&& ... arg)const{
			return (*this)(
				std::index_sequence_for< T ... >(),
				static_cast< A >(arg) ...
			);
		}

		template < size_t ... I, typename ... A >
		constexpr auto
		operator()(std::index_sequence< I ... >, A&& ... arg)const{
			return f_(single_call_(
				std::get< I >(arg_),
				static_cast< A >(arg) ...
			) ...);
		}
	};

	template < typename F, typename S, typename ... T >
	constexpr auto
	make_multi_invoke_adapter(F&& f, S&& single_call, T&& ... arg){
		return multi_invoke_adapter< F, S, T ... >(
			static_cast< F >(f),
			static_cast< S >(single_call),
			static_cast< T >(arg) ...
		);
	}



}


#endif
