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


using point_t = point_t;


constexpr int org[3][3] = {
	{0, 1, 2},
	{3, 4, 5},
	{6, 7, 8}
};


constexpr auto m(){
	return make_matrix(3_CS, 3_RS, org);
}


template < typename M >
constexpr bool check1(M const& m){
	return
		m.cols() == 2_CS &&
		m.rows() == 2_RS &&
		m(0_c, 0_r) == 0 &&
		m(1_c, 0_r) == 1 &&
		m(0_c, 1_r) == 3 &&
		m(1_c, 1_r) == 4;
}

template < typename M >
constexpr bool check2(M const& m){
	return
		m.cols() == 2_CS &&
		m.rows() == 2_RS &&
		m(0_c, 0_r) == 1 &&
		m(1_c, 0_r) == 2 &&
		m(0_c, 1_r) == 4 &&
		m(1_c, 1_r) == 5;
}

template < typename M >
constexpr bool check3(M const& m){
	return
		m.cols() == 2_CS &&
		m.rows() == 2_RS &&
		m(0_c, 0_r) == 3 &&
		m(1_c, 0_r) == 4 &&
		m(0_c, 1_r) == 6 &&
		m(1_c, 1_r) == 7;
}

template < typename M >
constexpr bool check4(M const& m){
	return
		m.cols() == 2_CS &&
		m.rows() == 2_RS &&
		m(0_c, 0_r) == 4 &&
		m(1_c, 0_r) == 5 &&
		m(0_c, 1_r) == 7 &&
		m(1_c, 1_r) == 8;
}


// TODO: add more unit tests
// TODO: check also for result types
// TODO: check move version and const/non-const versions
// TODO: use non square matrices


BOOST_AUTO_TEST_SUITE(suite_sub_matrix)


BOOST_AUTO_TEST_CASE(test_sub_matrix_3x3){
	constexpr auto m = make_matrix(3_CS, 3_RS, org);

	constexpr auto sub1 = sub_matrix(m, 0_c, 0_r, 2_CS, 2_RS);
	auto type1 = id< std_matrix< int, 2_C, 2_R > >;
	BOOST_TEST(rt_id(sub1) == type1);
	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, 2_CD, 2_RS)) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, 2_CS, 2_RD)) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, 2_CD, 2_RD)) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, 2_CS, 2_RS)));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, 2_CS, 2_RS)));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, 2_CS, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, 2_CS, 2_RS)));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, 2_CD, 2_RS)));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, 2_CD, 2_RS)));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, 2_CD, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, 2_CD, 2_RS)));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, 2_CS, 2_RD)));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, 2_CS, 2_RD)));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, 2_CS, 2_RD)));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, 2_CS, 2_RD)));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, 2_CD, 2_RD)));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, 2_CD, 2_RD)));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, 2_CD, 2_RD)));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, 2_CD, 2_RD)));


	constexpr auto sub2 = sub_matrix(m, 0_c, 0_r, dim_pair(2_CS, 2_RS));
	auto type2 = id< std_matrix< int, 2_C, 2_R > >;
	BOOST_TEST(rt_id(sub2) == type2);
	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, dim_pair(2_CD, 2_RS))) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, dim_pair(2_CS, 2_RD))) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, dim_pair(2_CD, 2_RD))) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, dim_pair(2_CS, 2_RS))));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, dim_pair(2_CD, 2_RS))));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, dim_pair(2_CS, 2_RD))));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, dim_pair(2_CD, 2_RD))));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, dim_pair(2_CD, 2_RD))));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, dim_pair(2_CD, 2_RD))));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, dim_pair(2_CD, 2_RD))));

	constexpr auto sub3 = sub_matrix(m, point_t(0_c, 0_r), 2_CS, 2_RS);
	auto type3 = id< std_matrix< int, 2_C, 2_R > >;
	BOOST_TEST(rt_id(sub3) == type3);
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), 2_CD, 2_RS)) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), 2_CS, 2_RD)) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), 2_CD, 2_RD)) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), 2_CS, 2_RS)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), 2_CS, 2_RS)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), 2_CS, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), 2_CS, 2_RS)));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), 2_CD, 2_RS)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), 2_CD, 2_RS)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), 2_CD, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), 2_CD, 2_RS)));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), 2_CS, 2_RD)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), 2_CS, 2_RD)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), 2_CS, 2_RD)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), 2_CS, 2_RD)));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), 2_CD, 2_RD)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), 2_CD, 2_RD)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), 2_CD, 2_RD)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), 2_CD, 2_RD)));


	constexpr auto sub4 = sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CS, 2_RS));
	auto type4 = id< std_matrix< int, 2_C, 2_R > >;
	BOOST_TEST(rt_id(sub4) == type4);
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CD, 2_RS))) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CS, 2_RD))) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CD, 2_RD))) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), dim_pair(2_CS, 2_RS))));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), dim_pair(2_CD, 2_RS))));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), dim_pair(2_CS, 2_RD))));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CD, 2_RD))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), dim_pair(2_CD, 2_RD))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), dim_pair(2_CD, 2_RD))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), dim_pair(2_CD, 2_RD))));
}

