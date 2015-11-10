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

#include "integer.hpp"

#include <boost/container/vector.hpp>

#include <type_traits>
#include <utility>


namespace mitrax{


	namespace detail{


		template < typename T, size_t N, size_t ... I >
		auto to_vector(T(&&v)[N], std::index_sequence< I ... >){
			return boost::container::vector< std::remove_cv_t< T > >{
				std::move(v[I]) ...
			};
		}

		template < typename T, size_t N, size_t ... I >
		auto to_vector(T(&v)[N], std::index_sequence< I ... >){
			return boost::container::vector< std::remove_cv_t< T > >{
				v[I] ...
			};
		}


		template < typename T, size_t C, size_t R, size_t ... I >
		auto to_vector(T(&&v)[R][C], std::index_sequence< I ... >){
			return boost::container::vector< std::remove_cv_t< T > >{
				std::move(v[I / C][I % C]) ...
			};
		}

		template < typename T, size_t C, size_t R, size_t ... I >
		auto to_vector(T(&v)[R][C], std::index_sequence< I ... >){
			return boost::container::vector< std::remove_cv_t< T > >{
				v[I / C][I % C] ...
			};
		}


	}


	template < typename T, size_t N >
	auto to_vector(T(&&v)[N]){
		return detail::to_vector(
			std::move(v), std::make_index_sequence< N >()
		);
	}

	template < typename T, size_t N >
	auto to_vector(T(&v)[N]){
		return detail::to_vector(
			v, std::make_index_sequence< N >()
		);
	}


	template < typename T, size_t C, size_t R >
	auto to_vector(T(&&v)[R][C]){
		return detail::to_vector(
			std::move(v), std::make_index_sequence< C * R >()
		);
	}

	template < typename T, size_t C, size_t R >
	auto to_vector(T(&v)[R][C]){
		return detail::to_vector(
			v, std::make_index_sequence< C * R >()
		);
	}


}


#endif
