//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__to_array__hpp_INCLUDED_
#define _mitrax__to_array__hpp_INCLUDED_

#include "integer.hpp"

#include <array>
#include <type_traits>
#include <utility>


namespace mitrax{


	namespace detail{


		template < typename T, size_t N, size_t ... I >
		constexpr auto
		to_array(T(&&v)[N], std::index_sequence< I ... >){
			return std::array< std::remove_cv_t< T >, N >{{
				std::move(v[I]) ...
			}};
		}

		template < typename T, size_t N, size_t ... I >
		constexpr auto
		to_array(T(&v)[N], std::index_sequence< I ... >){
			return std::array< std::remove_cv_t< T >, N >{{ v[I] ... }};
		}


		template < typename T, size_t C, size_t R, size_t ... I >
		constexpr auto
		to_array(T(&&v)[R][C], std::index_sequence< I ... >){
			return std::array< std::remove_cv_t< T >, C * R >{{
				std::move(v[I / C][I % C]) ...
			}};
		}

		template < typename T, size_t C, size_t R, size_t ... I >
		constexpr auto
		to_array(T(&v)[R][C], std::index_sequence< I ... >){
			return std::array< std::remove_cv_t< T >, C * R >{{
				v[I / C][I % C] ...
			}};
		}


	}


	template < typename T, size_t N >
	constexpr auto to_array(T(&&v)[N]){
		return detail::to_array(
			std::move(v), std::make_index_sequence< N >()
		);
	}

	template < typename T, size_t N >
	constexpr auto to_array(T(&v)[N]){
		return detail::to_array(
			v, std::make_index_sequence< N >()
		);
	}


	template < typename T, size_t C, size_t R >
	constexpr auto to_array(T(&&v)[R][C]){
		return detail::to_array(
			std::move(v), std::make_index_sequence< C * R >()
		);
	}

	template < typename T, size_t C, size_t R >
	constexpr auto to_array(T(&v)[R][C]){
		return detail::to_array(
			v, std::make_index_sequence< C * R >()
		);
	}


}


#endif
