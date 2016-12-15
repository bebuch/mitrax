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


template < bool Nct, typename CT, size_t N >
using DimT = mitrax::dim_type_t< Nct, CT, CT(N) >;


template < typename CT >
void construct(){
	constexpr auto cct = DimT< true,  CT, 3 >();
	constexpr auto crt = DimT< false, CT, 3 >();
	constexpr auto rrt = DimT< false, CT, 0 >(CT(3));

	BOOST_TEST((rt_id(cct) == id< DimT< true,  CT, 3 > >));
	BOOST_TEST((rt_id(crt) == id< DimT< false, CT, 3 > >));
	BOOST_TEST((rt_id(rrt) == id< DimT< false, CT, 0 > >));

	BOOST_TEST((size_t(cct) == 3));
	BOOST_TEST((size_t(crt) == 3));
	BOOST_TEST((size_t(rrt) == 3));
}


template < typename CT >
void default_construct(){
	constexpr auto cct = DimT< true,  CT, 3 >();
	constexpr auto crt = DimT< false, CT, 3 >();
	constexpr auto rrt = DimT< false, CT, 0 >();

	BOOST_TEST((rt_id(cct) == id< DimT< true,  CT, 3 > >));
	BOOST_TEST((rt_id(crt) == id< DimT< false, CT, 3 > >));
	BOOST_TEST((rt_id(rrt) == id< DimT< false, CT, 0 > >));

	BOOST_TEST((size_t(cct) == 3));
	BOOST_TEST((size_t(crt) == 3));
	BOOST_TEST((size_t(rrt) == 0));
}

void dim_literal(){
	BOOST_TEST((rt_id(3_c ) == id< col_t< true,  3_C > >));
	BOOST_TEST((rt_id(3_cd) == id< col_t< false, 3_C > >));

	BOOST_TEST((rt_id(3_r ) == id< row_t< true,  3_R > >));
	BOOST_TEST((rt_id(3_rd) == id< row_t< false, 3_R > >));

	BOOST_TEST((rt_id(3_d ) == id< dim_t< true,  3_D > >));
	BOOST_TEST((rt_id(3_dd) == id< dim_t< false, 3_D > >));
}

template < typename CT >
void convert2size_t(){
	constexpr auto cct = DimT< true,  CT, 3 >();
	constexpr auto crt = DimT< false, CT, 3 >();
	constexpr auto rrt = DimT< false, CT, 0 >(CT(3));

	BOOST_TEST((rt_id(size_t(cct)) == id< size_t >));
	BOOST_TEST((rt_id(size_t(crt)) == id< size_t >));
	BOOST_TEST((rt_id(size_t(rrt)) == id< size_t >));

	BOOST_TEST((CP(size_t(cct)) == 3));
	BOOST_TEST((CP(size_t(crt)) == 3));
	BOOST_TEST((CP(size_t(rrt)) == 3));
}

template < typename CT >
void convert2dim(){
	constexpr auto cct = DimT< true,  CT, 3 >();
	constexpr auto crt = DimT< false, CT, 3 >();
	constexpr auto rrt = DimT< false, CT, 0 >(CT(3));

	BOOST_TEST((rt_id(cct.as_col()) == id< col_t< true,  3_C > >));
	BOOST_TEST((rt_id(crt.as_col()) == id< col_t< false, 3_C > >));
	BOOST_TEST((rt_id(rrt.as_col()) == id< col_t< false, 0_C > >));

	BOOST_TEST((CP(cct.as_col()) == 3_c));
	BOOST_TEST((CP(crt.as_col()) == 3_c));
	BOOST_TEST((CP(rrt.as_col()) == 3_c));

	BOOST_TEST((rt_id(cct.as_row()) == id< row_t< true,  3_R > >));
	BOOST_TEST((rt_id(crt.as_row()) == id< row_t< false, 3_R > >));
	BOOST_TEST((rt_id(rrt.as_row()) == id< row_t< false, 0_R > >));

	BOOST_TEST((CP(cct.as_row()) == 3_r));
	BOOST_TEST((CP(crt.as_row()) == 3_r));
	BOOST_TEST((CP(rrt.as_row()) == 3_r));

	BOOST_TEST((rt_id(cct.as_dim()) == id< dim_t< true,  3_D > >));
	BOOST_TEST((rt_id(crt.as_dim()) == id< dim_t< false, 3_D > >));
	BOOST_TEST((rt_id(rrt.as_dim()) == id< dim_t< false, 0_D > >));

	BOOST_TEST((CP(cct.as_dim()) == 3_d));
	BOOST_TEST((CP(crt.as_dim()) == 3_d));
	BOOST_TEST((CP(rrt.as_dim()) == 3_d));
}

template < typename CT, typename Op >
void arithmetic(){
	constexpr auto op = Op();
	constexpr auto l = 4;
	constexpr auto r = 3;

	constexpr auto cct1 = DimT< true,  CT, l >();
	constexpr auto crt1 = DimT< false, CT, l >();
	constexpr auto rrt1 = DimT< false, CT, 0 >(CT(l));

	constexpr auto cct2 = DimT< true,  CT, r >();
	constexpr auto crt2 = DimT< false, CT, r >();
	constexpr auto rrt2 = DimT< false, CT, 0 >(CT(r));


	BOOST_TEST((rt_id(CP(op(cct1, cct2))) == id< DimT< true,  CT, op(l, r) > >));
	BOOST_TEST((rt_id(CP(op(cct1, crt2))) == id< DimT< true,  CT, op(l, r) > >));
	BOOST_TEST((rt_id(CP(op(cct1, rrt2))) == id< DimT< false, CT, 0 > >));

	BOOST_TEST((rt_id(CP(op(crt1, cct2))) == id< DimT< true,  CT, op(l, r) > >));
	BOOST_TEST((rt_id(CP(op(crt1, crt2))) == id< DimT< false, CT, op(l, r) > >));
	BOOST_TEST((rt_id(CP(op(crt1, rrt2))) == id< DimT< false, CT, 0 > >));

	BOOST_TEST((rt_id(CP(op(rrt1, cct2))) == id< DimT< false, CT, 0 > >));
	BOOST_TEST((rt_id(CP(op(rrt1, crt2))) == id< DimT< false, CT, 0 > >));
	BOOST_TEST((rt_id(CP(op(rrt1, rrt2))) == id< DimT< false, CT, 0 > >));


	BOOST_TEST((size_t(CP(op(cct1, cct2))) == op(l, r)));
	BOOST_TEST((size_t(CP(op(cct1, crt2))) == op(l, r)));
	BOOST_TEST((size_t(CP(op(cct1, rrt2))) == op(l, r)));

	BOOST_TEST((size_t(CP(op(crt1, cct2))) == op(l, r)));
	BOOST_TEST((size_t(CP(op(crt1, crt2))) == op(l, r)));
	BOOST_TEST((size_t(CP(op(crt1, rrt2))) == op(l, r)));

	BOOST_TEST((size_t(CP(op(rrt1, cct2))) == op(l, r)));
	BOOST_TEST((size_t(CP(op(rrt1, crt2))) == op(l, r)));
	BOOST_TEST((size_t(CP(op(rrt1, rrt2))) == op(l, r)));
}

