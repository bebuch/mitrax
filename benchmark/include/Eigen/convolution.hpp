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
	inline auto convolution(
		MatrixBase< DerivedM > const& m,
		MatrixBase< DerivedK > const& k
	){
		using ScalarK = typename DerivedK::Scalar;

		using ResultType = Matrix< ScalarK, Eigen::Dynamic, Eigen::Dynamic >;

		int kr = k.rows();
		int kc = k.cols();

		int res_r = m.rows() - kr + 1;
		int res_c = m.cols() - kc + 1;

		ResultType res(res_r, res_c);

		for(int my = 0; my < res_r; ++my){
			for(int mx = 0; mx < res_c; ++mx){
				ScalarK b = 0;

				for(int ky = 0; ky < kr; ++ky){
					for(int kx = 0; kx < kc; ++kx){
						b += m(my + ky, mx + kx) * k(ky, kx);
					}
				}

				res.coeffRef(my, mx) = b;
			}
		}

		return res;
	}

	template < typename DerivedM, typename DerivedKC, typename DerivedKR >
	inline auto convolution(
		MatrixBase< DerivedM > const& m,
		MatrixBase< DerivedKC > const& vc,
		MatrixBase< DerivedKR > const& vr
	){
		return convolution(convolution(m, vr), vc);
	}

}


#endif
