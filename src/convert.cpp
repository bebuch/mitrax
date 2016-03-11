//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#include <boost/test/unit_test.hpp>

#include <mitrax/convert.hpp>


using boost::typeindex::type_id;
using boost::typeindex::type_id_runtime;
using namespace mitrax;
using namespace mitrax::literals;


BOOST_AUTO_TEST_SUITE(test_suite_convert)


namespace{


	constexpr int data[2][2] = {{0, 1}, {2, 3}};

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


	using int_ref = std::reference_wrapper< int >;

	using cint_ref = std::reference_wrapper< int const >;


	template < typename T >
	auto rt_id(T&& v){
		return type_id_runtime(static_cast< T&& >(v));
	}

	template < typename T >
	auto const id = type_id< T >();


}


BOOST_AUTO_TEST_CASE(test_convert_as_raw_matrix){
	constexpr auto m1 = make_matrix(2_C, 2_R, data);
	auto m2 = make_matrix(2_C_rt, 2_R, data);
	auto m3 = make_matrix(2_C, 2_R_rt, data);
	auto m4 = make_matrix(2_C_rt, 2_R_rt, data);
	auto m5 = m1;

	constexpr auto n1 = as_raw_matrix(m1);
	auto const n2 = as_raw_matrix(m2);
	auto const n3 = as_raw_matrix(m3);
	auto const n4 = as_raw_matrix(m4);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	BOOST_TEST(rt_id(n1) == (id< raw_matrix< int, 2, 2 > >));
	BOOST_TEST(rt_id(n2) == (id< raw_matrix< int, 0, 2 > >));
	BOOST_TEST(rt_id(n3) == (id< raw_matrix< int, 2, 0 > >));
	BOOST_TEST(rt_id(n4) == (id< raw_matrix< int, 0, 0 > >));

	auto const o1 = as_raw_matrix(m5);
	auto const o2 = as_raw_matrix(m2);
	auto const o3 = as_raw_matrix(m3);
	auto const o4 = as_raw_matrix(m4);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));

	BOOST_TEST(rt_id(o1) == (id< raw_matrix< int, 2, 2 > >));
	BOOST_TEST(rt_id(o2) == (id< raw_matrix< int, 0, 2 > >));
	BOOST_TEST(rt_id(o3) == (id< raw_matrix< int, 2, 0 > >));
	BOOST_TEST(rt_id(o4) == (id< raw_matrix< int, 0, 0 > >));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_type){
	constexpr auto m1 = make_matrix(2_C, 2_R, data);
	auto m2 = make_matrix(2_C_rt, 2_R, data);
	auto m3 = make_matrix(2_C, 2_R_rt, data);
	auto m4 = make_matrix(2_C_rt, 2_R_rt, data);
	auto m5 = m1;

	constexpr auto n1 = convert< double >(m1);
	auto const n2 = convert< double >(m2);
	auto const n3 = convert< double >(m3);
	auto const n4 = convert< double >(m4);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	BOOST_TEST(rt_id(n1) == (id< raw_matrix< double, 2, 2 > >));
	BOOST_TEST(rt_id(n2) == (id< raw_matrix< double, 0, 2 > >));
	BOOST_TEST(rt_id(n3) == (id< raw_matrix< double, 2, 0 > >));
	BOOST_TEST(rt_id(n4) == (id< raw_matrix< double, 0, 0 > >));

	auto const o1 = convert< double >(m5);
	auto const o2 = convert< double >(m2);
	auto const o3 = convert< double >(m3);
	auto const o4 = convert< double >(m4);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));

	BOOST_TEST(rt_id(o1) == (id< raw_matrix< double, 2, 2 > >));
	BOOST_TEST(rt_id(o2) == (id< raw_matrix< double, 0, 2 > >));
	BOOST_TEST(rt_id(o3) == (id< raw_matrix< double, 2, 0 > >));
	BOOST_TEST(rt_id(o4) == (id< raw_matrix< double, 0, 0 > >));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2x2){
	constexpr auto m1 = make_matrix(2_C, 2_R, data);
	auto m2 = make_matrix(2_C_rt, 2_R, data);
	auto m3 = make_matrix(2_C, 2_R_rt, data);
	auto m4 = make_matrix(2_C_rt, 2_R_rt, data);
	auto m5 = m1;

	constexpr auto n1 = convert(m1, 2_C, 2_R);
	auto const n2 = convert(m2, 2_C, 2_R);
	auto const n3 = convert(m3, 2_C, 2_R);
	auto const n4 = convert(m4, 2_C, 2_R);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	BOOST_TEST(rt_id(n1) == (id< raw_matrix< int, 2, 2 > >));
	BOOST_TEST(rt_id(n2) == (id< raw_matrix< int, 2, 2 > >));
	BOOST_TEST(rt_id(n3) == (id< raw_matrix< int, 2, 2 > >));
	BOOST_TEST(rt_id(n4) == (id< raw_matrix< int, 2, 2 > >));

	auto const o1 = convert< int >(m5, 2_C, 2_R);
	auto const o2 = convert< int >(m2, 2_C, 2_R);
	auto const o3 = convert< int >(m3, 2_C, 2_R);
	auto const o4 = convert< int >(m4, 2_C, 2_R);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));

	BOOST_TEST(rt_id(o1) == (id< raw_matrix< int, 2, 2 > >));
	BOOST_TEST(rt_id(o2) == (id< raw_matrix< int, 2, 2 > >));
	BOOST_TEST(rt_id(o3) == (id< raw_matrix< int, 2, 2 > >));
	BOOST_TEST(rt_id(o4) == (id< raw_matrix< int, 2, 2 > >));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2rtx2){
	auto m1 = make_matrix(2_C, 2_R, data);
	auto m2 = make_matrix(2_C_rt, 2_R, data);
	auto m3 = make_matrix(2_C, 2_R_rt, data);
	auto m4 = make_matrix(2_C_rt, 2_R_rt, data);

	auto const n1 = convert(m1, 2_C_rt, 2_R);
	auto const n2 = convert(m2, 2_C_rt, 2_R);
	auto const n3 = convert(m3, 2_C_rt, 2_R);
	auto const n4 = convert(m4, 2_C_rt, 2_R);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	BOOST_TEST(rt_id(n1) == (id< raw_matrix< int, 0, 2 > >));
	BOOST_TEST(rt_id(n2) == (id< raw_matrix< int, 0, 2 > >));
	BOOST_TEST(rt_id(n3) == (id< raw_matrix< int, 0, 2 > >));
	BOOST_TEST(rt_id(n4) == (id< raw_matrix< int, 0, 2 > >));

	auto const o1 = convert< int >(m1, 2_C_rt, 2_R);
	auto const o2 = convert< int >(m2, 2_C_rt, 2_R);
	auto const o3 = convert< int >(m3, 2_C_rt, 2_R);
	auto const o4 = convert< int >(m4, 2_C_rt, 2_R);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));

	BOOST_TEST(rt_id(o1) == (id< raw_matrix< int, 0, 2 > >));
	BOOST_TEST(rt_id(o2) == (id< raw_matrix< int, 0, 2 > >));
	BOOST_TEST(rt_id(o3) == (id< raw_matrix< int, 0, 2 > >));
	BOOST_TEST(rt_id(o4) == (id< raw_matrix< int, 0, 2 > >));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2x2rt){
	auto m1 = make_matrix(2_C, 2_R, data);
	auto m2 = make_matrix(2_C_rt, 2_R, data);
	auto m3 = make_matrix(2_C, 2_R_rt, data);
	auto m4 = make_matrix(2_C_rt, 2_R_rt, data);

	auto const n1 = convert(m1, 2_C, 2_R_rt);
	auto const n2 = convert(m2, 2_C, 2_R_rt);
	auto const n3 = convert(m3, 2_C, 2_R_rt);
	auto const n4 = convert(m4, 2_C, 2_R_rt);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	BOOST_TEST(rt_id(n1) == (id< raw_matrix< int, 2, 0 > >));
	BOOST_TEST(rt_id(n2) == (id< raw_matrix< int, 2, 0 > >));
	BOOST_TEST(rt_id(n3) == (id< raw_matrix< int, 2, 0 > >));
	BOOST_TEST(rt_id(n4) == (id< raw_matrix< int, 2, 0 > >));

	auto const o1 = convert< int >(m1, 2_C, 2_R_rt);
	auto const o2 = convert< int >(m2, 2_C, 2_R_rt);
	auto const o3 = convert< int >(m3, 2_C, 2_R_rt);
	auto const o4 = convert< int >(m4, 2_C, 2_R_rt);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));

	BOOST_TEST(rt_id(o1) == (id< raw_matrix< int, 2, 0 > >));
	BOOST_TEST(rt_id(o2) == (id< raw_matrix< int, 2, 0 > >));
	BOOST_TEST(rt_id(o3) == (id< raw_matrix< int, 2, 0 > >));
	BOOST_TEST(rt_id(o4) == (id< raw_matrix< int, 2, 0 > >));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2rtx2rt){
	auto m1 = make_matrix(2_C, 2_R, data);
	auto m2 = make_matrix(2_C_rt, 2_R, data);
	auto m3 = make_matrix(2_C, 2_R_rt, data);
	auto m4 = make_matrix(2_C_rt, 2_R_rt, data);

	auto const n1 = convert(m1, 2_C_rt, 2_R_rt);
	auto const n2 = convert(m2, 2_C_rt, 2_R_rt);
	auto const n3 = convert(m3, 2_C_rt, 2_R_rt);
	auto const n4 = convert(m4, 2_C_rt, 2_R_rt);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	BOOST_TEST(rt_id(n1) == (id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST(rt_id(n2) == (id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST(rt_id(n3) == (id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST(rt_id(n4) == (id< raw_matrix< int, 0, 0 > >));

	auto const o1 = convert< int >(m1, 2_C_rt, 2_R_rt);
	auto const o2 = convert< int >(m2, 2_C_rt, 2_R_rt);
	auto const o3 = convert< int >(m3, 2_C_rt, 2_R_rt);
	auto const o4 = convert< int >(m4, 2_C_rt, 2_R_rt);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));

	BOOST_TEST(rt_id(o1) == (id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST(rt_id(o2) == (id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST(rt_id(o3) == (id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST(rt_id(o4) == (id< raw_matrix< int, 0, 0 > >));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2x2_and_type){
	constexpr auto m1 = make_matrix(2_C, 2_R, data);
	auto m2 = make_matrix(2_C_rt, 2_R, data);
	auto m3 = make_matrix(2_C, 2_R_rt, data);
	auto m4 = make_matrix(2_C_rt, 2_R_rt, data);
	auto m5 = m1;

	constexpr auto n1 = convert< double >(m1, 2_C, 2_R);
	auto const n2 = convert< double >(m2, 2_C, 2_R);
	auto const n3 = convert< double >(m3, 2_C, 2_R);
	auto const n4 = convert< double >(m4, 2_C, 2_R);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	BOOST_TEST(rt_id(n1) == (id< raw_matrix< double, 2, 2 > >));
	BOOST_TEST(rt_id(n2) == (id< raw_matrix< double, 2, 2 > >));
	BOOST_TEST(rt_id(n3) == (id< raw_matrix< double, 2, 2 > >));
	BOOST_TEST(rt_id(n4) == (id< raw_matrix< double, 2, 2 > >));

	auto const o1 = convert< double >(m5, 2_C, 2_R);
	auto const o2 = convert< double >(m2, 2_C, 2_R);
	auto const o3 = convert< double >(m3, 2_C, 2_R);
	auto const o4 = convert< double >(m4, 2_C, 2_R);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));

	BOOST_TEST(rt_id(o1) == (id< raw_matrix< double, 2, 2 > >));
	BOOST_TEST(rt_id(o2) == (id< raw_matrix< double, 2, 2 > >));
	BOOST_TEST(rt_id(o3) == (id< raw_matrix< double, 2, 2 > >));
	BOOST_TEST(rt_id(o4) == (id< raw_matrix< double, 2, 2 > >));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2rtx2_and_type){
	auto m1 = make_matrix(2_C, 2_R, data);
	auto m2 = make_matrix(2_C_rt, 2_R, data);
	auto m3 = make_matrix(2_C, 2_R_rt, data);
	auto m4 = make_matrix(2_C_rt, 2_R_rt, data);

	auto const n1 = convert< double >(m1, 2_C_rt, 2_R);
	auto const n2 = convert< double >(m2, 2_C_rt, 2_R);
	auto const n3 = convert< double >(m3, 2_C_rt, 2_R);
	auto const n4 = convert< double >(m4, 2_C_rt, 2_R);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	BOOST_TEST(rt_id(n1) == (id< raw_matrix< double, 0, 2 > >));
	BOOST_TEST(rt_id(n2) == (id< raw_matrix< double, 0, 2 > >));
	BOOST_TEST(rt_id(n3) == (id< raw_matrix< double, 0, 2 > >));
	BOOST_TEST(rt_id(n4) == (id< raw_matrix< double, 0, 2 > >));

	auto const o1 = convert< double >(m1, 2_C_rt, 2_R);
	auto const o2 = convert< double >(m2, 2_C_rt, 2_R);
	auto const o3 = convert< double >(m3, 2_C_rt, 2_R);
	auto const o4 = convert< double >(m4, 2_C_rt, 2_R);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));

	BOOST_TEST(rt_id(o1) == (id< raw_matrix< double, 0, 2 > >));
	BOOST_TEST(rt_id(o2) == (id< raw_matrix< double, 0, 2 > >));
	BOOST_TEST(rt_id(o3) == (id< raw_matrix< double, 0, 2 > >));
	BOOST_TEST(rt_id(o4) == (id< raw_matrix< double, 0, 2 > >));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2x2rt_and_type){
	auto m1 = make_matrix(2_C, 2_R, data);
	auto m2 = make_matrix(2_C_rt, 2_R, data);
	auto m3 = make_matrix(2_C, 2_R_rt, data);
	auto m4 = make_matrix(2_C_rt, 2_R_rt, data);

	auto const n1 = convert< double >(m1, 2_C, 2_R_rt);
	auto const n2 = convert< double >(m2, 2_C, 2_R_rt);
	auto const n3 = convert< double >(m3, 2_C, 2_R_rt);
	auto const n4 = convert< double >(m4, 2_C, 2_R_rt);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	BOOST_TEST(rt_id(n1) == (id< raw_matrix< double, 2, 0 > >));
	BOOST_TEST(rt_id(n2) == (id< raw_matrix< double, 2, 0 > >));
	BOOST_TEST(rt_id(n3) == (id< raw_matrix< double, 2, 0 > >));
	BOOST_TEST(rt_id(n4) == (id< raw_matrix< double, 2, 0 > >));

	auto const o1 = convert< double >(m1, 2_C, 2_R_rt);
	auto const o2 = convert< double >(m2, 2_C, 2_R_rt);
	auto const o3 = convert< double >(m3, 2_C, 2_R_rt);
	auto const o4 = convert< double >(m4, 2_C, 2_R_rt);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));

	BOOST_TEST(rt_id(o1) == (id< raw_matrix< double, 2, 0 > >));
	BOOST_TEST(rt_id(o2) == (id< raw_matrix< double, 2, 0 > >));
	BOOST_TEST(rt_id(o3) == (id< raw_matrix< double, 2, 0 > >));
	BOOST_TEST(rt_id(o4) == (id< raw_matrix< double, 2, 0 > >));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2rtx2rt_and_type){
	auto m1 = make_matrix(2_C, 2_R, data);
	auto m2 = make_matrix(2_C_rt, 2_R, data);
	auto m3 = make_matrix(2_C, 2_R_rt, data);
	auto m4 = make_matrix(2_C_rt, 2_R_rt, data);

	auto const n1 = convert< double >(m1, 2_C_rt, 2_R_rt);
	auto const n2 = convert< double >(m2, 2_C_rt, 2_R_rt);
	auto const n3 = convert< double >(m3, 2_C_rt, 2_R_rt);
	auto const n4 = convert< double >(m4, 2_C_rt, 2_R_rt);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	BOOST_TEST(rt_id(n1) == (id< raw_matrix< double, 0, 0 > >));
	BOOST_TEST(rt_id(n2) == (id< raw_matrix< double, 0, 0 > >));
	BOOST_TEST(rt_id(n3) == (id< raw_matrix< double, 0, 0 > >));
	BOOST_TEST(rt_id(n4) == (id< raw_matrix< double, 0, 0 > >));

	auto const o1 = convert< double >(m1, 2_C_rt, 2_R_rt);
	auto const o2 = convert< double >(m2, 2_C_rt, 2_R_rt);
	auto const o3 = convert< double >(m3, 2_C_rt, 2_R_rt);
	auto const o4 = convert< double >(m4, 2_C_rt, 2_R_rt);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));

	BOOST_TEST(rt_id(o1) == (id< raw_matrix< double, 0, 0 > >));
	BOOST_TEST(rt_id(o2) == (id< raw_matrix< double, 0, 0 > >));
	BOOST_TEST(rt_id(o3) == (id< raw_matrix< double, 0, 0 > >));
	BOOST_TEST(rt_id(o4) == (id< raw_matrix< double, 0, 0 > >));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2x2_and_type_to_ref){
	auto m1 = make_matrix(2_C, 2_R, data);
	auto m2 = make_matrix(2_C_rt, 2_R, data);
	auto m3 = make_matrix(2_C, 2_R_rt, data);
	auto m4 = make_matrix(2_C_rt, 2_R_rt, data);

	auto const n1 = convert< int_ref >(m1, 2_C, 2_R);
	auto const n2 = convert< int_ref >(m2, 2_C, 2_R);
	auto const n3 = convert< int_ref >(m3, 2_C, 2_R);
	auto const n4 = convert< int_ref >(m4, 2_C, 2_R);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	BOOST_TEST(rt_id(n1) == (id< raw_matrix< int_ref, 2, 2 > >));
	BOOST_TEST(rt_id(n2) == (id< raw_matrix< int_ref, 2, 2 > >));
	BOOST_TEST(rt_id(n3) == (id< raw_matrix< int_ref, 2, 2 > >));
	BOOST_TEST(rt_id(n4) == (id< raw_matrix< int_ref, 2, 2 > >));

	auto const o1 = convert< cint_ref >(m1, 2_C, 2_R);
	auto const o2 = convert< cint_ref >(m2, 2_C, 2_R);
	auto const o3 = convert< cint_ref >(m3, 2_C, 2_R);
	auto const o4 = convert< cint_ref >(m4, 2_C, 2_R);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));

	BOOST_TEST(rt_id(o1) == (id< raw_matrix< cint_ref, 2, 2 > >));
	BOOST_TEST(rt_id(o2) == (id< raw_matrix< cint_ref, 2, 2 > >));
	BOOST_TEST(rt_id(o3) == (id< raw_matrix< cint_ref, 2, 2 > >));
	BOOST_TEST(rt_id(o4) == (id< raw_matrix< cint_ref, 2, 2 > >));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2rtx2_and_type_to_ref){
	auto m1 = make_matrix(2_C, 2_R, data);
	auto m2 = make_matrix(2_C_rt, 2_R, data);
	auto m3 = make_matrix(2_C, 2_R_rt, data);
	auto m4 = make_matrix(2_C_rt, 2_R_rt, data);

	auto const n1 = convert< int_ref >(m1, 2_C_rt, 2_R);
	auto const n2 = convert< int_ref >(m2, 2_C_rt, 2_R);
	auto const n3 = convert< int_ref >(m3, 2_C_rt, 2_R);
	auto const n4 = convert< int_ref >(m4, 2_C_rt, 2_R);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	BOOST_TEST(rt_id(n1) == (id< raw_matrix< int_ref, 0, 2 > >));
	BOOST_TEST(rt_id(n2) == (id< raw_matrix< int_ref, 0, 2 > >));
	BOOST_TEST(rt_id(n3) == (id< raw_matrix< int_ref, 0, 2 > >));
	BOOST_TEST(rt_id(n4) == (id< raw_matrix< int_ref, 0, 2 > >));

	auto const o1 = convert< cint_ref >(m1, 2_C_rt, 2_R);
	auto const o2 = convert< cint_ref >(m2, 2_C_rt, 2_R);
	auto const o3 = convert< cint_ref >(m3, 2_C_rt, 2_R);
	auto const o4 = convert< cint_ref >(m4, 2_C_rt, 2_R);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));

	BOOST_TEST(rt_id(o1) == (id< raw_matrix< cint_ref, 0, 2 > >));
	BOOST_TEST(rt_id(o2) == (id< raw_matrix< cint_ref, 0, 2 > >));
	BOOST_TEST(rt_id(o3) == (id< raw_matrix< cint_ref, 0, 2 > >));
	BOOST_TEST(rt_id(o4) == (id< raw_matrix< cint_ref, 0, 2 > >));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2x2rt_and_type_to_ref){
	auto m1 = make_matrix(2_C, 2_R, data);
	auto m2 = make_matrix(2_C_rt, 2_R, data);
	auto m3 = make_matrix(2_C, 2_R_rt, data);
	auto m4 = make_matrix(2_C_rt, 2_R_rt, data);

	auto const n1 = convert< int_ref >(m1, 2_C, 2_R_rt);
	auto const n2 = convert< int_ref >(m2, 2_C, 2_R_rt);
	auto const n3 = convert< int_ref >(m3, 2_C, 2_R_rt);
	auto const n4 = convert< int_ref >(m4, 2_C, 2_R_rt);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	BOOST_TEST(rt_id(n1) == (id< raw_matrix< int_ref, 2, 0 > >));
	BOOST_TEST(rt_id(n2) == (id< raw_matrix< int_ref, 2, 0 > >));
	BOOST_TEST(rt_id(n3) == (id< raw_matrix< int_ref, 2, 0 > >));
	BOOST_TEST(rt_id(n4) == (id< raw_matrix< int_ref, 2, 0 > >));

	auto const o1 = convert< cint_ref >(m1, 2_C, 2_R_rt);
	auto const o2 = convert< cint_ref >(m2, 2_C, 2_R_rt);
	auto const o3 = convert< cint_ref >(m3, 2_C, 2_R_rt);
	auto const o4 = convert< cint_ref >(m4, 2_C, 2_R_rt);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));

	BOOST_TEST(rt_id(o1) == (id< raw_matrix< cint_ref, 2, 0 > >));
	BOOST_TEST(rt_id(o2) == (id< raw_matrix< cint_ref, 2, 0 > >));
	BOOST_TEST(rt_id(o3) == (id< raw_matrix< cint_ref, 2, 0 > >));
	BOOST_TEST(rt_id(o4) == (id< raw_matrix< cint_ref, 2, 0 > >));
}


