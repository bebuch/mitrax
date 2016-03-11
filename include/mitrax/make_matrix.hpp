//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__make_matrix__hpp_INCLUDED_
#define _mitrax__make_matrix__hpp_INCLUDED_

#include "raw_matrix.hpp"


namespace mitrax{


	namespace detail{


		template < size_t C, size_t R >
		struct is_static: std::true_type{};

		template < size_t R >
		struct is_static< 0, R >: std::false_type{};

		template < size_t C >
		struct is_static< C, 0 >: std::false_type{};

		template <>
		struct is_static< 0, 0 >: std::false_type{};


		template < typename T, size_t N >
		constexpr auto to_raw_matrix_data(std::true_type, T(&&a)[N]){
			return to_array(std::move(a), std::make_index_sequence< N >());
		}

		template < typename T, size_t N >
		constexpr auto to_raw_matrix_data(std::true_type, T(&a)[N]){
			return to_array(a, std::make_index_sequence< N >());
		}

		template < typename T, size_t C, size_t R >
		constexpr auto to_raw_matrix_data(std::true_type, T(&&a)[R][C]){
			return to_array(std::move(a), std::make_index_sequence< C * R >());
		}

		template < typename T, size_t C, size_t R >
		constexpr auto to_raw_matrix_data(std::true_type, T(&a)[R][C]){
			return to_array(a, std::make_index_sequence< C * R >());
		}

		template < typename T, bool Cct, size_t C, bool Rct, size_t R >
		constexpr auto to_raw_matrix_data(
			std::true_type, col_t< Cct, C >, row_t< Rct, R >, T const& v
		){
			return init_array(v, std::make_index_sequence< C * R >());
		}

		template < typename T, size_t N >
		constexpr auto to_raw_matrix_data(std::false_type, T(&&a)[N]){
			return array_d< std::remove_cv_t< T > >(std::move(a));
		}

		template < typename T, size_t N >
		constexpr auto to_raw_matrix_data(std::false_type, T(&a)[N]){
			return array_d< std::remove_cv_t< T > >(a);
		}

		template < typename T, size_t C, size_t R >
		constexpr auto to_raw_matrix_data(std::false_type, T(&&a)[R][C]){
			return array_d< std::remove_cv_t< T > >(std::move(a));
		}

		template < typename T, size_t C, size_t R >
		constexpr auto to_raw_matrix_data(std::false_type, T(&a)[R][C]){
			return array_d< std::remove_cv_t< T > >(a);
		}

		template < typename T, bool Cct, size_t C, bool Rct, size_t R >
		constexpr auto to_raw_matrix_data(
			std::false_type, col_t< Cct, C > c, row_t< Rct, R > r, T const& v
		){
			return array_d< std::remove_cv_t< T > >(size_t(c) * size_t(r), v);
		}


		template < typename F, bool Cct, size_t C, bool Rct, size_t R >
		constexpr auto function_xy_to_raw_matrix_data(
			std::true_type,
			col_t< Cct, C >, row_t< Rct, R >, F&& f
		){
			return function_xy_to_array< C, R >(f);
		}

		template < typename F, bool Nct, size_t N >
		constexpr auto function_i_to_raw_matrix_data(
			std::true_type, dim_t< Nct, N >, F&& f
		){
			return function_i_to_array< N >(f);
		}

		template < typename F, bool Cct, size_t C, bool Rct, size_t R >
		constexpr auto function_xy_to_raw_matrix_data(
			std::false_type,
			col_t< Cct, C > c, row_t< Rct, R > r, F&& f
		){
			return array_d< fn_xy< F > >(c, r, f);
		}

		template < typename F, bool Nct, size_t N >
		constexpr auto function_i_to_raw_matrix_data(
			std::false_type, dim_t< Nct, N > n, F&& f
		){
			return array_d< fn_i< F > >(n, f);
		}


		template < typename F >
		struct init_diag_by_function{
			F f;

			constexpr fn_i< F > operator()(size_t x, size_t y){
				return x == y ? f(x) : decltype(f(x))();
			}
		};

		template < typename F >
		constexpr auto make_init_diag_by_function(F&& f){
			return init_diag_by_function< F&& >{static_cast< F&& >(f)};
		}

		template < typename T >
		struct init_diag_by_value{
			T const& v;

			constexpr std::remove_cv_t< T >
			operator()(size_t x, size_t y)const{
				return x == y ? v : std::remove_cv_t< T >();
			}
		};

		template < typename T, size_t N >
		struct init_diag_by_move_array{
			T(&&v)[N];

