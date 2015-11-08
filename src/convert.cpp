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


using boost::typeindex::type_id;
using boost::typeindex::type_id_runtime;
using namespace mitrax;


namespace{


	constexpr auto ref_int = to_square_matrix< int, 2 >({
		{0, 1},
		{2, 3}
	});

	constexpr auto ref_double = to_square_matrix< double, 2 >({
		{0.5, 1.3},
		{2.4, 3.8}
	});


	template < typename M >
	constexpr bool check(M const& m){
		return
			m.cols() == 2 &&
			m.rows() == 2 &&
			m(0, 0) == 0 &&
			m(1, 0) == 1 &&
			m(0, 1) == 2 &&
			m(1, 1) == 3;
	}


}


BOOST_AUTO_TEST_CASE(test_convert_2x2_to_2x2){
	constexpr auto m = ref_double.as_raw_matrix< int, 2, 2 >();

	constexpr auto eq1 = check(m);
	BOOST_TEST(eq1);


	auto double_m = ref_double;
	auto int_m = std::move(double_m).as_raw_matrix< int, 2, 2 >();

	auto eq2 = check(int_m);
	BOOST_TEST(eq2);
}

BOOST_AUTO_TEST_CASE(test_convert_2x2_to_0x2){
	auto m = ref_double.as_raw_matrix< int, 0, 2 >();

	auto eq1 = check(m);
	BOOST_TEST(eq1);


	auto double_m = ref_double;
	auto int_m = std::move(double_m).as_raw_matrix< int, 0, 2 >();

	auto eq2 = check(int_m);
	BOOST_TEST(eq2);
}

BOOST_AUTO_TEST_CASE(test_convert_2x2_to_2x0){
	auto m = ref_double.as_raw_matrix< int, 2, 0 >();

	auto eq1 = check(m);
	BOOST_TEST(eq1);


	auto double_m = ref_double;
	auto int_m = std::move(double_m).as_raw_matrix< int, 2, 0 >();

	auto eq2 = check(int_m);
	BOOST_TEST(eq2);
}

BOOST_AUTO_TEST_CASE(test_convert_2x2_to_0x0){
	auto m = ref_double.as_raw_matrix< int, 0, 0 >();

	auto eq1 = check(m);
	BOOST_TEST(eq1);


	auto double_m = ref_double;
	auto int_m = std::move(double_m).as_raw_matrix< int, 0, 0 >();

	auto eq2 = check(int_m);
	BOOST_TEST(eq2);
}


BOOST_AUTO_TEST_CASE(test_convert_0x2_to_2x2){
	auto m = ref_double.
		as_raw_matrix< int, 0, 2 >().
		as_raw_matrix< int, 2, 2 >();

	auto eq1 = check(m);
	BOOST_TEST(eq1);


	auto double_m = ref_double;
	auto int_m = std::move(double_m).
		as_raw_matrix< int, 0, 2 >().
		as_raw_matrix< int, 2, 2 >();

	auto eq2 = check(int_m);
	BOOST_TEST(eq2);
}

BOOST_AUTO_TEST_CASE(test_convert_0x2_to_0x2){
	auto m = ref_double.
		as_raw_matrix< int, 0, 2 >().
		as_raw_matrix< int, 0, 2 >();

	auto eq1 = check(m);
	BOOST_TEST(eq1);


	auto double_m = ref_double;
	auto int_m = std::move(double_m).
		as_raw_matrix< int, 0, 2 >().
		as_raw_matrix< int, 0, 2 >();

	auto eq2 = check(int_m);
	BOOST_TEST(eq2);
}

BOOST_AUTO_TEST_CASE(test_convert_0x2_to_2x0){
	auto m = ref_double.
		as_raw_matrix< int, 0, 2 >().
		as_raw_matrix< int, 2, 0 >();

	auto eq1 = check(m);
	BOOST_TEST(eq1);


	auto double_m = ref_double;
	auto int_m = std::move(double_m).
		as_raw_matrix< int, 0, 2 >().
		as_raw_matrix< int, 2, 0 >();

	auto eq2 = check(int_m);
	BOOST_TEST(eq2);
}

BOOST_AUTO_TEST_CASE(test_convert_0x2_to_0x0){
	auto m = ref_double.
		as_raw_matrix< int, 0, 2 >().
		as_raw_matrix< int, 0, 0 >();

	auto eq1 = check(m);
	BOOST_TEST(eq1);


	auto double_m = ref_double;
	auto int_m = std::move(double_m).
		as_raw_matrix< int, 0, 2 >().
		as_raw_matrix< int, 0, 0 >();

	auto eq2 = check(int_m);
	BOOST_TEST(eq2);
}


