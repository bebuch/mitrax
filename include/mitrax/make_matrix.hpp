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

#include "iterator/function.hpp"
#include "iterator/value.hpp"
#include "iterator/flat.hpp"
#include "iterator/move.hpp"
#include "iterator/utility.hpp"

#include "reference_wrapper.hpp"

#include "matrix/std.hpp"


namespace mitrax{


	namespace detail{


		template < typename F >
		struct init_diag_fn{
			F f;

			constexpr decltype(std::declval< F&& >()(size_t()))
			operator()(size_t x, size_t y)const
			noexcept(noexcept(std::declval< F&& >()(size_t()))){
				return x == y ? f(x) : decltype(f(x))();
			}
		};

		template < typename F >
		constexpr auto make_init_diag_fn(F&& f){
			return init_diag_fn< F >{static_cast< F&& >(f)};
		}

		template < typename T >
		struct init_diag_by_value{
			T const& v;

			constexpr std::remove_cv_t< T >
			operator()(size_t x, size_t y)const{
				return x == y ? v : std::remove_cv_t< T >();
			}
		};


		template < typename ArrayRef >
		struct array_1d_element{
			using type = std::remove_extent_t<
				std::remove_reference_t< ArrayRef > >;
		};

		template < typename ArrayRef >
		using array_1d_element_t = typename array_1d_element< ArrayRef >::type;


		template < typename ArrayRef >
		struct array_1d_element_ref{
			using value_type = array_1d_element_t< ArrayRef >;

			using type = std::conditional_t<
					std::is_rvalue_reference< ArrayRef >::value,
					std::add_rvalue_reference_t< value_type >,
					std::add_lvalue_reference_t< value_type >
				>;
		};

		template < typename ArrayRef >
		using array_1d_element_ref_t =
			typename array_1d_element_ref< ArrayRef >::type;


		template < typename Array, typename T >
		struct init_diag_by_array{
			Array array_;
			T default_;

			constexpr T operator()(size_t x, size_t y){
				return x == y ? array_[x] : default_;
			}
		};

		template < typename I >
		struct init_diag_by_iter{
			I i;

			constexpr auto operator()(size_t x, size_t y)const{
				return x == y ?
					static_cast< iter_type_t< I > >(i[x]) :
					iter_type_t< I >();
			}
		};


	}


	template < typename F, bool Cct, size_t C, bool Rct, size_t R,
		typename Maker = maker::std_t >
	constexpr auto make_matrix_fn(
		col_t< Cct, C > c, row_t< Rct, R > r, F&& f, Maker maker = maker::std
	){
		return maker.by_sequence(c, r,
			make_function_iterator(make_function_xy_adapter(
				static_cast< F&& >(f), c)));
	}

	template < typename F, size_t C, size_t R, typename Maker = maker::std_t >
	constexpr auto make_matrix_fn(
		dims_t< C, R > const& d, F&& f, Maker maker = maker::std
	){
		return make_matrix_fn(d.cols(), d.rows(), static_cast< F&& >(f), maker);
	}

	template < typename F, bool Nct, size_t N, typename Maker = maker::std_t >
	constexpr auto make_matrix_fn(
		dim_t< Nct, N > n, F&& f, Maker maker = maker::std
	){
		return make_matrix_fn(
			n.as_col(), n.as_row(), static_cast< F&& >(f), maker
		);
	}

	template < typename F, bool Nct, size_t N, typename Maker = maker::std_t >
	constexpr auto make_vector_fn(
		row_t< Nct, N > r, F&& f, Maker maker = maker::std
	){
		using namespace literals;
		return maker.by_sequence(1_C, r,
			make_function_iterator(static_cast< F&& >(f)));
	}

	template < typename F, bool Nct, size_t N, typename Maker = maker::std_t >
	constexpr auto make_vector_fn(
		col_t< Nct, N > c, F&& f, Maker maker = maker::std
	){
		using namespace literals;
		return maker.by_sequence(c, 1_R,
			make_function_iterator(static_cast< F&& >(f)));
	}

