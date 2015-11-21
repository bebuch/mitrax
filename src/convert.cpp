//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#include <boost/test/unit_test.hpp>

#include <mitrax/matrix.hpp>


using boost::typeindex::type_id;
using boost::typeindex::type_id_runtime;
using namespace mitrax;
using namespace mitrax::literals;


BOOST_AUTO_TEST_SUITE(test_suite_convert)


namespace{


	constexpr int data[2][2] = {{0, 1}, {2, 3}};

	constexpr double data_double[2][2] = {{0.5, 1.3}, {2.7, 3.3}};

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


BOOST_AUTO_TEST_CASE(test_convert_as_raw_matrix){
	constexpr auto m1 = make_matrix(2_C, 2_R, data);
	auto m2 = make_matrix(2_C_rt, 2_R, data);
	auto m3 = make_matrix(2_C, 2_R_rt, data);
	auto m4 = make_matrix(2_C_rt, 2_R_rt, data);
	auto m5 = m1;

	constexpr auto n1 = m1.as_raw_matrix();
	auto const n2 = m2.as_raw_matrix();
	auto const n3 = m3.as_raw_matrix();
	auto const n4 = m4.as_raw_matrix();

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	BOOST_TEST(type_id_runtime(n1) == (type_id< raw_matrix< int, 2, 2 > >()));
	BOOST_TEST(type_id_runtime(n2) == (type_id< raw_matrix< int, 0, 2 > >()));
	BOOST_TEST(type_id_runtime(n3) == (type_id< raw_matrix< int, 2, 0 > >()));
	BOOST_TEST(type_id_runtime(n4) == (type_id< raw_matrix< int, 0, 0 > >()));

	auto const o1 = m5.as_raw_matrix_by_move();
	auto const o2 = m2.as_raw_matrix_by_move();
	auto const o3 = m3.as_raw_matrix_by_move();
	auto const o4 = m4.as_raw_matrix_by_move();

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));

	BOOST_TEST(type_id_runtime(o1) == (type_id< raw_matrix< int, 2, 2 > >()));
	BOOST_TEST(type_id_runtime(o2) == (type_id< raw_matrix< int, 0, 2 > >()));
	BOOST_TEST(type_id_runtime(o3) == (type_id< raw_matrix< int, 2, 0 > >()));
	BOOST_TEST(type_id_runtime(o4) == (type_id< raw_matrix< int, 0, 0 > >()));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_type){
	constexpr auto m1 = make_matrix(2_C, 2_R, data_double);
	auto m2 = make_matrix(2_C_rt, 2_R, data_double);
	auto m3 = make_matrix(2_C, 2_R_rt, data_double);
	auto m4 = make_matrix(2_C_rt, 2_R_rt, data_double);
	auto m5 = m1;

	constexpr auto n1 = m1.convert< int >();
	auto const n2 = m2.convert< int >();
	auto const n3 = m3.convert< int >();
	auto const n4 = m4.convert< int >();

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	BOOST_TEST(type_id_runtime(n1) == (type_id< raw_matrix< int, 2, 2 > >()));
	BOOST_TEST(type_id_runtime(n2) == (type_id< raw_matrix< int, 0, 2 > >()));
	BOOST_TEST(type_id_runtime(n3) == (type_id< raw_matrix< int, 2, 0 > >()));
	BOOST_TEST(type_id_runtime(n4) == (type_id< raw_matrix< int, 0, 0 > >()));

	auto const o1 = m5.convert_by_move< int >();
	auto const o2 = m2.convert_by_move< int >();
	auto const o3 = m3.convert_by_move< int >();
	auto const o4 = m4.convert_by_move< int >();

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));

	BOOST_TEST(type_id_runtime(o1) == (type_id< raw_matrix< int, 2, 2 > >()));
	BOOST_TEST(type_id_runtime(o2) == (type_id< raw_matrix< int, 0, 2 > >()));
	BOOST_TEST(type_id_runtime(o3) == (type_id< raw_matrix< int, 2, 0 > >()));
	BOOST_TEST(type_id_runtime(o4) == (type_id< raw_matrix< int, 0, 0 > >()));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2x2){
	constexpr auto m1 = make_matrix(2_C, 2_R, data);
	auto m2 = make_matrix(2_C_rt, 2_R, data);
	auto m3 = make_matrix(2_C, 2_R_rt, data);
	auto m4 = make_matrix(2_C_rt, 2_R_rt, data);
	auto m5 = m1;

	constexpr auto n1 = m1.convert(2_C, 2_R);
	auto const n2 = m2.convert(2_C, 2_R);
	auto const n3 = m3.convert(2_C, 2_R);
	auto const n4 = m4.convert(2_C, 2_R);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	BOOST_TEST(type_id_runtime(n1) == (type_id< raw_matrix< int, 2, 2 > >()));
	BOOST_TEST(type_id_runtime(n2) == (type_id< raw_matrix< int, 2, 2 > >()));
	BOOST_TEST(type_id_runtime(n3) == (type_id< raw_matrix< int, 2, 2 > >()));
	BOOST_TEST(type_id_runtime(n4) == (type_id< raw_matrix< int, 2, 2 > >()));

	auto const o1 = m5.convert_by_move< int >(2_C, 2_R);
	auto const o2 = m2.convert_by_move< int >(2_C, 2_R);
	auto const o3 = m3.convert_by_move< int >(2_C, 2_R);
	auto const o4 = m4.convert_by_move< int >(2_C, 2_R);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));

	BOOST_TEST(type_id_runtime(o1) == (type_id< raw_matrix< int, 2, 2 > >()));
	BOOST_TEST(type_id_runtime(o2) == (type_id< raw_matrix< int, 2, 2 > >()));
	BOOST_TEST(type_id_runtime(o3) == (type_id< raw_matrix< int, 2, 2 > >()));
	BOOST_TEST(type_id_runtime(o4) == (type_id< raw_matrix< int, 2, 2 > >()));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2rtx2){
	auto m1 = make_matrix(2_C, 2_R, data);
	auto m2 = make_matrix(2_C_rt, 2_R, data);
	auto m3 = make_matrix(2_C, 2_R_rt, data);
	auto m4 = make_matrix(2_C_rt, 2_R_rt, data);

	auto const n1 = m1.convert(2_C_rt, 2_R);
	auto const n2 = m2.convert(2_C_rt, 2_R);
	auto const n3 = m3.convert(2_C_rt, 2_R);
	auto const n4 = m4.convert(2_C_rt, 2_R);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	BOOST_TEST(type_id_runtime(n1) == (type_id< raw_matrix< int, 0, 2 > >()));
	BOOST_TEST(type_id_runtime(n2) == (type_id< raw_matrix< int, 0, 2 > >()));
	BOOST_TEST(type_id_runtime(n3) == (type_id< raw_matrix< int, 0, 2 > >()));
	BOOST_TEST(type_id_runtime(n4) == (type_id< raw_matrix< int, 0, 2 > >()));

	auto const o1 = m1.convert_by_move< int >(2_C_rt, 2_R);
	auto const o2 = m2.convert_by_move< int >(2_C_rt, 2_R);
	auto const o3 = m3.convert_by_move< int >(2_C_rt, 2_R);
	auto const o4 = m4.convert_by_move< int >(2_C_rt, 2_R);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));

	BOOST_TEST(type_id_runtime(o1) == (type_id< raw_matrix< int, 0, 2 > >()));
	BOOST_TEST(type_id_runtime(o2) == (type_id< raw_matrix< int, 0, 2 > >()));
	BOOST_TEST(type_id_runtime(o3) == (type_id< raw_matrix< int, 0, 2 > >()));
	BOOST_TEST(type_id_runtime(o4) == (type_id< raw_matrix< int, 0, 2 > >()));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2x2rt){
	auto m1 = make_matrix(2_C, 2_R, data);
	auto m2 = make_matrix(2_C_rt, 2_R, data);
	auto m3 = make_matrix(2_C, 2_R_rt, data);
	auto m4 = make_matrix(2_C_rt, 2_R_rt, data);

	auto const n1 = m1.convert(2_C, 2_R_rt);
	auto const n2 = m2.convert(2_C, 2_R_rt);
	auto const n3 = m3.convert(2_C, 2_R_rt);
	auto const n4 = m4.convert(2_C, 2_R_rt);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	BOOST_TEST(type_id_runtime(n1) == (type_id< raw_matrix< int, 2, 0 > >()));
	BOOST_TEST(type_id_runtime(n2) == (type_id< raw_matrix< int, 2, 0 > >()));
	BOOST_TEST(type_id_runtime(n3) == (type_id< raw_matrix< int, 2, 0 > >()));
	BOOST_TEST(type_id_runtime(n4) == (type_id< raw_matrix< int, 2, 0 > >()));

	auto const o1 = m1.convert_by_move< int >(2_C, 2_R_rt);
	auto const o2 = m2.convert_by_move< int >(2_C, 2_R_rt);
	auto const o3 = m3.convert_by_move< int >(2_C, 2_R_rt);
	auto const o4 = m4.convert_by_move< int >(2_C, 2_R_rt);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));

	BOOST_TEST(type_id_runtime(o1) == (type_id< raw_matrix< int, 2, 0 > >()));
	BOOST_TEST(type_id_runtime(o2) == (type_id< raw_matrix< int, 2, 0 > >()));
	BOOST_TEST(type_id_runtime(o3) == (type_id< raw_matrix< int, 2, 0 > >()));
	BOOST_TEST(type_id_runtime(o4) == (type_id< raw_matrix< int, 2, 0 > >()));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2rtx2rt){
	auto m1 = make_matrix(2_C, 2_R, data);
	auto m2 = make_matrix(2_C_rt, 2_R, data);
	auto m3 = make_matrix(2_C, 2_R_rt, data);
	auto m4 = make_matrix(2_C_rt, 2_R_rt, data);

	auto const n1 = m1.convert(2_C_rt, 2_R_rt);
	auto const n2 = m2.convert(2_C_rt, 2_R_rt);
	auto const n3 = m3.convert(2_C_rt, 2_R_rt);
	auto const n4 = m4.convert(2_C_rt, 2_R_rt);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	BOOST_TEST(type_id_runtime(n1) == (type_id< raw_matrix< int, 0, 0 > >()));
	BOOST_TEST(type_id_runtime(n2) == (type_id< raw_matrix< int, 0, 0 > >()));
	BOOST_TEST(type_id_runtime(n3) == (type_id< raw_matrix< int, 0, 0 > >()));
	BOOST_TEST(type_id_runtime(n4) == (type_id< raw_matrix< int, 0, 0 > >()));

	auto const o1 = m1.convert_by_move< int >(2_C_rt, 2_R_rt);
	auto const o2 = m2.convert_by_move< int >(2_C_rt, 2_R_rt);
	auto const o3 = m3.convert_by_move< int >(2_C_rt, 2_R_rt);
	auto const o4 = m4.convert_by_move< int >(2_C_rt, 2_R_rt);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));

	BOOST_TEST(type_id_runtime(o1) == (type_id< raw_matrix< int, 0, 0 > >()));
	BOOST_TEST(type_id_runtime(o2) == (type_id< raw_matrix< int, 0, 0 > >()));
	BOOST_TEST(type_id_runtime(o3) == (type_id< raw_matrix< int, 0, 0 > >()));
	BOOST_TEST(type_id_runtime(o4) == (type_id< raw_matrix< int, 0, 0 > >()));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2x2_and_type){
	constexpr auto m1 = make_matrix(2_C, 2_R, data_double);
	auto m2 = make_matrix(2_C_rt, 2_R, data_double);
	auto m3 = make_matrix(2_C, 2_R_rt, data_double);
	auto m4 = make_matrix(2_C_rt, 2_R_rt, data_double);
	auto m5 = m1;

	constexpr auto n1 = m1.convert< int >(2_C, 2_R);
	auto const n2 = m2.convert< int >(2_C, 2_R);
	auto const n3 = m3.convert< int >(2_C, 2_R);
	auto const n4 = m4.convert< int >(2_C, 2_R);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	BOOST_TEST(type_id_runtime(n1) == (type_id< raw_matrix< int, 2, 2 > >()));
	BOOST_TEST(type_id_runtime(n2) == (type_id< raw_matrix< int, 2, 2 > >()));
	BOOST_TEST(type_id_runtime(n3) == (type_id< raw_matrix< int, 2, 2 > >()));
	BOOST_TEST(type_id_runtime(n4) == (type_id< raw_matrix< int, 2, 2 > >()));

	auto const o1 = m5.convert_by_move< int >(2_C, 2_R);
	auto const o2 = m2.convert_by_move< int >(2_C, 2_R);
	auto const o3 = m3.convert_by_move< int >(2_C, 2_R);
	auto const o4 = m4.convert_by_move< int >(2_C, 2_R);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));

	BOOST_TEST(type_id_runtime(o1) == (type_id< raw_matrix< int, 2, 2 > >()));
	BOOST_TEST(type_id_runtime(o2) == (type_id< raw_matrix< int, 2, 2 > >()));
	BOOST_TEST(type_id_runtime(o3) == (type_id< raw_matrix< int, 2, 2 > >()));
	BOOST_TEST(type_id_runtime(o4) == (type_id< raw_matrix< int, 2, 2 > >()));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2rtx2_and_type){
	auto m1 = make_matrix(2_C, 2_R, data_double);
	auto m2 = make_matrix(2_C_rt, 2_R, data_double);
	auto m3 = make_matrix(2_C, 2_R_rt, data_double);
	auto m4 = make_matrix(2_C_rt, 2_R_rt, data_double);

	auto const n1 = m1.convert< int >(2_C_rt, 2_R);
	auto const n2 = m2.convert< int >(2_C_rt, 2_R);
	auto const n3 = m3.convert< int >(2_C_rt, 2_R);
	auto const n4 = m4.convert< int >(2_C_rt, 2_R);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	BOOST_TEST(type_id_runtime(n1) == (type_id< raw_matrix< int, 0, 2 > >()));
	BOOST_TEST(type_id_runtime(n2) == (type_id< raw_matrix< int, 0, 2 > >()));
	BOOST_TEST(type_id_runtime(n3) == (type_id< raw_matrix< int, 0, 2 > >()));
	BOOST_TEST(type_id_runtime(n4) == (type_id< raw_matrix< int, 0, 2 > >()));

	auto const o1 = m1.convert_by_move< int >(2_C_rt, 2_R);
	auto const o2 = m2.convert_by_move< int >(2_C_rt, 2_R);
	auto const o3 = m3.convert_by_move< int >(2_C_rt, 2_R);
	auto const o4 = m4.convert_by_move< int >(2_C_rt, 2_R);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));

	BOOST_TEST(type_id_runtime(o1) == (type_id< raw_matrix< int, 0, 2 > >()));
	BOOST_TEST(type_id_runtime(o2) == (type_id< raw_matrix< int, 0, 2 > >()));
	BOOST_TEST(type_id_runtime(o3) == (type_id< raw_matrix< int, 0, 2 > >()));
	BOOST_TEST(type_id_runtime(o4) == (type_id< raw_matrix< int, 0, 2 > >()));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2x2rt_and_type){
	auto m1 = make_matrix(2_C, 2_R, data_double);
	auto m2 = make_matrix(2_C_rt, 2_R, data_double);
	auto m3 = make_matrix(2_C, 2_R_rt, data_double);
	auto m4 = make_matrix(2_C_rt, 2_R_rt, data_double);

	auto const n1 = m1.convert< int >(2_C, 2_R_rt);
	auto const n2 = m2.convert< int >(2_C, 2_R_rt);
	auto const n3 = m3.convert< int >(2_C, 2_R_rt);
	auto const n4 = m4.convert< int >(2_C, 2_R_rt);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	BOOST_TEST(type_id_runtime(n1) == (type_id< raw_matrix< int, 2, 0 > >()));
	BOOST_TEST(type_id_runtime(n2) == (type_id< raw_matrix< int, 2, 0 > >()));
	BOOST_TEST(type_id_runtime(n3) == (type_id< raw_matrix< int, 2, 0 > >()));
	BOOST_TEST(type_id_runtime(n4) == (type_id< raw_matrix< int, 2, 0 > >()));

	auto const o1 = m1.convert_by_move< int >(2_C, 2_R_rt);
	auto const o2 = m2.convert_by_move< int >(2_C, 2_R_rt);
	auto const o3 = m3.convert_by_move< int >(2_C, 2_R_rt);
	auto const o4 = m4.convert_by_move< int >(2_C, 2_R_rt);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));

	BOOST_TEST(type_id_runtime(o1) == (type_id< raw_matrix< int, 2, 0 > >()));
	BOOST_TEST(type_id_runtime(o2) == (type_id< raw_matrix< int, 2, 0 > >()));
	BOOST_TEST(type_id_runtime(o3) == (type_id< raw_matrix< int, 2, 0 > >()));
	BOOST_TEST(type_id_runtime(o4) == (type_id< raw_matrix< int, 2, 0 > >()));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2rtx2rt_and_type){
	auto m1 = make_matrix(2_C, 2_R, data_double);
	auto m2 = make_matrix(2_C_rt, 2_R, data_double);
	auto m3 = make_matrix(2_C, 2_R_rt, data_double);
	auto m4 = make_matrix(2_C_rt, 2_R_rt, data_double);

	auto const n1 = m1.convert< int >(2_C_rt, 2_R_rt);
	auto const n2 = m2.convert< int >(2_C_rt, 2_R_rt);
	auto const n3 = m3.convert< int >(2_C_rt, 2_R_rt);
	auto const n4 = m4.convert< int >(2_C_rt, 2_R_rt);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	BOOST_TEST(type_id_runtime(n1) == (type_id< raw_matrix< int, 0, 0 > >()));
	BOOST_TEST(type_id_runtime(n2) == (type_id< raw_matrix< int, 0, 0 > >()));
	BOOST_TEST(type_id_runtime(n3) == (type_id< raw_matrix< int, 0, 0 > >()));
	BOOST_TEST(type_id_runtime(n4) == (type_id< raw_matrix< int, 0, 0 > >()));

	auto const o1 = m1.convert_by_move< int >(2_C_rt, 2_R_rt);
	auto const o2 = m2.convert_by_move< int >(2_C_rt, 2_R_rt);
	auto const o3 = m3.convert_by_move< int >(2_C_rt, 2_R_rt);
	auto const o4 = m4.convert_by_move< int >(2_C_rt, 2_R_rt);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));

	BOOST_TEST(type_id_runtime(o1) == (type_id< raw_matrix< int, 0, 0 > >()));
	BOOST_TEST(type_id_runtime(o2) == (type_id< raw_matrix< int, 0, 0 > >()));
	BOOST_TEST(type_id_runtime(o3) == (type_id< raw_matrix< int, 0, 0 > >()));
	BOOST_TEST(type_id_runtime(o4) == (type_id< raw_matrix< int, 0, 0 > >()));
}