			constexpr std::remove_cv_t< T >
			operator()(size_t x, size_t y)const{
				return x == y ? std::move(v[x]) : std::remove_cv_t< T >();
			}
		};

		template < typename T, size_t N >
		struct init_diag_by_array{
			T(&v)[N];

			constexpr std::remove_cv_t< T >
			operator()(size_t x, size_t y)const{
				return x == y ? v[x] : std::remove_cv_t< T >();
			}
		};


	}


	template < typename F, bool Cct, size_t C, bool Rct, size_t R >
	constexpr raw_matrix< fn_xy< F >, dim(Cct, C), dim(Rct, R) >
	make_matrix_by_function(
		col_t< Cct, C > c, row_t< Rct, R > r, F&& f
	){
		return detail::raw_matrix_impl< fn_xy< F >, dim(Cct, C), dim(Rct, R) >(
			c, r, detail::function_xy_to_raw_matrix_data(
				bool_t< Cct && Rct >(), c, r, f
			)
		);
	}

	template < typename F, size_t C, size_t R >
	constexpr auto
	make_matrix_by_function(dims_t< C, R > const& d, F&& f){
		return make_matrix_by_function(d.cols(), d.rows(), f);
	}

	template < typename F, bool Nct, size_t N >
	constexpr auto
	make_square_matrix_by_function(dim_t< Nct, N > n, F&& f){
		return make_matrix_by_function(n.as_col(), n.as_row(), f);
	}

	template < typename F, bool Nct, size_t N >
	constexpr raw_col_vector< fn_i< F >, dim(Nct, N) >
	make_col_vector_by_function(row_t< Nct, N > r, F&& f){
		using namespace literals;
		return detail::raw_matrix_impl< fn_i< F >, 1, dim(Nct, N) >(
			1_C, r, detail::function_i_to_raw_matrix_data(
				bool_t< Nct >(), r.as_dim(), f
			)
		);
	}

	template < typename F, bool Nct, size_t N >
	constexpr raw_row_vector< fn_i< F >, dim(Nct, N) >
	make_row_vector_by_function(col_t< Nct, N > c, F&& f){
		using namespace literals;
		return detail::raw_matrix_impl< fn_i< F >, dim(Nct, N), 1 >(
			c, 1_R, detail::function_i_to_raw_matrix_data(
				bool_t< Nct >(), c.as_dim(), f
			)
		);
	}

	template < typename F, size_t C, size_t R >
	auto make_bitmap_by_function(dims_t< C, R > const& d, F&& f){
		return make_matrix_by_function(
			col_t< false, 0 >(d.cols()),
			row_t< false, 0 >(d.rows()),
			f
		);
	}

	template < typename F >
	auto make_bitmap_by_function(size_t c, size_t r, F&& f){
		return make_matrix_by_function(
			col_t< false, 0 >(c), row_t< false, 0 >(r), f
		);
	}


	template < typename F, bool Nct, size_t N >
	constexpr auto
	make_diag_matrix_by_function(dim_t< Nct, N > n, F&& f){
		return make_square_matrix_by_function(n,
			detail::make_init_diag_by_function(static_cast< F&& >(f)));
	}


	template < typename T, bool Cct, size_t C, bool Rct, size_t R >
	constexpr raw_matrix< std::remove_cv_t< T >, dim(Cct, C), dim(Rct, R) >
	make_matrix(col_t< Cct, C > c, row_t< Rct, R > r, T const& v = T()){
		return detail::raw_matrix_impl<
			std::remove_cv_t< T >, dim(Cct, C), dim(Rct, R)
		>(c, r, detail::to_raw_matrix_data(bool_t< Cct && Rct >(), c, r, v));
	}

	template < typename T, size_t C, size_t R >
	constexpr auto make_matrix(dims_t< C, R > const& d, T const& v = T()){
		return make_matrix(d.cols(), d.rows(), v);
	}

	template < typename T, bool Cct, size_t C, bool Rct, size_t R >
	constexpr raw_matrix< std::remove_cv_t< T >, dim(Cct, C), dim(Rct, R) >
	make_matrix(col_t< Cct, C > c, row_t< Rct, R > r, T(&&v)[R][C]){
		return detail::raw_matrix_impl<
			std::remove_cv_t< T >, dim(Cct, C), dim(Rct, R)
		>(
			c, r,
			detail::to_raw_matrix_data(bool_t< Cct && Rct >(), std::move(v))
		);
	}

	template < typename T, bool Cct, size_t C, bool Rct, size_t R >
	constexpr raw_matrix< std::remove_cv_t< T >, dim(Cct, C), dim(Rct, R) >
	make_matrix(col_t< Cct, C > c, row_t< Rct, R > r, T(&v)[R][C]){
		return detail::raw_matrix_impl<
			std::remove_cv_t< T >, dim(Cct, C), dim(Rct, R)
		>(
			c, r,
			detail::to_raw_matrix_data(bool_t< Cct && Rct >(), v)
		);
	}


