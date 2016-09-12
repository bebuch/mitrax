//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__region__hpp_INCLUDED_
#define _mitrax__region__hpp_INCLUDED_

#include "multi_invoke_adapter.hpp"
#include "sub_matrix.hpp"

#include <vector>


namespace mitrax{


	namespace detail{


		template < size_t Cr, size_t Rr >
		struct region_sub_matrix{
			dims_t< Cr, Rr > region_dims;
			double x_factor;
			double y_factor;

			template < typename M >
			constexpr auto operator()(M const& m, size_t x, size_t y)const{
				x = static_cast< size_t >(x * x_factor + 0.5);
				y = static_cast< size_t >(y * y_factor + 0.5);
				return sub_matrix(m, x, y, region_dims);
			}
		};

		template < size_t Cr, size_t Rr >
		constexpr auto make_region_sub_matrix(
			dims_t< Cr, Rr > const& region_dims,
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
		F&& f,
		dims_t< Cr, Rr > const& region_dims,
		dims_t< Co, Ro > const& overlapp_dims,
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

		return make_matrix_fn(result_dims, make_multi_invoke_adapter(
			static_cast< F&& >(f), detail::make_region_sub_matrix(
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
		F&& f,
		col_t< Cctr, Cr > region_cols,
		row_t< Rctr, Rr > region_rows,
		col_t< Ccto, Co > overlapp_cols,
		row_t< Rcto, Ro > overlapp_rows,
		matrix< M, C, R > const& ... images
	){
		return calc_regions(
			static_cast< F&& >(f),
			dims(region_cols, region_rows),
			dims(overlapp_cols, overlapp_rows),
			images ...
		);
	}


	template <
		typename F,
		size_t Cr, size_t Rr,
		typename M, size_t C, size_t R,
		typename ... Mi, size_t ... Ci, size_t ... Ri
	> auto apply_regions(
		F&& f,
		dims_t< Cr, Rr > const& region_dims,
		matrix< M, C, R > const& regions,
		matrix< Mi, Ci, Ri > const& ... images
	){
		using namespace literals;

		using value_type = value_type_t< M >;

		auto size = get_dims(images ...);

		double x_factor =
			static_cast< double >(size.cols() - region_dims.cols()) /
			static_cast< double >(regions.cols() - 1_C);

		double y_factor =
			static_cast< double >(size.rows() - region_dims.rows()) /
			static_cast< double >(regions.rows() - 1_R);


		auto x_bounds = make_vector_fn(regions.cols().as_row() * 2_R,
			[x_factor, &region_dims](size_t i){
				auto p = static_cast< size_t >((i / 2) * x_factor + 0.5);
				bool begin = i % 2 == 0;
				return std::make_pair(
					begin ? p : p + static_cast< size_t >(region_dims.cols()),
					begin
				);
			}
		);

		auto y_bounds = make_vector_fn(regions.rows() * 2_R,
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

		// pair< start in image, start in region, count of regions >
		std::vector< std::tuple< size_t, size_t, size_t > > x_sc;
		std::vector< std::tuple< size_t, size_t, size_t > > y_sc;

		for(size_t x = 0, s = 0, c = 0; x < x_bounds.rows() - 1_R; ++x){
			if(x_bounds[x].second){
				++c;
			}else{
				--c;
				++s;
			}

			if(x_bounds[x].first == x_bounds[x + 1].first) continue;

			x_sc.emplace_back(x_bounds[x].first, s, c);
		}

		for(size_t y = 0, s = 0, c = 0; y < y_bounds.rows() - 1_R; ++y){
			if(y_bounds[y].second){
				++c;
			}else{
				--c;
				++s;
			}

			if(y_bounds[y].first == y_bounds[y + 1].first) continue;

			y_sc.emplace_back(y_bounds[y].first, s, c);
		}

		return make_matrix_fn(size,
			[&f, &x_sc, &y_sc, &regions, &images ...](size_t c, size_t r){
				size_t x = 0;
				size_t y = 0;

				while(x < x_sc.size() && std::get< 0 >(x_sc[x]) <= c) ++x;
				while(y < y_sc.size() && std::get< 0 >(y_sc[y]) <= r) ++y;
				--x;
				--y;

				std::vector< value_type_t< M > > input;
				input.reserve(std::get< 2 >(x_sc[x]) * std::get< 2 >(y_sc[y]));

				for(size_t dy = 0; dy < std::get< 2 >(y_sc[y]); ++dy){
					for(size_t dx = 0; dx < std::get< 2 >(x_sc[x]); ++dx){
						input.emplace_back(regions(
							std::get< 1 >(x_sc[x]) + dx,
							std::get< 1 >(y_sc[y]) + dy
						));
					}
				}

				return f(std::move(input), images(c, r) ...);
			});
	}


	template <
		typename F,
		bool Cctr, size_t Cr, bool Rctr, size_t Rr,
		typename M, size_t C, size_t R,
		typename ... Mi, size_t ... Ci, size_t ... Ri
	> auto apply_regions(
		F&& f,
		col_t< Cctr, Cr > region_cols,
		row_t< Rctr, Rr > region_rows,
		matrix< M, C, R > const& regions,
		matrix< Mi, Ci, Ri > const& ... images
	){
		return apply_regions(
			static_cast< F&& >(f),
			dims(region_cols, region_rows),
			regions, images ...
		);
	}


}


#endif