template < typename CT, typename Op >
void compare(){
	constexpr auto op = Op();
	constexpr auto l = 4;
	constexpr auto r = 3;

	constexpr auto cct1 = DimT< true,  CT, l >();
	constexpr auto crt1 = DimT< false, CT, l >();
	constexpr auto rrt1 = DimT< false, CT, 0 >(CT(l));

	constexpr auto cct2 = DimT< true,  CT, r >();
	constexpr auto crt2 = DimT< false, CT, r >();
	constexpr auto rrt2 = DimT< false, CT, 0 >(CT(r));


	BOOST_TEST((rt_id(CP(op(cct1, cct2))) == id< bool >));
	BOOST_TEST((rt_id(CP(op(cct1, crt2))) == id< bool >));
	BOOST_TEST((rt_id(CP(op(cct1, rrt2))) == id< bool >));

	BOOST_TEST((rt_id(CP(op(crt1, cct2))) == id< bool >));
	BOOST_TEST((rt_id(CP(op(crt1, crt2))) == id< bool >));
	BOOST_TEST((rt_id(CP(op(crt1, rrt2))) == id< bool >));

	BOOST_TEST((rt_id(CP(op(rrt1, cct2))) == id< bool >));
	BOOST_TEST((rt_id(CP(op(rrt1, crt2))) == id< bool >));
	BOOST_TEST((rt_id(CP(op(rrt1, rrt2))) == id< bool >));


	BOOST_TEST((CP(op(cct1, cct2)) == op(l, r)));
	BOOST_TEST((CP(op(cct1, crt2)) == op(l, r)));
	BOOST_TEST((CP(op(cct1, rrt2)) == op(l, r)));

	BOOST_TEST((CP(op(crt1, cct2)) == op(l, r)));
	BOOST_TEST((CP(op(crt1, crt2)) == op(l, r)));
	BOOST_TEST((CP(op(crt1, rrt2)) == op(l, r)));

	BOOST_TEST((CP(op(rrt1, cct2)) == op(l, r)));
	BOOST_TEST((CP(op(rrt1, crt2)) == op(l, r)));
	BOOST_TEST((CP(op(rrt1, rrt2)) == op(l, r)));
}


template < typename CT >
void get_dim(){
	constexpr auto v = 7;

	constexpr auto d1 = DimT< true,  CT, v >();
	constexpr auto d2 = DimT< false, CT, v >();
	constexpr auto d3 = DimT< false, CT, 0 >(CT(v));

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

	BOOST_TEST((size_t(res01) == 7));
	BOOST_TEST((size_t(res02) == 7));
	BOOST_TEST((size_t(res03) == 7));
	BOOST_TEST((size_t(res04) == 7));
	BOOST_TEST((size_t(res05) == 7));
	BOOST_TEST((size_t(res06) == 7));
	BOOST_TEST((size_t(res07) == 7));
	BOOST_TEST((size_t(res08) == 7));
	BOOST_TEST((size_t(res09) == 7));
	BOOST_TEST((size_t(res10) == 7));
	BOOST_TEST((size_t(res11) == 7));
	BOOST_TEST((size_t(res12) == 7));
	BOOST_TEST((size_t(res13) == 7));
	BOOST_TEST((size_t(res14) == 7));
	BOOST_TEST((size_t(res15) == 7));
	BOOST_TEST((size_t(res16) == 7));
	BOOST_TEST((size_t(res17) == 7));
	BOOST_TEST((size_t(res18) == 7));
	BOOST_TEST((size_t(res19) == 7));
	BOOST_TEST((size_t(res20) == 7));
	BOOST_TEST((size_t(res21) == 7));
	BOOST_TEST((size_t(res22) == 7));
	BOOST_TEST((size_t(res23) == 7));
	BOOST_TEST((size_t(res24) == 7));
	BOOST_TEST((size_t(res25) == 7));
	BOOST_TEST((size_t(res26) == 7));
	BOOST_TEST((size_t(res27) == 7));
	BOOST_TEST((size_t(res28) == 7));
	BOOST_TEST((size_t(res29) == 7));
	BOOST_TEST((size_t(res30) == 7));
	BOOST_TEST((size_t(res31) == 7));
	BOOST_TEST((size_t(res32) == 7));
	BOOST_TEST((size_t(res33) == 7));

	BOOST_TEST((rt_id(res01) == (id< DimT< true,  CT, 7 > >)));
	BOOST_TEST((rt_id(res02) == (id< DimT< false, CT, 7 > >)));
	BOOST_TEST((rt_id(res03) == (id< DimT< false, CT, 0 > >)));
	BOOST_TEST((rt_id(res04) == (id< DimT< true,  CT, 7 > >)));
	BOOST_TEST((rt_id(res05) == (id< DimT< false, CT, 7 > >)));
	BOOST_TEST((rt_id(res06) == (id< DimT< false, CT, 0 > >)));
	BOOST_TEST((rt_id(res07) == (id< DimT< true,  CT, 7 > >)));
	BOOST_TEST((rt_id(res08) == (id< DimT< true,  CT, 7 > >)));
	BOOST_TEST((rt_id(res09) == (id< DimT< true,  CT, 7 > >)));
	BOOST_TEST((rt_id(res10) == (id< DimT< false, CT, 7 > >)));
	BOOST_TEST((rt_id(res11) == (id< DimT< true,  CT, 7 > >)));
	BOOST_TEST((rt_id(res12) == (id< DimT< false, CT, 7 > >)));
	BOOST_TEST((rt_id(res13) == (id< DimT< true,  CT, 7 > >)));
	BOOST_TEST((rt_id(res14) == (id< DimT< false, CT, 7 > >)));
	BOOST_TEST((rt_id(res15) == (id< DimT< false, CT, 0 > >)));
	BOOST_TEST((rt_id(res16) == (id< DimT< true,  CT, 7 > >)));
	BOOST_TEST((rt_id(res17) == (id< DimT< true,  CT, 7 > >)));
	BOOST_TEST((rt_id(res18) == (id< DimT< true,  CT, 7 > >)));
	BOOST_TEST((rt_id(res19) == (id< DimT< true,  CT, 7 > >)));
	BOOST_TEST((rt_id(res20) == (id< DimT< true,  CT, 7 > >)));
	BOOST_TEST((rt_id(res21) == (id< DimT< true,  CT, 7 > >)));
	BOOST_TEST((rt_id(res22) == (id< DimT< true,  CT, 7 > >)));
	BOOST_TEST((rt_id(res23) == (id< DimT< true,  CT, 7 > >)));
	BOOST_TEST((rt_id(res24) == (id< DimT< true,  CT, 7 > >)));
	BOOST_TEST((rt_id(res25) == (id< DimT< true,  CT, 7 > >)));
	BOOST_TEST((rt_id(res26) == (id< DimT< false, CT, 7 > >)));
	BOOST_TEST((rt_id(res27) == (id< DimT< false, CT, 7 > >)));
	BOOST_TEST((rt_id(res28) == (id< DimT< true,  CT, 7 > >)));
	BOOST_TEST((rt_id(res29) == (id< DimT< true,  CT, 7 > >)));
	BOOST_TEST((rt_id(res30) == (id< DimT< true,  CT, 7 > >)));
	BOOST_TEST((rt_id(res31) == (id< DimT< true,  CT, 7 > >)));
	BOOST_TEST((rt_id(res32) == (id< DimT< false, CT, 7 > >)));
	BOOST_TEST((rt_id(res33) == (id< DimT< false, CT, 7 > >)));
}