// BOOST_AUTO_TEST_CASE(test_convert_convert_to_2x2_and_type_to_ref){
// 	auto m1 = make_matrix(2_C, 2_R, data);
// 	auto m2 = make_matrix(2_C_rt, 2_R, data);
// 	auto m3 = make_matrix(2_C, 2_R_rt, data);
// 	auto m4 = make_matrix(2_C_rt, 2_R_rt, data);
// 
// 	auto const n1 = m1.convert< std::reference_wrapper< int > >(2_C, 2_R);
// 	auto const n2 = m2.convert< std::reference_wrapper< int > >(2_C, 2_R);
// 	auto const n3 = m3.convert< std::reference_wrapper< int > >(2_C, 2_R);
// 	auto const n4 = m4.convert< std::reference_wrapper< int > >(2_C, 2_R);
// 
// 	BOOST_TEST(check(n1));
// 	BOOST_TEST(check(n2));
// 	BOOST_TEST(check(n3));
// 	BOOST_TEST(check(n4));
// 
// 	auto const o1 = std::move(m1).convert< int >(2_C, 2_R);
// 	auto const o2 = std::move(m2).convert< int >(2_C, 2_R);
// 	auto const o3 = std::move(m3).convert< int >(2_C, 2_R);
// 	auto const o4 = std::move(m4).convert< int >(2_C, 2_R);
// 
// 	BOOST_TEST(check(o1));
// 	BOOST_TEST(check(o2));
// 	BOOST_TEST(check(o3));
// 	BOOST_TEST(check(o4));
// }