	template < typename F, bool Nct, size_t N, typename Maker = maker::std_t >
	constexpr auto make_diag_matrix_fn(
		dim_t< Nct, N > n, F&& f, Maker maker = maker::std
	){
		return make_matrix_fn(n,
			detail::make_init_diag_fn(static_cast< F&& >(f)), maker);
	}


	template < typename T, bool Cct, size_t C, bool Rct, size_t R,
		typename Maker = maker::std_t >
	constexpr auto make_matrix_v(
		col_t< Cct, C > c, row_t< Rct, R > r, T const& v = T(),
		Maker maker = maker::std
	){
		return maker.by_sequence(c, r, mitrax::make_value_iterator(v));
	}

	template < typename T, size_t C, size_t R, typename Maker = maker::std_t >
	constexpr auto make_matrix_v(
		dims_t< C, R > const& d, T const& v = T(), Maker maker = maker::std
	){
		return make_matrix_v(d.cols(), d.rows(), v, maker);
	}

	template < typename T, bool Nct, size_t N, typename Maker = maker::std_t >
	constexpr auto make_matrix_v(
		dim_t< Nct, N > n, T const& v = T(), Maker maker = maker::std
	){
		return make_matrix_v(n.as_col(), n.as_row(), v, maker);
	}

	template < typename T, bool Nct, size_t N, typename Maker = maker::std_t >
	constexpr auto make_vector_v(
		row_t< Nct, N > r, T const& v = T(), Maker maker = maker::std
	){
		using namespace literals;
		return make_matrix_v(1_C, r, v, maker);
	}

	template < typename T, bool Nct, size_t N, typename Maker = maker::std_t >
	constexpr auto make_vector_v(
		col_t< Nct, N > c, T const& v = T(), Maker maker = maker::std
	){
		using namespace literals;
		return make_matrix_v(c, 1_R, v, maker);
	}

	template < typename T, bool Nct, size_t N, typename Maker = maker::std_t >
	constexpr auto make_diag_matrix_v(
		dim_t< Nct, N > n, T const& v = T(), Maker maker = maker::std
	){
		return make_matrix_fn(
			n, detail::init_diag_by_value< T >{v}, maker
		);
	}

	template < typename T, bool Nct, size_t N, typename Maker = maker::std_t >
	constexpr auto make_identity_matrix(
		dim_t< Nct, N > n, Maker maker = maker::std
	){
		return make_diag_matrix_v(n, T(1), maker);
	}


	template < typename I, bool Cct, size_t C, bool Rct, size_t R,
		typename Maker = maker::std_t >
	constexpr auto make_matrix_i(
		col_t< Cct, C > c, row_t< Rct, R > r, I i,
		Maker maker = maker::std
	){
		return maker.by_sequence(c, r, i);
	}

	template < typename I, size_t C, size_t R, typename Maker = maker::std_t >
	constexpr auto make_matrix_i(
		dims_t< C, R > const& d, I i, Maker maker = maker::std
	){
		return make_matrix_i(d.cols(), d.rows(), i, maker);
	}

	template < typename I, bool Nct, size_t N, typename Maker = maker::std_t >
	constexpr auto make_matrix_i(
		dim_t< Nct, N > n, I i, Maker maker = maker::std
	){
		return make_matrix_i(n.as_col(), n.as_row(), i, maker);
	}

	template < typename I, bool Nct, size_t N, typename Maker = maker::std_t >
	constexpr auto make_vector_i(
		row_t< Nct, N > r, I i, Maker maker = maker::std
	){
		using namespace literals;
		return make_matrix_i(1_C, r, i, maker);
	}

	template < typename I, bool Nct, size_t N, typename Maker = maker::std_t >
	constexpr auto make_vector_i(
		col_t< Nct, N > c, I i, Maker maker = maker::std
	){
		using namespace literals;
		return make_matrix_i(c, 1_R, i, maker);
	}

