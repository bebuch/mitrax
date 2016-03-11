//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__least_square__hpp_INCLUDED_
#define _mitrax__least_square__hpp_INCLUDED_

#include "polynom.hpp"
#include "operator.hpp"
#include "gaussian_elimination.hpp"

#include <boost/container/vector.hpp>

#include <cmath>


namespace mitrax{


	template < size_t Degree, typename T >
	polynom< T, Degree > least_square(
		boost::container::vector< point< T > > const& values
	){
		auto m = make_matrix(cols< Degree + 1 >(), rows(values.size()), T(1));
		auto b = make_col_vector< T >(rows(values.size()));

		for(size_t y = 0; y < values.size(); ++y){
			for(size_t x = 1; x < Degree + 1; ++x){
				m(x, y) = std::pow(values[y].x(), x);
			}
			b[y] = values[y].y();
		}

		auto m_res = transpose(m) * m;
		auto b_res = transpose(m) * b;

		auto res = gaussian_elimination(m_res, b_res);

		polynom< T, Degree > result;

		for(size_t i = 0; i < Degree + 1; ++i){
			result[i] = res[i];
		}

		return result;
	}

}


#endif
