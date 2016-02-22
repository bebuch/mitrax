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

#include "dim.hpp"

#include <boost/container/vector.hpp>

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

		template <
			typename F, bool Cct, size_t C, bool Rct, size_t R, size_t ... I
		> auto function_xy_to_vector(
			col_t< Cct, C >,
			row_t< Rct, R >,
			F const& f,
			std::index_sequence< I ... >
		){
			return boost::container::vector< fn_xy< F > >{
				f(I % C, I / C) ...
			};
		}

		template < typename F, bool Cct, size_t C, bool Rct, size_t R >
		auto function_xy_to_vector(
			col_t< Cct, C > c,
			row_t< Rct, R > r,
			F const& f,
			std::index_sequence<>
		){
			boost::container::vector< fn_xy< F > > res;
			res.reserve(size_t(c) * size_t(r));

			for(size_t y = 0; y < r; ++y){
				for(size_t x = 0; x < c; ++x){
					res.push_back(f(x, y));
				}
			}
			return res;
		}

		template < typename F, bool Nct, size_t N, size_t ... I >
		auto function_i_to_vector(
			dim_t< Nct, N >, F const& f, std::index_sequence< I ... >
		){
			return boost::container::vector< fn_i< F > >{
				f(I) ...
			};
		}

		template < typename F, bool Nct, size_t N >
		auto function_i_to_vector(
			dim_t< Nct, N > n, F const& f, std::index_sequence<>
		){
			boost::container::vector< fn_i< F > > res;
			res.reserve(n);
			for(size_t i = 0; i < n; ++i){
				res.push_back(f(i));
			}
			return res;
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

	template < typename F, bool Cct, size_t C, bool Rct, size_t R >
	auto function_xy_to_vector(
		col_t< Cct, C > c, row_t< Rct, R > r, F const& f
	){
		return detail::function_xy_to_vector(
			c, r, f, std::make_index_sequence<
				Cct && Rct ? C * R : 0
			>()
		);
	}

	template < typename F, bool Nct, size_t N >
	auto function_i_to_vector(dim_t< Nct, N > n, F const& f){
		return detail::function_i_to_vector(
			n, f, std::make_index_sequence< Nct ? N : 0 >()
		);
	}


}


#endif