template < typename CT >
void add_test(utf::test_suite* ts){
	ts->add(BOOST_TEST_CASE(&construct< CT >));
	ts->add(BOOST_TEST_CASE(&default_construct< CT >));
	ts->add(BOOST_TEST_CASE(&convert2size_t< CT >));
	ts->add(BOOST_TEST_CASE(&convert2dim< CT >));
	ts->add(BOOST_TEST_CASE(&get_dim< CT >));
	ts->add(BOOST_TEST_CASE((&arithmetic< CT, std::plus<> >)));
	ts->add(BOOST_TEST_CASE((&arithmetic< CT, std::minus<> >)));
	ts->add(BOOST_TEST_CASE((&arithmetic< CT, std::multiplies<> >)));
	ts->add(BOOST_TEST_CASE((&arithmetic< CT, std::divides<> >)));
	ts->add(BOOST_TEST_CASE((&arithmetic< CT, std::modulus<> >)));
	ts->add(BOOST_TEST_CASE((&compare< CT, std::equal_to<> >)));
	ts->add(BOOST_TEST_CASE((&compare< CT, std::not_equal_to<> >)));
	ts->add(BOOST_TEST_CASE((&compare< CT, std::less<> >)));
	ts->add(BOOST_TEST_CASE((&compare< CT, std::less_equal<> >)));
	ts->add(BOOST_TEST_CASE((&compare< CT, std::greater<> >)));
	ts->add(BOOST_TEST_CASE((&compare< CT, std::greater_equal<> >)));
}

void make_col_t(){
	constexpr auto cct = cols< 3_C >();
	constexpr auto crt = cols_rt< 3_C >();
	constexpr auto rrt = cols(3_C);

	BOOST_TEST((rt_id(cct) == id< col_t< true,  3_C > >));
	BOOST_TEST((rt_id(crt) == id< col_t< false, 3_C > >));
	BOOST_TEST((rt_id(rrt) == id< col_t< false, 0_C > >));

	BOOST_TEST((cct == 3_c));
	BOOST_TEST((crt == 3_c));
	BOOST_TEST((rrt == 3_c));
}

void make_row_t(){
	constexpr auto cct = rows< 3_R >();
	constexpr auto crt = rows_rt< 3_R >();
	constexpr auto rrt = rows(3_R);

	BOOST_TEST((rt_id(cct) == id< row_t< true,  3_R > >));
	BOOST_TEST((rt_id(crt) == id< row_t< false, 3_R > >));
	BOOST_TEST((rt_id(rrt) == id< row_t< false, 0_R > >));

	BOOST_TEST((cct == 3_r));
	BOOST_TEST((crt == 3_r));
	BOOST_TEST((rrt == 3_r));
}

void make_dim_t(){
	constexpr auto cct = dims< 3_D >();
	constexpr auto crt = dims_rt< 3_D >();
	constexpr auto rrt = dims(3_D);

	BOOST_TEST((rt_id(cct) == id< dim_t< true,  3_D > >));
	BOOST_TEST((rt_id(crt) == id< dim_t< false, 3_D > >));
	BOOST_TEST((rt_id(rrt) == id< dim_t< false, 0_D > >));

	BOOST_TEST((cct == 3_d));
	BOOST_TEST((crt == 3_d));
	BOOST_TEST((rrt == 3_d));
}


void dim_pair_t_default_construct(){
	constexpr auto c = 3_C;
	constexpr auto r = 4_R;

	constexpr auto cc = auto_dim_pair_t< c, r >();
	constexpr auto cr = auto_dim_pair_t< c, 0_R >();
	constexpr auto rc = auto_dim_pair_t< 0_C, r >();
	constexpr auto rr = auto_dim_pair_t< 0_C, 0_R >();

	BOOST_TEST((CP(cc.cols()) == cols(c)));
	BOOST_TEST((CP(cr.cols()) == cols(c)));
	BOOST_TEST((CP(rc.cols()) == 0_cd));
	BOOST_TEST((CP(rr.cols()) == 0_cd));

	BOOST_TEST((CP(cc.rows()) == rows(r)));
	BOOST_TEST((CP(cr.rows()) == 0_rd));
	BOOST_TEST((CP(rc.rows()) == rows(r)));
	BOOST_TEST((CP(rr.rows()) == 0_rd));
}


void dim_pair_t_construct(){
	constexpr auto c = 3_C;
	constexpr auto r = 4_R;

	constexpr auto cc = auto_dim_pair_t< c, r >(cols< c >(), rows< r >());
	constexpr auto cr = auto_dim_pair_t< c, 0_R >(cols< c >(), rows(r));
	constexpr auto rc = auto_dim_pair_t< 0_C, r >(cols(c), rows< r >());
	constexpr auto rr = auto_dim_pair_t< 0_C, 0_R >(cols(c), rows(r));

	BOOST_TEST((CP(cc.cols()) == cols(c)));
	BOOST_TEST((CP(cr.cols()) == cols(c)));
	BOOST_TEST((CP(rc.cols()) == cols(c)));
	BOOST_TEST((CP(rr.cols()) == cols(c)));

	BOOST_TEST((CP(cc.rows()) == rows(r)));
	BOOST_TEST((CP(cr.rows()) == rows(r)));
	BOOST_TEST((CP(rc.rows()) == rows(r)));
	BOOST_TEST((CP(rr.rows()) == rows(r)));
}


