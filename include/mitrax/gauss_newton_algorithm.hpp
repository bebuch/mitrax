//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__gauss_newton_algorithm__hpp_INCLUDED_
#define _mitrax__gauss_newton_algorithm__hpp_INCLUDED_

#include <mitrax/make_matrix.hpp>
#include <mitrax/gaussian_elimination.hpp>
#include <mitrax/operator.hpp>


namespace mitrax{


	template < typename F, typename M, size_t R, typename X >
	auto gauss_newton_algorithm(
		F const& /*f*/,
		col_vector< M, R > const& start_value,
		X const& /*threshold*/,
		boost::container::vector< std::pair< X, X > > const& /*data*/
	){
		using std::abs;

		auto arg = start_value;

// 		auto r = make_col_vector< X >(rows(data.size()),
// 			[&data](size_t, size_t y){ return data[y].second; });
// 
// 		auto d = make_matrix< X >(arg.rows().as_col(), rows(data.size()),
// 			[&data](size_t x, size_t y){
// 				auto arg1 = arg;
// 				auto arg2 = arg;
// 				arg1[x] -= threshold / 8;
// 				arg2[x] += threshold / 8;
// 				return (f(arg1, data[y].second) - f(arg1, data[y].second)) /
// 					threshold - data[y].first;
// 			}
// 		);
// 
// 		auto trans_d = transpose(d);
// 		auto arg_new = arg - inverse(trans_d * d) * trans_d * r;
// 
// 		while(abs(arg_new - arg) < threshold){
// 			arg = arg_new;
// 
// 			trans_d = transpose(d);
// 			arg_new = arg - inverse(trans_d * d) * trans_d * r;
// 		}

		return arg;
	}


}


#endif
