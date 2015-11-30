//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#include <boost/test/unit_test.hpp>

#include <mitrax/householder_transformation.hpp>
#include <mitrax/operator.hpp>

#include <cmath>
#include <algorithm>


using boost::typeindex::type_id;
using boost::typeindex::type_id_runtime;
using namespace mitrax;
using namespace mitrax::literals;


BOOST_AUTO_TEST_SUITE(test_suite_householder_transformation)


namespace{


	template < typename T, typename U >
	constexpr bool equal(T const& a, U const& b){
		using std::abs;
		return abs(a - b) < 0.00001;
	}

	template < typename T, typename U >
	constexpr bool matrix_equal(T const& a, U const& b){
		using std::abs;
		auto m = a - b;
		return std::any_of(m.begin(), m.end(), [](auto v){
			return v < 0.00001;
		});
	}


}


BOOST_AUTO_TEST_CASE(test_householder_transformation){
	constexpr auto m = make_square_matrix< double >(3_D, {
		{0, -4,  2},
		{6, -3, -2},
		{8,  1, -1}
	});

	auto q = make_square_matrix< double >(3_D);
	auto r = make_square_matrix< double >(3_D);

	std::tie(q, r) = householder_transformation(m);

	BOOST_TEST((
		equal(q(0, 0),  0) &&
		equal(q(1, 0),  0.8) &&
		equal(q(2, 0),  0.6) &&
		equal(q(0, 1), -0.6) &&
		equal(q(1, 1),  0.48) &&
		equal(q(2, 1), -0.64) &&
		equal(q(0, 2), -0.8) &&
		equal(q(1, 2), -0.36) &&
		equal(q(2, 2),  0.48)
	));

	BOOST_TEST((
		equal(r(0, 0), -10) &&
		equal(r(1, 0),   1) &&
		equal(r(2, 0),   2) &&
		equal(r(0, 1),   0) &&
		equal(r(1, 1),  -5) &&
		equal(r(2, 1),   1) &&
		equal(r(0, 2),   0) &&
		equal(r(1, 2),   0) &&
		equal(r(2, 2),   2)
	));

	BOOST_TEST(matrix_equal(q * r, m));
}


BOOST_AUTO_TEST_SUITE_END()