BOOST_AUTO_TEST_CASE(test_sub_matrix_3x3_move){
	constexpr auto sub1 = sub_matrix(m(), 0_c, 0_r, 2_CS, 2_RS);
	auto type1 = id< std_matrix< int, 2_C, 2_R > >;
	BOOST_TEST(rt_id(sub1) == type1);
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, 2_CD, 2_RS)) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, 2_CS, 2_RD)) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, 2_CD, 2_RD)) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, 2_CS, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, 2_CD, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, 2_CS, 2_RD)));
	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, 2_CD, 2_RD)));

	constexpr auto sub2 = sub_matrix(m(), 0_c, 0_r, dim_pair(2_CS, 2_RS));
	auto type2 = id< std_matrix< int, 2_C, 2_R > >;
	BOOST_TEST(rt_id(sub2) == type2);
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, dim_pair(2_CD, 2_RS))) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, dim_pair(2_CS, 2_RD))) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, dim_pair(2_CD, 2_RD))) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, dim_pair(2_CD, 2_RD))));

	constexpr auto sub3 = sub_matrix(m(), point_t(0_c, 0_r), 2_CS, 2_RS);
	auto type3 = id< std_matrix< int, 2_C, 2_R > >;
	BOOST_TEST(rt_id(sub3) == type3);
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), 2_CD, 2_RS)) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), 2_CS, 2_RD)) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), 2_CD, 2_RD)) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), 2_CS, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), 2_CD, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), 2_CS, 2_RD)));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), 2_CD, 2_RD)));

	constexpr auto sub4 = sub_matrix(m(), point_t(0_c, 0_r), dim_pair(2_CS, 2_RS));
	auto type4 = id< std_matrix< int, 2_C, 2_R > >;
	BOOST_TEST(rt_id(sub4) == type4);
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), dim_pair(2_CD, 2_RS))) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), dim_pair(2_CS, 2_RD))) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), dim_pair(2_CD, 2_RD))) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), dim_pair(2_CD, 2_RD))));
}

