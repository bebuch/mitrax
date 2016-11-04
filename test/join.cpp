//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#define BOOST_TEST_MODULE mitrax join
#include <boost/test/unit_test.hpp>

#include <mitrax/join.hpp>
#include <mitrax/compare.hpp>


using boost::typeindex::type_id;
using boost::typeindex::type_id_runtime;
using namespace mitrax;
using namespace mitrax::literals;


template < typename T >
auto rt_id(T&& v){
	return boost::typeindex::type_id_runtime(static_cast< T&& >(v));
}

template < typename T >
auto const id = boost::typeindex::type_id< T >();


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


constexpr auto ref3x3 = make_matrix(3_C, 3_R, {
	{0, 1, 2},
	{3, 4, 5},
	{6, 7, 8}
});


constexpr auto ref6x6 = make_matrix(6_C, 6_R, {
	{0, 1, 2, 0, 1, 2},
	{3, 4, 5, 3, 4, 5},
	{6, 7, 8, 6, 7, 8},
	{0, 1, 2, 0, 1, 2},
	{3, 4, 5, 3, 4, 5},
	{6, 7, 8, 6, 7, 8}
});


BOOST_AUTO_TEST_SUITE(suite_join)


BOOST_AUTO_TEST_CASE(test_join_ct){
	constexpr auto m1 = make_matrix(2_C, 2_R, {{0, 1}, {3, 4}});
	constexpr auto m2 = make_matrix(1_C, 2_R, {{2}, {5}});
	constexpr auto m3 = make_matrix(2_C, 1_R, {{6, 7}});
	constexpr auto m4 = make_matrix(1_C, 1_R, {{8}});

	constexpr auto m5 = join(join_v(
		join_h(m1, m2),
		join_h(m3, m4)
	));

	constexpr auto m6 = join(join_h(
		join_v(m1, m3),
		join_v(m2, m4)
	));

	constexpr auto m7 = join(
		join_v(join_h(join_v(m1, m3), join_v(m2, m4), m5), join_h(m5, m6)));

	BOOST_TEST((rt_id(m5) == id< std_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m6) == id< std_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m7) == id< std_matrix< int, 6, 6 > >));

	BOOST_TEST((m5 == ref3x3));
	BOOST_TEST((m6 == ref3x3));
	BOOST_TEST((m7 == ref6x6));
}

BOOST_AUTO_TEST_CASE(test_join_rt){
	auto m1 = make_matrix(2_Cd, 2_Rd, {{0, 1}, {3, 4}});
	auto m2 = make_matrix(1_Cd, 2_Rd, {{2}, {5}});
	auto m3 = make_matrix(2_Cd, 1_Rd, {{6, 7}});
	auto m4 = make_matrix(1_Cd, 1_Rd, {{8}});

	auto m5 = join(join_v(
		join_h(m1, m2),
		join_h(m3, m4)
	));

	auto m6 = join(join_h(
		join_v(m1, m3),
		join_v(m2, m4)
	));

	auto m7 = join(
		join_v(join_h(join_v(m1, m3), join_v(m2, m4), m5), join_h(m5, m6)));

	BOOST_TEST((rt_id(m5) == id< std_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m6) == id< std_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m7) == id< std_matrix< int, 0, 0 > >));

	BOOST_TEST((m5 == ref3x3));
	BOOST_TEST((m6 == ref3x3));
	BOOST_TEST((m7 == ref6x6));
}

BOOST_AUTO_TEST_CASE(test_join_ct_and_rt_1){
	auto m1 = make_matrix(2_Cd, 2_Rd, {{0, 1}, {3, 4}});
	constexpr auto m2 = make_matrix(1_C, 2_R, {{2}, {5}});
	constexpr auto m3 = make_matrix(2_C, 1_R, {{6, 7}});
	constexpr auto m4 = make_matrix(1_C, 1_R, {{8}});

	auto m5 = join(join_v(
		join_h(m1, m2),
		join_h(m3, m4)
	));

	auto m6 = join(join_h(
		join_v(m1, m3),
		join_v(m2, m4)
	));

	auto m7 = join(
		join_v(join_h(join_v(m1, m3), join_v(m2, m4), m5), join_h(m5, m6)));

	BOOST_TEST((rt_id(m5) == id< std_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m6) == id< std_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m7) == id< std_matrix< int, 6, 6 > >));

	BOOST_TEST((m5 == ref3x3));
	BOOST_TEST((m6 == ref3x3));
	BOOST_TEST((m7 == ref6x6));
}

BOOST_AUTO_TEST_CASE(test_join_ct_and_rt_2){
	auto m1 = make_matrix(2_Cd, 2_Rd, {{0, 1}, {3, 4}});
	constexpr auto m2 = make_matrix(1_C, 2_R, {{2}, {5}});
	constexpr auto m3 = make_matrix(2_C, 1_R, {{6, 7}});
	auto m4 = make_matrix(1_Cd, 1_Rd, {{8}});

	auto m5 = join(join_v(
		join_h(m1, m2),
		join_h(m3, m4)
	));

	auto m6 = join(join_h(
		join_v(m1, m3),
		join_v(m2, m4)
	));

	auto m7 = join(
		join_v(join_h(join_v(m1, m3), join_v(m2, m4), m5), join_h(m5, m6)));

	BOOST_TEST((rt_id(m5) == id< std_matrix< int, 0, 3 > >));
	BOOST_TEST((rt_id(m6) == id< std_matrix< int, 3, 0 > >));
	BOOST_TEST((rt_id(m7) == id< std_matrix< int, 0, 6 > >));

	BOOST_TEST((m5 == ref3x3));
	BOOST_TEST((m6 == ref3x3));
	BOOST_TEST((m7 == ref6x6));
}


BOOST_AUTO_TEST_SUITE_END()
