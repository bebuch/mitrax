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
		constexpr auto fn_xy_to_raw_matrix_data(
			std::true_type, col_t< Cct, C >, row_t< Rct, R >, F&& f
		){
			return fn_xy_to_array< C, R >(static_cast< F&& >(f));
		}

		template < typename F, bool Nct, size_t N >
		constexpr auto fn_i_to_raw_matrix_data(
			std::true_type, dim_t< Nct, N >, F&& f
		){
			return fn_i_to_array< N >(static_cast< F&& >(f));
		}

		template < typename F, bool Cct, size_t C, bool Rct, size_t R >
		constexpr auto fn_xy_to_raw_matrix_data(
			std::false_type, col_t< Cct, C > c, row_t< Rct, R > r, F&& f
		){
			return array_d< fn_xy< F > >(c, r, static_cast< F&& >(f));
		}

		template < typename F, bool Nct, size_t N >
		constexpr auto fn_i_to_raw_matrix_data(
			std::false_type, dim_t< Nct, N > n, F&& f
		){
			return array_d< fn_i< F > >(n, static_cast< F&& >(f));
		}


		template < typename F >
		struct init_diag_fn{
			F f;

			constexpr fn_i< F > operator()(size_t x, size_t y){
				return x == y ? f(x) : decltype(f(x))();
			}
		};

		template < typename F >
		constexpr auto make_init_diag_fn(F&& f){
			return init_diag_fn< F&& >{static_cast< F&& >(f)};
		}

		template < typename T >
		struct init_diag_by_value{
			T const& v;

			constexpr std::remove_cv_t< T >
			operator()(size_t x, size_t y)const{
				return x == y ? v : std::remove_cv_t< T >();
			}
		};

		template < typename Array >
		struct init_diag_by_array{
			Array array;

			constexpr auto operator()(size_t x, size_t y){
				return x == y ?
					static_cast< array_1d_element_ref_t< Array > >(array[x]) :
					array_1d_element_t< Array >();
			}
		};


	}


	struct memory_std_t{
		template < typename F, bool Cct, size_t C, bool Rct, size_t R >
		static constexpr raw_matrix< fn_xy< F >, Cct ? C : 0, Rct ? R : 0 >
		make_matrix_fn(col_t< Cct, C > c, row_t< Rct, R > r, F&& f){
			return detail::raw_matrix_impl<
				fn_xy< F >, Cct ? C : 0, Rct ? R : 0
			>(
				c, r, detail::fn_xy_to_raw_matrix_data(
					bool_t< Cct && Rct >(), c, r, static_cast< F&& >(f)
				)
			);
		}

		template < typename F, bool Nct, size_t N >
		static constexpr raw_col_vector< fn_i< F >, Nct ? N : 0 >
		make_col_vector_fn(row_t< Nct, N > r, F&& f){
			using namespace literals;
			return detail::raw_matrix_impl< fn_i< F >, 1, Nct ? N : 0 >(
				1_C, r, detail::fn_i_to_raw_matrix_data(
					bool_t< Nct >(), r.as_dim(), static_cast< F&& >(f)
				)
			);
		}

		template < typename F, bool Nct, size_t N >
		static constexpr raw_row_vector< fn_i< F >, Nct ? N : 0 >
		make_row_vector_fn(col_t< Nct, N > c, F&& f){
			using namespace literals;
			return detail::raw_matrix_impl< fn_i< F >, Nct ? N : 0, 1 >(
				c, 1_R, detail::fn_i_to_raw_matrix_data(
					bool_t< Nct >(), c.as_dim(), static_cast< F&& >(f)
				)
			);
		}

		template < typename T, bool Cct, size_t C, bool Rct, size_t R >
		static constexpr
		raw_matrix< std::remove_cv_t< T >, Cct ? C : 0, Rct ? R : 0 >
		make_matrix_v(col_t< Cct, C > c, row_t< Rct, R > r, T const& v = T()){
			return detail::raw_matrix_impl<
				std::remove_cv_t< T >, Cct ? C : 0, Rct ? R : 0
			>(
				c, r,
				detail::to_raw_matrix_data(bool_t< Cct && Rct >(), c, r, v)
			);
		}

		template < typename T, bool Cct, size_t C, bool Rct, size_t R >
		static constexpr
		raw_matrix< std::remove_cv_t< T >, Cct ? C : 0, Rct ? R : 0 >
		make_matrix(col_t< Cct, C > c, row_t< Rct, R > r, T(&&v)[R][C]){
			return detail::raw_matrix_impl<
				std::remove_cv_t< T >, Cct ? C : 0, Rct ? R : 0
			>(
				c, r,
				detail::to_raw_matrix_data(bool_t< Cct && Rct >(), std::move(v))
			);
		}

		template < typename T, bool Cct, size_t C, bool Rct, size_t R >
		static constexpr
		raw_matrix< std::remove_cv_t< T >, Cct ? C : 0, Rct ? R : 0 >
		make_matrix(col_t< Cct, C > c, row_t< Rct, R > r, T(&v)[R][C]){
			return detail::raw_matrix_impl<
				std::remove_cv_t< T >, Cct ? C : 0, Rct ? R : 0
			>(
				c, r,
				detail::to_raw_matrix_data(bool_t< Cct && Rct >(), v)
			);
		}

		template < typename T, bool Nct, size_t N >
		static constexpr raw_col_vector< std::remove_cv_t< T >, Nct ? N : 0 >
		make_col_vector(row_t< Nct, N > r, T(&&v)[N]){
			using namespace literals;
			return detail::raw_matrix_impl<
				std::remove_cv_t< T >, 1, Nct ? N : 0
			>(
				1_C, r,
				detail::to_raw_matrix_data(bool_t< Nct >(), std::move(v))
			);
		}

		template < typename T, bool Nct, size_t N >
		static constexpr raw_col_vector< std::remove_cv_t< T >, Nct ? N : 0 >
		make_col_vector(row_t< Nct, N > r, T(&v)[N]){
			using namespace literals;
			return detail::raw_matrix_impl<
				std::remove_cv_t< T >, 1, Nct ? N : 0
			>(
				1_C, r,
				detail::to_raw_matrix_data(bool_t< Nct >(), v)
			);
		}

		template < typename T, bool Nct, size_t N >
		static constexpr raw_row_vector< std::remove_cv_t< T >, Nct ? N : 0 >
		make_row_vector(col_t< Nct, N > c, T(&&v)[N]){
			using namespace literals;
			return detail::raw_matrix_impl<
				std::remove_cv_t< T >, Nct ? N : 0, 1
			>(
				c, 1_R,
				detail::to_raw_matrix_data(bool_t< Nct >(), std::move(v))
			);
		}

		template < typename T, bool Nct, size_t N >
		static constexpr raw_row_vector< std::remove_cv_t< T >, Nct ? N : 0 >
		make_row_vector(col_t< Nct, N > c, T(&v)[N]){
			using namespace literals;
			return detail::raw_matrix_impl<
				std::remove_cv_t< T >, Nct ? N : 0, 1
			>(
				c, 1_R,
				detail::to_raw_matrix_data(bool_t< Nct >(), v)
			);
		}
	};

	constexpr memory_std_t memory_std{};


	struct memory_heap_t{
		template < typename F, bool Cct, size_t C, bool Rct, size_t R >
		static constexpr
		raw_heap_matrix< fn_xy< F >, Cct ? C : 0, Rct ? R : 0 >
		make_matrix_fn(col_t< Cct, C > c, row_t< Rct, R > r, F&& f){
			return detail::raw_heap_matrix_impl<
				fn_xy< F >, Cct ? C : 0, Rct ? R : 0
			>(
				c, r, detail::fn_xy_to_raw_matrix_data(
					std::false_type(), c, r, static_cast< F&& >(f)
				)
			);
		}

		template < typename F, bool Nct, size_t N >
		static constexpr raw_heap_col_vector< fn_i< F >, Nct ? N : 0 >
		make_col_vector_fn(row_t< Nct, N > r, F&& f){
			using namespace literals;
			return detail::raw_heap_matrix_impl< fn_i< F >, 1, Nct ? N : 0 >(
				1_C, r, detail::fn_i_to_raw_matrix_data(
					std::false_type(), r.as_dim(), static_cast< F&& >(f)
				)
			);
		}

		template < typename F, bool Nct, size_t N >
		static constexpr raw_heap_row_vector< fn_i< F >, Nct ? N : 0 >
		make_row_vector_fn(col_t< Nct, N > c, F&& f){
			using namespace literals;
			return detail::raw_heap_matrix_impl< fn_i< F >, Nct ? N : 0, 1 >(
				c, 1_R, detail::fn_i_to_raw_matrix_data(
					std::false_type(), c.as_dim(), static_cast< F&& >(f)
				)
			);
		}

		template < typename T, bool Cct, size_t C, bool Rct, size_t R >
		static constexpr
		raw_heap_matrix< std::remove_cv_t< T >, Cct ? C : 0, Rct ? R : 0 >
		make_matrix_v(col_t< Cct, C > c, row_t< Rct, R > r, T const& v = T()){
			return detail::raw_heap_matrix_impl<
				std::remove_cv_t< T >, Cct ? C : 0, Rct ? R : 0
			>(
				c, r,
				detail::to_raw_matrix_data(std::false_type(), c, r, v)
			);
		}

		template < typename T, bool Cct, size_t C, bool Rct, size_t R >
		static constexpr
		raw_heap_matrix< std::remove_cv_t< T >, Cct ? C : 0, Rct ? R : 0 >
		make_matrix(col_t< Cct, C > c, row_t< Rct, R > r, T(&&v)[R][C]){
			return detail::raw_heap_matrix_impl<
				std::remove_cv_t< T >, Cct ? C : 0, Rct ? R : 0
			>(
				c, r,
				detail::to_raw_matrix_data(std::false_type(), std::move(v))
			);
		}

		template < typename T, bool Cct, size_t C, bool Rct, size_t R >
		static constexpr
		raw_heap_matrix< std::remove_cv_t< T >, Cct ? C : 0, Rct ? R : 0 >
		make_matrix(col_t< Cct, C > c, row_t< Rct, R > r, T(&v)[R][C]){
			return detail::raw_heap_matrix_impl<
				std::remove_cv_t< T >, Cct ? C : 0, Rct ? R : 0
			>(
				c, r,
				detail::to_raw_matrix_data(std::false_type(), v)
			);
		}

		template < typename T, bool Nct, size_t N >
		static constexpr
		raw_heap_col_vector< std::remove_cv_t< T >, Nct ? N : 0 >
		make_col_vector(row_t< Nct, N > r, T(&&v)[N]){
			using namespace literals;
			return detail::raw_heap_matrix_impl<
				std::remove_cv_t< T >, 1, Nct ? N : 0
			>(
				1_C, r,
				detail::to_raw_matrix_data(std::false_type(), std::move(v))
			);
		}

		template < typename T, bool Nct, size_t N >
		static constexpr
		raw_heap_col_vector< std::remove_cv_t< T >, Nct ? N : 0 >
		make_col_vector(row_t< Nct, N > r, T(&v)[N]){
			using namespace literals;
			return detail::raw_heap_matrix_impl<
				std::remove_cv_t< T >, 1, Nct ? N : 0
			>(
				1_C, r,
				detail::to_raw_matrix_data(std::false_type(), v)
			);
		}

		template < typename T, bool Nct, size_t N >
		static constexpr
		raw_heap_row_vector< std::remove_cv_t< T >, Nct ? N : 0 >
		make_row_vector(col_t< Nct, N > c, T(&&v)[N]){
			using namespace literals;
			return detail::raw_heap_matrix_impl<
				std::remove_cv_t< T >, Nct ? N : 0, 1
			>(
				c, 1_R,
				detail::to_raw_matrix_data(std::false_type(), std::move(v))
			);
		}

		template < typename T, bool Nct, size_t N >
		static constexpr
		raw_heap_row_vector< std::remove_cv_t< T >, Nct ? N : 0 >
		make_row_vector(col_t< Nct, N > c, T(&v)[N]){
			using namespace literals;
			return detail::raw_heap_matrix_impl<
				std::remove_cv_t< T >, Nct ? N : 0, 1
			>(
				c, 1_R,
				detail::to_raw_matrix_data(std::false_type(), v)
			);
		}
	};

	constexpr memory_heap_t memory_heap{};


	template <
		typename F, bool Cct, size_t C, bool Rct, size_t R,
		typename Memory = memory_std_t
	> constexpr auto make_matrix_fn(
		col_t< Cct, C > c, row_t< Rct, R > r, F&& f, Memory = memory_std
	){
		return Memory::make_matrix_fn(c, r, static_cast< F&& >(f));
	}

	template <
		typename F, size_t C, size_t R,
		typename Memory = memory_std_t
	> constexpr auto make_matrix_fn(
		dims_t< C, R > const& d, F&& f, Memory mem = memory_std
	){
		return make_matrix_fn(d.cols(), d.rows(), static_cast< F&& >(f), mem);
	}

	template <
		typename F, bool Nct, size_t N,
		typename Memory = memory_std_t
	> constexpr auto make_square_matrix_fn(
		dim_t< Nct, N > n, F&& f, Memory mem = memory_std
	){
		return make_matrix_fn(
			n.as_col(), n.as_row(), static_cast< F&& >(f), mem
		);
	}

	template <
		typename F, bool Nct, size_t N,
		typename Memory = memory_std_t
	> constexpr auto make_col_vector_fn(
		row_t< Nct, N > r, F&& f, Memory = memory_std
	){
		return Memory::make_col_vector_fn(r, static_cast< F&& >(f));
	}

	template <
		typename F, bool Nct, size_t N,
		typename Memory = memory_std_t
	> constexpr auto make_row_vector_fn(
		col_t< Nct, N > c, F&& f, Memory = memory_std
	){
		return Memory::make_row_vector_fn(c, static_cast< F&& >(f));
	}

	template <
		typename F, size_t C, size_t R,
		typename Memory = memory_std_t
	> auto make_bitmap_fn(
		dims_t< C, R > const& d, F&& f, Memory mem = memory_std
	){
		return make_matrix_fn(
			col_t< false, 0 >(d.cols()),
			row_t< false, 0 >(d.rows()),
			static_cast< F&& >(f), mem
		);
	}

	template < typename F, typename Memory = memory_std_t >
	auto make_bitmap_fn(
		size_t c, size_t r, F&& f, Memory mem = memory_std
	){
		return make_matrix_fn(
			col_t< false, 0 >(c),
			row_t< false, 0 >(r),
			static_cast< F&& >(f), mem
		);
	}


	template <
		typename F, bool Nct, size_t N,
		typename Memory = memory_std_t
	> constexpr auto make_diag_matrix_fn(
		dim_t< Nct, N > n, F&& f, Memory mem = memory_std
	){
		return make_square_matrix_fn(n,
			detail::make_init_diag_fn(static_cast< F&& >(f)), mem);
	}


	template <
		typename T, bool Cct, size_t C, bool Rct, size_t R,
		typename Memory = memory_std_t
	> constexpr auto make_matrix_v(
		col_t< Cct, C > c, row_t< Rct, R > r, T const& v = T(),
		Memory = memory_std
	){
		return Memory::make_matrix_v(c, r, v);
	}

	template <
		typename T, size_t C, size_t R,
		typename Memory = memory_std_t
	> constexpr auto make_matrix_v(
		dims_t< C, R > const& d, T const& v = T(), Memory mem = memory_std
	){
		return make_matrix_v(d.cols(), d.rows(), v, mem);
	}

	template <
		typename T, bool Cct, size_t C, bool Rct, size_t R,
		typename Memory = memory_std_t
	> constexpr auto make_matrix(
		col_t< Cct, C > c, row_t< Rct, R > r, T(&&v)[R][C],
		Memory = memory_std
	){
		return Memory::make_matrix(c, r, std::move(v));
	}

	template <
		typename T, bool Cct, size_t C, bool Rct, size_t R,
		typename Memory = memory_std_t
	> constexpr auto make_matrix(
		col_t< Cct, C > c, row_t< Rct, R > r, T(&v)[R][C],
		Memory = memory_std
	){
		return Memory::make_matrix(c, r, v);
	}


	template <
		typename T, bool Nct, size_t N,
		typename Memory = memory_std_t
	> constexpr auto make_square_matrix_v(
		dim_t< Nct, N > n, T const& v = T(), Memory mem = memory_std
	){
		return make_matrix_v(n.as_col(), n.as_row(), v, mem);
	}

	template <
		typename T, bool Nct, size_t N,
		typename Memory = memory_std_t
	> constexpr auto make_square_matrix(
		dim_t< Nct, N > n, T(&&v)[N][N], Memory mem = memory_std
	){
		return make_matrix(n.as_col(), n.as_row(), std::move(v), mem);
	}

	template <
		typename T, bool Nct, size_t N,
		typename Memory = memory_std_t
	> constexpr auto make_square_matrix(
		dim_t< Nct, N > n, T(&v)[N][N], Memory mem = memory_std
	){
		return make_matrix(n.as_col(), n.as_row(), v, mem);
	}


	template <
		typename T, bool Nct, size_t N,
		typename Memory = memory_std_t
	> constexpr auto make_col_vector_v(
		row_t< Nct, N > r, T const& v = T(), Memory mem = memory_std
	){
		using namespace literals;
		return make_matrix_v(1_C, r, v, mem);
	}

	template <
		typename T, bool Nct, size_t N,
		typename Memory = memory_std_t
	> constexpr auto make_col_vector(
		row_t< Nct, N > r, T(&&v)[N], Memory = memory_std
	){
		return Memory::make_col_vector(r, std::move(v));
	}

	template <
		typename T, bool Nct, size_t N,
		typename Memory = memory_std_t
	> constexpr auto make_col_vector(
		row_t< Nct, N > r, T(&v)[N], Memory = memory_std
	){
		return Memory::make_col_vector(r, v);
	}


	template <
		typename T, bool Nct, size_t N,
		typename Memory = memory_std_t
	> constexpr auto make_row_vector_v(
		col_t< Nct, N > c, T const& v = T(), Memory mem = memory_std
	){
		using namespace literals;
		return make_matrix_v(c, 1_R, v, mem);
	}

	template <
		typename T, bool Nct, size_t N,
		typename Memory = memory_std_t
	> constexpr auto make_row_vector(
		col_t< Nct, N > c, T(&&v)[N], Memory = memory_std
	){
		return Memory::make_row_vector(c, std::move(v));
	}

	template <
		typename T, bool Nct, size_t N,
		typename Memory = memory_std_t
	> constexpr auto make_row_vector(
		col_t< Nct, N > c, T(&v)[N], Memory = memory_std
	){
		return Memory::make_row_vector(c, v);
	}

	template <
		typename T, size_t C, size_t R,
		typename Memory = memory_std_t
	> auto make_bitmap_v(
		dims_t< C, R > const& d, T const& v = T(), Memory mem = memory_std
	){
		return make_matrix_v(
			col_t< false, 0 >(d.cols()),
			row_t< false, 0 >(d.rows()),
			v, mem
		);
	}

	template < typename T, typename Memory = memory_std_t >
	auto make_bitmap_v(
		size_t c, size_t r, T const& v = T(), Memory mem = memory_std
	){
		return make_matrix_v(
			col_t< false, 0 >(c), row_t< false, 0 >(r), v, mem
		);
	}


	template <
		typename T, bool Nct, size_t N,
		typename Memory = memory_std_t
	> constexpr auto make_diag_matrix_v(
		dim_t< Nct, N > n, T const& v = T(), Memory mem = memory_std
	){
		return make_square_matrix_fn(
			n, detail::init_diag_by_value< T >{v}, mem
		);
	}

	template <
		typename T, bool Nct, size_t N,
		typename Memory = memory_std_t
	> constexpr auto make_diag_matrix(
		dim_t< Nct, N > n, T(&&v)[N], Memory mem = memory_std
	){
		return make_square_matrix_fn(n,
			detail::init_diag_by_array< T(&&)[N] >{std::move(v)}, mem);
	}

	template <
		typename T, bool Nct, size_t N,
		typename Memory = memory_std_t
	> constexpr auto make_diag_matrix(
		dim_t< Nct, N > n, T(&v)[N], Memory mem = memory_std
	){
		return make_square_matrix_fn(n,
			detail::init_diag_by_array< T(&)[N] >{v}, mem);
	}


	template <
		typename T, bool Nct, size_t N,
		typename Memory = memory_std_t
	> constexpr auto make_identity_matrix(
		dim_t< Nct, N > n, Memory mem = memory_std
	){
		return make_diag_matrix_v(n, T(1), mem);
	}


}

#endif
