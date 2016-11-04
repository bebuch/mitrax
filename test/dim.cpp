//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#define BOOST_TEST_MODULE mitrax dim
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include <functional>

#include <mitrax/dim.hpp>


namespace utf = boost::unit_test;
using boost::typeindex::type_id;
using boost::typeindex::type_id_runtime;
using namespace mitrax;


#define CP(expr) [&]{ constexpr auto tmp = expr; return tmp; }()


template < typename T >
auto rt_id(T&& v){
	return type_id_runtime(static_cast< T&& >(v));
}

template < typename T >
auto const id = type_id< T >();



template < template < bool, size_t > typename DimT >
void construct(){
	constexpr auto cct = DimT< true, 3 >();
	constexpr auto crt = DimT< false, 3 >();
	constexpr auto rrt = DimT< false, 0 >(3);

	BOOST_TEST((rt_id(cct) == id< DimT< true, 3 > >));
	BOOST_TEST((rt_id(crt) == id< DimT< false, 3 > >));
	BOOST_TEST((rt_id(rrt) == id< DimT< false, 0 > >));

	BOOST_TEST((cct == 3));
	BOOST_TEST((crt == 3));
	BOOST_TEST((rrt == 3));
}


template < template < bool, size_t > typename DimT >
void default_construct(){
	constexpr auto cct = DimT< true, 3 >();
	constexpr auto crt = DimT< false, 3 >();
	constexpr auto rrt = DimT< false, 0 >();

	BOOST_TEST((rt_id(cct) == id< DimT< true, 3 > >));
	BOOST_TEST((rt_id(crt) == id< DimT< false, 3 > >));
	BOOST_TEST((rt_id(rrt) == id< DimT< false, 0 > >));

	BOOST_TEST((cct == 3));
	BOOST_TEST((crt == 3));
	BOOST_TEST((rrt == 0));
}

void dim_literal(){
	using namespace mitrax::literals;

	BOOST_TEST((rt_id(3_C) == id< col_t< true, 3 > >));
	BOOST_TEST((rt_id(3_Cd) == id< col_t< false, 3 > >));

	BOOST_TEST((rt_id(3_R) == id< row_t< true, 3 > >));
	BOOST_TEST((rt_id(3_Rd) == id< row_t< false, 3 > >));

	BOOST_TEST((rt_id(3_D) == id< dim_t< true, 3 > >));
	BOOST_TEST((rt_id(3_Dd) == id< dim_t< false, 3 > >));
}

template < template < bool, size_t > typename DimT >
void convert2size_t(){
	constexpr auto cct = DimT< true, 3 >();
	constexpr auto crt = DimT< false, 3 >();
	constexpr auto rrt = DimT< false, 0 >(3);

	BOOST_TEST((rt_id(size_t(cct)) == id< size_t >));
	BOOST_TEST((rt_id(size_t(crt)) == id< size_t >));
	BOOST_TEST((rt_id(size_t(rrt)) == id< size_t >));

	BOOST_TEST((CP(size_t(cct)) == 3));
	BOOST_TEST((CP(size_t(crt)) == 3));
	BOOST_TEST((CP(size_t(rrt)) == 3));
}

template < template < bool, size_t > typename DimT >
void convert2dim(){
	constexpr auto cct = DimT< true, 3 >();
	constexpr auto crt = DimT< false, 3 >();
	constexpr auto rrt = DimT< false, 0 >(3);

	BOOST_TEST((rt_id(cct.as_col()) == id< col_t< true, 3 > >));
	BOOST_TEST((rt_id(crt.as_col()) == id< col_t< false, 3 > >));
	BOOST_TEST((rt_id(rrt.as_col()) == id< col_t< false, 0 > >));

	BOOST_TEST((CP(cct.as_col()) == 3));
	BOOST_TEST((CP(crt.as_col()) == 3));
	BOOST_TEST((CP(rrt.as_col()) == 3));

	BOOST_TEST((rt_id(cct.as_row()) == id< row_t< true, 3 > >));
	BOOST_TEST((rt_id(crt.as_row()) == id< row_t< false, 3 > >));
	BOOST_TEST((rt_id(rrt.as_row()) == id< row_t< false, 0 > >));

	BOOST_TEST((CP(cct.as_row()) == 3));
	BOOST_TEST((CP(crt.as_row()) == 3));
	BOOST_TEST((CP(rrt.as_row()) == 3));

	BOOST_TEST((rt_id(cct.as_dim()) == id< dim_t< true, 3 > >));
	BOOST_TEST((rt_id(crt.as_dim()) == id< dim_t< false, 3 > >));
	BOOST_TEST((rt_id(rrt.as_dim()) == id< dim_t< false, 0 > >));

	BOOST_TEST((CP(cct.as_dim()) == 3));
	BOOST_TEST((CP(crt.as_dim()) == 3));
	BOOST_TEST((CP(rrt.as_dim()) == 3));
}

template < template < bool, size_t > typename DimT, typename Op >
void arithmetic(){
	constexpr auto op = Op();
	constexpr auto l = 4;
	constexpr auto r = 3;

	constexpr auto cct1 = DimT< true, l >();
	constexpr auto crt1 = DimT< false, l >();
	constexpr auto rrt1 = DimT< false, 0 >(l);
	constexpr auto rru1 = size_t(l);
	constexpr auto rrs1 = l;

	constexpr auto cct2 = DimT< true, r >();
	constexpr auto crt2 = DimT< false, r >();
	constexpr auto rrt2 = DimT< false, 0 >(r);
	constexpr auto rru2 = size_t(r);
	constexpr auto rrs2 = r;


	BOOST_TEST((rt_id(CP(op(cct1, cct2))) == id< DimT< true, op(l, r) > >));
	BOOST_TEST((rt_id(CP(op(cct1, crt2))) == id< DimT< false, op(l, r) > >));
	BOOST_TEST((rt_id(CP(op(cct1, rrt2))) == id< DimT< false, 0 > >));
	BOOST_TEST((rt_id(CP(op(cct1, rru2))) == id< DimT< false, 0 > >));
	BOOST_TEST((rt_id(CP(op(cct1, rrs2))) == id< DimT< false, 0 > >));

	BOOST_TEST((rt_id(CP(op(crt1, cct2))) == id< DimT< false, op(l, r) > >));
	BOOST_TEST((rt_id(CP(op(crt1, crt2))) == id< DimT< false, op(l, r) > >));
	BOOST_TEST((rt_id(CP(op(crt1, rrt2))) == id< DimT< false, 0 > >));
	BOOST_TEST((rt_id(CP(op(crt1, rru2))) == id< DimT< false, 0 > >));
	BOOST_TEST((rt_id(CP(op(crt1, rrs2))) == id< DimT< false, 0 > >));

	BOOST_TEST((rt_id(CP(op(rrt1, cct2))) == id< DimT< false, 0 > >));
	BOOST_TEST((rt_id(CP(op(rrt1, crt2))) == id< DimT< false, 0 > >));
	BOOST_TEST((rt_id(CP(op(rrt1, rrt2))) == id< DimT< false, 0 > >));
	BOOST_TEST((rt_id(CP(op(rrt1, rru2))) == id< DimT< false, 0 > >));
	BOOST_TEST((rt_id(CP(op(rrt1, rrs2))) == id< DimT< false, 0 > >));

	BOOST_TEST((rt_id(CP(op(rru1, cct2))) == id< DimT< false, 0 > >));
	BOOST_TEST((rt_id(CP(op(rru1, crt2))) == id< DimT< false, 0 > >));
	BOOST_TEST((rt_id(CP(op(rru1, rrt2))) == id< DimT< false, 0 > >));
	BOOST_TEST((rt_id(CP(op(rru1, rru2))) == id< size_t >));
	BOOST_TEST((rt_id(CP(op(rru1, rrs2))) == id< size_t >));

	BOOST_TEST((rt_id(CP(op(rrs1, cct2))) == id< DimT< false, 0 > >));
	BOOST_TEST((rt_id(CP(op(rrs1, crt2))) == id< DimT< false, 0 > >));
	BOOST_TEST((rt_id(CP(op(rrs1, rrt2))) == id< DimT< false, 0 > >));
	BOOST_TEST((rt_id(CP(op(rrs1, rru2))) == id< size_t >));
	BOOST_TEST((rt_id(CP(op(rrs1, rrs2))) == id< int >));


	BOOST_TEST((size_t(CP(op(cct1, cct2))) == op(l, r)));
	BOOST_TEST((size_t(CP(op(cct1, crt2))) == op(l, r)));
	BOOST_TEST((size_t(CP(op(cct1, rrt2))) == op(l, r)));
	BOOST_TEST((size_t(CP(op(cct1, rru2))) == op(l, r)));
	BOOST_TEST((size_t(CP(op(cct1, rrs2))) == op(l, r)));

	BOOST_TEST((size_t(CP(op(crt1, cct2))) == op(l, r)));
	BOOST_TEST((size_t(CP(op(crt1, crt2))) == op(l, r)));
	BOOST_TEST((size_t(CP(op(crt1, rrt2))) == op(l, r)));
	BOOST_TEST((size_t(CP(op(crt1, rru2))) == op(l, r)));
	BOOST_TEST((size_t(CP(op(crt1, rrs2))) == op(l, r)));

	BOOST_TEST((size_t(CP(op(rrt1, cct2))) == op(l, r)));
	BOOST_TEST((size_t(CP(op(rrt1, crt2))) == op(l, r)));
	BOOST_TEST((size_t(CP(op(rrt1, rrt2))) == op(l, r)));
	BOOST_TEST((size_t(CP(op(rrt1, rru2))) == op(l, r)));
	BOOST_TEST((size_t(CP(op(rrt1, rrs2))) == op(l, r)));

	BOOST_TEST((size_t(CP(op(rru1, cct2))) == op(l, r)));
	BOOST_TEST((size_t(CP(op(rru1, crt2))) == op(l, r)));
	BOOST_TEST((size_t(CP(op(rru1, rrt2))) == op(l, r)));
	BOOST_TEST((size_t(CP(op(rru1, rru2))) == op(l, r)));
	BOOST_TEST((size_t(CP(op(rru1, rrs2))) == op(l, r)));

	BOOST_TEST((size_t(CP(op(rrs1, cct2))) == op(l, r)));
	BOOST_TEST((size_t(CP(op(rrs1, crt2))) == op(l, r)));
	BOOST_TEST((size_t(CP(op(rrs1, rrt2))) == op(l, r)));
	BOOST_TEST((size_t(CP(op(rrs1, rru2))) == op(l, r)));
	BOOST_TEST((size_t(CP(op(rrs1, rrs2))) == op(l, r)));
}