	template < typename I, bool Nct, size_t N, typename Maker = maker::std_t >
	constexpr auto make_diag_matrix_i(
		dim_t< Nct, N > n, I i, Maker maker = maker::std
	){
		return make_matrix_fn(
			n, detail::init_diag_by_iter< I >{i}, maker
		);
	}


	template < typename T, bool Cct, size_t C, bool Rct, size_t R,
		typename Maker = maker::std_t >
	constexpr auto make_matrix(
		col_t< Cct, C > c, row_t< Rct, R > r, T(&&v)[R][C],
		Maker maker = maker::std
	){
		return make_matrix_i(c, r, mitrax::make_move_iterator(
			mitrax::flat_iterator< T, R, C >(&v)), maker);
	}

	template < typename T, bool Cct, size_t C, bool Rct, size_t R,
		typename Maker = maker::std_t >
	constexpr auto make_matrix(
		col_t< Cct, C > c, row_t< Rct, R > r, T(&v)[R][C],
		Maker maker = maker::std
	){
		return make_matrix_i(c, r, mitrax::flat_iterator< T, R, C >(&v), maker);
	}

	template < typename T, bool Nct, size_t N, typename Maker = maker::std_t >
	constexpr auto make_matrix(
		dim_t< Nct, N > n, T(&&v)[N][N], Maker maker = maker::std
	){
		return make_matrix(n.as_col(), n.as_row(), std::move(v), maker);
	}

	template < typename T, bool Nct, size_t N, typename Maker = maker::std_t >
	constexpr auto make_matrix(
		dim_t< Nct, N > n, T(&v)[N][N], Maker maker = maker::std
	){
		return make_matrix(n.as_col(), n.as_row(), v, maker);
	}

	template < typename T, bool Nct, size_t N, typename Maker = maker::std_t >
	constexpr auto make_vector(
		row_t< Nct, N > r, T(&&v)[N], Maker maker = maker::std
	){
		using namespace literals;
		return make_matrix_i(1_C, r,
			mitrax::make_move_iterator(mitrax::begin(v)), maker);
	}

	template < typename T, bool Nct, size_t N, typename Maker = maker::std_t >
	constexpr auto make_vector(
		row_t< Nct, N > r, T(&v)[N], Maker maker = maker::std
	){
		using namespace literals;
		return make_matrix_i(1_C, r, mitrax::begin(v), maker);
	}

	template < typename T, bool Nct, size_t N, typename Maker = maker::std_t >
	constexpr auto make_vector(
		col_t< Nct, N > c, T(&&v)[N], Maker maker = maker::std
	){
		using namespace literals;
		return make_matrix_i(c, 1_R,
			mitrax::make_move_iterator(mitrax::begin(v)), maker);
	}

	template < typename T, bool Nct, size_t N, typename Maker = maker::std_t >
	constexpr auto make_vector(
		col_t< Nct, N > c, T(&v)[N], Maker maker = maker::std
	){
		using namespace literals;
		return make_matrix_i(c, 1_R, mitrax::begin(v), maker);
	}

	template < typename T, bool Nct, size_t N, typename Maker = maker::std_t >
	constexpr auto make_diag_matrix(
		dim_t< Nct, N > n, T(&&v)[N], Maker maker = maker::std
	){
		detail::init_diag_by_array< T(&&)[N], std::decay_t< T > > init
			{std::move(v), std::decay_t< T >()};
		return make_matrix_fn(n, mitrax::ref(init), maker);
	}

	template < typename T, bool Nct, size_t N, typename Maker = maker::std_t >
	constexpr auto make_diag_matrix(
		dim_t< Nct, N > n, T(&v)[N], Maker maker = maker::std
	){
		detail::init_diag_by_array< T(&)[N], std::decay_t< T > > init
			{v, std::decay_t< T >()};
		return make_matrix_fn(n, mitrax::ref(init), maker);
	}


}

#endif