void dim_pair_t_make(){
	constexpr auto c = 3_C;
	constexpr auto r = 4_R;

	constexpr auto ll = dim_pair(c, r);
	constexpr auto lr = dim_pair(c, rows(r));
	constexpr auto lc = dim_pair(c, rows< r >());
	constexpr auto ld = dim_pair(c, rows_rt< r >());

	constexpr auto rl = dim_pair(cols(c), r);
	constexpr auto rr = dim_pair(cols(c), rows(r));
	constexpr auto rc = dim_pair(cols(c), rows< r >());
	constexpr auto rd = dim_pair(cols(c), rows_rt< r >());

	constexpr auto cl = dim_pair(cols< c >(), r);
	constexpr auto cr = dim_pair(cols< c >(), rows(r));
	constexpr auto cc = dim_pair(cols< c >(), rows< r >());
	constexpr auto cd = dim_pair(cols< c >(), rows_rt< r >());

	constexpr auto dl = dim_pair(cols_rt< c >(), r);
	constexpr auto dr = dim_pair(cols_rt< c >(), rows(r));
	constexpr auto dc = dim_pair(cols_rt< c >(), rows< r >());
	constexpr auto dd = dim_pair(cols_rt< c >(), rows_rt< r >());


	BOOST_TEST((rt_id(ll) == id< dim_pair_t< false, 0_C, false, 0_R > >));
	BOOST_TEST((rt_id(lr) == id< dim_pair_t< false, 0_C, false, 0_R > >));
	BOOST_TEST((rt_id(lc) == id< dim_pair_t< false, 0_C, true,  4_R > >));
	BOOST_TEST((rt_id(ld) == id< dim_pair_t< false, 0_C, false, 4_R > >));

	BOOST_TEST((rt_id(rl) == id< dim_pair_t< false, 0_C, false, 0_R > >));
	BOOST_TEST((rt_id(rr) == id< dim_pair_t< false, 0_C, false, 0_R > >));
	BOOST_TEST((rt_id(rc) == id< dim_pair_t< false, 0_C, true,  4_R > >));
	BOOST_TEST((rt_id(rd) == id< dim_pair_t< false, 0_C, false, 4_R > >));

	BOOST_TEST((rt_id(cl) == id< dim_pair_t< true,  3_C, false, 0_R > >));
	BOOST_TEST((rt_id(cr) == id< dim_pair_t< true,  3_C, false, 0_R > >));
	BOOST_TEST((rt_id(cc) == id< dim_pair_t< true,  3_C, true,  4_R > >));
	BOOST_TEST((rt_id(cd) == id< dim_pair_t< true,  3_C, false, 4_R > >));

	BOOST_TEST((rt_id(dl) == id< dim_pair_t< false, 3_C, false, 0_R > >));
	BOOST_TEST((rt_id(dr) == id< dim_pair_t< false, 3_C, false, 0_R > >));
	BOOST_TEST((rt_id(dc) == id< dim_pair_t< false, 3_C, true,  4_R > >));
	BOOST_TEST((rt_id(dd) == id< dim_pair_t< false, 3_C, false, 4_R > >));


	BOOST_TEST((rt_id(ll.cols()) == id< col_t< false, 0_C > >));
	BOOST_TEST((rt_id(lr.cols()) == id< col_t< false, 0_C > >));
	BOOST_TEST((rt_id(lc.cols()) == id< col_t< false, 0_C > >));
	BOOST_TEST((rt_id(ld.cols()) == id< col_t< false, 0_C > >));

	BOOST_TEST((rt_id(rl.cols()) == id< col_t< false, 0_C > >));
	BOOST_TEST((rt_id(rr.cols()) == id< col_t< false, 0_C > >));
	BOOST_TEST((rt_id(rc.cols()) == id< col_t< false, 0_C > >));
	BOOST_TEST((rt_id(rd.cols()) == id< col_t< false, 0_C > >));

	BOOST_TEST((rt_id(cl.cols()) == id< col_t< true,  3_C > >));
	BOOST_TEST((rt_id(cr.cols()) == id< col_t< true,  3_C > >));
	BOOST_TEST((rt_id(cc.cols()) == id< col_t< true,  3_C > >));
	BOOST_TEST((rt_id(cd.cols()) == id< col_t< true,  3_C > >));

	BOOST_TEST((rt_id(dl.cols()) == id< col_t< false, 3_C > >));
	BOOST_TEST((rt_id(dr.cols()) == id< col_t< false, 3_C > >));
	BOOST_TEST((rt_id(dc.cols()) == id< col_t< false, 3_C > >));
	BOOST_TEST((rt_id(dd.cols()) == id< col_t< false, 3_C > >));


	BOOST_TEST((rt_id(ll.rows()) == id< row_t< false, 0_R > >));
	BOOST_TEST((rt_id(lr.rows()) == id< row_t< false, 0_R > >));
	BOOST_TEST((rt_id(lc.rows()) == id< row_t< true,  4_R > >));
	BOOST_TEST((rt_id(ld.rows()) == id< row_t< false, 4_R > >));

	BOOST_TEST((rt_id(rl.rows()) == id< row_t< false, 0_R > >));
	BOOST_TEST((rt_id(rr.rows()) == id< row_t< false, 0_R > >));
	BOOST_TEST((rt_id(rc.rows()) == id< row_t< true,  4_R > >));
	BOOST_TEST((rt_id(rd.rows()) == id< row_t< false, 4_R > >));

	BOOST_TEST((rt_id(cl.rows()) == id< row_t< false, 0_R > >));
	BOOST_TEST((rt_id(cr.rows()) == id< row_t< false, 0_R > >));
	BOOST_TEST((rt_id(cc.rows()) == id< row_t< true,  4_R > >));
	BOOST_TEST((rt_id(cd.rows()) == id< row_t< false, 4_R > >));

	BOOST_TEST((rt_id(dl.rows()) == id< row_t< false, 0_R > >));
	BOOST_TEST((rt_id(dr.rows()) == id< row_t< false, 0_R > >));
	BOOST_TEST((rt_id(dc.rows()) == id< row_t< true,  4_R > >));
	BOOST_TEST((rt_id(dd.rows()) == id< row_t< false, 4_R > >));


	BOOST_TEST((CP(ll.cols()) == 3_c));
	BOOST_TEST((CP(lr.cols()) == 3_c));
	BOOST_TEST((CP(lc.cols()) == 3_c));
	BOOST_TEST((CP(ld.cols()) == 3_c));

	BOOST_TEST((CP(rl.cols()) == 3_c));
	BOOST_TEST((CP(rr.cols()) == 3_c));
	BOOST_TEST((CP(rc.cols()) == 3_c));
	BOOST_TEST((CP(rd.cols()) == 3_c));

	BOOST_TEST((CP(cl.cols()) == 3_c));
	BOOST_TEST((CP(cr.cols()) == 3_c));
	BOOST_TEST((CP(cc.cols()) == 3_c));
	BOOST_TEST((CP(cd.cols()) == 3_c));

	BOOST_TEST((CP(dl.cols()) == 3_c));
	BOOST_TEST((CP(dr.cols()) == 3_c));
	BOOST_TEST((CP(dc.cols()) == 3_c));
	BOOST_TEST((CP(dd.cols()) == 3_c));


	BOOST_TEST((CP(ll.rows()) == 4_r));
	BOOST_TEST((CP(lr.rows()) == 4_r));
	BOOST_TEST((CP(lc.rows()) == 4_r));
	BOOST_TEST((CP(ld.rows()) == 4_r));

	BOOST_TEST((CP(rl.rows()) == 4_r));
	BOOST_TEST((CP(rr.rows()) == 4_r));
	BOOST_TEST((CP(rc.rows()) == 4_r));
	BOOST_TEST((CP(rd.rows()) == 4_r));

	BOOST_TEST((CP(cl.rows()) == 4_r));
	BOOST_TEST((CP(cr.rows()) == 4_r));
	BOOST_TEST((CP(cc.rows()) == 4_r));
	BOOST_TEST((CP(cd.rows()) == 4_r));

	BOOST_TEST((CP(dl.rows()) == 4_r));
	BOOST_TEST((CP(dr.rows()) == 4_r));
	BOOST_TEST((CP(dc.rows()) == 4_r));
	BOOST_TEST((CP(dd.rows()) == 4_r));
}


