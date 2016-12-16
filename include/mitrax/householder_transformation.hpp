//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__householder_transformation__hpp_INCLUDED_
#define _mitrax__householder_transformation__hpp_INCLUDED_

#include "matrix.hpp"
#include "norm.hpp"


namespace mitrax{


	template < typename M, col_t C, row_t R >
	auto householder_transformation(matrix< M, C, R > const& m){
		using namespace literals;

		using value_type = value_type_t< M >;

		auto const identity = make_identity_matrix< value_type >(
			m.rows().as_dim()
		);

		auto r = m;
		auto q = identity;

		for(size_t i = 0; i < m.cols() - 1_c; ++i){
			auto v = make_vector_fn(m.rows(),
				[i, &r](size_t y){
					if(y < i) return value_type();
					return r(i, y);
				});
			v[i] += vector_norm_2(v);
			auto tv = transpose(v);
			value_type d = tv * v;
			auto h = identity - (2 / d * v * tv);

			r = h * r;
			q = q * h;
		}

		return std::make_pair(q, r);
	}


}


#endif
