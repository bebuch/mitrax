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

#include "io_debug.hpp"
#include "output.hpp"


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

		using value_type = value_type_t< M >;

		double x_factor =
			static_cast< double >(original_dims.cols() - region_dims.cols()) /
			static_cast< double >(regions.cols() - 1_C);

		double y_factor =
			static_cast< double >(original_dims.rows() - region_dims.rows()) /
			static_cast< double >(regions.rows() - 1_R);


		auto x_bounds = make_col_vector_by_function(
			regions.cols().as_row() * 2_R,
			[x_factor, &region_dims](size_t i){
				auto p = static_cast< size_t >((i / 2) * x_factor + 0.5);
				bool begin = i % 2 == 0;
				return std::make_pair(
					begin ? p : p + static_cast< size_t >(region_dims.cols()),
					begin
				);
			}
		);

		auto y_bounds = make_col_vector_by_function(
			regions.rows() * 2_R,
			[y_factor, &region_dims](size_t i){
				auto p = static_cast< size_t >((i / 2) * y_factor + 0.5);
				bool begin = i % 2 == 0;
				return std::make_pair(
					begin ? p : p + static_cast< size_t >(region_dims.rows()),
					begin
				);
			}
		);

		std::sort(x_bounds.begin(), x_bounds.end());
		std::sort(y_bounds.begin(), y_bounds.end());

		// pair< start in region, count of regions >
		boost::container::vector< std::pair< size_t, size_t > > x_sc;
		boost::container::vector< std::pair< size_t, size_t > > y_sc;

		for(size_t x = 0, s = 0, c = 0; x < x_bounds.rows() - 1_R; ++x){
			if(x_bounds[x].second){
				++c;
			}else{
				--c;
				++s;
			}

			if(x_bounds[x].first == x_bounds[x + 1].first) continue;

			x_sc.emplace_back(s, c);
		}

		for(size_t y = 0, s = 0, c = 0; y < y_bounds.rows() - 1_R; ++y){
			if(y_bounds[y].second){
				++c;
			}else{
				--c;
				++s;
			}

			if(y_bounds[y].first == y_bounds[y + 1].first) continue;

			y_sc.emplace_back(s, c);
		}

		return make_matrix_by_function(dims(x_sc.size(), y_sc.size()),
			[&f, &x_sc, &y_sc, &regions](size_t x, size_t y){
				boost::container::vector< value_type_t< M > > input;
				input.reserve(y_sc[y].second * x_sc[x].second);

				for(size_t dy = 0; dy < y_sc[y].second; ++dy){
					for(size_t dx = 0; dx < x_sc[x].second; ++dx){
						input.emplace_back(
							regions(x_sc[x].first + dx, y_sc[y].first + dy)
						);
					}
				}

				return f(std::move(input));
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