template < template < bool, size_t > typename DimT, typename Op >
void compare(){
	constexpr auto op = Op();
	constexpr auto l = 4;
	constexpr auto r = 3;

	constexpr auto cct1 = DimT< true, l >();
	constexpr auto crt1 = DimT< false, l >();
	constexpr auto rrt1 = DimT< false, 0 >(l);
	constexpr auto rru1 = size_t(l);
	constexpr auto rrs1 = l;

	constexpr auto cct2 = DimT< true, r >();
	constexpr auto crt2 = DimT< false, r >();
	constexpr auto rrt2 = DimT< false, 0 >(r);
	constexpr auto rru2 = size_t(r);
	constexpr auto rrs2 = r;


	BOOST_TEST((rt_id(CP(op(cct1, cct2))) == id< bool >));
	BOOST_TEST((rt_id(CP(op(cct1, crt2))) == id< bool >));
	BOOST_TEST((rt_id(CP(op(cct1, rrt2))) == id< bool >));
	BOOST_TEST((rt_id(CP(op(cct1, rru2))) == id< bool >));
	BOOST_TEST((rt_id(CP(op(cct1, rrs2))) == id< bool >));

	BOOST_TEST((rt_id(CP(op(crt1, cct2))) == id< bool >));
	BOOST_TEST((rt_id(CP(op(crt1, crt2))) == id< bool >));
	BOOST_TEST((rt_id(CP(op(crt1, rrt2))) == id< bool >));
	BOOST_TEST((rt_id(CP(op(crt1, rru2))) == id< bool >));
	BOOST_TEST((rt_id(CP(op(crt1, rrs2))) == id< bool >));

	BOOST_TEST((rt_id(CP(op(rrt1, cct2))) == id< bool >));
	BOOST_TEST((rt_id(CP(op(rrt1, crt2))) == id< bool >));
	BOOST_TEST((rt_id(CP(op(rrt1, rrt2))) == id< bool >));
	BOOST_TEST((rt_id(CP(op(rrt1, rru2))) == id< bool >));
	BOOST_TEST((rt_id(CP(op(rrt1, rrs2))) == id< bool >));

	BOOST_TEST((rt_id(CP(op(rru1, cct2))) == id< bool >));
	BOOST_TEST((rt_id(CP(op(rru1, crt2))) == id< bool >));
	BOOST_TEST((rt_id(CP(op(rru1, rrt2))) == id< bool >));
	BOOST_TEST((rt_id(CP(op(rru1, rru2))) == id< bool >));
	BOOST_TEST((rt_id(CP(op(rru1, rrs2))) == id< bool >));

	BOOST_TEST((rt_id(CP(op(rrs1, cct2))) == id< bool >));
	BOOST_TEST((rt_id(CP(op(rrs1, crt2))) == id< bool >));
	BOOST_TEST((rt_id(CP(op(rrs1, rrt2))) == id< bool >));
	BOOST_TEST((rt_id(CP(op(rrs1, rru2))) == id< bool >));
	BOOST_TEST((rt_id(CP(op(rrs1, rrs2))) == id< bool >));


	BOOST_TEST((CP(op(cct1, cct2)) == op(l, r)));
	BOOST_TEST((CP(op(cct1, crt2)) == op(l, r)));
	BOOST_TEST((CP(op(cct1, rrt2)) == op(l, r)));
	BOOST_TEST((CP(op(cct1, rru2)) == op(l, r)));
	BOOST_TEST((CP(op(cct1, rrs2)) == op(l, r)));

	BOOST_TEST((CP(op(crt1, cct2)) == op(l, r)));
	BOOST_TEST((CP(op(crt1, crt2)) == op(l, r)));
	BOOST_TEST((CP(op(crt1, rrt2)) == op(l, r)));
	BOOST_TEST((CP(op(crt1, rru2)) == op(l, r)));
	BOOST_TEST((CP(op(crt1, rrs2)) == op(l, r)));

	BOOST_TEST((CP(op(rrt1, cct2)) == op(l, r)));
	BOOST_TEST((CP(op(rrt1, crt2)) == op(l, r)));
	BOOST_TEST((CP(op(rrt1, rrt2)) == op(l, r)));
	BOOST_TEST((CP(op(rrt1, rru2)) == op(l, r)));
	BOOST_TEST((CP(op(rrt1, rrs2)) == op(l, r)));

	BOOST_TEST((CP(op(rru1, cct2)) == op(l, r)));
	BOOST_TEST((CP(op(rru1, crt2)) == op(l, r)));
	BOOST_TEST((CP(op(rru1, rrt2)) == op(l, r)));
	BOOST_TEST((CP(op(rru1, rru2)) == op(l, r)));
	BOOST_TEST((CP(op(rru1, rrs2)) == op(l, r)));

	BOOST_TEST((CP(op(rrs1, cct2)) == op(l, r)));
	BOOST_TEST((CP(op(rrs1, crt2)) == op(l, r)));
	BOOST_TEST((CP(op(rrs1, rrt2)) == op(l, r)));
	BOOST_TEST((CP(op(rrs1, rru2)) == op(l, r)));
	BOOST_TEST((CP(op(rrs1, rrs2)) == op(l, r)));
}


