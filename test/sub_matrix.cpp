//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#define BOOST_TEST_MODULE mitrax sub_matrix
#include <boost/test/unit_test.hpp>

#include <mitrax/sub_matrix.hpp>


using namespace mitrax;
using namespace mitrax::literals;


template < typename T >
auto rt_id(T&& v){
	return boost::typeindex::type_id_runtime(static_cast< T&& >(v));
}

template < typename T >
auto const id = boost::typeindex::type_id< T >();


using point_t = point< size_t >;


constexpr int org[3][3] = {
	{0, 1, 2},
	{3, 4, 5},
	{6, 7, 8}
};


constexpr auto m(){
	return make_matrix(3_C, 3_R, org);
}


template < typename M >
constexpr bool check1(M const& m){
	return
		m.cols() == 2 &&
		m.rows() == 2 &&
		m(0, 0) == 0 &&
		m(1, 0) == 1 &&
		m(0, 1) == 3 &&
		m(1, 1) == 4;
}

template < typename M >
constexpr bool check2(M const& m){
	return
		m.cols() == 2 &&
		m.rows() == 2 &&
		m(0, 0) == 1 &&
		m(1, 0) == 2 &&
		m(0, 1) == 4 &&
		m(1, 1) == 5;
}

template < typename M >
constexpr bool check3(M const& m){
	return
		m.cols() == 2 &&
		m.rows() == 2 &&
		m(0, 0) == 3 &&
		m(1, 0) == 4 &&
		m(0, 1) == 6 &&
		m(1, 1) == 7;
}

template < typename M >
constexpr bool check4(M const& m){
	return
		m.cols() == 2 &&
		m.rows() == 2 &&
		m(0, 0) == 4 &&
		m(1, 0) == 5 &&
		m(0, 1) == 7 &&
		m(1, 1) == 8;
}


// TODO: add more unit tests
// TODO: check also for result types
// TODO: check move version and const/non-const versions
// TODO: use non square matrices


BOOST_AUTO_TEST_SUITE(suite_sub_matrix)


BOOST_AUTO_TEST_CASE(test_sub_matrix_3x3){
	constexpr auto m = make_matrix(3_C, 3_R, org);

	constexpr auto sub1 = sub_matrix(m, 0, 0, 2_C, 2_R);
	auto type1 = id< std_matrix< int, 2, 2 > >;
	BOOST_TEST(rt_id(sub1) == type1);
	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, 2_Cd, 2_R)) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, 2_C, 2_Rd)) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, 2_Cd, 2_Rd)) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, 2_C, 2_R)));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, 2_C, 2_R)));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, 2_C, 2_R)));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, 2_C, 2_R)));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, 2_Cd, 2_R)));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, 2_Cd, 2_R)));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, 2_Cd, 2_R)));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, 2_Cd, 2_R)));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, 2_C, 2_Rd)));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, 2_C, 2_Rd)));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, 2_C, 2_Rd)));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, 2_C, 2_Rd)));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, 2_Cd, 2_Rd)));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, 2_Cd, 2_Rd)));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, 2_Cd, 2_Rd)));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, 2_Cd, 2_Rd)));


	constexpr auto sub2 = sub_matrix(m, 0, 0, dims(2_C, 2_R));
	auto type2 = id< std_matrix< int, 2, 2 > >;
	BOOST_TEST(rt_id(sub2) == type2);
	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, dims(2_Cd, 2_R))) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, dims(2_C, 2_Rd))) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, dims(2_Cd, 2_Rd))) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, dims(2_C, 2_R))));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, dims(2_C, 2_R))));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, dims(2_C, 2_R))));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, dims(2_C, 2_R))));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, dims(2_Cd, 2_R))));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, dims(2_Cd, 2_R))));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, dims(2_Cd, 2_R))));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, dims(2_Cd, 2_R))));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, dims(2_C, 2_Rd))));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, dims(2_C, 2_Rd))));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, dims(2_C, 2_Rd))));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, dims(2_C, 2_Rd))));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, dims(2_Cd, 2_Rd))));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, dims(2_Cd, 2_Rd))));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, dims(2_Cd, 2_Rd))));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, dims(2_Cd, 2_Rd))));

	constexpr auto sub3 = sub_matrix(m, point_t(0, 0), 2_C, 2_R);
	auto type3 = id< std_matrix< int, 2, 2 > >;
	BOOST_TEST(rt_id(sub3) == type3);
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), 2_Cd, 2_R)) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), 2_C, 2_Rd)) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), 2_Cd, 2_Rd)) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), 2_C, 2_R)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), 2_C, 2_R)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), 2_C, 2_R)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), 2_C, 2_R)));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), 2_Cd, 2_R)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), 2_Cd, 2_R)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), 2_Cd, 2_R)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), 2_Cd, 2_R)));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), 2_C, 2_Rd)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), 2_C, 2_Rd)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), 2_C, 2_Rd)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), 2_C, 2_Rd)));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), 2_Cd, 2_Rd)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), 2_Cd, 2_Rd)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), 2_Cd, 2_Rd)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), 2_Cd, 2_Rd)));


	constexpr auto sub4 = sub_matrix(m, point_t(0, 0), dims(2_C, 2_R));
	auto type4 = id< std_matrix< int, 2, 2 > >;
	BOOST_TEST(rt_id(sub4) == type4);
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), dims(2_Cd, 2_R))) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), dims(2_C, 2_Rd))) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), dims(2_Cd, 2_Rd))) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), dims(2_C, 2_R))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), dims(2_C, 2_R))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), dims(2_C, 2_R))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), dims(2_C, 2_R))));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), dims(2_Cd, 2_R))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), dims(2_Cd, 2_R))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), dims(2_Cd, 2_R))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), dims(2_Cd, 2_R))));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), dims(2_C, 2_Rd))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), dims(2_C, 2_Rd))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), dims(2_C, 2_Rd))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), dims(2_C, 2_Rd))));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), dims(2_Cd, 2_Rd))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), dims(2_Cd, 2_Rd))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), dims(2_Cd, 2_Rd))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), dims(2_Cd, 2_Rd))));
}