	template < typename T, bool Nct, size_t N >
	constexpr auto make_square_matrix(dim_t< Nct, N > n, T const& v = T()){
		return make_matrix(n.as_col(), n.as_row(), v);
	}

	template < typename T, bool Nct, size_t N >
	constexpr auto make_square_matrix(dim_t< Nct, N > n, T(&&v)[N][N]){
		return make_matrix(n.as_col(), n.as_row(), std::move(v));
	}

	template < typename T, bool Nct, size_t N >
	constexpr auto make_square_matrix(dim_t< Nct, N > n, T(&v)[N][N]){
		return make_matrix(n.as_col(), n.as_row(), v);
	}


	template < typename T, bool Nct, size_t N >
	constexpr auto make_col_vector(row_t< Nct, N > r, T const& v = T()){
		using namespace literals;
		return make_matrix(1_C, r, v);
	}

	template < typename T, bool Nct, size_t N >
	constexpr raw_col_vector< std::remove_cv_t< T >, dim(Nct, N) >
	make_col_vector(row_t< Nct, N > r, T(&&v)[N]){
		using namespace literals;
		return detail::raw_matrix_impl<
			std::remove_cv_t< T >, 1, dim(Nct, N)
		>(
			1_C, r,
			detail::to_raw_matrix_data(bool_t< Nct >(), std::move(v))
		);
	}

	template < typename T, bool Nct, size_t N >
	constexpr raw_col_vector< std::remove_cv_t< T >, dim(Nct, N) >
	make_col_vector(row_t< Nct, N > r, T(&v)[N]){
		using namespace literals;
		return detail::raw_matrix_impl<
			std::remove_cv_t< T >, 1, dim(Nct, N)
		>(
			1_C, r,
			detail::to_raw_matrix_data(bool_t< Nct >(), v)
		);
	}


	template < typename T, bool Nct, size_t N >
	constexpr auto make_row_vector(col_t< Nct, N > c, T const& v = T()){
		using namespace literals;
		return make_matrix(c, 1_R, v);
	}

	template < typename T, bool Nct, size_t N >
	constexpr raw_row_vector< std::remove_cv_t< T >, dim(Nct, N) >
	make_row_vector(col_t< Nct, N > c, T(&&v)[N]){
		using namespace literals;
		return detail::raw_matrix_impl<
			std::remove_cv_t< T >, dim(Nct, N), 1
		>(
			c, 1_R,
			detail::to_raw_matrix_data(bool_t< Nct >(), std::move(v))
		);
	}

	template < typename T, bool Nct, size_t N >
	constexpr raw_row_vector< std::remove_cv_t< T >, dim(Nct, N) >
	make_row_vector(col_t< Nct, N > c, T(&v)[N]){
		using namespace literals;
		return detail::raw_matrix_impl<
			std::remove_cv_t< T >, dim(Nct, N), 1
		>(
			c, 1_R,
			detail::to_raw_matrix_data(bool_t< Nct >(), v)
		);
	}

	template < typename T, size_t C, size_t R >
	auto make_bitmap(dims_t< C, R > const& d, T const& v = T()){
		return make_matrix(
			col_t< false, 0 >(d.cols()),
			row_t< false, 0 >(d.rows()),
			v
		);
	}

	template < typename T >
	auto make_bitmap(size_t c, size_t r, T const& v = T()){
		return make_matrix(col_t< false, 0 >(c), row_t< false, 0 >(r), v);
	}


	template < typename T, bool Nct, size_t N >
	constexpr auto make_diag_matrix(dim_t< Nct, N > n, T const& v = T()){
		return make_square_matrix_by_function(n,
			detail::init_diag_by_value< T >{v});
	}

	template < typename T, bool Nct, size_t N >
	constexpr auto make_diag_matrix(dim_t< Nct, N > n, T(&&v)[N]){
		return make_square_matrix_by_function(n,
			detail::init_diag_by_move_array< T, N >{std::move(v)});
	}

	template < typename T, bool Nct, size_t N >
	constexpr auto make_diag_matrix(dim_t< Nct, N > n, T(&v)[N]){
		return make_square_matrix_by_function(n,
			detail::init_diag_by_array< T, N >{v});
	}


	template < typename T, bool Nct, size_t N >
	constexpr auto make_identity_matrix(dim_t< Nct, N > n){
		return make_diag_matrix(n, T(1));
	}


}

#endif