/*
BOOST_AUTO_TEST_CASE(test_convert_convert_to_2rtx2_and_type_to_ref){
	auto const m1 = make_matrix(2_C, 2_R, data);
	auto const m2 = make_matrix(2_C_rt, 2_R, data);
	auto const m3 = make_matrix(2_C, 2_R_rt, data);
	auto const m4 = make_matrix(2_C_rt, 2_R_rt, data);

	auto const n1 = m1.convert< int >(2_C_rt, 2_R);
	auto const n2 = m2.convert< int >(2_C_rt, 2_R);
	auto const n3 = m3.convert< int >(2_C_rt, 2_R);
	auto const n4 = m4.convert< int >(2_C_rt, 2_R);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	auto const o1 = std::move(m1).convert< int >(2_C_rt, 2_R);
	auto const o2 = std::move(m2).convert< int >(2_C_rt, 2_R);
	auto const o3 = std::move(m3).convert< int >(2_C_rt, 2_R);
	auto const o4 = std::move(m4).convert< int >(2_C_rt, 2_R);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2x2rt_and_type_to_ref){
	auto const m1 = make_matrix(2_C, 2_R, data);
	auto const m2 = make_matrix(2_C_rt, 2_R, data);
	auto const m3 = make_matrix(2_C, 2_R_rt, data);
	auto const m4 = make_matrix(2_C_rt, 2_R_rt, data);

	auto const n1 = m1.convert< int >(2_C, 2_R_rt);
	auto const n2 = m2.convert< int >(2_C, 2_R_rt);
	auto const n3 = m3.convert< int >(2_C, 2_R_rt);
	auto const n4 = m4.convert< int >(2_C, 2_R_rt);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	auto const o1 = std::move(m1).convert< int >(2_C, 2_R_rt);
	auto const o2 = std::move(m2).convert< int >(2_C, 2_R_rt);
	auto const o3 = std::move(m3).convert< int >(2_C, 2_R_rt);
	auto const o4 = std::move(m4).convert< int >(2_C, 2_R_rt);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2rtx2rt_and_type_to_ref){
	auto const m1 = make_matrix(2_C, 2_R, data);
	auto const m2 = make_matrix(2_C_rt, 2_R, data);
	auto const m3 = make_matrix(2_C, 2_R_rt, data);
	auto const m4 = make_matrix(2_C_rt, 2_R_rt, data);

	auto const n1 = m1.convert< int >(2_C_rt, 2_R_rt);
	auto const n2 = m2.convert< int >(2_C_rt, 2_R_rt);
	auto const n3 = m3.convert< int >(2_C_rt, 2_R_rt);
	auto const n4 = m4.convert< int >(2_C_rt, 2_R_rt);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	auto const o1 = std::move(m1).convert< int >(2_C_rt, 2_R_rt);
	auto const o2 = std::move(m2).convert< int >(2_C_rt, 2_R_rt);
	auto const o3 = std::move(m3).convert< int >(2_C_rt, 2_R_rt);
	auto const o4 = std::move(m4).convert< int >(2_C_rt, 2_R_rt);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));
}*/


BOOST_AUTO_TEST_SUITE_END()