BOOST_AUTO_TEST_CASE(test_convert_2x0_to_2x2){
	auto m = ref_double.
		as_raw_matrix< int, 2, 0 >().
		as_raw_matrix< int, 2, 2 >();

	auto eq1 = check(m);
	BOOST_TEST(eq1);


	auto double_m = ref_double;
	auto int_m = std::move(double_m).
		as_raw_matrix< int, 2, 0 >().
		as_raw_matrix< int, 2, 2 >();

	auto eq2 = check(int_m);
	BOOST_TEST(eq2);
}

BOOST_AUTO_TEST_CASE(test_convert_2x0_to_0x2){
	auto m = ref_double.
		as_raw_matrix< int, 2, 0 >().
		as_raw_matrix< int, 0, 2 >();

	auto eq1 = check(m);
	BOOST_TEST(eq1);


	auto double_m = ref_double;
	auto int_m = std::move(double_m).
		as_raw_matrix< int, 2, 0 >().
		as_raw_matrix< int, 0, 2 >();

	auto eq2 = check(int_m);
	BOOST_TEST(eq2);
}

BOOST_AUTO_TEST_CASE(test_convert_2x0_to_2x0){
	auto m = ref_double.
		as_raw_matrix< int, 2, 0 >().
		as_raw_matrix< int, 2, 0 >();

	auto eq1 = check(m);
	BOOST_TEST(eq1);


	auto double_m = ref_double;
	auto int_m = std::move(double_m).
		as_raw_matrix< int, 2, 0 >().
		as_raw_matrix< int, 2, 0 >();

	auto eq2 = check(int_m);
	BOOST_TEST(eq2);
}

BOOST_AUTO_TEST_CASE(test_convert_2x0_to_0x0){
	auto m = ref_double.
		as_raw_matrix< int, 2, 0 >().
		as_raw_matrix< int, 0, 0 >();

	auto eq1 = check(m);
	BOOST_TEST(eq1);


	auto double_m = ref_double;
	auto int_m = std::move(double_m).
		as_raw_matrix< int, 2, 0 >().
		as_raw_matrix< int, 0, 0 >();

	auto eq2 = check(int_m);
	BOOST_TEST(eq2);
}


BOOST_AUTO_TEST_CASE(test_convert_0x0_to_2x2){
	auto m = ref_double.
		as_raw_matrix< int, 0, 0 >().
		as_raw_matrix< int, 2, 2 >();

	auto eq1 = check(m);
	BOOST_TEST(eq1);


	auto double_m = ref_double;
	auto int_m = std::move(double_m).
		as_raw_matrix< int, 0, 0 >().
		as_raw_matrix< int, 2, 2 >();

	auto eq2 = check(int_m);
	BOOST_TEST(eq2);
}

BOOST_AUTO_TEST_CASE(test_convert_0x0_to_0x2){
	auto m = ref_double.
		as_raw_matrix< int, 0, 0 >().
		as_raw_matrix< int, 0, 2 >();

	auto eq1 = check(m);
	BOOST_TEST(eq1);


	auto double_m = ref_double;
	auto int_m = std::move(double_m).
		as_raw_matrix< int, 0, 0 >().
		as_raw_matrix< int, 0, 2 >();

	auto eq2 = check(int_m);
	BOOST_TEST(eq2);
}

BOOST_AUTO_TEST_CASE(test_convert_0x0_to_2x0){
	auto m = ref_double.
		as_raw_matrix< int, 0, 0 >().
		as_raw_matrix< int, 2, 0 >();

	auto eq1 = check(m);
	BOOST_TEST(eq1);


	auto double_m = ref_double;
	auto int_m = std::move(double_m).
		as_raw_matrix< int, 0, 0 >().
		as_raw_matrix< int, 2, 0 >();

	auto eq2 = check(int_m);
	BOOST_TEST(eq2);
}

BOOST_AUTO_TEST_CASE(test_convert_0x0_to_0x0){
	auto m = ref_double.
		as_raw_matrix< int, 0, 0 >().
		as_raw_matrix< int, 0, 0 >();

	auto eq1 = check(m);
	BOOST_TEST(eq1);


	auto double_m = ref_double;
	auto int_m = std::move(double_m).
		as_raw_matrix< int, 0, 0 >().
		as_raw_matrix< int, 0, 0 >();

	auto eq2 = check(int_m);
	BOOST_TEST(eq2);
}
