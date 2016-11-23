//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__Eigen__convert__hpp_INCLUDED_
#define _mitrax__Eigen__convert__hpp_INCLUDED_

#include <Eigen/Core>

#include <mitrax/matrix.hpp>


namespace mitrax{


	template < typename Derived >
	constexpr auto convert(Eigen::MatrixBase< Derived > const& m){
		return make_matrix_fn(dim_pair(m.cols(), m.rows()), [&m](auto x, auto y){
			return m(y, x);
		});
	}

	template < typename M, size_t C, size_t R >
	constexpr auto convert(matrix< M, C, R > const& m){
		Eigen::Matrix<
			value_type_t< M >,
			R == 0 ? Eigen::Dynamic : int(R),
			C == 0 ? Eigen::Dynamic : int(C)
		> res(int(m.rows()), int(m.cols()));

		for(size_t y = 0; y < m.rows(); ++y){
			for(size_t x = 0; x < m.cols(); ++x){
				res.coeffRef(y, x) = m(x, y);
			}
		}

		return res;
	}


}


#endif
