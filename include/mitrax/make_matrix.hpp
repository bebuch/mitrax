//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
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


		template < typename F >
		using fn_xy =
			std::decay_t< decltype(std::declval< F >()(size_t(), size_t())) >;

		template < typename F >
		using fn_i = std::decay_t< decltype(std::declval< F >()(size_t())) >;


		template < typename T, size_t N >
		constexpr auto to_raw_matrix_data(std::true_type, T(&&v)[N]){
			return mitrax::to_array(std::move(v));
		}

		template < typename T, size_t N >
		constexpr auto to_raw_matrix_data(std::true_type, T(&v)[N]){
			return mitrax::to_array(v);
		}

		template < typename T, size_t C, size_t R >
		constexpr auto to_raw_matrix_data(std::true_type, T(&&v)[R][C]){
			return mitrax::to_array(std::move(v));
		}

		template < typename T, size_t C, size_t R >
		constexpr auto to_raw_matrix_data(std::true_type, T(&v)[R][C]){
			return mitrax::to_array(v);
		}

		template < typename T, size_t C, size_t R >
		constexpr auto to_raw_matrix_data(
			std::true_type, col_t< C >, row_t< R >, T const& v
		){
			return mitrax::init_array< C * R >(v);
		}

		template < typename T, size_t N >
		constexpr auto to_raw_matrix_data(std::false_type, T(&&v)[N]){
			return mitrax::to_vector(std::move(v));
		}

		template < typename T, size_t N >
		constexpr auto to_raw_matrix_data(std::false_type, T(&v)[N]){
			return mitrax::to_vector(v);
		}

		template < typename T, size_t C, size_t R >
		constexpr auto to_raw_matrix_data(std::false_type, T(&&v)[R][C]){
			return mitrax::to_vector(std::move(v));
		}

		template < typename T, size_t C, size_t R >
		constexpr auto to_raw_matrix_data(std::false_type, T(&v)[R][C]){
			return mitrax::to_vector(v);
		}

		template < typename T, size_t C, size_t R >
		constexpr auto to_raw_matrix_data(
			std::false_type, col_t< C > c, row_t< R > r, T const& v
		){
			return boost::container::vector< T >(
				static_cast< size_t >(c) * static_cast< size_t >(r), v
			);
		}

		template < typename T, size_t C, size_t R >
		constexpr auto to_raw_matrix_data(
			col_t< C > c, row_t< R > r, T const& v
		){
			return to_raw_matrix_data(is_static< C, R >(), c, r, v);
		}


	}


