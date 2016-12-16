//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__uBLAS__convolution__hpp_INCLUDED_
#define _mitrax__uBLAS__convolution__hpp_INCLUDED_

#include <boost/numeric/ublas/matrix.hpp>


namespace uBLAS{


	namespace ublas = boost::numeric::ublas;

	template < typename M1, typename M2 >
	inline auto convolution(M1 const& m, M2 const& k){
		int kc = k.size1();
		int kr = k.size2();

		int res_c = m.size1() - kc + 1;
		int res_r = m.size2() - kr + 1;

		using value_type = typename M2::value_type;
		ublas::matrix< value_type > res(res_c, res_r);

		for(int my = 0; my < res_r; ++my){
			for(int mx = 0; mx < res_c; ++mx){
				value_type b = 0;

				for(int ky = 0; ky < kr; ++ky){
					for(int kx = 0; kx < kc; ++kx){
						b += m(mx + kx, my + ky) * k(kx, ky);
					}
				}

				res(mx, my) = b;
			}
		}


		return res;
	}

	template < typename TM, typename V1, typename V2 >
	inline auto convolution(
		ublas::matrix< TM > const& m,
		V1 const& vc,
		V2 const& vr
	){
		return convolution(convolution(m, vr), vc);
	}

}


#endif
