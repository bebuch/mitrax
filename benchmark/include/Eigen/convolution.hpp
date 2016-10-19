//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__Eigen__convolution__hpp_INCLUDED_
#define _mitrax__Eigen__convolution__hpp_INCLUDED_

#include <Eigen/Core>


namespace Eigen{


	template < typename DerivedM, typename DerivedK >
	auto convolution(MatrixBase< DerivedM > const& m, MatrixBase< DerivedK > const& k){
		using ScalarK = typename DerivedK::Scalar;

		using ResultType = Matrix< ScalarK, Eigen::Dynamic, Eigen::Dynamic >;

		int kr = k.rows();
		int kc = k.cols();

		int res_r = m.rows() - kr + 1;
		int res_c = m.cols() - kc + 1;

		ResultType res(res_r, res_c);

		for(int row = 0; row < res_r; ++row){
			for(int col = 0; col < res_c; ++col){
				ScalarK b = 0;

				for(int r = 0; r < kr; ++r){
					for(int c = 0; c < kc; ++c){
						b += m(row + r, col + c) * k(r, c);
					}
				}

				res.coeffRef(row, col) = b;
			}
		}

		return res;
	}

	template < typename DerivedM, typename DerivedKC, typename DerivedKR >
	auto convolution(
		MatrixBase< DerivedM > const& m,
		MatrixBase< DerivedKC > const& vc,
		MatrixBase< DerivedKR > const& vr
	){
		return convolution(convolution(m, vr), vc);
	}

}


#endif