// 	template < typename F, bool Cct, size_t C, bool Rct, size_t R >
// 	constexpr raw_matrix< fn_xy< F >, dim(Cct, C), dim(Rct, R) >
// 	make_matrix_by_function(
// 		col_init_t< Cct, C > c, row_init_t< Rct, R > r, F const& f
// 	){
// 		return raw_matrix_impl< fn_xy< F >, dim(Cct, C), dim(Rct, R) >(
// 			c.get(), r.get(), f(size_t(), size_t())
// 		);
// 	}
// 
// 	template < typename F, size_t C, size_t R >
// 	constexpr auto
// 	make_matrix_by_function(dim_t< C, R > const& d, F const& f){
// 		return make_matrix_by_function(d.cols().init(), d.rows().init(), f);
// 	}
// 
// 	template < typename F, bool Nct, size_t N >
// 	constexpr auto
// 	make_square_matrix_by_function(dim_init_t< Nct, N > n, F const& f){
// 		return make_matrix_by_function(n.as_col(), n.as_row(), f);
// 	}
// 
// 	template < typename F, bool Nct, size_t N >
// 	constexpr raw_col_vector< fn_i< F >, dim(Nct, N) >
// 	make_col_vector_by_function(row_init_t< Nct, N > r, F const& f){
// 		using namespace literals;
// 		return make_matrix(1_C, r, f);
// 	}
// 
// 	template < typename F, bool Nct, size_t N >
// 	constexpr raw_row_vector< fn_i< F >, dim(Nct, N) >
// 	make_row_vector_by_function(col_init_t< Nct, N > c, F const& f){
// 		using namespace literals;
// 		return make_matrix(c, 1_R, f);
// 	}
// 
// 	template < typename F, size_t C, size_t R >
// 	auto make_bitmap_by_function(dim_t< C, R > const& d, F const& f){
// 		return make_matrix(
// 			col_t< 0 >(d.cols()).init(),
// 			row_t< 0 >(d.rows()).init(),
// 			f
// 		);
// 	}
// 
// 	template < typename F >
// 	auto make_bitmap_by_function(size_t c, size_t r, F const& f){
// 		return make_matrix(col_t< 0 >(c).init(), row_t< 0 >(r).init(), f);
// 	}


	template < typename T, bool Cct, size_t C, bool Rct, size_t R >
	constexpr auto make_matrix(col_init_t< Cct, C > c, row_init_t< Rct, R > r){
		return make_matrix(c, r, T());
	}

	template < typename T, size_t C, size_t R >
	constexpr auto make_matrix(dim_t< C, R > const& d){
		return make_matrix< T >(d.cols().init(), d.rows().init());
	}

	template < typename T, bool Cct, size_t C, bool Rct, size_t R >
	constexpr raw_matrix< std::remove_cv_t< T >, dim(Cct, C), dim(Rct, R) >
	make_matrix(col_init_t< Cct, C > c, row_init_t< Rct, R > r, T const& v){
		return raw_matrix_impl<
			std::remove_cv_t< T >, dim(Cct, C), dim(Rct, R)
		>(c.get(), r.get(), detail::to_raw_matrix_data(c.get(), r.get(), v));
	}

	template < typename T, size_t C, size_t R >
	constexpr auto make_matrix(dim_t< C, R > const& d, T const& v){
		return make_matrix(d.cols().init(), d.rows().init(), v);
	}

	template < typename T, bool Cct, size_t C, bool Rct, size_t R >
	constexpr raw_matrix< std::remove_cv_t< T >, dim(Cct, C), dim(Rct, R) >
	make_matrix(col_init_t< Cct, C > c, row_init_t< Rct, R > r, T(&&v)[R][C]){
		return raw_matrix_impl<
			std::remove_cv_t< T >, dim(Cct, C), dim(Rct, R)
		>(
			c.get(), r.get(),
			detail::to_raw_matrix_data(bool_t< Cct && Rct >(), std::move(v))
		);
	}

	template < typename T, bool Cct, size_t C, bool Rct, size_t R >
	constexpr raw_matrix< std::remove_cv_t< T >, dim(Cct, C), dim(Rct, R) >
	make_matrix(col_init_t< Cct, C > c, row_init_t< Rct, R > r, T(&v)[R][C]){
		return raw_matrix_impl<
			std::remove_cv_t< T >, dim(Cct, C), dim(Rct, R)
		>(
			c.get(), r.get(),
			detail::to_raw_matrix_data(bool_t< Cct && Rct >(), v)
		);
	}


	template < typename T, bool Nct, size_t N >
	constexpr auto make_square_matrix(dim_init_t< Nct, N > n){
		return make_matrix< T >(n.as_col(), n.as_row());
	}

	template < typename T, bool Nct, size_t N >
	constexpr auto make_square_matrix(dim_init_t< Nct, N > n, T const& v){
		return make_matrix(n.as_col(), n.as_row(), v);
	}

	template < typename T, bool Nct, size_t N >
	constexpr auto make_square_matrix(dim_init_t< Nct, N > n, T(&&v)[N][N]){
		return make_matrix(n.as_col(), n.as_row(), std::move(v));
	}

	template < typename T, bool Nct, size_t N >
	constexpr auto make_square_matrix(dim_init_t< Nct, N > n, T(&v)[N][N]){
		return make_matrix(n.as_col(), n.as_row(), v);
	}


	template < typename T, bool Nct, size_t N >
	constexpr auto make_col_vector(row_init_t< Nct, N > r){
		return make_col_vector(r, T());
	}

	template < typename T, bool Nct, size_t N >
	constexpr auto make_col_vector(row_init_t< Nct, N > r, T const& v){
		using namespace literals;
		return make_matrix(1_C, r, v);
	}

	template < typename T, bool Nct, size_t N >
	constexpr raw_col_vector< std::remove_cv_t< T >, dim(Nct, N) >
	make_col_vector(row_init_t< Nct, N > r, T(&&v)[N]){
		using namespace literals;
		return raw_matrix_impl< std::remove_cv_t< T >, 1, dim(Nct, N) >(
			1_C .get(), r.get(),
			detail::to_raw_matrix_data(bool_t< Nct >(), std::move(v))
		);
	}

	template < typename T, bool Nct, size_t N >
	constexpr raw_col_vector< std::remove_cv_t< T >, dim(Nct, N) >
	make_col_vector(row_init_t< Nct, N > r, T(&v)[N]){
		using namespace literals;
		return raw_matrix_impl< std::remove_cv_t< T >, 1, dim(Nct, N) >(
			1_C .get(), r.get(),
			detail::to_raw_matrix_data(bool_t< Nct >(), v)
		);
	}


	template < typename T, bool Nct, size_t N >
	constexpr auto make_row_vector(col_init_t< Nct, N > c){
		return make_row_vector(c, T());
	}

	template < typename T, bool Nct, size_t N >
	constexpr auto make_row_vector(col_init_t< Nct, N > c, T const& v){
		using namespace literals;
		return make_matrix(c, 1_R, v);
	}

	template < typename T, bool Nct, size_t N >
	constexpr raw_row_vector< std::remove_cv_t< T >, dim(Nct, N) >
	make_row_vector(col_init_t< Nct, N > c, T(&&v)[N]){
		using namespace literals;
		return raw_matrix_impl< std::remove_cv_t< T >, dim(Nct, N), 1 >(
			c.get(), 1_R .get(),
			detail::to_raw_matrix_data(bool_t< Nct >(), std::move(v))
		);
	}

	template < typename T, bool Nct, size_t N >
	constexpr raw_row_vector< std::remove_cv_t< T >, dim(Nct, N) >
	make_row_vector(col_init_t< Nct, N > c, T(&v)[N]){
		using namespace literals;
		return raw_matrix_impl< std::remove_cv_t< T >, dim(Nct, N), 1 >(
			c.get(), 1_R .get(),
			detail::to_raw_matrix_data(bool_t< Nct >(), v)
		);
	}

	template < typename T, size_t C, size_t R >
	auto make_bitmap(dim_t< C, R > const& d){
		return make_matrix< T >(
			col_t< 0 >(d.cols()).init(),
			row_t< 0 >(d.rows()).init()
		);
	}

	template < typename T, size_t C, size_t R >
	auto make_bitmap(dim_t< C, R > const& d, T const& v){
		return make_matrix(
			col_t< 0 >(d.cols()).init(),
			row_t< 0 >(d.rows()).init(),
			v
		);
	}

	template < typename T >
	auto make_bitmap(size_t c, size_t r){
		return make_matrix< T >(col_t< 0 >(c).init(), row_t< 0 >(r).init());
	}

	template < typename T >
	auto make_bitmap(size_t c, size_t r, T const& v){
		return make_matrix(col_t< 0 >(c).init(), row_t< 0 >(r).init(), v);
	}


}

#endif
