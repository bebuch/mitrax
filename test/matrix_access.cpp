// -----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
// -----------------------------------------------------------------------------
#define BOOST_TEST_MODULE mitrax make_matrix
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>

#include <mitrax/make_matrix.hpp>

#include <complex>
#include <iostream>


using namespace mitrax;
using namespace mitrax::literals;


BOOST_AUTO_TEST_SUITE(suite_matrix_access)


using types = boost::mpl::list< int, double, std::complex< float > >;



BOOST_AUTO_TEST_CASE_TEMPLATE(test_1x1, T, types){
	constexpr auto m1 = make_matrix(1_CS, 1_RS, {{T(5)}});
	auto m2 = make_matrix(1_CS, 1_RS, {{T(5)}});

	T a = m1;
	T b = m2;

	BOOST_TEST(a == T(5));
	BOOST_TEST(b == T(5));

	static_cast< T& >(m2) = T(7);
	T c = m2;

	BOOST_TEST(c == T(7));
}


BOOST_AUTO_TEST_SUITE_END()
