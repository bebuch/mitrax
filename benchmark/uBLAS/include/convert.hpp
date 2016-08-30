//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__uBLAS__convert__hpp_INCLUDED_
#define _mitrax__uBLAS__convert__hpp_INCLUDED_

#include <boost/numeric/ublas/matrix.hpp>

#include <mitrax/matrix.hpp>


namespace mitrax{


	namespace ublas = boost::numeric::ublas;

	template < typename T >
	constexpr auto convert(ublas::matrix< T > const& m){
		return make_matrix_fn(dims(m.size1(), m.size2()), [&m](auto x, auto y){
			return m(x, y);
		});
	}

	template < typename M, size_t C, size_t R >
	constexpr auto convert(matrix< M, C, R > const& m){
		ublas::matrix< value_type_t< M > > res(size_t(m.cols()), size_t(m.rows()));

		for(size_t y = 0; y < m.rows(); ++y){
			for(size_t x = 0; x < m.cols(); ++x){
				res(x, y) = m(x, y);
			}
		}

		return res;
	}


}


#endif
