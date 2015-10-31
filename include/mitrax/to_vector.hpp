//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__to_vector__hpp_INCLUDED_
#define _mitrax__to_vector__hpp_INCLUDED_

#include <boost/container/vector.hpp>

#include <type_traits>
#include <utility>


namespace mitrax{


	namespace detail{


		template < typename T, std::size_t N, std::size_t ... I >
		constexpr auto to_vector(T(&&arr)[N], std::index_sequence< I ... >){
			return boost::container::vector< std::remove_cv_t< T > >{
				std::move(arr[I]) ...
			};
		}

		template < typename T, std::size_t N, std::size_t ... I >
		constexpr auto to_vector(T(&arr)[N], std::index_sequence< I ... >){
			return boost::container::vector< std::remove_cv_t< T > >{
				arr[I] ...
			};
		}


	}


	template < typename T, std::size_t N >
	constexpr auto to_vector(T(&&arr)[N]){
		return detail::to_vector(
			std::move(arr), std::make_index_sequence< N >()
		);
	}

	template < typename T, std::size_t N >
	constexpr auto to_vector(T(&arr)[N]){
		return detail::to_vector(arr, std::make_index_sequence< N >());
	}


}


#endif
