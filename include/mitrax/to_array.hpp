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

#include <array>
#include <utility>


namespace mitrax{ namespace detail{


	template < typename T, size_t N, size_t ... I >
	constexpr std::array< std::remove_cv_t< T >, N >
	to_array(T(&a)[N], std::index_sequence< I ... >){
		return {{ a[I] ... }};
	}

	template < typename T, size_t N, size_t ... I >
	constexpr std::array< std::remove_cv_t< T >, N >
	to_array(T(&&a)[N], std::index_sequence< I ... >){
		return {{ std::move(a[I]) ... }};
	}

	template < typename T, size_t C, size_t R, size_t ... I >
	constexpr std::array< std::remove_cv_t< T >, C * R >
	to_array(T(&a)[R][C], std::index_sequence< I ... >){
		return {{ a[I / C][I % C] ... }};
	}

	template < typename T, size_t C, size_t R, size_t ... I >
	constexpr std::array< std::remove_cv_t< T >, C * R >
	to_array(T(&&a)[R][C], std::index_sequence< I ... >){
		return {{ std::move(a[I / C][I % C]) ... }};
	}

	template < size_t, typename T >
	constexpr T const& nop(T const& v){ return v; }

	template < typename T, size_t ... I >
	constexpr std::array< std::remove_cv_t< T >, sizeof...(I) >
	init_array(T const& v, std::index_sequence< I ... >){
		return {{ nop< I >(v) ... }};
	}

	template < size_t C, size_t R, typename F, size_t ... I >
	constexpr auto function_xy_to_array(
		F&& f, std::index_sequence< I ... >
	){
		return std::array< fn_xy< F >, sizeof...(I) >{{
			f(I % C, I / C) ...
		}};
	}

	template < typename F, size_t ... I >
	constexpr auto function_i_to_array(
		F&& f, std::index_sequence< I ... >
	){
		return std::array< fn_i< F >, sizeof...(I) >{{
			f(I) ...
		}};
	}


	template < typename T, size_t N >
	constexpr auto to_array(T(&&v)[N]){
		return to_array(
			std::move(v), std::make_index_sequence< N >()
		);
	}

	template < typename T, size_t N >
	constexpr auto to_array(T(&v)[N]){
		return to_array(
			v, std::make_index_sequence< N >()
		);
	}


	template < typename T, size_t C, size_t R >
	constexpr auto to_array(T(&&v)[R][C]){
		return to_array(
			std::move(v), std::make_index_sequence< C * R >()
		);
	}

	template < typename T, size_t C, size_t R >
	constexpr auto to_array(T(&v)[R][C]){
		return to_array(
			v, std::make_index_sequence< C * R >()
		);
	}

	template < size_t N, typename T >
	constexpr auto init_array(T const& v){
		return init_array(
			v, std::make_index_sequence< N >()
		);
	}

	template < size_t C, size_t R, typename F >
	constexpr auto function_xy_to_array(F&& f){
		return function_xy_to_array< C, R >(
			f, std::make_index_sequence< C * R >()
		);
	}

	template < size_t N, typename F >
	constexpr auto function_i_to_array(F&& f){
		return function_i_to_array(
			f, std::make_index_sequence< N >()
		);
	}


} }


#endif
