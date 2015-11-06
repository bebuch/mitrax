//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#include <boost/test/unit_test.hpp>

#include <mitrax/raw_matrix.hpp>
#include <mitrax/compare.hpp>


using boost::typeindex::type_id;
using boost::typeindex::type_id_runtime;
using namespace mitrax;


namespace{


	constexpr auto ref_int = to_square_matrix< int, 2 >({
		{0, 1},
		{2, 3}
	});

	constexpr auto ref_double = to_square_matrix< double, 2 >({
		{0, 1},
		{2, 3}
	});

	constexpr auto ref_double_half = to_square_matrix< double, 2 >({
		{0.5, 1.3},
		{2.4, 3.8}
	});


}


BOOST_AUTO_TEST_CASE(test_convert_2x2_to_2x2){
	constexpr auto m = ref_double_half.as_raw_matrix< int, 2, 2 >();

	constexpr auto eq1 = m == ref_int;
	BOOST_TEST(eq1);

	constexpr auto neq1 = m != ref_double_half;
	BOOST_TEST(neq1);

	auto double_m = ref_double_half;
	auto int_m = std::move(double_m).as_raw_matrix< int, 2, 2 >();

	auto eq2 = int_m == ref_int;
	BOOST_TEST(eq2);

	auto neq2 = int_m != ref_double_half;
	BOOST_TEST(neq2);

}