BOOST_AUTO_TEST_CASE(test_sub_matrix_3x3_move){
	constexpr auto sub1 = sub_matrix(m(), 0, 0, 2_C, 2_R);
	auto type1 = id< std_matrix< int, 2, 2 > >;
	BOOST_TEST(rt_id(sub1) == type1);
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, 2_Cd, 2_R)) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, 2_C, 2_Rd)) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, 2_Cd, 2_Rd)) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check4(sub_matrix(m(), 1, 1, 2_C, 2_R)));
	BOOST_TEST(check4(sub_matrix(m(), 1, 1, 2_Cd, 2_R)));
	BOOST_TEST(check4(sub_matrix(m(), 1, 1, 2_C, 2_Rd)));
	BOOST_TEST(check4(sub_matrix(m(), 1, 1, 2_Cd, 2_Rd)));

	constexpr auto sub2 = sub_matrix(m(), 0, 0, dims(2_C, 2_R));
	auto type2 = id< std_matrix< int, 2, 2 > >;
	BOOST_TEST(rt_id(sub2) == type2);
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, dims(2_Cd, 2_R))) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, dims(2_C, 2_Rd))) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, dims(2_Cd, 2_Rd))) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check4(sub_matrix(m(), 1, 1, dims(2_C, 2_R))));
	BOOST_TEST(check4(sub_matrix(m(), 1, 1, dims(2_Cd, 2_R))));
	BOOST_TEST(check4(sub_matrix(m(), 1, 1, dims(2_C, 2_Rd))));
	BOOST_TEST(check4(sub_matrix(m(), 1, 1, dims(2_Cd, 2_Rd))));

	constexpr auto sub3 = sub_matrix(m(), point_t(0, 0), 2_C, 2_R);
	auto type3 = id< std_matrix< int, 2, 2 > >;
	BOOST_TEST(rt_id(sub3) == type3);
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), 2_Cd, 2_R)) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), 2_C, 2_Rd)) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), 2_Cd, 2_Rd)) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), 2_C, 2_R)));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), 2_Cd, 2_R)));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), 2_C, 2_Rd)));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), 2_Cd, 2_Rd)));

	constexpr auto sub4 = sub_matrix(m(), point_t(0, 0), dims(2_C, 2_R));
	auto type4 = id< std_matrix< int, 2, 2 > >;
	BOOST_TEST(rt_id(sub4) == type4);
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), dims(2_Cd, 2_R))) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), dims(2_C, 2_Rd))) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), dims(2_Cd, 2_Rd))) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), dims(2_C, 2_R))));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), dims(2_Cd, 2_R))));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), dims(2_C, 2_Rd))));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), dims(2_Cd, 2_Rd))));
}

