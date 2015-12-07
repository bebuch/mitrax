//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__region__hpp_INCLUDED_
#define _mitrax__region__hpp_INCLUDED_

#include "multi_invoke_adapter.hpp"
#include "matrix.hpp"


namespace mitrax{


	namespace detail{


		template < size_t Cr, size_t Rr >
		struct region_call_sub_matrix{
			dim_t< Cr, Rr > region_dims;
			double factor_x;
			double factor_y;

			template < typename M >
			constexpr auto operator()(M const& m, size_t x, size_t y)const{
				x = static_cast< size_t >(x * factor_x + 0.5);
				y = static_cast< size_t >(y * factor_y + 0.5);
				return m.sub_matrix(x, y, region_dims);
			}
		};

		template < size_t Cr, size_t Rr >
		constexpr auto region_make_call_sub_matrix(
			dim_t< Cr, Rr > const& region_dims,
			double factor_x,
			double factor_y
		){
			return region_call_sub_matrix< Cr, Rr >{
				region_dims, factor_x, factor_y
			};
		}


	}


	template <
		typename F,
		size_t Cr, size_t Rr,
		size_t Co, size_t Ro,
		typename ... M, size_t ... C, size_t ... R
	> constexpr auto region(
		F const& f,
		dim_t< Cr, Rr > const& region_dims,
		dim_t< Co, Ro > const& overlapp_dims,
		matrix< M, C, R > const& ... images
	){
		using namespace literals;

		auto size = get_dims(images ...);

		if(
			region_dims.cols() <= overlapp_dims.cols() ||
			region_dims.rows() <= overlapp_dims.rows()
		) throw std::logic_error("overlapp_dims must be less region_dims");

		if(
			region_dims.cols() > size.cols() ||
			region_dims.rows() > size.rows()
		) throw std::logic_error(
			"overlapp_dims must be less or equal image dims"
		);

		auto result_dims =
			(size - dims(1_C, 1_R) - (region_dims - overlapp_dims)) /
			(region_dims - overlapp_dims) + dims(1_C, 1_R);

		double factor_x =
			static_cast< double >(size.cols() - region_dims.cols()) /
			static_cast< double >(result_dims.cols() - 1_C);

		double factor_y =
			static_cast< double >(size.rows() - region_dims.rows()) /
			static_cast< double >(result_dims.rows() - 1_R);

		return make_matrix_by_function(
			result_dims,
			make_multi_invoke_adapter(
				f, detail::region_make_call_sub_matrix(
					region_dims, factor_x, factor_y
				), images ...
			));
	}


	template <
		typename F,
		bool Cctr, size_t Cr, bool Rctr, size_t Rr,
		bool Ccto, size_t Co, bool Rcto, size_t Ro,
		typename ... M, size_t ... C, size_t ... R
	> constexpr auto region(
		F const& f,
		col_init_t< Cctr, Cr > region_cols,
		row_init_t< Rctr, Rr > region_rows,
		col_init_t< Ccto, Co > overlapp_cols,
		row_init_t< Rcto, Ro > overlapp_rows,
		matrix< M, C, R > const& ... images
	){
		return region(
			f,
			dims(region_cols, region_rows),
			dims(overlapp_cols, overlapp_rows),
			images ...
		);
	}


}


#endif