template <
	bool Cct1, col_ct C1, bool Rct1, row_ct R1,
	bool Cct2, col_ct C2, bool Rct2, row_ct R2 >
constexpr void dim_compare_test(
	dim_pair_t< Cct1, C1, Rct1, R1 > const& d1,
	dim_pair_t< Cct2, C2, Rct2, R2 > const& d2,
	bool equal_expection
)noexcept{
	BOOST_TEST((rt_id(d1 == d2) == id< bool >));
	BOOST_TEST((d1 == d2) == equal_expection);
	BOOST_TEST(!(d1 == d2) != equal_expection);
}


void dim_pair_t_compare(){
	using namespace ::mitrax::literals;

	constexpr auto cc1 = dim_pair(3_c,  4_r );
	constexpr auto cr1 = dim_pair(3_c,  4_rd);
	constexpr auto rc1 = dim_pair(3_cd, 4_r );
	constexpr auto rr1 = dim_pair(3_cd, 4_rd);

	constexpr auto cc2 = dim_pair(6_c,  5_r );
	constexpr auto cr2 = dim_pair(6_c,  5_rd);
	constexpr auto rc2 = dim_pair(6_cd, 5_r );
	constexpr auto rr2 = dim_pair(6_cd, 5_rd);

	constexpr auto cc3 = dim_pair(3_c,  5_r );
	constexpr auto cr3 = dim_pair(3_c,  5_rd);
	constexpr auto rc3 = dim_pair(3_cd, 5_r );
	constexpr auto rr3 = dim_pair(3_cd, 5_rd);

	constexpr auto cc4 = dim_pair(6_c,  4_r );
	constexpr auto cr4 = dim_pair(6_c,  4_rd);
	constexpr auto rc4 = dim_pair(6_cd, 4_r );
	constexpr auto rr4 = dim_pair(6_cd, 4_rd);


	dim_compare_test(cc1, cc1, true);
	dim_compare_test(cr1, cc1, true);
	dim_compare_test(rc1, cc1, true);
	dim_compare_test(rr1, cc1, true);

	dim_compare_test(cc1, cr1, true);
	dim_compare_test(cr1, cr1, true);
	dim_compare_test(rc1, cr1, true);
	dim_compare_test(rr1, cr1, true);

	dim_compare_test(cc1, rc1, true);
	dim_compare_test(cr1, rc1, true);
	dim_compare_test(rc1, rc1, true);
	dim_compare_test(rr1, rc1, true);

	dim_compare_test(cc1, rr1, true);
	dim_compare_test(cr1, rr1, true);
	dim_compare_test(rc1, rr1, true);
	dim_compare_test(rr1, rr1, true);


	dim_compare_test(cc1, cc2, false);
	dim_compare_test(cr1, cc2, false);
	dim_compare_test(rc1, cc2, false);
	dim_compare_test(rr1, cc2, false);

	dim_compare_test(cc1, cr2, false);
	dim_compare_test(cr1, cr2, false);
	dim_compare_test(rc1, cr2, false);
	dim_compare_test(rr1, cr2, false);

	dim_compare_test(cc1, rc2, false);
	dim_compare_test(cr1, rc2, false);
	dim_compare_test(rc1, rc2, false);
	dim_compare_test(rr1, rc2, false);

	dim_compare_test(cc1, rr2, false);
	dim_compare_test(cr1, rr2, false);
	dim_compare_test(rc1, rr2, false);
	dim_compare_test(rr1, rr2, false);


	dim_compare_test(cc1, cc3, false);
	dim_compare_test(cr1, cc3, false);
	dim_compare_test(rc1, cc3, false);
	dim_compare_test(rr1, cc3, false);

	dim_compare_test(cc1, cr3, false);
	dim_compare_test(cr1, cr3, false);
	dim_compare_test(rc1, cr3, false);
	dim_compare_test(rr1, cr3, false);

	dim_compare_test(cc1, rc3, false);
	dim_compare_test(cr1, rc3, false);
	dim_compare_test(rc1, rc3, false);
	dim_compare_test(rr1, rc3, false);

	dim_compare_test(cc1, rr3, false);
	dim_compare_test(cr1, rr3, false);
	dim_compare_test(rc1, rr3, false);
	dim_compare_test(rr1, rr3, false);


	dim_compare_test(cc1, cc4, false);
	dim_compare_test(cr1, cc4, false);
	dim_compare_test(rc1, cc4, false);
	dim_compare_test(rr1, cc4, false);

	dim_compare_test(cc1, cr4, false);
	dim_compare_test(cr1, cr4, false);
	dim_compare_test(rc1, cr4, false);
	dim_compare_test(rr1, cr4, false);

	dim_compare_test(cc1, rc4, false);
	dim_compare_test(cr1, rc4, false);
	dim_compare_test(rc1, rc4, false);
	dim_compare_test(rr1, rc4, false);

	dim_compare_test(cc1, rr4, false);
	dim_compare_test(cr1, rr4, false);
	dim_compare_test(rc1, rr4, false);
	dim_compare_test(rr1, rr4, false);
}