BOOST_AUTO_TEST_CASE(test_sub_matrix_3rtx3){
	auto m = make_matrix(3_CD, 3_RS, org);

	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, 2_CS, 2_RS)) ==
		id< std_matrix< int, 2_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, 2_CD, 2_RS)) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, 2_CS, 2_RD)) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, 2_CD, 2_RD)) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, 2_CS, 2_RS)));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, 2_CS, 2_RS)));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, 2_CS, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, 2_CS, 2_RS)));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, 2_CD, 2_RS)));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, 2_CD, 2_RS)));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, 2_CD, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, 2_CD, 2_RS)));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, 2_CS, 2_RD)));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, 2_CS, 2_RD)));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, 2_CS, 2_RD)));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, 2_CS, 2_RD)));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, 2_CD, 2_RD)));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, 2_CD, 2_RD)));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, 2_CD, 2_RD)));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, 2_CD, 2_RD)));

	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, dim_pair(2_CS, 2_RS))) ==
		id< std_matrix< int, 2_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, dim_pair(2_CD, 2_RS))) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, dim_pair(2_CS, 2_RD))) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, dim_pair(2_CD, 2_RD))) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, dim_pair(2_CS, 2_RS))));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, dim_pair(2_CD, 2_RS))));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, dim_pair(2_CS, 2_RD))));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, dim_pair(2_CD, 2_RD))));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, dim_pair(2_CD, 2_RD))));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, dim_pair(2_CD, 2_RD))));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, dim_pair(2_CD, 2_RD))));

	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), 2_CS, 2_RS)) ==
		id< std_matrix< int, 2_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), 2_CD, 2_RS)) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), 2_CS, 2_RD)) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), 2_CD, 2_RD)) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), 2_CS, 2_RS)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), 2_CS, 2_RS)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), 2_CS, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), 2_CS, 2_RS)));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), 2_CD, 2_RS)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), 2_CD, 2_RS)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), 2_CD, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), 2_CD, 2_RS)));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), 2_CS, 2_RD)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), 2_CS, 2_RD)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), 2_CS, 2_RD)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), 2_CS, 2_RD)));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), 2_CD, 2_RD)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), 2_CD, 2_RD)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), 2_CD, 2_RD)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), 2_CD, 2_RD)));

	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CS, 2_RS))) ==
		id< std_matrix< int, 2_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CD, 2_RS))) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CS, 2_RD))) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CD, 2_RD))) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), dim_pair(2_CS, 2_RS))));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), dim_pair(2_CD, 2_RS))));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), dim_pair(2_CS, 2_RD))));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CD, 2_RD))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), dim_pair(2_CD, 2_RD))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), dim_pair(2_CD, 2_RD))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), dim_pair(2_CD, 2_RD))));
}

BOOST_AUTO_TEST_CASE(test_sub_matrix_3rtx3_move){
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, 2_CS, 2_RS)) ==
		id< std_matrix< int, 2_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, 2_CD, 2_RS)) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, 2_CS, 2_RD)) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, 2_CD, 2_RD)) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, 2_CS, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, 2_CD, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, 2_CS, 2_RD)));
	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, 2_CD, 2_RD)));

	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, dim_pair(2_CS, 2_RS))) ==
		id< std_matrix< int, 2_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, dim_pair(2_CD, 2_RS))) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, dim_pair(2_CS, 2_RD))) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, dim_pair(2_CD, 2_RD))) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, dim_pair(2_CD, 2_RD))));

	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), 2_CS, 2_RS)) ==
		id< std_matrix< int, 2_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), 2_CD, 2_RS)) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), 2_CS, 2_RD)) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), 2_CD, 2_RD)) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), 2_CS, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), 2_CD, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), 2_CS, 2_RD)));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), 2_CD, 2_RD)));

	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), dim_pair(2_CS, 2_RS))) ==
		id< std_matrix< int, 2_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), dim_pair(2_CD, 2_RS))) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), dim_pair(2_CS, 2_RD))) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), dim_pair(2_CD, 2_RD))) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), dim_pair(2_CD, 2_RD))));
}