template < template < bool, size_t > typename DimT >
void get_dim(){
	constexpr auto v = 7;

	constexpr auto d1 = DimT< true, v >();
	constexpr auto d2 = DimT< false, v >();
	constexpr auto d3 = DimT< false, 0 >(v);

	constexpr auto res01 = get(d1);
	constexpr auto res02 = get(d2);
	constexpr auto res03 = get(d3);
	constexpr auto res04 = get(d1, d1);
	constexpr auto res05 = get(d2, d2);
	constexpr auto res06 = get(d3, d3);
	constexpr auto res07 = get(d1, d2);
	constexpr auto res08 = get(d1, d3);
	constexpr auto res09 = get(d2, d1);
	constexpr auto res10 = get(d2, d3);
	constexpr auto res11 = get(d3, d1);
	constexpr auto res12 = get(d3, d2);
	constexpr auto res13 = get(d1, d1, d1);
	constexpr auto res14 = get(d2, d2, d2);
	constexpr auto res15 = get(d3, d3, d3);
	constexpr auto res16 = get(d1, d2, d1);
	constexpr auto res17 = get(d1, d2, d2);
	constexpr auto res18 = get(d1, d2, d3);
	constexpr auto res19 = get(d1, d3, d1);
	constexpr auto res20 = get(d1, d3, d2);
	constexpr auto res21 = get(d1, d3, d3);
	constexpr auto res22 = get(d2, d1, d1);
	constexpr auto res23 = get(d2, d1, d2);
	constexpr auto res24 = get(d2, d1, d3);
	constexpr auto res25 = get(d2, d3, d1);
	constexpr auto res26 = get(d2, d3, d2);
	constexpr auto res27 = get(d2, d3, d3);
	constexpr auto res28 = get(d3, d1, d1);
	constexpr auto res29 = get(d3, d1, d2);
	constexpr auto res30 = get(d3, d1, d3);
	constexpr auto res31 = get(d3, d2, d1);
	constexpr auto res32 = get(d3, d2, d2);
	constexpr auto res33 = get(d3, d2, d3);

	BOOST_TEST((res01 == 7));
	BOOST_TEST((res02 == 7));
	BOOST_TEST((res03 == 7));
	BOOST_TEST((res04 == 7));
	BOOST_TEST((res05 == 7));
	BOOST_TEST((res06 == 7));
	BOOST_TEST((res07 == 7));
	BOOST_TEST((res08 == 7));
	BOOST_TEST((res09 == 7));
	BOOST_TEST((res10 == 7));
	BOOST_TEST((res11 == 7));
	BOOST_TEST((res12 == 7));
	BOOST_TEST((res13 == 7));
	BOOST_TEST((res14 == 7));
	BOOST_TEST((res15 == 7));
	BOOST_TEST((res16 == 7));
	BOOST_TEST((res17 == 7));
	BOOST_TEST((res18 == 7));
	BOOST_TEST((res19 == 7));
	BOOST_TEST((res20 == 7));
	BOOST_TEST((res21 == 7));
	BOOST_TEST((res22 == 7));
	BOOST_TEST((res23 == 7));
	BOOST_TEST((res24 == 7));
	BOOST_TEST((res25 == 7));
	BOOST_TEST((res26 == 7));
	BOOST_TEST((res27 == 7));
	BOOST_TEST((res28 == 7));
	BOOST_TEST((res29 == 7));
	BOOST_TEST((res30 == 7));
	BOOST_TEST((res31 == 7));
	BOOST_TEST((res32 == 7));
	BOOST_TEST((res33 == 7));

	BOOST_TEST((rt_id(res01) == (id< DimT< true, 7 > >)));
	BOOST_TEST((rt_id(res02) == (id< DimT< false, 7 > >)));
	BOOST_TEST((rt_id(res03) == (id< DimT< false, 0 > >)));
	BOOST_TEST((rt_id(res04) == (id< DimT< true, 7 > >)));
	BOOST_TEST((rt_id(res05) == (id< DimT< false, 7 > >)));
	BOOST_TEST((rt_id(res06) == (id< DimT< false, 0 > >)));
	BOOST_TEST((rt_id(res07) == (id< DimT< true, 7 > >)));
	BOOST_TEST((rt_id(res08) == (id< DimT< true, 7 > >)));
	BOOST_TEST((rt_id(res09) == (id< DimT< true, 7 > >)));
	BOOST_TEST((rt_id(res10) == (id< DimT< false, 7 > >)));
	BOOST_TEST((rt_id(res11) == (id< DimT< true, 7 > >)));
	BOOST_TEST((rt_id(res12) == (id< DimT< false, 7 > >)));
	BOOST_TEST((rt_id(res13) == (id< DimT< true, 7 > >)));
	BOOST_TEST((rt_id(res14) == (id< DimT< false, 7 > >)));
	BOOST_TEST((rt_id(res15) == (id< DimT< false, 0 > >)));
	BOOST_TEST((rt_id(res16) == (id< DimT< true, 7 > >)));
	BOOST_TEST((rt_id(res17) == (id< DimT< true, 7 > >)));
	BOOST_TEST((rt_id(res18) == (id< DimT< true, 7 > >)));
	BOOST_TEST((rt_id(res19) == (id< DimT< true, 7 > >)));
	BOOST_TEST((rt_id(res20) == (id< DimT< true, 7 > >)));
	BOOST_TEST((rt_id(res21) == (id< DimT< true, 7 > >)));
	BOOST_TEST((rt_id(res22) == (id< DimT< true, 7 > >)));
	BOOST_TEST((rt_id(res23) == (id< DimT< true, 7 > >)));
	BOOST_TEST((rt_id(res24) == (id< DimT< true, 7 > >)));
	BOOST_TEST((rt_id(res25) == (id< DimT< true, 7 > >)));
	BOOST_TEST((rt_id(res26) == (id< DimT< false, 7 > >)));
	BOOST_TEST((rt_id(res27) == (id< DimT< false, 7 > >)));
	BOOST_TEST((rt_id(res28) == (id< DimT< true, 7 > >)));
	BOOST_TEST((rt_id(res29) == (id< DimT< true, 7 > >)));
	BOOST_TEST((rt_id(res30) == (id< DimT< true, 7 > >)));
	BOOST_TEST((rt_id(res31) == (id< DimT< true, 7 > >)));
	BOOST_TEST((rt_id(res32) == (id< DimT< false, 7 > >)));
	BOOST_TEST((rt_id(res33) == (id< DimT< false, 7 > >)));
}


template < template < bool, size_t > typename DimT >
void add_test(utf::test_suite* ts){
	ts->add(BOOST_TEST_CASE(&construct< DimT >));
	ts->add(BOOST_TEST_CASE(&default_construct< DimT >));
	ts->add(BOOST_TEST_CASE(&convert2size_t< DimT >));
	ts->add(BOOST_TEST_CASE(&convert2dim< DimT >));
	ts->add(BOOST_TEST_CASE(&get_dim< DimT >));
	ts->add(BOOST_TEST_CASE((&arithmetic< DimT, std::plus<> >)));
	ts->add(BOOST_TEST_CASE((&arithmetic< DimT, std::minus<> >)));
	ts->add(BOOST_TEST_CASE((&arithmetic< DimT, std::multiplies<> >)));
	ts->add(BOOST_TEST_CASE((&arithmetic< DimT, std::divides<> >)));
	ts->add(BOOST_TEST_CASE((&arithmetic< DimT, std::modulus<> >)));
	ts->add(BOOST_TEST_CASE((&compare< DimT, std::equal_to<> >)));
	ts->add(BOOST_TEST_CASE((&compare< DimT, std::not_equal_to<> >)));
	ts->add(BOOST_TEST_CASE((&compare< DimT, std::less<> >)));
	ts->add(BOOST_TEST_CASE((&compare< DimT, std::less_equal<> >)));
	ts->add(BOOST_TEST_CASE((&compare< DimT, std::greater<> >)));
	ts->add(BOOST_TEST_CASE((&compare< DimT, std::greater_equal<> >)));
}

void make_col_t(){
	constexpr auto cct = cols< 3 >();
	constexpr auto crt = cols_rt< 3 >();
	constexpr auto rrt = cols(3);

	BOOST_TEST((rt_id(cct) == id< col_t< true, 3 > >));
	BOOST_TEST((rt_id(crt) == id< col_t< false, 3 > >));
	BOOST_TEST((rt_id(rrt) == id< col_t< false, 0 > >));

	BOOST_TEST((cct == 3));
	BOOST_TEST((crt == 3));
	BOOST_TEST((rrt == 3));
}