BOOST_AUTO_TEST_CASE(test_sub_matrix_3rtx3){
	auto m = make_matrix(3_Cd, 3_R, org);

	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, 2_C, 2_R)) ==
		id< std_matrix< int, 2, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, 2_Cd, 2_R)) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, 2_C, 2_Rd)) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, 2_Cd, 2_Rd)) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, 2_C, 2_R)));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, 2_C, 2_R)));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, 2_C, 2_R)));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, 2_C, 2_R)));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, 2_Cd, 2_R)));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, 2_Cd, 2_R)));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, 2_Cd, 2_R)));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, 2_Cd, 2_R)));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, 2_C, 2_Rd)));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, 2_C, 2_Rd)));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, 2_C, 2_Rd)));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, 2_C, 2_Rd)));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, 2_Cd, 2_Rd)));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, 2_Cd, 2_Rd)));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, 2_Cd, 2_Rd)));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, 2_Cd, 2_Rd)));

	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, dims(2_C, 2_R))) ==
		id< std_matrix< int, 2, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, dims(2_Cd, 2_R))) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, dims(2_C, 2_Rd))) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, dims(2_Cd, 2_Rd))) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, dims(2_C, 2_R))));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, dims(2_C, 2_R))));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, dims(2_C, 2_R))));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, dims(2_C, 2_R))));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, dims(2_Cd, 2_R))));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, dims(2_Cd, 2_R))));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, dims(2_Cd, 2_R))));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, dims(2_Cd, 2_R))));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, dims(2_C, 2_Rd))));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, dims(2_C, 2_Rd))));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, dims(2_C, 2_Rd))));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, dims(2_C, 2_Rd))));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, dims(2_Cd, 2_Rd))));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, dims(2_Cd, 2_Rd))));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, dims(2_Cd, 2_Rd))));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, dims(2_Cd, 2_Rd))));

	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), 2_C, 2_R)) ==
		id< std_matrix< int, 2, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), 2_Cd, 2_R)) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), 2_C, 2_Rd)) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), 2_Cd, 2_Rd)) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), 2_C, 2_R)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), 2_C, 2_R)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), 2_C, 2_R)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), 2_C, 2_R)));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), 2_Cd, 2_R)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), 2_Cd, 2_R)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), 2_Cd, 2_R)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), 2_Cd, 2_R)));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), 2_C, 2_Rd)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), 2_C, 2_Rd)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), 2_C, 2_Rd)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), 2_C, 2_Rd)));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), 2_Cd, 2_Rd)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), 2_Cd, 2_Rd)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), 2_Cd, 2_Rd)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), 2_Cd, 2_Rd)));

	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), dims(2_C, 2_R))) ==
		id< std_matrix< int, 2, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), dims(2_Cd, 2_R))) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), dims(2_C, 2_Rd))) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), dims(2_Cd, 2_Rd))) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), dims(2_C, 2_R))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), dims(2_C, 2_R))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), dims(2_C, 2_R))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), dims(2_C, 2_R))));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), dims(2_Cd, 2_R))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), dims(2_Cd, 2_R))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), dims(2_Cd, 2_R))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), dims(2_Cd, 2_R))));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), dims(2_C, 2_Rd))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), dims(2_C, 2_Rd))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), dims(2_C, 2_Rd))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), dims(2_C, 2_Rd))));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), dims(2_Cd, 2_Rd))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), dims(2_Cd, 2_Rd))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), dims(2_Cd, 2_Rd))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), dims(2_Cd, 2_Rd))));
}