template < typename Op >
void dim_pair_t_arithmetic_size_t(){
	constexpr auto op = Op();
	constexpr auto c = 9_C;
	constexpr auto r = 7_R;
	constexpr auto v = 5_D;

	constexpr auto cc = auto_dim_pair_t< c, r >(cols< c >(), rows< r >());
	constexpr auto cr = auto_dim_pair_t< c, 0_R >(cols< c >(), rows(r));
	constexpr auto rc = auto_dim_pair_t< 0_C, r >(cols(c), rows< r >());
	constexpr auto rr = auto_dim_pair_t< 0_C, 0_R >(cols(c), rows(r));

	constexpr auto vcc = dims< v >();
	constexpr auto vcr = dims_rt< v >();
	constexpr auto vrr = dims(v);


	BOOST_TEST((rt_id(CP(op(cc, vcc))) == id< auto_dim_pair_t< op(c, col_ct(v)), op(r, row_ct(v)) > >));
	BOOST_TEST((rt_id(CP(op(cr, vcc))) == id< auto_dim_pair_t< op(c, col_ct(v)), 0_R > >));
	BOOST_TEST((rt_id(CP(op(rc, vcc))) == id< auto_dim_pair_t< 0_C, op(r, row_ct(v)) > >));
	BOOST_TEST((rt_id(CP(op(rr, vcc))) == id< auto_dim_pair_t< 0_C, 0_R > >));

	BOOST_TEST((rt_id(CP(op(cc, vcr))) == id< auto_dim_pair_t< op(c, col_ct(v)), op(r, row_ct(v)) > >));
	BOOST_TEST((rt_id(CP(op(cr, vcr))) == id< auto_dim_pair_t< op(c, col_ct(v)), 0_R > >));
	BOOST_TEST((rt_id(CP(op(rc, vcr))) == id< auto_dim_pair_t< 0_C, op(r, row_ct(v)) > >));
	BOOST_TEST((rt_id(CP(op(rr, vcr))) == id< auto_dim_pair_t< 0_C, 0_R > >));

	BOOST_TEST((rt_id(CP(op(cc, vrr))) == id< auto_dim_pair_t< 0_C, 0_R > >));
	BOOST_TEST((rt_id(CP(op(cr, vrr))) == id< auto_dim_pair_t< 0_C, 0_R > >));
	BOOST_TEST((rt_id(CP(op(rc, vrr))) == id< auto_dim_pair_t< 0_C, 0_R > >));
	BOOST_TEST((rt_id(CP(op(rr, vrr))) == id< auto_dim_pair_t< 0_C, 0_R > >));


	BOOST_TEST((CP(op(cc, vcc).cols()) == cols(op(c, col_ct(v)))));
	BOOST_TEST((CP(op(cr, vcc).cols()) == cols(op(c, col_ct(v)))));
	BOOST_TEST((CP(op(rc, vcc).cols()) == cols(op(c, col_ct(v)))));
	BOOST_TEST((CP(op(rr, vcc).cols()) == cols(op(c, col_ct(v)))));

	BOOST_TEST((CP(op(cc, vcr).cols()) == cols(op(c, col_ct(v)))));
	BOOST_TEST((CP(op(cr, vcr).cols()) == cols(op(c, col_ct(v)))));
	BOOST_TEST((CP(op(rc, vcr).cols()) == cols(op(c, col_ct(v)))));
	BOOST_TEST((CP(op(rr, vcr).cols()) == cols(op(c, col_ct(v)))));

	BOOST_TEST((CP(op(cc, vrr).cols()) == cols(op(c, col_ct(v)))));
	BOOST_TEST((CP(op(cr, vrr).cols()) == cols(op(c, col_ct(v)))));
	BOOST_TEST((CP(op(rc, vrr).cols()) == cols(op(c, col_ct(v)))));
	BOOST_TEST((CP(op(rr, vrr).cols()) == cols(op(c, col_ct(v)))));


	BOOST_TEST((CP(op(cc, vcc).rows()) == rows(op(r, row_ct(v)))));
	BOOST_TEST((CP(op(cr, vcc).rows()) == rows(op(r, row_ct(v)))));
	BOOST_TEST((CP(op(rc, vcc).rows()) == rows(op(r, row_ct(v)))));
	BOOST_TEST((CP(op(rr, vcc).rows()) == rows(op(r, row_ct(v)))));

	BOOST_TEST((CP(op(cc, vcr).rows()) == rows(op(r, row_ct(v)))));
	BOOST_TEST((CP(op(cr, vcr).rows()) == rows(op(r, row_ct(v)))));
	BOOST_TEST((CP(op(rc, vcr).rows()) == rows(op(r, row_ct(v)))));
	BOOST_TEST((CP(op(rr, vcr).rows()) == rows(op(r, row_ct(v)))));

	BOOST_TEST((CP(op(cc, vrr).rows()) == rows(op(r, row_ct(v)))));
	BOOST_TEST((CP(op(cr, vrr).rows()) == rows(op(r, row_ct(v)))));
	BOOST_TEST((CP(op(rc, vrr).rows()) == rows(op(r, row_ct(v)))));
	BOOST_TEST((CP(op(rr, vrr).rows()) == rows(op(r, row_ct(v)))));
}


template < typename Op >
void dim_pair_t_arithmetic(){
	constexpr auto op = Op();
	constexpr auto c1 = 9_C;
	constexpr auto r1 = 15_R;
	constexpr auto c2 = 5_C;
	constexpr auto r2 = 7_R;

	constexpr auto cc1 = auto_dim_pair_t< c1, r1 >(cols< c1 >(), rows< r1 >());
	constexpr auto cr1 = auto_dim_pair_t< c1, 0_R >(cols< c1 >(), rows(r1));
	constexpr auto rc1 = auto_dim_pair_t< 0_C, r1 >(cols(c1), rows< r1 >());
	constexpr auto rr1 = auto_dim_pair_t< 0_C, 0_R >(cols(c1), rows(r1));

	constexpr auto cc2 = auto_dim_pair_t< c2, r2 >(cols< c2 >(), rows< r2 >());
	constexpr auto cr2 = auto_dim_pair_t< c2, 0_R >(cols< c2 >(), rows(r2));
	constexpr auto rc2 = auto_dim_pair_t< 0_C, r2 >(cols(c2), rows< r2 >());
	constexpr auto rr2 = auto_dim_pair_t< 0_C, 0_R >(cols(c2), rows(r2));


	BOOST_TEST((rt_id(CP(op(cc1, cc2))) == id< auto_dim_pair_t< op(c1, c2), op(r1, r2) > >));
	BOOST_TEST((rt_id(CP(op(cc1, cr2))) == id< auto_dim_pair_t< op(c1, c2), 0_R > >));
	BOOST_TEST((rt_id(CP(op(cc1, rc2))) == id< auto_dim_pair_t< 0_C, op(r1, r2) > >));
	BOOST_TEST((rt_id(CP(op(cc1, rr2))) == id< auto_dim_pair_t< 0_C, 0_R > >));

	BOOST_TEST((rt_id(CP(op(cr1, cc2))) == id< auto_dim_pair_t< op(c1, c2), 0_R > >));
	BOOST_TEST((rt_id(CP(op(cr1, cr2))) == id< auto_dim_pair_t< op(c1, c2), 0_R > >));
	BOOST_TEST((rt_id(CP(op(cr1, rc2))) == id< auto_dim_pair_t< 0_C, 0_R > >));
	BOOST_TEST((rt_id(CP(op(cr1, rr2))) == id< auto_dim_pair_t< 0_C, 0_R > >));

	BOOST_TEST((rt_id(CP(op(rc1, cc2))) == id< auto_dim_pair_t< 0_C, op(r1, r2) > >));
	BOOST_TEST((rt_id(CP(op(rc1, cr2))) == id< auto_dim_pair_t< 0_C, 0_R > >));
	BOOST_TEST((rt_id(CP(op(rc1, rc2))) == id< auto_dim_pair_t< 0_C, op(r1, r2) > >));
	BOOST_TEST((rt_id(CP(op(rc1, rr2))) == id< auto_dim_pair_t< 0_C, 0_R > >));

	BOOST_TEST((rt_id(CP(op(rr1, cc2))) == id< auto_dim_pair_t< 0_C, 0_R > >));
	BOOST_TEST((rt_id(CP(op(rr1, cr2))) == id< auto_dim_pair_t< 0_C, 0_R > >));
	BOOST_TEST((rt_id(CP(op(rr1, rc2))) == id< auto_dim_pair_t< 0_C, 0_R > >));
	BOOST_TEST((rt_id(CP(op(rr1, rr2))) == id< auto_dim_pair_t< 0_C, 0_R > >));


	BOOST_TEST((CP(op(cc1, cc2).cols()) == cols(op(c1, c2))));
	BOOST_TEST((CP(op(cc1, cr2).cols()) == cols(op(c1, c2))));
	BOOST_TEST((CP(op(cc1, rc2).cols()) == cols(op(c1, c2))));
	BOOST_TEST((CP(op(cc1, rr2).cols()) == cols(op(c1, c2))));

	BOOST_TEST((CP(op(cr1, cc2).cols()) == cols(op(c1, c2))));
	BOOST_TEST((CP(op(cr1, cr2).cols()) == cols(op(c1, c2))));
	BOOST_TEST((CP(op(cr1, rc2).cols()) == cols(op(c1, c2))));
	BOOST_TEST((CP(op(cr1, rr2).cols()) == cols(op(c1, c2))));

	BOOST_TEST((CP(op(rc1, cc2).cols()) == cols(op(c1, c2))));
	BOOST_TEST((CP(op(rc1, cr2).cols()) == cols(op(c1, c2))));
	BOOST_TEST((CP(op(rc1, rc2).cols()) == cols(op(c1, c2))));
	BOOST_TEST((CP(op(rc1, rr2).cols()) == cols(op(c1, c2))));

	BOOST_TEST((CP(op(rr1, cc2).cols()) == cols(op(c1, c2))));
	BOOST_TEST((CP(op(rr1, cr2).cols()) == cols(op(c1, c2))));
	BOOST_TEST((CP(op(rr1, rc2).cols()) == cols(op(c1, c2))));
	BOOST_TEST((CP(op(rr1, rr2).cols()) == cols(op(c1, c2))));


	BOOST_TEST((CP(op(cc1, cc2).rows()) == rows(op(r1, r2))));
	BOOST_TEST((CP(op(cc1, cr2).rows()) == rows(op(r1, r2))));
	BOOST_TEST((CP(op(cc1, rc2).rows()) == rows(op(r1, r2))));
	BOOST_TEST((CP(op(cc1, rr2).rows()) == rows(op(r1, r2))));

	BOOST_TEST((CP(op(cr1, cc2).rows()) == rows(op(r1, r2))));
	BOOST_TEST((CP(op(cr1, cr2).rows()) == rows(op(r1, r2))));
	BOOST_TEST((CP(op(cr1, rc2).rows()) == rows(op(r1, r2))));
	BOOST_TEST((CP(op(cr1, rr2).rows()) == rows(op(r1, r2))));

	BOOST_TEST((CP(op(rc1, cc2).rows()) == rows(op(r1, r2))));
	BOOST_TEST((CP(op(rc1, cr2).rows()) == rows(op(r1, r2))));
	BOOST_TEST((CP(op(rc1, rc2).rows()) == rows(op(r1, r2))));
	BOOST_TEST((CP(op(rc1, rr2).rows()) == rows(op(r1, r2))));

	BOOST_TEST((CP(op(rr1, cc2).rows()) == rows(op(r1, r2))));
	BOOST_TEST((CP(op(rr1, cr2).rows()) == rows(op(r1, r2))));
	BOOST_TEST((CP(op(rr1, rc2).rows()) == rows(op(r1, r2))));
	BOOST_TEST((CP(op(rr1, rr2).rows()) == rows(op(r1, r2))));
}