void make_row_t(){
	constexpr auto cct = rows< 3 >();
	constexpr auto crt = rows_rt< 3 >();
	constexpr auto rrt = rows(3);

	BOOST_TEST((rt_id(cct) == id< row_t< true, 3 > >));
	BOOST_TEST((rt_id(crt) == id< row_t< false, 3 > >));
	BOOST_TEST((rt_id(rrt) == id< row_t< false, 0 > >));

	BOOST_TEST((cct == 3));
	BOOST_TEST((crt == 3));
	BOOST_TEST((rrt == 3));
}

void make_dim_t(){
	constexpr auto cct = dims< 3 >();
	constexpr auto crt = dims_rt< 3 >();
	constexpr auto rrt = dims(3);

	BOOST_TEST((rt_id(cct) == id< dim_t< true, 3 > >));
	BOOST_TEST((rt_id(crt) == id< dim_t< false, 3 > >));
	BOOST_TEST((rt_id(rrt) == id< dim_t< false, 0 > >));

	BOOST_TEST((cct == 3));
	BOOST_TEST((crt == 3));
	BOOST_TEST((rrt == 3));
}


void dims_t_default_construct(){
	constexpr auto c = 3;
	constexpr auto r = 4;

	constexpr auto cc = dims_t< c, r >();
	constexpr auto cr = dims_t< c, 0 >();
	constexpr auto rc = dims_t< 0, r >();
	constexpr auto rr = dims_t< 0, 0 >();

	BOOST_TEST((CP(cc.cols()) == c));
	BOOST_TEST((CP(cr.cols()) == c));
	BOOST_TEST((CP(rc.cols()) == 0));
	BOOST_TEST((CP(rr.cols()) == 0));

	BOOST_TEST((CP(cc.rows()) == r));
	BOOST_TEST((CP(cr.rows()) == 0));
	BOOST_TEST((CP(rc.rows()) == r));
	BOOST_TEST((CP(rr.rows()) == 0));
}


void dims_t_construct(){
	constexpr auto c = 3;
	constexpr auto r = 4;

	constexpr auto cc = dims_t< c, r >(cols< c >(), rows< r >());
	constexpr auto cr = dims_t< c, 0 >(cols< c >(), rows(r));
	constexpr auto rc = dims_t< 0, r >(cols(c), rows< r >());
	constexpr auto rr = dims_t< 0, 0 >(cols(c), rows(r));

	BOOST_TEST((CP(cc.cols()) == c));
	BOOST_TEST((CP(cr.cols()) == c));
	BOOST_TEST((CP(rc.cols()) == c));
	BOOST_TEST((CP(rr.cols()) == c));

	BOOST_TEST((CP(cc.rows()) == r));
	BOOST_TEST((CP(cr.rows()) == r));
	BOOST_TEST((CP(rc.rows()) == r));
	BOOST_TEST((CP(rr.rows()) == r));
}


void dims_t_make(){
	constexpr auto c = 3;
	constexpr auto r = 4;

	constexpr auto ll = dims(c, r);
	constexpr auto lr = dims(c, rows(r));
	constexpr auto lc = dims(c, rows< r >());
	constexpr auto ld = dims(c, rows_rt< r >());

	constexpr auto rl = dims(cols(c), r);
	constexpr auto rr = dims(cols(c), rows(r));
	constexpr auto rc = dims(cols(c), rows< r >());
	constexpr auto rd = dims(cols(c), rows_rt< r >());

	constexpr auto cl = dims(cols< c >(), r);
	constexpr auto cr = dims(cols< c >(), rows(r));
	constexpr auto cc = dims(cols< c >(), rows< r >());
	constexpr auto cd = dims(cols< c >(), rows_rt< r >());

	constexpr auto dl = dims(cols_rt< c >(), r);
	constexpr auto dr = dims(cols_rt< c >(), rows(r));
	constexpr auto dc = dims(cols_rt< c >(), rows< r >());
	constexpr auto dd = dims(cols_rt< c >(), rows_rt< r >());


	BOOST_TEST((rt_id(ll) == id< dims_t< 0, 0 > >));
	BOOST_TEST((rt_id(lr) == id< dims_t< 0, 0 > >));
	BOOST_TEST((rt_id(lc) == id< dims_t< 0, 4 > >));
	BOOST_TEST((rt_id(ld) == id< dims_t< 0, 0 > >));

	BOOST_TEST((rt_id(rl) == id< dims_t< 0, 0 > >));
	BOOST_TEST((rt_id(rr) == id< dims_t< 0, 0 > >));
	BOOST_TEST((rt_id(rc) == id< dims_t< 0, 4 > >));
	BOOST_TEST((rt_id(rd) == id< dims_t< 0, 0 > >));

	BOOST_TEST((rt_id(cl) == id< dims_t< 3, 0 > >));
	BOOST_TEST((rt_id(cr) == id< dims_t< 3, 0 > >));
	BOOST_TEST((rt_id(cc) == id< dims_t< 3, 4 > >));
	BOOST_TEST((rt_id(cd) == id< dims_t< 3, 0 > >));

	BOOST_TEST((rt_id(dl) == id< dims_t< 0, 0 > >));
	BOOST_TEST((rt_id(dr) == id< dims_t< 0, 0 > >));
	BOOST_TEST((rt_id(dc) == id< dims_t< 0, 4 > >));
	BOOST_TEST((rt_id(dd) == id< dims_t< 0, 0 > >));


	BOOST_TEST((rt_id(ll.cols()) == id< col_t< false, 0 > >));
	BOOST_TEST((rt_id(lr.cols()) == id< col_t< false, 0 > >));
	BOOST_TEST((rt_id(lc.cols()) == id< col_t< false, 0 > >));
	BOOST_TEST((rt_id(ld.cols()) == id< col_t< false, 0 > >));

	BOOST_TEST((rt_id(rl.cols()) == id< col_t< false, 0 > >));
	BOOST_TEST((rt_id(rr.cols()) == id< col_t< false, 0 > >));
	BOOST_TEST((rt_id(rc.cols()) == id< col_t< false, 0 > >));
	BOOST_TEST((rt_id(rd.cols()) == id< col_t< false, 0 > >));

	BOOST_TEST((rt_id(cl.cols()) == id< col_t< true, 3 > >));
	BOOST_TEST((rt_id(cr.cols()) == id< col_t< true, 3 > >));
	BOOST_TEST((rt_id(cc.cols()) == id< col_t< true, 3 > >));
	BOOST_TEST((rt_id(cd.cols()) == id< col_t< true, 3 > >));

	BOOST_TEST((rt_id(dl.cols()) == id< col_t< false, 0 > >));
	BOOST_TEST((rt_id(dr.cols()) == id< col_t< false, 0 > >));
	BOOST_TEST((rt_id(dc.cols()) == id< col_t< false, 0 > >));
	BOOST_TEST((rt_id(dd.cols()) == id< col_t< false, 0 > >));


	BOOST_TEST((rt_id(ll.rows()) == id< row_t< false, 0 > >));
	BOOST_TEST((rt_id(lr.rows()) == id< row_t< false, 0 > >));
	BOOST_TEST((rt_id(lc.rows()) == id< row_t< true, 4 > >));
	BOOST_TEST((rt_id(ld.rows()) == id< row_t< false, 0 > >));

	BOOST_TEST((rt_id(rl.rows()) == id< row_t< false, 0 > >));
	BOOST_TEST((rt_id(rr.rows()) == id< row_t< false, 0 > >));
	BOOST_TEST((rt_id(rc.rows()) == id< row_t< true, 4 > >));
	BOOST_TEST((rt_id(rd.rows()) == id< row_t< false, 0 > >));

	BOOST_TEST((rt_id(cl.rows()) == id< row_t< false, 0 > >));
	BOOST_TEST((rt_id(cr.rows()) == id< row_t< false, 0 > >));
	BOOST_TEST((rt_id(cc.rows()) == id< row_t< true, 4 > >));
	BOOST_TEST((rt_id(cd.rows()) == id< row_t< false, 0 > >));

	BOOST_TEST((rt_id(dl.rows()) == id< row_t< false, 0 > >));
	BOOST_TEST((rt_id(dr.rows()) == id< row_t< false, 0 > >));
	BOOST_TEST((rt_id(dc.rows()) == id< row_t< true, 4 > >));
	BOOST_TEST((rt_id(dd.rows()) == id< row_t< false, 0 > >));


	BOOST_TEST((CP(ll.cols()) == 3));
	BOOST_TEST((CP(lr.cols()) == 3));
	BOOST_TEST((CP(lc.cols()) == 3));
	BOOST_TEST((CP(ld.cols()) == 3));

	BOOST_TEST((CP(rl.cols()) == 3));
	BOOST_TEST((CP(rr.cols()) == 3));
	BOOST_TEST((CP(rc.cols()) == 3));
	BOOST_TEST((CP(rd.cols()) == 3));

	BOOST_TEST((CP(cl.cols()) == 3));
	BOOST_TEST((CP(cr.cols()) == 3));
	BOOST_TEST((CP(cc.cols()) == 3));
	BOOST_TEST((CP(cd.cols()) == 3));

	BOOST_TEST((CP(dl.cols()) == 3));
	BOOST_TEST((CP(dr.cols()) == 3));
	BOOST_TEST((CP(dc.cols()) == 3));
	BOOST_TEST((CP(dd.cols()) == 3));


	BOOST_TEST((CP(ll.rows()) == 4));
	BOOST_TEST((CP(lr.rows()) == 4));
	BOOST_TEST((CP(lc.rows()) == 4));
	BOOST_TEST((CP(ld.rows()) == 4));

	BOOST_TEST((CP(rl.rows()) == 4));
	BOOST_TEST((CP(rr.rows()) == 4));
	BOOST_TEST((CP(rc.rows()) == 4));
	BOOST_TEST((CP(rd.rows()) == 4));

	BOOST_TEST((CP(cl.rows()) == 4));
	BOOST_TEST((CP(cr.rows()) == 4));
	BOOST_TEST((CP(cc.rows()) == 4));
	BOOST_TEST((CP(cd.rows()) == 4));

	BOOST_TEST((CP(dl.rows()) == 4));
	BOOST_TEST((CP(dr.rows()) == 4));
	BOOST_TEST((CP(dc.rows()) == 4));
	BOOST_TEST((CP(dd.rows()) == 4));
}