BOOST_AUTO_TEST_CASE(test_sub_matrix_3rtx3_move){
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, 2_C, 2_R)) ==
		id< std_matrix< int, 2, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, 2_Cd, 2_R)) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, 2_C, 2_Rd)) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, 2_Cd, 2_Rd)) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check4(sub_matrix(m(), 1, 1, 2_C, 2_R)));
	BOOST_TEST(check4(sub_matrix(m(), 1, 1, 2_Cd, 2_R)));
	BOOST_TEST(check4(sub_matrix(m(), 1, 1, 2_C, 2_Rd)));
	BOOST_TEST(check4(sub_matrix(m(), 1, 1, 2_Cd, 2_Rd)));

	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, dims(2_C, 2_R))) ==
		id< std_matrix< int, 2, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, dims(2_Cd, 2_R))) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, dims(2_C, 2_Rd))) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, dims(2_Cd, 2_Rd))) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check4(sub_matrix(m(), 1, 1, dims(2_C, 2_R))));
	BOOST_TEST(check4(sub_matrix(m(), 1, 1, dims(2_Cd, 2_R))));
	BOOST_TEST(check4(sub_matrix(m(), 1, 1, dims(2_C, 2_Rd))));
	BOOST_TEST(check4(sub_matrix(m(), 1, 1, dims(2_Cd, 2_Rd))));

	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), 2_C, 2_R)) ==
		id< std_matrix< int, 2, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), 2_Cd, 2_R)) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), 2_C, 2_Rd)) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), 2_Cd, 2_Rd)) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), 2_C, 2_R)));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), 2_Cd, 2_R)));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), 2_C, 2_Rd)));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), 2_Cd, 2_Rd)));

	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), dims(2_C, 2_R))) ==
		id< std_matrix< int, 2, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), dims(2_Cd, 2_R))) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), dims(2_C, 2_Rd))) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), dims(2_Cd, 2_Rd))) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), dims(2_C, 2_R))));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), dims(2_Cd, 2_R))));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), dims(2_C, 2_Rd))));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), dims(2_Cd, 2_Rd))));
}

BOOST_AUTO_TEST_CASE(test_sub_matrix_3x3rt){
	auto m = make_matrix(3_C, 3_Rd, org);

	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, 2_C, 2_R)) ==
		id< std_matrix< int, 2, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, 2_Cd, 2_R)) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, 2_C, 2_Rd)) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, 2_Cd, 2_Rd)) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, 2_C, 2_R)));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, 2_C, 2_R)));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, 2_C, 2_R)));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, 2_C, 2_R)));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, 2_Cd, 2_R)));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, 2_Cd, 2_R)));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, 2_Cd, 2_R)));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, 2_Cd, 2_R)));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, 2_C, 2_Rd)));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, 2_C, 2_Rd)));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, 2_C, 2_Rd)));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, 2_C, 2_Rd)));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, 2_Cd, 2_Rd)));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, 2_Cd, 2_Rd)));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, 2_Cd, 2_Rd)));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, 2_Cd, 2_Rd)));

	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, dims(2_C, 2_R))) ==
		id< std_matrix< int, 2, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, dims(2_Cd, 2_R))) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, dims(2_C, 2_Rd))) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, dims(2_Cd, 2_Rd))) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, dims(2_C, 2_R))));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, dims(2_C, 2_R))));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, dims(2_C, 2_R))));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, dims(2_C, 2_R))));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, dims(2_Cd, 2_R))));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, dims(2_Cd, 2_R))));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, dims(2_Cd, 2_R))));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, dims(2_Cd, 2_R))));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, dims(2_C, 2_Rd))));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, dims(2_C, 2_Rd))));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, dims(2_C, 2_Rd))));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, dims(2_C, 2_Rd))));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, dims(2_Cd, 2_Rd))));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, dims(2_Cd, 2_Rd))));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, dims(2_Cd, 2_Rd))));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, dims(2_Cd, 2_Rd))));

	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), 2_C, 2_R)) ==
		id< std_matrix< int, 2, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), 2_Cd, 2_R)) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), 2_C, 2_Rd)) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), 2_Cd, 2_Rd)) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), 2_C, 2_R)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), 2_C, 2_R)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), 2_C, 2_R)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), 2_C, 2_R)));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), 2_Cd, 2_R)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), 2_Cd, 2_R)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), 2_Cd, 2_R)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), 2_Cd, 2_R)));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), 2_C, 2_Rd)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), 2_C, 2_Rd)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), 2_C, 2_Rd)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), 2_C, 2_Rd)));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), 2_Cd, 2_Rd)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), 2_Cd, 2_Rd)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), 2_Cd, 2_Rd)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), 2_Cd, 2_Rd)));

	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), dims(2_C, 2_R))) ==
		id< std_matrix< int, 2, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), dims(2_Cd, 2_R))) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), dims(2_C, 2_Rd))) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), dims(2_Cd, 2_Rd))) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), dims(2_C, 2_R))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), dims(2_C, 2_R))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), dims(2_C, 2_R))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), dims(2_C, 2_R))));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), dims(2_Cd, 2_R))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), dims(2_Cd, 2_R))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), dims(2_Cd, 2_R))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), dims(2_Cd, 2_R))));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), dims(2_C, 2_Rd))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), dims(2_C, 2_Rd))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), dims(2_C, 2_Rd))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), dims(2_C, 2_Rd))));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), dims(2_Cd, 2_Rd))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), dims(2_Cd, 2_Rd))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), dims(2_Cd, 2_Rd))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), dims(2_Cd, 2_Rd))));
}