BOOST_AUTO_TEST_CASE(test_sub_matrix_3x3rt){
	auto m = make_matrix(3_CS, 3_RD, org);

	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, 2_CS, 2_RS)) ==
		id< std_matrix< int, 2_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, 2_CD, 2_RS)) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, 2_CS, 2_RD)) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, 2_CD, 2_RD)) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, 2_CS, 2_RS)));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, 2_CS, 2_RS)));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, 2_CS, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, 2_CS, 2_RS)));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, 2_CD, 2_RS)));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, 2_CD, 2_RS)));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, 2_CD, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, 2_CD, 2_RS)));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, 2_CS, 2_RD)));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, 2_CS, 2_RD)));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, 2_CS, 2_RD)));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, 2_CS, 2_RD)));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, 2_CD, 2_RD)));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, 2_CD, 2_RD)));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, 2_CD, 2_RD)));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, 2_CD, 2_RD)));

	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, dim_pair(2_CS, 2_RS))) ==
		id< std_matrix< int, 2_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, dim_pair(2_CD, 2_RS))) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, dim_pair(2_CS, 2_RD))) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, dim_pair(2_CD, 2_RD))) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, dim_pair(2_CS, 2_RS))));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, dim_pair(2_CD, 2_RS))));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, dim_pair(2_CS, 2_RD))));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, dim_pair(2_CD, 2_RD))));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, dim_pair(2_CD, 2_RD))));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, dim_pair(2_CD, 2_RD))));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, dim_pair(2_CD, 2_RD))));

	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), 2_CS, 2_RS)) ==
		id< std_matrix< int, 2_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), 2_CD, 2_RS)) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), 2_CS, 2_RD)) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), 2_CD, 2_RD)) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), 2_CS, 2_RS)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), 2_CS, 2_RS)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), 2_CS, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), 2_CS, 2_RS)));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), 2_CD, 2_RS)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), 2_CD, 2_RS)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), 2_CD, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), 2_CD, 2_RS)));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), 2_CS, 2_RD)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), 2_CS, 2_RD)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), 2_CS, 2_RD)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), 2_CS, 2_RD)));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), 2_CD, 2_RD)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), 2_CD, 2_RD)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), 2_CD, 2_RD)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), 2_CD, 2_RD)));

	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CS, 2_RS))) ==
		id< std_matrix< int, 2_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CD, 2_RS))) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CS, 2_RD))) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CD, 2_RD))) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), dim_pair(2_CS, 2_RS))));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), dim_pair(2_CD, 2_RS))));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), dim_pair(2_CS, 2_RD))));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CD, 2_RD))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), dim_pair(2_CD, 2_RD))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), dim_pair(2_CD, 2_RD))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), dim_pair(2_CD, 2_RD))));
}

BOOST_AUTO_TEST_CASE(test_sub_matrix_3x3rt_move){
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, 2_CS, 2_RS)) ==
		id< std_matrix< int, 2_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, 2_CD, 2_RS)) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, 2_CS, 2_RD)) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, 2_CD, 2_RD)) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, 2_CS, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, 2_CD, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, 2_CS, 2_RD)));
	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, 2_CD, 2_RD)));

	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, dim_pair(2_CS, 2_RS))) ==
		id< std_matrix< int, 2_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, dim_pair(2_CD, 2_RS))) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, dim_pair(2_CS, 2_RD))) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, dim_pair(2_CD, 2_RD))) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, dim_pair(2_CD, 2_RD))));

	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), 2_CS, 2_RS)) ==
		id< std_matrix< int, 2_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), 2_CD, 2_RS)) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), 2_CS, 2_RD)) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), 2_CD, 2_RD)) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), 2_CS, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), 2_CD, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), 2_CS, 2_RD)));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), 2_CD, 2_RD)));

	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), dim_pair(2_CS, 2_RS))) ==
		id< std_matrix< int, 2_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), dim_pair(2_CD, 2_RS))) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), dim_pair(2_CS, 2_RD))) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), dim_pair(2_CD, 2_RD))) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), dim_pair(2_CD, 2_RD))));
}