void dims_t_compare(){
	constexpr auto c1 = 3;
	constexpr auto r1 = 4;
	constexpr auto c2 = 6;
	constexpr auto r2 = 5;

	constexpr auto cc1 = dims_t< c1, r1 >(cols< c1 >(), rows< r1 >());
	constexpr auto cr1 = dims_t< c1, 0 >(cols< c1 >(), rows(r1));
	constexpr auto rc1 = dims_t< 0, r1 >(cols(c1), rows< r1 >());
	constexpr auto rr1 = dims_t< 0, 0 >(cols(c1), rows(r1));

	constexpr auto cc2 = dims_t< c2, r2 >(cols< c2 >(), rows< r2 >());
	constexpr auto cr2 = dims_t< c2, 0 >(cols< c2 >(), rows(r2));
	constexpr auto rc2 = dims_t< 0, r2 >(cols(c2), rows< r2 >());
	constexpr auto rr2 = dims_t< 0, 0 >(cols(c2), rows(r2));


	BOOST_TEST((rt_id(cc1 == cc2) == id< bool >));
	BOOST_TEST((rt_id(cc1 == cr2) == id< bool >));
	BOOST_TEST((rt_id(cc1 == rc2) == id< bool >));
	BOOST_TEST((rt_id(cc1 == rr2) == id< bool >));

	BOOST_TEST((rt_id(cr1 == cc2) == id< bool >));
	BOOST_TEST((rt_id(cr1 == cr2) == id< bool >));
	BOOST_TEST((rt_id(cr1 == rc2) == id< bool >));
	BOOST_TEST((rt_id(cr1 == rr2) == id< bool >));

	BOOST_TEST((rt_id(rc1 == cc2) == id< bool >));
	BOOST_TEST((rt_id(rc1 == cr2) == id< bool >));
	BOOST_TEST((rt_id(rc1 == rc2) == id< bool >));
	BOOST_TEST((rt_id(rc1 == rr2) == id< bool >));

	BOOST_TEST((rt_id(rr1 == cc2) == id< bool >));
	BOOST_TEST((rt_id(rr1 == cr2) == id< bool >));
	BOOST_TEST((rt_id(rr1 == rc2) == id< bool >));
	BOOST_TEST((rt_id(rr1 == rr2) == id< bool >));


	BOOST_TEST((rt_id(cc1 != cc2) == id< bool >));
	BOOST_TEST((rt_id(cc1 != cr2) == id< bool >));
	BOOST_TEST((rt_id(cc1 != rc2) == id< bool >));
	BOOST_TEST((rt_id(cc1 != rr2) == id< bool >));

	BOOST_TEST((rt_id(cr1 != cc2) == id< bool >));
	BOOST_TEST((rt_id(cr1 != cr2) == id< bool >));
	BOOST_TEST((rt_id(cr1 != rc2) == id< bool >));
	BOOST_TEST((rt_id(cr1 != rr2) == id< bool >));

	BOOST_TEST((rt_id(rc1 != cc2) == id< bool >));
	BOOST_TEST((rt_id(rc1 != cr2) == id< bool >));
	BOOST_TEST((rt_id(rc1 != rc2) == id< bool >));
	BOOST_TEST((rt_id(rc1 != rr2) == id< bool >));

	BOOST_TEST((rt_id(rr1 != cc2) == id< bool >));
	BOOST_TEST((rt_id(rr1 != cr2) == id< bool >));
	BOOST_TEST((rt_id(rr1 != rc2) == id< bool >));
	BOOST_TEST((rt_id(rr1 != rr2) == id< bool >));


	BOOST_TEST((!(cc1 == cc2)));
	BOOST_TEST((!(cc1 == cr2)));
	BOOST_TEST((!(cc1 == rc2)));
	BOOST_TEST((!(cc1 == rr2)));

	BOOST_TEST((!(cr1 == cc2)));
	BOOST_TEST((!(cr1 == cr2)));
	BOOST_TEST((!(cr1 == rc2)));
	BOOST_TEST((!(cr1 == rr2)));

	BOOST_TEST((!(rc1 == cc2)));
	BOOST_TEST((!(rc1 == cr2)));
	BOOST_TEST((!(rc1 == rc2)));
	BOOST_TEST((!(rc1 == rr2)));

	BOOST_TEST((!(rr1 == cc2)));
	BOOST_TEST((!(rr1 == cr2)));
	BOOST_TEST((!(rr1 == rc2)));
	BOOST_TEST((!(rr1 == rr2)));


	BOOST_TEST(((cc1 != cc2)));
	BOOST_TEST(((cc1 != cr2)));
	BOOST_TEST(((cc1 != rc2)));
	BOOST_TEST(((cc1 != rr2)));

	BOOST_TEST(((cr1 != cc2)));
	BOOST_TEST(((cr1 != cr2)));
	BOOST_TEST(((cr1 != rc2)));
	BOOST_TEST(((cr1 != rr2)));

	BOOST_TEST(((rc1 != cc2)));
	BOOST_TEST(((rc1 != cr2)));
	BOOST_TEST(((rc1 != rc2)));
	BOOST_TEST(((rc1 != rr2)));

	BOOST_TEST(((rr1 != cc2)));
	BOOST_TEST(((rr1 != cr2)));
	BOOST_TEST(((rr1 != rc2)));
	BOOST_TEST(((rr1 != rr2)));
}

