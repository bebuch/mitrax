//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
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
		constexpr multi_invoke_adapter(
			F const& f, S const& single_call, T const& ... arg
		): f_(f), single_call_(single_call), arg_(arg ...) {}

		F const& f_;
		S const& single_call_;
		std::tuple< T const& ... > arg_;

		template < typename ... A >
		constexpr auto operator()(A&& ... arg)const{
			return (*this)(std::index_sequence_for< T ... >(), arg ...);
		}

		template < size_t ... I, typename ... A >
		constexpr auto
		operator()(std::index_sequence< I ... >, A&& ... arg)const{
			return f_(single_call_(std::get< I >(arg_), arg ...) ...);
		}
	};

	template < typename F, typename S, typename ... T >
	constexpr auto
	make_multi_invoke_adapter(
		F const& f, S const& single_call, T const& ... arg
	){
		return multi_invoke_adapter< F, S, T ... >(f, single_call, arg ...);
	}



}


#endif