BOOST_AUTO_TEST_CASE(test_convert_convert_to_2rtx2rt_and_type_to_ref){
	auto m1 = make_matrix(2_C, 2_R, data);
	auto m2 = make_matrix(2_C_rt, 2_R, data);
	auto m3 = make_matrix(2_C, 2_R_rt, data);
	auto m4 = make_matrix(2_C_rt, 2_R_rt, data);

	auto const n1 = convert< int_ref >(m1, 2_C_rt, 2_R_rt);
	auto const n2 = convert< int_ref >(m2, 2_C_rt, 2_R_rt);
	auto const n3 = convert< int_ref >(m3, 2_C_rt, 2_R_rt);
	auto const n4 = convert< int_ref >(m4, 2_C_rt, 2_R_rt);

	BOOST_TEST(check(n1));
	BOOST_TEST(check(n2));
	BOOST_TEST(check(n3));
	BOOST_TEST(check(n4));

	BOOST_TEST(rt_id(n1) == (id< raw_matrix< int_ref, 0, 0 > >));
	BOOST_TEST(rt_id(n2) == (id< raw_matrix< int_ref, 0, 0 > >));
	BOOST_TEST(rt_id(n3) == (id< raw_matrix< int_ref, 0, 0 > >));
	BOOST_TEST(rt_id(n4) == (id< raw_matrix< int_ref, 0, 0 > >));

	auto const o1 = convert< cint_ref >(m1, 2_C_rt, 2_R_rt);
	auto const o2 = convert< cint_ref >(m2, 2_C_rt, 2_R_rt);
	auto const o3 = convert< cint_ref >(m3, 2_C_rt, 2_R_rt);
	auto const o4 = convert< cint_ref >(m4, 2_C_rt, 2_R_rt);

	BOOST_TEST(check(o1));
	BOOST_TEST(check(o2));
	BOOST_TEST(check(o3));
	BOOST_TEST(check(o4));

	BOOST_TEST(rt_id(o1) == (id< raw_matrix< cint_ref, 0, 0 > >));
	BOOST_TEST(rt_id(o2) == (id< raw_matrix< cint_ref, 0, 0 > >));
	BOOST_TEST(rt_id(o3) == (id< raw_matrix< cint_ref, 0, 0 > >));
	BOOST_TEST(rt_id(o4) == (id< raw_matrix< cint_ref, 0, 0 > >));
}


BOOST_AUTO_TEST_SUITE_END()