template < typename Op >
void dims_t_arithmetic_size_t(){
	constexpr auto op = Op();
	constexpr auto c = size_t(9);
	constexpr auto r = size_t(7);
	constexpr auto v = size_t(5);

	constexpr auto cc = dims_t< c, r >(cols< c >(), rows< r >());
	constexpr auto cr = dims_t< c, 0 >(cols< c >(), rows(r));
	constexpr auto rc = dims_t< 0, r >(cols(c), rows< r >());
	constexpr auto rr = dims_t< 0, 0 >(cols(c), rows(r));

	constexpr auto vcc = dims< v >();
	constexpr auto vcr = dims_rt< v >();
	constexpr auto vrr = dims(v);


	BOOST_TEST((rt_id(CP(op(cc, vcc))) == id< dims_t< op(c, v), op(r, v) > >));
	BOOST_TEST((rt_id(CP(op(cr, vcc))) == id< dims_t< op(c, v), 0 > >));
	BOOST_TEST((rt_id(CP(op(rc, vcc))) == id< dims_t< 0, op(r, v) > >));
	BOOST_TEST((rt_id(CP(op(rr, vcc))) == id< dims_t< 0, 0 > >));

	BOOST_TEST((rt_id(CP(op(cc, vcr))) == id< dims_t< 0, 0 > >));
	BOOST_TEST((rt_id(CP(op(cr, vcr))) == id< dims_t< 0, 0 > >));
	BOOST_TEST((rt_id(CP(op(rc, vcr))) == id< dims_t< 0, 0 > >));
	BOOST_TEST((rt_id(CP(op(rr, vcr))) == id< dims_t< 0, 0 > >));

	BOOST_TEST((rt_id(CP(op(cc, vrr))) == id< dims_t< 0, 0 > >));
	BOOST_TEST((rt_id(CP(op(cr, vrr))) == id< dims_t< 0, 0 > >));
	BOOST_TEST((rt_id(CP(op(rc, vrr))) == id< dims_t< 0, 0 > >));
	BOOST_TEST((rt_id(CP(op(rr, vrr))) == id< dims_t< 0, 0 > >));


	BOOST_TEST((size_t(CP(op(cc, vcc).cols())) == op(c, v)));
	BOOST_TEST((size_t(CP(op(cr, vcc).cols())) == op(c, v)));
	BOOST_TEST((size_t(CP(op(rc, vcc).cols())) == op(c, v)));
	BOOST_TEST((size_t(CP(op(rr, vcc).cols())) == op(c, v)));

	BOOST_TEST((size_t(CP(op(cc, vcr).cols())) == op(c, v)));
	BOOST_TEST((size_t(CP(op(cr, vcr).cols())) == op(c, v)));
	BOOST_TEST((size_t(CP(op(rc, vcr).cols())) == op(c, v)));
	BOOST_TEST((size_t(CP(op(rr, vcr).cols())) == op(c, v)));

	BOOST_TEST((size_t(CP(op(cc, vrr).cols())) == op(c, v)));
	BOOST_TEST((size_t(CP(op(cr, vrr).cols())) == op(c, v)));
	BOOST_TEST((size_t(CP(op(rc, vrr).cols())) == op(c, v)));
	BOOST_TEST((size_t(CP(op(rr, vrr).cols())) == op(c, v)));


	BOOST_TEST((size_t(CP(op(cc, vcc).rows())) == op(r, v)));
	BOOST_TEST((size_t(CP(op(cr, vcc).rows())) == op(r, v)));
	BOOST_TEST((size_t(CP(op(rc, vcc).rows())) == op(r, v)));
	BOOST_TEST((size_t(CP(op(rr, vcc).rows())) == op(r, v)));

	BOOST_TEST((size_t(CP(op(cc, vcr).rows())) == op(r, v)));
	BOOST_TEST((size_t(CP(op(cr, vcr).rows())) == op(r, v)));
	BOOST_TEST((size_t(CP(op(rc, vcr).rows())) == op(r, v)));
	BOOST_TEST((size_t(CP(op(rr, vcr).rows())) == op(r, v)));

	BOOST_TEST((size_t(CP(op(cc, vrr).rows())) == op(r, v)));
	BOOST_TEST((size_t(CP(op(cr, vrr).rows())) == op(r, v)));
	BOOST_TEST((size_t(CP(op(rc, vrr).rows())) == op(r, v)));
	BOOST_TEST((size_t(CP(op(rr, vrr).rows())) == op(r, v)));
}


template < typename Op >
void dims_t_arithmetic(){
	constexpr auto op = Op();
	constexpr auto c1 = size_t(9);
	constexpr auto r1 = size_t(7);
	constexpr auto c2 = size_t(5);
	constexpr auto r2 = size_t(13);

	constexpr auto cc1 = dims_t< c1, r1 >(cols< c1 >(), rows< r1 >());
	constexpr auto cr1 = dims_t< c1, 0 >(cols< c1 >(), rows(r1));
	constexpr auto rc1 = dims_t< 0, r1 >(cols(c1), rows< r1 >());
	constexpr auto rr1 = dims_t< 0, 0 >(cols(c1), rows(r1));

	constexpr auto cc2 = dims_t< c2, r2 >(cols< c2 >(), rows< r2 >());
	constexpr auto cr2 = dims_t< c2, 0 >(cols< c2 >(), rows(r2));
	constexpr auto rc2 = dims_t< 0, r2 >(cols(c2), rows< r2 >());
	constexpr auto rr2 = dims_t< 0, 0 >(cols(c2), rows(r2));


	BOOST_TEST((rt_id(CP(op(cc1, cc2))) == id< dims_t< op(c1, c2), op(r1, r2) > >));
	BOOST_TEST((rt_id(CP(op(cc1, cr2))) == id< dims_t< op(c1, c2), 0 > >));
	BOOST_TEST((rt_id(CP(op(cc1, rc2))) == id< dims_t< 0, op(r1, r2) > >));
	BOOST_TEST((rt_id(CP(op(cc1, rr2))) == id< dims_t< 0, 0 > >));

	BOOST_TEST((rt_id(CP(op(cr1, cc2))) == id< dims_t< op(c1, c2), 0 > >));
	BOOST_TEST((rt_id(CP(op(cr1, cr2))) == id< dims_t< op(c1, c2), 0 > >));
	BOOST_TEST((rt_id(CP(op(cr1, rc2))) == id< dims_t< 0, 0 > >));
	BOOST_TEST((rt_id(CP(op(cr1, rr2))) == id< dims_t< 0, 0 > >));

	BOOST_TEST((rt_id(CP(op(rc1, cc2))) == id< dims_t< 0, op(r1, r2) > >));
	BOOST_TEST((rt_id(CP(op(rc1, cr2))) == id< dims_t< 0, 0 > >));
	BOOST_TEST((rt_id(CP(op(rc1, rc2))) == id< dims_t< 0, op(r1, r2) > >));
	BOOST_TEST((rt_id(CP(op(rc1, rr2))) == id< dims_t< 0, 0 > >));

	BOOST_TEST((rt_id(CP(op(rr1, cc2))) == id< dims_t< 0, 0 > >));
	BOOST_TEST((rt_id(CP(op(rr1, cr2))) == id< dims_t< 0, 0 > >));
	BOOST_TEST((rt_id(CP(op(rr1, rc2))) == id< dims_t< 0, 0 > >));
	BOOST_TEST((rt_id(CP(op(rr1, rr2))) == id< dims_t< 0, 0 > >));


	BOOST_TEST((size_t(CP(op(cc1, cc2).cols())) == op(c1, c2)));
	BOOST_TEST((size_t(CP(op(cc1, cr2).cols())) == op(c1, c2)));
	BOOST_TEST((size_t(CP(op(cc1, rc2).cols())) == op(c1, c2)));
	BOOST_TEST((size_t(CP(op(cc1, rr2).cols())) == op(c1, c2)));

	BOOST_TEST((size_t(CP(op(cr1, cc2).cols())) == op(c1, c2)));
	BOOST_TEST((size_t(CP(op(cr1, cr2).cols())) == op(c1, c2)));
	BOOST_TEST((size_t(CP(op(cr1, rc2).cols())) == op(c1, c2)));
	BOOST_TEST((size_t(CP(op(cr1, rr2).cols())) == op(c1, c2)));

	BOOST_TEST((size_t(CP(op(rc1, cc2).cols())) == op(c1, c2)));
	BOOST_TEST((size_t(CP(op(rc1, cr2).cols())) == op(c1, c2)));
	BOOST_TEST((size_t(CP(op(rc1, rc2).cols())) == op(c1, c2)));
	BOOST_TEST((size_t(CP(op(rc1, rr2).cols())) == op(c1, c2)));

	BOOST_TEST((size_t(CP(op(rr1, cc2).cols())) == op(c1, c2)));
	BOOST_TEST((size_t(CP(op(rr1, cr2).cols())) == op(c1, c2)));
	BOOST_TEST((size_t(CP(op(rr1, rc2).cols())) == op(c1, c2)));
	BOOST_TEST((size_t(CP(op(rr1, rr2).cols())) == op(c1, c2)));


	BOOST_TEST((size_t(CP(op(cc1, cc2).rows())) == op(r1, r2)));
	BOOST_TEST((size_t(CP(op(cc1, cr2).rows())) == op(r1, r2)));
	BOOST_TEST((size_t(CP(op(cc1, rc2).rows())) == op(r1, r2)));
	BOOST_TEST((size_t(CP(op(cc1, rr2).rows())) == op(r1, r2)));

	BOOST_TEST((size_t(CP(op(cr1, cc2).rows())) == op(r1, r2)));
	BOOST_TEST((size_t(CP(op(cr1, cr2).rows())) == op(r1, r2)));
	BOOST_TEST((size_t(CP(op(cr1, rc2).rows())) == op(r1, r2)));
	BOOST_TEST((size_t(CP(op(cr1, rr2).rows())) == op(r1, r2)));

	BOOST_TEST((size_t(CP(op(rc1, cc2).rows())) == op(r1, r2)));
	BOOST_TEST((size_t(CP(op(rc1, cr2).rows())) == op(r1, r2)));
	BOOST_TEST((size_t(CP(op(rc1, rc2).rows())) == op(r1, r2)));
	BOOST_TEST((size_t(CP(op(rc1, rr2).rows())) == op(r1, r2)));

	BOOST_TEST((size_t(CP(op(rr1, cc2).rows())) == op(r1, r2)));
	BOOST_TEST((size_t(CP(op(rr1, cr2).rows())) == op(r1, r2)));
	BOOST_TEST((size_t(CP(op(rr1, rc2).rows())) == op(r1, r2)));
	BOOST_TEST((size_t(CP(op(rr1, rr2).rows())) == op(r1, r2)));
}