BOOST_AUTO_TEST_CASE(test_sub_matrix_3rtx3rt){
	auto m = make_matrix(3_CD, 3_RD, org);

	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, 2_CS, 2_RS)) ==
		id< std_matrix< int, 2_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, 2_CD, 2_RS)) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, 2_CS, 2_RD)) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, 2_CD, 2_RD)) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, 2_CS, 2_RS)));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, 2_CS, 2_RS)));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, 2_CS, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, 2_CS, 2_RS)));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, 2_CD, 2_RS)));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, 2_CD, 2_RS)));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, 2_CD, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, 2_CD, 2_RS)));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, 2_CS, 2_RD)));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, 2_CS, 2_RD)));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, 2_CS, 2_RD)));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, 2_CS, 2_RD)));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, 2_CD, 2_RD)));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, 2_CD, 2_RD)));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, 2_CD, 2_RD)));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, 2_CD, 2_RD)));

	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, dim_pair(2_CS, 2_RS))) ==
		id< std_matrix< int, 2_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, dim_pair(2_CD, 2_RS))) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, dim_pair(2_CS, 2_RD))) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, 0_c, 0_r, dim_pair(2_CD, 2_RD))) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, dim_pair(2_CS, 2_RS))));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, dim_pair(2_CD, 2_RS))));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, dim_pair(2_CS, 2_RD))));

	BOOST_TEST(check1(sub_matrix(m, 0_c, 0_r, dim_pair(2_CD, 2_RD))));
	BOOST_TEST(check2(sub_matrix(m, 1_c, 0_r, dim_pair(2_CD, 2_RD))));
	BOOST_TEST(check3(sub_matrix(m, 0_c, 1_r, dim_pair(2_CD, 2_RD))));
	BOOST_TEST(check4(sub_matrix(m, 1_c, 1_r, dim_pair(2_CD, 2_RD))));

	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), 2_CS, 2_RS)) ==
		id< std_matrix< int, 2_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), 2_CD, 2_RS)) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), 2_CS, 2_RD)) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), 2_CD, 2_RD)) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), 2_CS, 2_RS)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), 2_CS, 2_RS)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), 2_CS, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), 2_CS, 2_RS)));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), 2_CD, 2_RS)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), 2_CD, 2_RS)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), 2_CD, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), 2_CD, 2_RS)));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), 2_CS, 2_RD)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), 2_CS, 2_RD)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), 2_CS, 2_RD)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), 2_CS, 2_RD)));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), 2_CD, 2_RD)));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), 2_CD, 2_RD)));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), 2_CD, 2_RD)));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), 2_CD, 2_RD)));

	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CS, 2_RS))) ==
		id< std_matrix< int, 2_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CD, 2_RS))) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CS, 2_RD))) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CD, 2_RD))) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), dim_pair(2_CS, 2_RS))));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), dim_pair(2_CD, 2_RS))));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), dim_pair(2_CS, 2_RD))));

	BOOST_TEST(check1(sub_matrix(m, point_t(0_c, 0_r), dim_pair(2_CD, 2_RD))));
	BOOST_TEST(check2(sub_matrix(m, point_t(1_c, 0_r), dim_pair(2_CD, 2_RD))));
	BOOST_TEST(check3(sub_matrix(m, point_t(0_c, 1_r), dim_pair(2_CD, 2_RD))));
	BOOST_TEST(check4(sub_matrix(m, point_t(1_c, 1_r), dim_pair(2_CD, 2_RD))));
}

BOOST_AUTO_TEST_CASE(test_sub_matrix_3rtx3rt_move){
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, 2_CS, 2_RS)) ==
		id< std_matrix< int, 2_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, 2_CD, 2_RS)) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, 2_CS, 2_RD)) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, 2_CD, 2_RD)) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, 2_CS, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, 2_CD, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, 2_CS, 2_RD)));
	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, 2_CD, 2_RD)));

	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, dim_pair(2_CS, 2_RS))) ==
		id< std_matrix< int, 2_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, dim_pair(2_CD, 2_RS))) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, dim_pair(2_CS, 2_RD))) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), 0_c, 0_r, dim_pair(2_CD, 2_RD))) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check4(sub_matrix(m(), 1_c, 1_r, dim_pair(2_CD, 2_RD))));

	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), 2_CS, 2_RS)) ==
		id< std_matrix< int, 2_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), 2_CD, 2_RS)) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), 2_CS, 2_RD)) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), 2_CD, 2_RD)) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), 2_CS, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), 2_CD, 2_RS)));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), 2_CS, 2_RD)));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), 2_CD, 2_RD)));

	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), dim_pair(2_CS, 2_RS))) ==
		id< std_matrix< int, 2_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), dim_pair(2_CD, 2_RS))) ==
		id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), dim_pair(2_CS, 2_RD))) ==
		id< std_matrix< int, 2_C, 0_R > >));
	BOOST_TEST((rt_id(sub_matrix(m(), point_t(0_c, 0_r), dim_pair(2_CD, 2_RD))) ==
		id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), dim_pair(2_CS, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), dim_pair(2_CD, 2_RS))));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), dim_pair(2_CS, 2_RD))));
	BOOST_TEST(check4(sub_matrix(m(), point_t(1_c, 1_r), dim_pair(2_CD, 2_RD))));
}


BOOST_AUTO_TEST_SUITE_END()
