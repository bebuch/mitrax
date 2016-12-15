//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__gauss_newton_algorithm__hpp_INCLUDED_
#define _mitrax__gauss_newton_algorithm__hpp_INCLUDED_

#include "make_matrix.hpp"
#include "gaussian_elimination.hpp"
#include "operator.hpp"
#include "norm.hpp"

#include "io/matrix.hpp"

#include <boost/container/vector.hpp>

#include <iostream>


namespace mitrax{


	template < typename F, typename M, row_ct R, typename T, typename ... V >
	auto gauss_newton_algorithm(
		F&& f,
		col_vector< M, R > const& start_value,
		T const& threshold,
		boost::container::vector< std::tuple< V ... > > const& data
	){
		using std::abs;

		auto arg = start_value;

		for(;;){
			std::cout << arg << std::endl;

			auto r = make_vector_fn(rows(data.size()),
				[&data, &arg, &f](size_t y){
					return f(arg, data[y]);
				});

			auto d = make_matrix_fn(dim_pair(arg.rows().as_col(), data.size()),
				[&data, &arg, &f, &threshold](size_t x, size_t y){
					auto arg1 = arg;
					arg1[x] += threshold / 128;
					return (
						f(arg1, data[y]) - f(arg, data[y])
					) / (threshold / 128);
				}
			);

			auto trans_d = transpose(d);
// 			std::cout << d << std::endl;
// 			std::cout << trans_d << std::endl;
// 			std::cout << trans_d * d << std::endl;
// 			std::cout << trans_d * r << std::endl;
			auto s = gaussian_elimination(trans_d * d, -trans_d * r);
			auto arg_new = arg + s;

			auto diff = arg_new - arg;

			arg = arg_new;

			if(vector_norm_2sqr(diff) < threshold) break;
		}

		return arg;
	}


	template < typename F, typename M, row_ct R, typename T, typename ... V >
	auto levenberg_marquardt_algorithm(
		F&& f,
		col_vector< M, R > const& start_value,
		T const& threshold,
		T mu,
		T const& beta0,
		T const& beta1,
		boost::container::vector< std::tuple< V ... > > const& data
	){
		using std::abs;

		auto arg = start_value;

		auto r = make_vector_fn(rows(data.size()),
			[&data, &arg, &f](size_t y){
				return f(arg, data[y]);
			});

		for(;;){
// 			std::cout << arg << std::endl;

			auto d = make_matrix_fn(dim_pair(arg.rows().as_col(), data.size()),
				[&data, &arg, &f, &threshold](size_t x, size_t y){
					auto arg1 = arg;
					arg1[x] += threshold / 128;
					return (
						f(arg1, data[y]) - f(arg, data[y])
					) / (threshold / 128);
				}
			);

			auto s = [&data, &arg, &r, &d, &f, &mu, beta0, beta1]{ for(;;){
				auto const mu2_matrix = make_diag_matrix_v< T >(
					arg.rows().as_dim(), mu * mu
				);

				auto trans_d = transpose(d);
				auto s = gaussian_elimination(
					trans_d * d + mu2_matrix,
					-trans_d * r
				);

				auto r_new = make_vector_fn(rows(data.size()),
					[&data, &arg, &s, &f](size_t y){
						return f(arg + s, data[y]);
					});

				auto r_norm = vector_norm_2sqr(r);
				auto numerator = (r_norm - vector_norm_2sqr(r_new));
				auto denominator = (r_norm - vector_norm_2sqr(r + d * s));
				auto eps = numerator / denominator;

				if(denominator == 0){
					throw std::runtime_error("eps is infinite");
				}

// 				std::cout << "eps: " << eps << std::endl;
				if(eps <= beta0){
					mu *= 2;
					continue;
				}

				r = r_new;

				if(eps < beta1){
					return s;
				}

				mu /= 2;
				return s;
			} }();

// 			std::cout << "s: " << s << std::endl;
			auto arg_new = arg + s;

			arg = arg_new;

			if(vector_norm_2sqr(s) < threshold) break;
		}

		return arg;
	}


}


#endif
