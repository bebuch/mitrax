// //-----------------------------------------------------------------------------
// // Copyright (c) 2015 Benjamin Buch
// //
// // https://github.com/bebuch/mitrax
// //
// // Distributed under the Boost Software License, Version 1.0. (See accompanying
// // file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
// //-----------------------------------------------------------------------------
// #include <boost/test/unit_test.hpp>
// 
// #include <mitrax/raw_matrix.hpp>
// #include <mitrax/matrix_swap.hpp>
// 
// 
// using boost::typeindex::type_id;
// using boost::typeindex::type_id_runtime;
// using namespace mitrax;
// 
// 
// namespace{
// 
// 
// 	constexpr auto ref1 = to_square_matrix< int, 3 >({
// 		{0, 1, 2},
// 		{3, 4, 5},
// 		{6, 7, 8}
// 	});
// 
// 	constexpr auto ref2 = to_square_matrix< int, 3 >({
// 		{10, 11, 12},
// 		{13, 14, 15},
// 		{16, 17, 18}
// 	});
// 
// 
// }
// 
// 
// BOOST_AUTO_TEST_CASE(test_swap_rows_m_0_m_1){
// 	auto m = ref1;
// 
// 	swap_rows(m, 0, 1);
// 
// 	auto eq =
// 		m(0, 0) == 3 &&
// 		m(1, 0) == 4 &&
// 		m(2, 0) == 5 &&
// 		m(0, 1) == 0 &&
// 		m(1, 1) == 1 &&
// 		m(2, 1) == 2 &&
// 		m(0, 2) == 6 &&
// 		m(1, 2) == 7 &&
// 		m(2, 2) == 8;
// 
// 	BOOST_TEST(eq);
// }
// 
// BOOST_AUTO_TEST_CASE(test_swap_rows_m_0_m_2){
// 	auto m = ref1;
// 
// 	swap_rows(m, 0, 2);
// 
// 	auto eq =
// 		m(0, 0) == 6 &&
// 		m(1, 0) == 7 &&
// 		m(2, 0) == 8 &&
// 		m(0, 1) == 3 &&
// 		m(1, 1) == 4 &&
// 		m(2, 1) == 5 &&
// 		m(0, 2) == 0 &&
// 		m(1, 2) == 1 &&
// 		m(2, 2) == 2;
// 
// 	BOOST_TEST(eq);
// }
// 
// BOOST_AUTO_TEST_CASE(test_swap_rows_m1_1_m2_2){
// 	auto m1 = ref1;
// 	auto m2 = ref2;
// 
// 	swap_rows(m1, 1, m2, 2);
// 
// 	auto eq =
// 		m1(0, 0) == 0 &&
// 		m1(1, 0) == 1 &&
// 		m1(2, 0) == 2 &&
// 		m1(0, 1) == 16 &&
// 		m1(1, 1) == 17 &&
// 		m1(2, 1) == 18 &&
// 		m1(0, 2) == 6 &&
// 		m1(1, 2) == 7 &&
// 		m1(2, 2) == 8 &&
// 		m2(0, 0) == 10 &&
// 		m2(1, 0) == 11 &&
// 		m2(2, 0) == 12 &&
// 		m2(0, 1) == 13 &&
// 		m2(1, 1) == 14 &&
// 		m2(2, 1) == 15 &&
// 		m2(0, 2) == 3 &&
// 		m2(1, 2) == 4 &&
// 		m2(2, 2) == 5;
// 
// 	BOOST_TEST(eq);
// }
// 
// 
// BOOST_AUTO_TEST_CASE(test_swap_cols_m_0_m_1){
// 	auto m = ref1;
// 
// 	swap_cols(m, 0, 1);
// 
// 	auto eq =
// 		m(0, 0) == 1 &&
// 		m(1, 0) == 0 &&
// 		m(2, 0) == 2 &&
// 		m(0, 1) == 4 &&
// 		m(1, 1) == 3 &&
// 		m(2, 1) == 5 &&
// 		m(0, 2) == 7 &&
// 		m(1, 2) == 6 &&
// 		m(2, 2) == 8;
// 
// 	BOOST_TEST(eq);
// }
// 
// BOOST_AUTO_TEST_CASE(test_swap_cols_m_0_m_2){
// 	auto m = ref1;
// 
// 	swap_cols(m, 0, 2);
// 
// 	auto eq =
// 		m(0, 0) == 2 &&
// 		m(1, 0) == 1 &&
// 		m(2, 0) == 0 &&
// 		m(0, 1) == 5 &&
// 		m(1, 1) == 4 &&
// 		m(2, 1) == 3 &&
// 		m(0, 2) == 8 &&
// 		m(1, 2) == 7 &&
// 		m(2, 2) == 6;
// 
// 	BOOST_TEST(eq);
// }
// 
// BOOST_AUTO_TEST_CASE(test_swap_cols_m1_1_m2_2){
// 	auto m1 = ref1;
// 	auto m2 = ref2;
// 
// 	swap_cols(m1, 1, m2, 2);
// 
// 	auto eq =
// 		m1(0, 0) == 0 &&
// 		m1(1, 0) == 12 &&
// 		m1(2, 0) == 2 &&
// 		m1(0, 1) == 3 &&
// 		m1(1, 1) == 15 &&
// 		m1(2, 1) == 5 &&
// 		m1(0, 2) == 6 &&
// 		m1(1, 2) == 18 &&
// 		m1(2, 2) == 8 &&
// 		m2(0, 0) == 10 &&
// 		m2(1, 0) == 11 &&
// 		m2(2, 0) == 1 &&
// 		m2(0, 1) == 13 &&
// 		m2(1, 1) == 14 &&
// 		m2(2, 1) == 4 &&
// 		m2(0, 2) == 16 &&
// 		m2(1, 2) == 17 &&
// 		m2(2, 2) == 7;
// 
// 	BOOST_TEST(eq);
// }
