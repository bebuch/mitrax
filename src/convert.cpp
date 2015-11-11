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
using namespace mitrax::literals;


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


// TODO: check also for result types


BOOST_AUTO_TEST_CASE(test_convert_as_raw_matrix){
	constexpr auto m1 = make_matrix(2_C, 2_R, data);
	auto const m2 = make_matrix(2_C_rt, 2_R, data);
	auto const m3 = make_matrix(2_C, 2_R_rt, data);
	auto const m4 = make_matrix(2_C_rt, 2_R_rt, data);
	auto const m5 = m1;

	constexpr auto n1 = m1.as_raw_matrix();
	auto const n2 = m2.as_raw_matrix();
	auto const n3 = m3.as_raw_matrix();
	auto const n4 = m4.as_raw_matrix();

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	auto const o1 = std::move(m5).as_raw_matrix();
	auto const o2 = std::move(m2).as_raw_matrix();
	auto const o3 = std::move(m3).as_raw_matrix();
	auto const o4 = std::move(m4).as_raw_matrix();

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_type){
	constexpr auto m1 = make_matrix(2_C, 2_R, data_double);
	auto const m2 = make_matrix(2_C_rt, 2_R, data_double);
	auto const m3 = make_matrix(2_C, 2_R_rt, data_double);
	auto const m4 = make_matrix(2_C_rt, 2_R_rt, data_double);
	auto const m5 = m1;

	constexpr auto n1 = m1.convert< int >();
	auto const n2 = m2.convert< int >();
	auto const n3 = m3.convert< int >();
	auto const n4 = m4.convert< int >();

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	auto const o1 = std::move(m5).convert< int >();
	auto const o2 = std::move(m2).convert< int >();
	auto const o3 = std::move(m3).convert< int >();
	auto const o4 = std::move(m4).convert< int >();

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2x2){
	constexpr auto m1 = make_matrix(2_C, 2_R, data);
	auto const m2 = make_matrix(2_C_rt, 2_R, data);
	auto const m3 = make_matrix(2_C, 2_R_rt, data);
	auto const m4 = make_matrix(2_C_rt, 2_R_rt, data);
	auto const m5 = m1;

	constexpr auto n1 = m1.convert(2_C, 2_R);
	auto const n2 = m2.convert(2_C, 2_R);
	auto const n3 = m3.convert(2_C, 2_R);
	auto const n4 = m4.convert(2_C, 2_R);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	auto const o1 = std::move(m5).convert(2_C, 2_R);
	auto const o2 = std::move(m2).convert(2_C, 2_R);
	auto const o3 = std::move(m3).convert(2_C, 2_R);
	auto const o4 = std::move(m4).convert(2_C, 2_R);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2rtx2){
	auto const m1 = make_matrix(2_C, 2_R, data);
	auto const m2 = make_matrix(2_C_rt, 2_R, data);
	auto const m3 = make_matrix(2_C, 2_R_rt, data);
	auto const m4 = make_matrix(2_C_rt, 2_R_rt, data);

	auto const n1 = m1.convert(2_C_rt, 2_R);
	auto const n2 = m2.convert(2_C_rt, 2_R);
	auto const n3 = m3.convert(2_C_rt, 2_R);
	auto const n4 = m4.convert(2_C_rt, 2_R);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	auto const o1 = std::move(m1).convert(2_C_rt, 2_R);
	auto const o2 = std::move(m2).convert(2_C_rt, 2_R);
	auto const o3 = std::move(m3).convert(2_C_rt, 2_R);
	auto const o4 = std::move(m4).convert(2_C_rt, 2_R);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2x2rt){
	auto const m1 = make_matrix(2_C, 2_R, data);
	auto const m2 = make_matrix(2_C_rt, 2_R, data);
	auto const m3 = make_matrix(2_C, 2_R_rt, data);
	auto const m4 = make_matrix(2_C_rt, 2_R_rt, data);

	auto const n1 = m1.convert(2_C, 2_R_rt);
	auto const n2 = m2.convert(2_C, 2_R_rt);
	auto const n3 = m3.convert(2_C, 2_R_rt);
	auto const n4 = m4.convert(2_C, 2_R_rt);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	auto const o1 = std::move(m1).convert(2_C, 2_R_rt);
	auto const o2 = std::move(m2).convert(2_C, 2_R_rt);
	auto const o3 = std::move(m3).convert(2_C, 2_R_rt);
	auto const o4 = std::move(m4).convert(2_C, 2_R_rt);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2rtx2rt){
	auto const m1 = make_matrix(2_C, 2_R, data);
	auto const m2 = make_matrix(2_C_rt, 2_R, data);
	auto const m3 = make_matrix(2_C, 2_R_rt, data);
	auto const m4 = make_matrix(2_C_rt, 2_R_rt, data);

	auto const n1 = m1.convert(2_C_rt, 2_R_rt);
	auto const n2 = m2.convert(2_C_rt, 2_R_rt);
	auto const n3 = m3.convert(2_C_rt, 2_R_rt);
	auto const n4 = m4.convert(2_C_rt, 2_R_rt);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	auto const o1 = std::move(m1).convert(2_C_rt, 2_R_rt);
	auto const o2 = std::move(m2).convert(2_C_rt, 2_R_rt);
	auto const o3 = std::move(m3).convert(2_C_rt, 2_R_rt);
	auto const o4 = std::move(m4).convert(2_C_rt, 2_R_rt);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2x2_and_type){
	constexpr auto m1 = make_matrix(2_C, 2_R, data_double);
	auto const m2 = make_matrix(2_C_rt, 2_R, data_double);
	auto const m3 = make_matrix(2_C, 2_R_rt, data_double);
	auto const m4 = make_matrix(2_C_rt, 2_R_rt, data_double);
	auto const m5 = m1;

	constexpr auto n1 = m1.convert< int >(2_C, 2_R);
	auto const n2 = m2.convert< int >(2_C, 2_R);
	auto const n3 = m3.convert< int >(2_C, 2_R);
	auto const n4 = m4.convert< int >(2_C, 2_R);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	auto const o1 = std::move(m5).convert< int >(2_C, 2_R);
	auto const o2 = std::move(m2).convert< int >(2_C, 2_R);
	auto const o3 = std::move(m3).convert< int >(2_C, 2_R);
	auto const o4 = std::move(m4).convert< int >(2_C, 2_R);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2rtx2_and_type){
	auto const m1 = make_matrix(2_C, 2_R, data_double);
	auto const m2 = make_matrix(2_C_rt, 2_R, data_double);
	auto const m3 = make_matrix(2_C, 2_R_rt, data_double);
	auto const m4 = make_matrix(2_C_rt, 2_R_rt, data_double);

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


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2x2rt_and_type){
	auto const m1 = make_matrix(2_C, 2_R, data_double);
	auto const m2 = make_matrix(2_C_rt, 2_R, data_double);
	auto const m3 = make_matrix(2_C, 2_R_rt, data_double);
	auto const m4 = make_matrix(2_C_rt, 2_R_rt, data_double);

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


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2rtx2rt_and_type){
	auto const m1 = make_matrix(2_C, 2_R, data_double);
	auto const m2 = make_matrix(2_C_rt, 2_R, data_double);
	auto const m3 = make_matrix(2_C, 2_R_rt, data_double);
	auto const m4 = make_matrix(2_C_rt, 2_R_rt, data_double);

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
}

