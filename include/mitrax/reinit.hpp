//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__reinit__hpp_INCLUDED_
#define _mitrax__reinit__hpp_INCLUDED_

#include "matrix_interface.hpp"


namespace mitrax{


	namespace detail{


		template< typename M, typename T, typename = void >
		struct has_reinit_v: std::false_type{};

		template< typename M, typename T >
		struct has_reinit_v< M, T, decltype((void)
			std::declval< M >().reinit_v(std::declval< T >())
		) >: std::true_type{};

		template< typename M, typename T >
		constexpr auto has_reinit_v_v = has_reinit_v< M, T >::value;


		template< typename M, typename T, typename = void >
		struct has_reinit_fn: std::false_type{};

		template< typename M, typename T >
		struct has_reinit_fn< M, T, decltype((void)
			std::declval< M >().reinit_fn(std::declval< T >())
		) >: std::true_type{};

		template< typename M, typename T >
		constexpr auto has_reinit_fn_v = has_reinit_fn< M, T >::value;


		template< typename M, typename T, typename = void >
		struct has_reinit_iter: std::false_type{};

		template< typename M, typename T >
		struct has_reinit_iter< M, T, decltype((void)
			std::declval< M >().reinit_iter(std::declval< T >())
		) >: std::true_type{};

		template< typename M, typename T >
		constexpr auto has_reinit_iter_v = has_reinit_iter< M, T >::value;


	}


	template < typename T, typename M, size_t C, size_t R >
	constexpr void reinit_v(matrix< M, C, R >& m, T const& v = T()){
		static_assert(detail::has_reinit_v_v< M, T >,
			"Matrix implementation M does not support reinit_v");

		m.impl().reinit_v(v);
	}

	template < typename M, size_t C, size_t R, typename F >
	constexpr void reinit_fn(matrix< M, C, R >& m, F&& f){
		static_assert(detail::has_reinit_fn_v< M, detail::fn_xy< F&& > >,
			"Matrix implementation M does not support reinit_fn");

		m.impl().reinit_fn(detail::fn_xy< F&& >{static_cast< F&& >(f)});
	}

	template < typename M, size_t C, size_t R, typename Iter >
	constexpr void reinit_iter(matrix< M, C, R >& m, Iter iter){
		static_assert(detail::has_reinit_iter_v< M, Iter >,
			"Matrix implementation M does not support reinit_iter");

		m.impl().reinit_iter(iter);
	}

	template < typename T, typename M, size_t C, size_t R,
		enable_if_t< C != 0 && R != 0 > = 0 >
	constexpr void reinit(matrix< M, C, R >& m, T(&v)[R][C]){
		reinit_iter(m, make_convert_iterator< value_type_t< M > >(
			flat_iterator< T, R, C >(&v)));
	}

	template < typename T, typename M, size_t C, size_t R,
		enable_if_t< C != 0 && R != 0 > = 0 >
	constexpr void reinit(matrix< M, C, R >& m, T(&&v)[R][C]){
		reinit_iter(m, mitrax::make_move_iterator(
			make_convert_iterator< value_type_t< M > >(
			flat_iterator< T, R, C >(&v))));
	}

	template < typename M, size_t C, size_t R, typename F >
	constexpr void reinit_vector_fn(matrix< M, C, R >& m, F&& f){
		static_assert((C == 1 && R != 0) || (C != 0 && R == 1),
			"reinit_vector_fn is only allowed for compile time dim vectors");

		static_assert(detail::has_reinit_fn_v< M, detail::fn_i< F&& > >,
			"Matrix implementation M does not support reinit_fn");

		m.impl().reinit_fn(detail::fn_i< F&& >{static_cast< F&& >(f)});
	}

	template < typename T, typename M, size_t C, size_t R,
		enable_if_t< (C == 1 && R != 0) || (C != 0 && R == 1) > = 0 >
	constexpr void reinit_vector(matrix< M, C, R >& m, T(&v)[R * C]){
		reinit_iter(m, make_convert_iterator< value_type_t< M > >(v));
	}

	template < typename T, typename M, size_t C, size_t R,
		enable_if_t< (C == 1 && R != 0) || (C != 0 && R == 1) > = 0 >
	constexpr void reinit_vector(matrix< M, C, R >& m, T(&&v)[R * C]){
		reinit_iter(m,
			mitrax::make_move_iterator(make_convert_iterator< value_type_t< M > >(
			v)));
	}


}


#endif