void get_dim_pair(){
	constexpr auto c = 3_C;
	constexpr auto r = 4_R;

	constexpr auto d1 = dim_pair(cols< c >(), rows< r >());
	constexpr auto d2 = dim_pair(cols< c >(), rows(r));
	constexpr auto d3 = dim_pair(cols(c), rows< r >());
	constexpr auto d4 = dim_pair(cols(c), rows(r));

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

	BOOST_TEST((rt_id(res01) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res02) == id< auto_dim_pair_t< c, 0_R > >));
	BOOST_TEST((rt_id(res03) == id< auto_dim_pair_t< 0_C, r > >));
	BOOST_TEST((rt_id(res04) == id< auto_dim_pair_t< 0_C, 0_R > >));
	BOOST_TEST((rt_id(res05) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res06) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res07) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res08) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res09) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res10) == id< auto_dim_pair_t< c, 0_R > >));
	BOOST_TEST((rt_id(res11) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res12) == id< auto_dim_pair_t< c, 0_R > >));
	BOOST_TEST((rt_id(res13) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res14) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res15) == id< auto_dim_pair_t< 0_C, r > >));
	BOOST_TEST((rt_id(res16) == id< auto_dim_pair_t< 0_C, r > >));
	BOOST_TEST((rt_id(res17) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res18) == id< auto_dim_pair_t< c, 0_R > >));
	BOOST_TEST((rt_id(res19) == id< auto_dim_pair_t< 0_C, r > >));
	BOOST_TEST((rt_id(res20) == id< auto_dim_pair_t< 0_C, 0_R > >));
	BOOST_TEST((rt_id(res21) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res22) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res23) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res24) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res25) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res26) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res27) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res28) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res29) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res30) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res31) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res32) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res33) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res34) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res35) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res36) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res37) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res38) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res39) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res40) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res41) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res42) == id< auto_dim_pair_t< c, 0_R > >));
	BOOST_TEST((rt_id(res43) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res44) == id< auto_dim_pair_t< c, 0_R > >));
	BOOST_TEST((rt_id(res45) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res46) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res47) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res48) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res49) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res50) == id< auto_dim_pair_t< c, 0_R > >));
	BOOST_TEST((rt_id(res51) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res52) == id< auto_dim_pair_t< c, 0_R > >));
	BOOST_TEST((rt_id(res53) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res54) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res55) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res56) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res57) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res58) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res59) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res60) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res61) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res62) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res63) == id< auto_dim_pair_t< 0_C, r > >));
	BOOST_TEST((rt_id(res64) == id< auto_dim_pair_t< 0_C, r > >));
	BOOST_TEST((rt_id(res65) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res66) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res67) == id< auto_dim_pair_t< 0_C, r > >));
	BOOST_TEST((rt_id(res68) == id< auto_dim_pair_t< 0_C, r > >));
	BOOST_TEST((rt_id(res69) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res70) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res71) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res72) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res73) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res74) == id< auto_dim_pair_t< c, 0_R > >));
	BOOST_TEST((rt_id(res75) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res76) == id< auto_dim_pair_t< c, 0_R > >));
	BOOST_TEST((rt_id(res77) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res78) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res79) == id< auto_dim_pair_t< 0_C, r > >));
	BOOST_TEST((rt_id(res80) == id< auto_dim_pair_t< 0_C, r > >));
	BOOST_TEST((rt_id(res81) == id< auto_dim_pair_t< c, r > >));
	BOOST_TEST((rt_id(res82) == id< auto_dim_pair_t< c, 0_R > >));
	BOOST_TEST((rt_id(res83) == id< auto_dim_pair_t< 0_C, r > >));
	BOOST_TEST((rt_id(res84) == id< auto_dim_pair_t< 0_C, 0_R > >));

	BOOST_TEST((res01 == dim_pair(c, r)));
	BOOST_TEST((res02 == dim_pair(c, r)));
	BOOST_TEST((res03 == dim_pair(c, r)));
	BOOST_TEST((res04 == dim_pair(c, r)));
	BOOST_TEST((res05 == dim_pair(c, r)));
	BOOST_TEST((res06 == dim_pair(c, r)));
	BOOST_TEST((res07 == dim_pair(c, r)));
	BOOST_TEST((res08 == dim_pair(c, r)));
	BOOST_TEST((res09 == dim_pair(c, r)));
	BOOST_TEST((res10 == dim_pair(c, r)));
	BOOST_TEST((res11 == dim_pair(c, r)));
	BOOST_TEST((res12 == dim_pair(c, r)));
	BOOST_TEST((res13 == dim_pair(c, r)));
	BOOST_TEST((res14 == dim_pair(c, r)));
	BOOST_TEST((res15 == dim_pair(c, r)));
	BOOST_TEST((res16 == dim_pair(c, r)));
	BOOST_TEST((res17 == dim_pair(c, r)));
	BOOST_TEST((res18 == dim_pair(c, r)));
	BOOST_TEST((res19 == dim_pair(c, r)));
	BOOST_TEST((res20 == dim_pair(c, r)));
	BOOST_TEST((res21 == dim_pair(c, r)));
	BOOST_TEST((res22 == dim_pair(c, r)));
	BOOST_TEST((res23 == dim_pair(c, r)));
	BOOST_TEST((res24 == dim_pair(c, r)));
	BOOST_TEST((res25 == dim_pair(c, r)));
	BOOST_TEST((res26 == dim_pair(c, r)));
	BOOST_TEST((res27 == dim_pair(c, r)));
	BOOST_TEST((res28 == dim_pair(c, r)));
	BOOST_TEST((res29 == dim_pair(c, r)));
	BOOST_TEST((res30 == dim_pair(c, r)));
	BOOST_TEST((res31 == dim_pair(c, r)));
	BOOST_TEST((res32 == dim_pair(c, r)));
	BOOST_TEST((res33 == dim_pair(c, r)));
	BOOST_TEST((res34 == dim_pair(c, r)));
	BOOST_TEST((res35 == dim_pair(c, r)));
	BOOST_TEST((res36 == dim_pair(c, r)));
	BOOST_TEST((res37 == dim_pair(c, r)));
	BOOST_TEST((res38 == dim_pair(c, r)));
	BOOST_TEST((res39 == dim_pair(c, r)));
	BOOST_TEST((res40 == dim_pair(c, r)));
	BOOST_TEST((res41 == dim_pair(c, r)));
	BOOST_TEST((res42 == dim_pair(c, r)));
	BOOST_TEST((res43 == dim_pair(c, r)));
	BOOST_TEST((res44 == dim_pair(c, r)));
	BOOST_TEST((res45 == dim_pair(c, r)));
	BOOST_TEST((res46 == dim_pair(c, r)));
	BOOST_TEST((res47 == dim_pair(c, r)));
	BOOST_TEST((res48 == dim_pair(c, r)));
	BOOST_TEST((res49 == dim_pair(c, r)));
	BOOST_TEST((res50 == dim_pair(c, r)));
	BOOST_TEST((res51 == dim_pair(c, r)));
	BOOST_TEST((res52 == dim_pair(c, r)));
	BOOST_TEST((res53 == dim_pair(c, r)));
	BOOST_TEST((res54 == dim_pair(c, r)));
	BOOST_TEST((res55 == dim_pair(c, r)));
	BOOST_TEST((res56 == dim_pair(c, r)));
	BOOST_TEST((res57 == dim_pair(c, r)));
	BOOST_TEST((res58 == dim_pair(c, r)));
	BOOST_TEST((res59 == dim_pair(c, r)));
	BOOST_TEST((res60 == dim_pair(c, r)));
	BOOST_TEST((res61 == dim_pair(c, r)));
	BOOST_TEST((res62 == dim_pair(c, r)));
	BOOST_TEST((res63 == dim_pair(c, r)));
	BOOST_TEST((res64 == dim_pair(c, r)));
	BOOST_TEST((res65 == dim_pair(c, r)));
	BOOST_TEST((res66 == dim_pair(c, r)));
	BOOST_TEST((res67 == dim_pair(c, r)));
	BOOST_TEST((res68 == dim_pair(c, r)));
	BOOST_TEST((res69 == dim_pair(c, r)));
	BOOST_TEST((res70 == dim_pair(c, r)));
	BOOST_TEST((res71 == dim_pair(c, r)));
	BOOST_TEST((res72 == dim_pair(c, r)));
	BOOST_TEST((res73 == dim_pair(c, r)));
	BOOST_TEST((res74 == dim_pair(c, r)));
	BOOST_TEST((res75 == dim_pair(c, r)));
	BOOST_TEST((res76 == dim_pair(c, r)));
	BOOST_TEST((res77 == dim_pair(c, r)));
	BOOST_TEST((res78 == dim_pair(c, r)));
	BOOST_TEST((res79 == dim_pair(c, r)));
	BOOST_TEST((res80 == dim_pair(c, r)));
	BOOST_TEST((res81 == dim_pair(c, r)));
	BOOST_TEST((res82 == dim_pair(c, r)));
	BOOST_TEST((res83 == dim_pair(c, r)));
	BOOST_TEST((res84 == dim_pair(c, r)));
}


