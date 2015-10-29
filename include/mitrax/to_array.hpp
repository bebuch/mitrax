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

#include <array>
#include <type_traits>
#include <utility>


namespace mitrax{


	namespace detail{


		template < typename T, std::size_t N, std::size_t ... I >
		constexpr auto to_array(T(&&arr)[N], std::index_sequence< I ... >){
			return std::array< std::remove_cv_t< T >, N >{{
				std::move(arr[I]) ...
			}};
		}

		template < typename T, std::size_t N, std::size_t ... I >
		constexpr auto to_array(T(&arr)[N], std::index_sequence< I ... >){
			return std::array< std::remove_cv_t< T >, N >{{ arr[I] ... }};
		}


	}


	template < typename T, std::size_t N >
	constexpr auto to_array(T(&&arr)[N]){
		return detail::to_array(
			std::move(arr), std::make_index_sequence< N >()
		);
	}

	template < typename T, std::size_t N >
	constexpr auto to_array(T(&arr)[N]){
		return detail::to_array(arr, std::make_index_sequence< N >());
	}


}


#endif
