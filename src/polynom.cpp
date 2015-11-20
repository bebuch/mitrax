//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#include <boost/test/unit_test.hpp>

#include <mitrax/least_square.hpp>

#include <cmath>


using boost::typeindex::type_id;
using boost::typeindex::type_id_runtime;
using namespace mitrax;
using namespace mitrax::literals;


BOOST_AUTO_TEST_SUITE(test_suite_polynom)


namespace{


	template < typename T, typename U >
	constexpr bool equal(T const& a, U const& b){
		return std::abs(a - b) < 0.00001;
	}


}


BOOST_AUTO_TEST_CASE(test_least_square_1_degree){
	auto points = boost::container::vector< point< float > >{
		{0,  2},
		{1,  1},
		{2,  0},
		{3, -1},
		{4,  1}
	};

	auto polynom = least_square< 1 >(points);

	BOOST_TEST((
		equal(polynom[0], 1.4) &&
		equal(polynom[1], -0.4)
	));
}

BOOST_AUTO_TEST_CASE(test_least_square_2_degree){
	auto points = boost::container::vector< point< float > >{
		{0,  2},
		{1,  1},
		{2,  0},
		{3, -1},
		{4,  1}
	};

	auto polynom = least_square< 2 >(points);

	BOOST_TEST((
		equal(polynom[0],  2.2571429) &&
		equal(polynom[1], -2.1142857) &&
		equal(polynom[2],  0.42857143)
	));
}


BOOST_AUTO_TEST_SUITE_END()