void get_dims(){
	constexpr auto c = 3;
	constexpr auto r = 4;

	constexpr auto d1 = dims(cols< c >(), rows< r >());
	constexpr auto d2 = dims(cols< c >(), rows(r));
	constexpr auto d3 = dims(cols(c), rows< r >());
	constexpr auto d4 = dims(cols(c), rows(r));

	constexpr auto res01 = get(d1);
	constexpr auto res02 = get(d2);
	constexpr auto res03 = get(d3);
	constexpr auto res04 = get(d4);
	constexpr auto res05 = get(d1, d1);
	constexpr auto res06 = get(d1, d2);
	constexpr auto res07 = get(d1, d3);
	constexpr auto res08 = get(d1, d4);
	constexpr auto res09 = get(d2, d1);
	constexpr auto res10 = get(d2, d2);
	constexpr auto res11 = get(d2, d3);
	constexpr auto res12 = get(d2, d4);
	constexpr auto res13 = get(d3, d1);
	constexpr auto res14 = get(d3, d2);
	constexpr auto res15 = get(d3, d3);
	constexpr auto res16 = get(d3, d4);
	constexpr auto res17 = get(d4, d1);
	constexpr auto res18 = get(d4, d2);
	constexpr auto res19 = get(d4, d3);
	constexpr auto res20 = get(d4, d4);
	constexpr auto res21 = get(d1, d1, d1);
	constexpr auto res22 = get(d1, d1, d2);
	constexpr auto res23 = get(d1, d1, d3);
	constexpr auto res24 = get(d1, d1, d4);
	constexpr auto res25 = get(d1, d2, d1);
	constexpr auto res26 = get(d1, d2, d2);
	constexpr auto res27 = get(d1, d2, d3);
	constexpr auto res28 = get(d1, d2, d4);
	constexpr auto res29 = get(d1, d3, d1);
	constexpr auto res30 = get(d1, d3, d2);
	constexpr auto res31 = get(d1, d3, d3);
	constexpr auto res32 = get(d1, d3, d4);
	constexpr auto res33 = get(d1, d4, d1);
	constexpr auto res34 = get(d1, d4, d2);
	constexpr auto res35 = get(d1, d4, d3);
	constexpr auto res36 = get(d1, d4, d4);
	constexpr auto res37 = get(d2, d1, d1);
	constexpr auto res38 = get(d2, d1, d2);
	constexpr auto res39 = get(d2, d1, d3);
	constexpr auto res40 = get(d2, d1, d4);
	constexpr auto res41 = get(d2, d2, d1);
	constexpr auto res42 = get(d2, d2, d2);
	constexpr auto res43 = get(d2, d2, d3);
	constexpr auto res44 = get(d2, d2, d4);
	constexpr auto res45 = get(d2, d3, d1);
	constexpr auto res46 = get(d2, d3, d2);
	constexpr auto res47 = get(d2, d3, d3);
	constexpr auto res48 = get(d2, d3, d4);
	constexpr auto res49 = get(d2, d4, d1);
	constexpr auto res50 = get(d2, d4, d2);
	constexpr auto res51 = get(d2, d4, d3);
	constexpr auto res52 = get(d2, d4, d4);
	constexpr auto res53 = get(d3, d1, d1);
	constexpr auto res54 = get(d3, d1, d2);
	constexpr auto res55 = get(d3, d1, d3);
	constexpr auto res56 = get(d3, d1, d4);
	constexpr auto res57 = get(d3, d2, d1);
	constexpr auto res58 = get(d3, d2, d2);
	constexpr auto res59 = get(d3, d2, d3);
	constexpr auto res60 = get(d3, d2, d4);
	constexpr auto res61 = get(d3, d3, d1);
	constexpr auto res62 = get(d3, d3, d2);
	constexpr auto res63 = get(d3, d3, d3);
	constexpr auto res64 = get(d3, d3, d4);
	constexpr auto res65 = get(d3, d4, d1);
	constexpr auto res66 = get(d3, d4, d2);
	constexpr auto res67 = get(d3, d4, d3);
	constexpr auto res68 = get(d3, d4, d4);
	constexpr auto res69 = get(d4, d1, d1);
	constexpr auto res70 = get(d4, d1, d2);
	constexpr auto res71 = get(d4, d1, d3);
	constexpr auto res72 = get(d4, d1, d4);
	constexpr auto res73 = get(d4, d2, d1);
	constexpr auto res74 = get(d4, d2, d2);
	constexpr auto res75 = get(d4, d2, d3);
	constexpr auto res76 = get(d4, d2, d4);
	constexpr auto res77 = get(d4, d3, d1);
	constexpr auto res78 = get(d4, d3, d2);
	constexpr auto res79 = get(d4, d3, d3);
	constexpr auto res80 = get(d4, d3, d4);
	constexpr auto res81 = get(d4, d4, d1);
	constexpr auto res82 = get(d4, d4, d2);
	constexpr auto res83 = get(d4, d4, d3);
	constexpr auto res84 = get(d4, d4, d4);

	BOOST_TEST((rt_id(res01) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res02) == id< dims_t< c, 0 > >));
	BOOST_TEST((rt_id(res03) == id< dims_t< 0, r > >));
	BOOST_TEST((rt_id(res04) == id< dims_t< 0, 0 > >));
	BOOST_TEST((rt_id(res05) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res06) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res07) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res08) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res09) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res10) == id< dims_t< c, 0 > >));
	BOOST_TEST((rt_id(res11) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res12) == id< dims_t< c, 0 > >));
	BOOST_TEST((rt_id(res13) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res14) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res15) == id< dims_t< 0, r > >));
	BOOST_TEST((rt_id(res16) == id< dims_t< 0, r > >));
	BOOST_TEST((rt_id(res17) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res18) == id< dims_t< c, 0 > >));
	BOOST_TEST((rt_id(res19) == id< dims_t< 0, r > >));
	BOOST_TEST((rt_id(res20) == id< dims_t< 0, 0 > >));
	BOOST_TEST((rt_id(res21) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res22) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res23) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res24) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res25) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res26) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res27) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res28) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res29) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res30) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res31) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res32) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res33) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res34) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res35) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res36) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res37) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res38) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res39) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res40) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res41) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res42) == id< dims_t< c, 0 > >));
	BOOST_TEST((rt_id(res43) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res44) == id< dims_t< c, 0 > >));
	BOOST_TEST((rt_id(res45) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res46) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res47) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res48) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res49) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res50) == id< dims_t< c, 0 > >));
	BOOST_TEST((rt_id(res51) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res52) == id< dims_t< c, 0 > >));
	BOOST_TEST((rt_id(res53) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res54) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res55) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res56) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res57) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res58) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res59) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res60) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res61) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res62) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res63) == id< dims_t< 0, r > >));
	BOOST_TEST((rt_id(res64) == id< dims_t< 0, r > >));
	BOOST_TEST((rt_id(res65) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res66) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res67) == id< dims_t< 0, r > >));
	BOOST_TEST((rt_id(res68) == id< dims_t< 0, r > >));
	BOOST_TEST((rt_id(res69) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res70) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res71) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res72) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res73) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res74) == id< dims_t< c, 0 > >));
	BOOST_TEST((rt_id(res75) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res76) == id< dims_t< c, 0 > >));
	BOOST_TEST((rt_id(res77) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res78) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res79) == id< dims_t< 0, r > >));
	BOOST_TEST((rt_id(res80) == id< dims_t< 0, r > >));
	BOOST_TEST((rt_id(res81) == id< dims_t< c, r > >));
	BOOST_TEST((rt_id(res82) == id< dims_t< c, 0 > >));
	BOOST_TEST((rt_id(res83) == id< dims_t< 0, r > >));
	BOOST_TEST((rt_id(res84) == id< dims_t< 0, 0 > >));

	BOOST_TEST((res01 == dims(c, r)));
	BOOST_TEST((res02 == dims(c, r)));
	BOOST_TEST((res03 == dims(c, r)));
	BOOST_TEST((res04 == dims(c, r)));
	BOOST_TEST((res05 == dims(c, r)));
	BOOST_TEST((res06 == dims(c, r)));
	BOOST_TEST((res07 == dims(c, r)));
	BOOST_TEST((res08 == dims(c, r)));
	BOOST_TEST((res09 == dims(c, r)));
	BOOST_TEST((res10 == dims(c, r)));
	BOOST_TEST((res11 == dims(c, r)));
	BOOST_TEST((res12 == dims(c, r)));
	BOOST_TEST((res13 == dims(c, r)));
	BOOST_TEST((res14 == dims(c, r)));
	BOOST_TEST((res15 == dims(c, r)));
	BOOST_TEST((res16 == dims(c, r)));
	BOOST_TEST((res17 == dims(c, r)));
	BOOST_TEST((res18 == dims(c, r)));
	BOOST_TEST((res19 == dims(c, r)));
	BOOST_TEST((res20 == dims(c, r)));
	BOOST_TEST((res21 == dims(c, r)));
	BOOST_TEST((res22 == dims(c, r)));
	BOOST_TEST((res23 == dims(c, r)));
	BOOST_TEST((res24 == dims(c, r)));
	BOOST_TEST((res25 == dims(c, r)));
	BOOST_TEST((res26 == dims(c, r)));
	BOOST_TEST((res27 == dims(c, r)));
	BOOST_TEST((res28 == dims(c, r)));
	BOOST_TEST((res29 == dims(c, r)));
	BOOST_TEST((res30 == dims(c, r)));
	BOOST_TEST((res31 == dims(c, r)));
	BOOST_TEST((res32 == dims(c, r)));
	BOOST_TEST((res33 == dims(c, r)));
	BOOST_TEST((res34 == dims(c, r)));
	BOOST_TEST((res35 == dims(c, r)));
	BOOST_TEST((res36 == dims(c, r)));
	BOOST_TEST((res37 == dims(c, r)));
	BOOST_TEST((res38 == dims(c, r)));
	BOOST_TEST((res39 == dims(c, r)));
	BOOST_TEST((res40 == dims(c, r)));
	BOOST_TEST((res41 == dims(c, r)));
	BOOST_TEST((res42 == dims(c, r)));
	BOOST_TEST((res43 == dims(c, r)));
	BOOST_TEST((res44 == dims(c, r)));
	BOOST_TEST((res45 == dims(c, r)));
	BOOST_TEST((res46 == dims(c, r)));
	BOOST_TEST((res47 == dims(c, r)));
	BOOST_TEST((res48 == dims(c, r)));
	BOOST_TEST((res49 == dims(c, r)));
	BOOST_TEST((res50 == dims(c, r)));
	BOOST_TEST((res51 == dims(c, r)));
	BOOST_TEST((res52 == dims(c, r)));
	BOOST_TEST((res53 == dims(c, r)));
	BOOST_TEST((res54 == dims(c, r)));
	BOOST_TEST((res55 == dims(c, r)));
	BOOST_TEST((res56 == dims(c, r)));
	BOOST_TEST((res57 == dims(c, r)));
	BOOST_TEST((res58 == dims(c, r)));
	BOOST_TEST((res59 == dims(c, r)));
	BOOST_TEST((res60 == dims(c, r)));
	BOOST_TEST((res61 == dims(c, r)));
	BOOST_TEST((res62 == dims(c, r)));
	BOOST_TEST((res63 == dims(c, r)));
	BOOST_TEST((res64 == dims(c, r)));
	BOOST_TEST((res65 == dims(c, r)));
	BOOST_TEST((res66 == dims(c, r)));
	BOOST_TEST((res67 == dims(c, r)));
	BOOST_TEST((res68 == dims(c, r)));
	BOOST_TEST((res69 == dims(c, r)));
	BOOST_TEST((res70 == dims(c, r)));
	BOOST_TEST((res71 == dims(c, r)));
	BOOST_TEST((res72 == dims(c, r)));
	BOOST_TEST((res73 == dims(c, r)));
	BOOST_TEST((res74 == dims(c, r)));
	BOOST_TEST((res75 == dims(c, r)));
	BOOST_TEST((res76 == dims(c, r)));
	BOOST_TEST((res77 == dims(c, r)));
	BOOST_TEST((res78 == dims(c, r)));
	BOOST_TEST((res79 == dims(c, r)));
	BOOST_TEST((res80 == dims(c, r)));
	BOOST_TEST((res81 == dims(c, r)));
	BOOST_TEST((res82 == dims(c, r)));
	BOOST_TEST((res83 == dims(c, r)));
	BOOST_TEST((res84 == dims(c, r)));
}


