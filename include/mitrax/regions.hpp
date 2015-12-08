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
		struct region_sub_matrix{
			dim_t< Cr, Rr > region_dims;
			double x_factor;
			double y_factor;

			template < typename M >
			constexpr auto operator()(M const& m, size_t x, size_t y)const{
				x = static_cast< size_t >(x * x_factor + 0.5);
				y = static_cast< size_t >(y * y_factor + 0.5);
				return m.sub_matrix(x, y, region_dims);
			}
		};

		template < size_t Cr, size_t Rr >
		constexpr auto make_region_sub_matrix(
			dim_t< Cr, Rr > const& region_dims,
			double x_factor,
			double y_factor
		){
			return region_sub_matrix< Cr, Rr >{
				region_dims, x_factor, y_factor
			};
		}


	}


	template <
		typename F,
		size_t Cr, size_t Rr,
		size_t Co, size_t Ro,
		typename ... M, size_t ... C, size_t ... R
	> constexpr auto calc_regions(
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

		double x_factor =
			static_cast< double >(size.cols() - region_dims.cols()) /
			static_cast< double >(result_dims.cols() - 1_C);

		double y_factor =
			static_cast< double >(size.rows() - region_dims.rows()) /
			static_cast< double >(result_dims.rows() - 1_R);

		return make_matrix_by_function(
			result_dims,
			make_multi_invoke_adapter(
				f, detail::make_region_sub_matrix(
					region_dims, x_factor, y_factor
				), images ...
			));
	}


	template <
		typename F,
		bool Cctr, size_t Cr, bool Rctr, size_t Rr,
		bool Ccto, size_t Co, bool Rcto, size_t Ro,
		typename ... M, size_t ... C, size_t ... R
	> constexpr auto calc_regions(
		F const& f,
		col_init_t< Cctr, Cr > region_cols,
		row_init_t< Rctr, Rr > region_rows,
		col_init_t< Ccto, Co > overlapp_cols,
		row_init_t< Rcto, Ro > overlapp_rows,
		matrix< M, C, R > const& ... images
	){
		return calc_regions(
			f,
			dims(region_cols, region_rows),
			dims(overlapp_cols, overlapp_rows),
			images ...
		);
	}


	template <
		typename F,
		size_t Cr, size_t Rr,
		size_t Co, size_t Ro,
		typename M, size_t C, size_t R
	> auto eval_regions(
		F const& f,
		dim_t< Cr, Rr > const& region_dims,
		dim_t< Co, Ro > const& original_dims,
		matrix< M, C, R > const& regions
	){
		using namespace literals;

		double x_factor =
			static_cast< double >(original_dims.cols() - region_dims.cols()) /
			static_cast< double >(regions.cols() - 1_C);

		double y_factor =
			static_cast< double >(original_dims.rows() - region_dims.rows()) /
			static_cast< double >(regions.rows() - 1_R);

		boost::container::vector< size_t > x_breaks;
		boost::container::vector< size_t > y_breaks;

		x_breaks.reserve(regions.cols() * 2_C);
		y_breaks.reserve(regions.rows() * 2_R);

		for(size_t x = 0; x < regions.cols(); ++x){
			auto p = static_cast< size_t >(x * x_factor + 0.5);
			x_breaks.push_back(p);
			x_breaks.push_back(p + region_dims.cols());
		}

		for(size_t y = 0; y < regions.rows(); ++y){
			auto p = static_cast< size_t >(y * y_factor + 0.5);
			y_breaks.push_back(p);
			y_breaks.push_back(p + region_dims.rows());
		}

		x_breaks.pop_back();
		y_breaks.pop_back();

		std::sort(x_breaks.begin(), x_breaks.end());
		std::sort(y_breaks.begin(), y_breaks.end());

		std::unique(x_breaks.begin(), x_breaks.end());
		std::unique(y_breaks.begin(), y_breaks.end());

		return mitrax::make_matrix_by_function(
			dims(x_breaks.size(), y_breaks.size()),
			[&x_breaks, &y_breaks](size_t x, size_t y){
// 				using value_type = value_type_t< M >;

				return point< size_t >(x_breaks[x], y_breaks[y]);
// 				auto start_x = static_cast< size_t >(x * x_factor + 0.5);
// 				auto start_y = static_cast< size_t >(y * y_factor + 0.5);
// 
// 				auto x_begin = std::find(
// 					x_breaks.begin(), x_breaks.end(), start_x
// 				);
// 				assert(x_begin != x_breaks.end());
// 
// 				auto y_begin = std::find(
// 					y_breaks.begin(), y_breaks.end(), start_y
// 				);
// 				assert(y_begin != y_breaks.end());
// 
// 				auto x_end = x_begin + 1;
// 				auto y_end = y_begin + 1;
// 
// 				while(*x_end < start_x + regions.cols()) ++x_end;
// 				while(*y_end < start_y + regions.rows()) ++y_end;
// 
// 				boost::container::vector< value_type > values;
// 				values.reserve();
				
			});
	}


	template <
		typename F,
		bool Cctr, size_t Cr, bool Rctr, size_t Rr,
		bool Ccto, size_t Co, bool Rcto, size_t Ro,
		typename M, size_t C, size_t R
	> auto eval_regions(
		F const& f,
		col_init_t< Cctr, Cr > region_cols,
		row_init_t< Rctr, Rr > region_rows,
		col_init_t< Ccto, Co > original_cols,
		row_init_t< Rcto, Ro > original_rows,
		matrix< M, C, R > const& regions
	){
		return evaluate_regions(
			f,
			dims(region_cols, region_rows),
			dims(original_cols, original_rows),
			regions
		);
	}


}


#endif