BOOST_AUTO_TEST_CASE(test_sub_matrix_3x3rt_move){
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, 2_C, 2_R)) ==
		id< std_matrix< int, 2, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, 2_Cd, 2_R)) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, 2_C, 2_Rd)) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, 2_Cd, 2_Rd)) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check4(sub_matrix(m(), 1, 1, 2_C, 2_R)));
	BOOST_TEST(check4(sub_matrix(m(), 1, 1, 2_Cd, 2_R)));
	BOOST_TEST(check4(sub_matrix(m(), 1, 1, 2_C, 2_Rd)));
	BOOST_TEST(check4(sub_matrix(m(), 1, 1, 2_Cd, 2_Rd)));

	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, dims(2_C, 2_R))) ==
		id< std_matrix< int, 2, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, dims(2_Cd, 2_R))) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, dims(2_C, 2_Rd))) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, dims(2_Cd, 2_Rd))) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check4(sub_matrix(m(), 1, 1, dims(2_C, 2_R))));
	BOOST_TEST(check4(sub_matrix(m(), 1, 1, dims(2_Cd, 2_R))));
	BOOST_TEST(check4(sub_matrix(m(), 1, 1, dims(2_C, 2_Rd))));
	BOOST_TEST(check4(sub_matrix(m(), 1, 1, dims(2_Cd, 2_Rd))));

	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), 2_C, 2_R)) ==
		id< std_matrix< int, 2, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), 2_Cd, 2_R)) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), 2_C, 2_Rd)) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), 2_Cd, 2_Rd)) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), 2_C, 2_R)));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), 2_Cd, 2_R)));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), 2_C, 2_Rd)));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), 2_Cd, 2_Rd)));

	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), dims(2_C, 2_R))) ==
		id< std_matrix< int, 2, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), dims(2_Cd, 2_R))) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), dims(2_C, 2_Rd))) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), dims(2_Cd, 2_Rd))) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), dims(2_C, 2_R))));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), dims(2_Cd, 2_R))));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), dims(2_C, 2_Rd))));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), dims(2_Cd, 2_Rd))));
}