int main(int argc, char** argv, char** /*envp*/){
	auto ts = BOOST_TEST_SUITE("suite_dim");

	add_test< col_t >(ts);
	add_test< row_t >(ts);
	add_test< dim_t >(ts);
	ts->add(BOOST_TEST_CASE(&dim_literal));
	ts->add(BOOST_TEST_CASE(&make_col_t));
	ts->add(BOOST_TEST_CASE(&make_row_t));
	ts->add(BOOST_TEST_CASE(&make_dim_t));
	ts->add(BOOST_TEST_CASE(&dims_t_default_construct));
	ts->add(BOOST_TEST_CASE(&dims_t_construct));
	ts->add(BOOST_TEST_CASE(&dims_t_make));
	ts->add(BOOST_TEST_CASE(&dims_t_compare));
	ts->add(BOOST_TEST_CASE(&dims_t_arithmetic_size_t< std::multiplies<> >));
	ts->add(BOOST_TEST_CASE(&dims_t_arithmetic_size_t< std::divides<> >));
	ts->add(BOOST_TEST_CASE(&dims_t_arithmetic_size_t< std::modulus<> >));
	ts->add(BOOST_TEST_CASE(&dims_t_arithmetic< std::plus<> >));
	ts->add(BOOST_TEST_CASE(&dims_t_arithmetic< std::minus<> >));
	ts->add(BOOST_TEST_CASE(&dims_t_arithmetic< std::multiplies<> >));
	ts->add(BOOST_TEST_CASE(&dims_t_arithmetic< std::divides<> >));
	ts->add(BOOST_TEST_CASE(&dims_t_arithmetic< std::modulus<> >));
	ts->add(BOOST_TEST_CASE(&get_dims));

	utf::framework::master_test_suite().add(ts);

	return utf::unit_test_main(&init_unit_test, argc, argv);
}