int main(int argc, char** argv, char** /*envp*/){
	auto ts = BOOST_TEST_SUITE("suite_dim");

	add_test< col_ct >(ts);
	add_test< row_ct >(ts);
	add_test< dim_ct >(ts);
	ts->add(BOOST_TEST_CASE(&dim_literal));
	ts->add(BOOST_TEST_CASE(&make_col_t));
	ts->add(BOOST_TEST_CASE(&make_row_t));
	ts->add(BOOST_TEST_CASE(&make_dim_t));
	ts->add(BOOST_TEST_CASE(&dim_pair_t_default_construct));
	ts->add(BOOST_TEST_CASE(&dim_pair_t_construct));
	ts->add(BOOST_TEST_CASE(&dim_pair_t_make));
	ts->add(BOOST_TEST_CASE(&dim_pair_t_compare));
	ts->add(BOOST_TEST_CASE(&dim_pair_t_arithmetic_size_t< std::multiplies<> >));
	ts->add(BOOST_TEST_CASE(&dim_pair_t_arithmetic_size_t< std::divides<> >));
	ts->add(BOOST_TEST_CASE(&dim_pair_t_arithmetic_size_t< std::modulus<> >));
	ts->add(BOOST_TEST_CASE(&dim_pair_t_arithmetic< std::plus<> >));
	ts->add(BOOST_TEST_CASE(&dim_pair_t_arithmetic< std::minus<> >));
	ts->add(BOOST_TEST_CASE(&dim_pair_t_arithmetic< std::multiplies<> >));
	ts->add(BOOST_TEST_CASE(&dim_pair_t_arithmetic< std::divides<> >));
	ts->add(BOOST_TEST_CASE(&dim_pair_t_arithmetic< std::modulus<> >));
	ts->add(BOOST_TEST_CASE(&get_dim_pair));

	utf::framework::master_test_suite().add(ts);

	return utf::unit_test_main(&init_unit_test, argc, argv);
}