BOOST_AUTO_TEST_CASE(test_sub_matrix_3rtx3rt){
	auto m = make_matrix(3_Cd, 3_Rd, org);

	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, 2_C, 2_R)) ==
		id< std_matrix< int, 2, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, 2_Cd, 2_R)) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, 2_C, 2_Rd)) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, 2_Cd, 2_Rd)) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, 2_C, 2_R)));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, 2_C, 2_R)));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, 2_C, 2_R)));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, 2_C, 2_R)));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, 2_Cd, 2_R)));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, 2_Cd, 2_R)));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, 2_Cd, 2_R)));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, 2_Cd, 2_R)));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, 2_C, 2_Rd)));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, 2_C, 2_Rd)));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, 2_C, 2_Rd)));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, 2_C, 2_Rd)));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, 2_Cd, 2_Rd)));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, 2_Cd, 2_Rd)));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, 2_Cd, 2_Rd)));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, 2_Cd, 2_Rd)));

	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, dims(2_C, 2_R))) ==
		id< std_matrix< int, 2, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, dims(2_Cd, 2_R))) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, dims(2_C, 2_Rd))) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0, 0, dims(2_Cd, 2_Rd))) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, dims(2_C, 2_R))));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, dims(2_C, 2_R))));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, dims(2_C, 2_R))));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, dims(2_C, 2_R))));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, dims(2_Cd, 2_R))));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, dims(2_Cd, 2_R))));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, dims(2_Cd, 2_R))));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, dims(2_Cd, 2_R))));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, dims(2_C, 2_Rd))));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, dims(2_C, 2_Rd))));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, dims(2_C, 2_Rd))));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, dims(2_C, 2_Rd))));

	BOOST_TEST(check1(sub_matrix(m, 0, 0, dims(2_Cd, 2_Rd))));
	BOOST_TEST(check2(sub_matrix(m, 1, 0, dims(2_Cd, 2_Rd))));
	BOOST_TEST(check3(sub_matrix(m, 0, 1, dims(2_Cd, 2_Rd))));
	BOOST_TEST(check4(sub_matrix(m, 1, 1, dims(2_Cd, 2_Rd))));

	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), 2_C, 2_R)) ==
		id< std_matrix< int, 2, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), 2_Cd, 2_R)) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), 2_C, 2_Rd)) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), 2_Cd, 2_Rd)) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), 2_C, 2_R)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), 2_C, 2_R)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), 2_C, 2_R)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), 2_C, 2_R)));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), 2_Cd, 2_R)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), 2_Cd, 2_R)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), 2_Cd, 2_R)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), 2_Cd, 2_R)));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), 2_C, 2_Rd)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), 2_C, 2_Rd)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), 2_C, 2_Rd)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), 2_C, 2_Rd)));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), 2_Cd, 2_Rd)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), 2_Cd, 2_Rd)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), 2_Cd, 2_Rd)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), 2_Cd, 2_Rd)));

	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), dims(2_C, 2_R))) ==
		id< std_matrix< int, 2, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), dims(2_Cd, 2_R))) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), dims(2_C, 2_Rd))) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0, 0), dims(2_Cd, 2_Rd))) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), dims(2_C, 2_R))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), dims(2_C, 2_R))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), dims(2_C, 2_R))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), dims(2_C, 2_R))));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), dims(2_Cd, 2_R))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), dims(2_Cd, 2_R))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), dims(2_Cd, 2_R))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), dims(2_Cd, 2_R))));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), dims(2_C, 2_Rd))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), dims(2_C, 2_Rd))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), dims(2_C, 2_Rd))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), dims(2_C, 2_Rd))));

	BOOST_TEST(check1(sub_matrix(m, point_t(0, 0), dims(2_Cd, 2_Rd))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1, 0), dims(2_Cd, 2_Rd))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0, 1), dims(2_Cd, 2_Rd))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1, 1), dims(2_Cd, 2_Rd))));
}

BOOST_AUTO_TEST_CASE(test_sub_matrix_3rtx3rt_move){
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, 2_C, 2_R)) ==
		id< std_matrix< int, 2, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, 2_Cd, 2_R)) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, 2_C, 2_Rd)) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, 2_Cd, 2_Rd)) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check4(sub_matrix(m(), 1, 1, 2_C, 2_R)));
	BOOST_TEST(check4(sub_matrix(m(), 1, 1, 2_Cd, 2_R)));
	BOOST_TEST(check4(sub_matrix(m(), 1, 1, 2_C, 2_Rd)));
	BOOST_TEST(check4(sub_matrix(m(), 1, 1, 2_Cd, 2_Rd)));

	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, dims(2_C, 2_R))) ==
		id< std_matrix< int, 2, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, dims(2_Cd, 2_R))) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, dims(2_C, 2_Rd))) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0, 0, dims(2_Cd, 2_Rd))) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check4(sub_matrix(m(), 1, 1, dims(2_C, 2_R))));
	BOOST_TEST(check4(sub_matrix(m(), 1, 1, dims(2_Cd, 2_R))));
	BOOST_TEST(check4(sub_matrix(m(), 1, 1, dims(2_C, 2_Rd))));
	BOOST_TEST(check4(sub_matrix(m(), 1, 1, dims(2_Cd, 2_Rd))));

	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), 2_C, 2_R)) ==
		id< std_matrix< int, 2, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), 2_Cd, 2_R)) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), 2_C, 2_Rd)) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), 2_Cd, 2_Rd)) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), 2_C, 2_R)));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), 2_Cd, 2_R)));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), 2_C, 2_Rd)));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), 2_Cd, 2_Rd)));

	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), dims(2_C, 2_R))) ==
		id< std_matrix< int, 2, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), dims(2_Cd, 2_R))) ==
		id< std_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), dims(2_C, 2_Rd))) ==
		id< std_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0, 0), dims(2_Cd, 2_Rd))) ==
		id< std_matrix< int, 0, 0 > >));

	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), dims(2_C, 2_R))));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), dims(2_Cd, 2_R))));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), dims(2_C, 2_Rd))));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1, 1), dims(2_Cd, 2_Rd))));
}


BOOST_AUTO_TEST_SUITE_END()
