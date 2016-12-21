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

			constexpr decltype(std::declval< F&& >()(c_t()))
			operator()(c_t c, r_t r)const
			noexcept(noexcept(std::declval< F&& >()(c_t()))){
				return c == c_t(r) ? f(c) : decltype(f(c))();
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
			operator()(c_t c, r_t r)const{
				return c == c_t(r) ? v : std::remove_cv_t< T >();
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

			constexpr T operator()(c_t c, r_t r){
				return c == c_t(r) ? array_[size_t(c)] : default_;
			}
		};

		template < typename I >
		struct init_diag_by_iter{
			I i;

			constexpr auto operator()(c_t c, r_t r)const{
				return c == c_t(r) ?
					static_cast< iter_type_t< I > >(i[size_t(c)]) :
					iter_type_t< I >();
			}
		};


	}


	template < typename F, bool Cct, col_t C, bool Rct, row_t R,
		typename Maker = maker::std_t >
	constexpr auto make_matrix_fn(
		col< Cct, C > c, row< Rct, R > r, F&& f,
		Maker&& maker = maker::std_t()
	){
		return maker.by_sequence(c, r,
			make_function_iterator(make_function_xy_adapter(
				static_cast< F&& >(f), c)));
	}

	template < typename F, bool Cct, col_t C, bool Rct, row_t R,
		typename Maker = maker::std_t >
	constexpr auto make_matrix_fn(
		dim_pair_t< Cct, C, Rct, R > const& d, F&& f,
		Maker&& maker = maker::std_t()
	){
		return make_matrix_fn(d.cols(), d.rows(),
			static_cast< F&& >(f), static_cast< Maker&& >(maker));
	}

	template < typename F, bool Dct, dim_t D, typename Maker = maker::std_t >
	constexpr auto make_matrix_fn(
		dim< Dct, D > d, F&& f, Maker&& maker = maker::std_t()
	){
		return make_matrix_fn(d.as_col(), d.as_row(),
			static_cast< F&& >(f), static_cast< Maker&& >(maker)
		);
	}

	template < typename F, bool Rct, row_t R, typename Maker = maker::std_t >
	constexpr auto make_vector_fn(
		row< Rct, R > r, F&& f, Maker&& maker = maker::std_t()
	){
		using namespace literals;
		return maker.by_sequence(1_CS, r,
			make_function_iterator(static_cast< F&& >(f)));
	}

	template < typename F, bool Cct, col_t C, typename Maker = maker::std_t >
	constexpr auto make_vector_fn(
		col< Cct, C > c, F&& f, Maker&& maker = maker::std_t()
	){
		using namespace literals;
		return maker.by_sequence(c, 1_RS,
			make_function_iterator(static_cast< F&& >(f)));
	}

	template < typename F, bool Dct, dim_t D, typename Maker = maker::std_t >
	constexpr auto make_diag_matrix_fn(
		dim< Dct, D > d, F&& f, Maker&& maker = maker::std_t()
	){
		return make_matrix_fn(d,
			detail::make_init_diag_fn(static_cast< F&& >(f)),
			static_cast< Maker&& >(maker));
	}


	template < typename T, bool Cct, col_t C, bool Rct, row_t R,
		typename Maker = maker::std_t >
	constexpr auto make_matrix_v(
		col< Cct, C > c, row< Rct, R > r, T const& v = T(),
		Maker&& maker = maker::std_t()
	){
		return maker.by_sequence(c, r, mitrax::make_value_iterator(v));
	}

	template < typename T, bool Cct, col_t C, bool Rct, row_t R,
		typename Maker = maker::std_t >
	constexpr auto make_matrix_v(
		dim_pair_t< Cct, C, Rct, R > const& d, T const& v = T(),
		Maker&& maker = maker::std_t()
	){
		return make_matrix_v(d.cols(), d.rows(), v,
			static_cast< Maker&& >(maker));
	}

	template < typename T, bool Dct, dim_t D, typename Maker = maker::std_t >
	constexpr auto make_matrix_v(
		dim< Dct, D > d, T const& v = T(), Maker&& maker = maker::std_t()
	){
		return make_matrix_v(d.as_col(), d.as_row(), v,
			static_cast< Maker&& >(maker));
	}

	template < typename T, bool Rct, row_t R, typename Maker = maker::std_t >
	constexpr auto make_vector_v(
		row< Rct, R > r, T const& v = T(), Maker&& maker = maker::std_t()
	){
		using namespace literals;
		return make_matrix_v(1_CS, r, v, static_cast< Maker&& >(maker));
	}

	template < typename T, bool Cct, col_t C, typename Maker = maker::std_t >
	constexpr auto make_vector_v(
		col< Cct, C > c, T const& v = T(), Maker&& maker = maker::std_t()
	){
		using namespace literals;
		return make_matrix_v(c, 1_RS, v, static_cast< Maker&& >(maker));
	}

	template < typename T, bool Dct, dim_t D, typename Maker = maker::std_t >
	constexpr auto make_diag_matrix_v(
		dim< Dct, D > d, T const& v = T(), Maker&& maker = maker::std_t()
	){
		return make_matrix_fn(
			d, detail::init_diag_by_value< T >{v},
			static_cast< Maker&& >(maker)
		);
	}

	template < typename T, bool Dct, dim_t D, typename Maker = maker::std_t >
	constexpr auto make_identity_matrix(
		dim< Dct, D > d, Maker&& maker = maker::std_t()
	){
		return make_diag_matrix_v(d, T(1), static_cast< Maker&& >(maker));
	}


	template < typename I, bool Cct, col_t C, bool Rct, row_t R,
		typename Maker = maker::std_t >
	constexpr auto make_matrix_i(
		col< Cct, C > c, row< Rct, R > r, I i,
		Maker&& maker = maker::std_t()
	){
		return maker.by_sequence(c, r, i);
	}

	template < typename I, bool Cct, col_t C, bool Rct, row_t R,
		typename Maker = maker::std_t >
	constexpr auto make_matrix_i(
		dim_pair_t< Cct, C, Rct, R > const& d, I i,
		Maker&& maker = maker::std_t()
	){
		return make_matrix_i(d.cols(), d.rows(), i,
			static_cast< Maker&& >(maker));
	}

	template < typename I, bool Dct, dim_t D, typename Maker = maker::std_t >
	constexpr auto make_matrix_i(
		dim< Dct, D > d, I i, Maker&& maker = maker::std_t()
	){
		return make_matrix_i(d.as_col(), d.as_row(), i,
			static_cast< Maker&& >(maker));
	}

	template < typename I, bool Rct, row_t R, typename Maker = maker::std_t >
	constexpr auto make_vector_i(
		row< Rct, R > r, I i, Maker&& maker = maker::std_t()
	){
		using namespace literals;
		return make_matrix_i(1_CS, r, i, static_cast< Maker&& >(maker));
	}

	template < typename I, bool Cct, col_t C, typename Maker = maker::std_t >
	constexpr auto make_vector_i(
		col< Cct, C > c, I i, Maker&& maker = maker::std_t()
	){
		using namespace literals;
		return make_matrix_i(c, 1_RS, i, static_cast< Maker&& >(maker));
	}

	template < typename I, bool Dct, dim_t D, typename Maker = maker::std_t >
	constexpr auto make_diag_matrix_i(
		dim< Dct, D > d, I i, Maker&& maker = maker::std_t()
	){
		return make_matrix_fn(
			d, detail::init_diag_by_iter< I >{i}, static_cast< Maker&& >(maker)
		);
	}


	template < typename T, bool Cct, col_t C, bool Rct, row_t R,
		typename Maker = maker::std_t >
	constexpr auto make_matrix(
		col< Cct, C > c, row< Rct, R > r, T(&&v)[size_t(R)][size_t(C)],
		Maker&& maker = maker::std_t()
	){
		return make_matrix_i(c, r, mitrax::make_move_iterator(
			mitrax::flat_iterator< T, size_t(R), size_t(C) >(&v)),
			static_cast< Maker&& >(maker));
	}

	template < typename T, bool Cct, col_t C, bool Rct, row_t R,
		typename Maker = maker::std_t >
	constexpr auto make_matrix(
		col< Cct, C > c, row< Rct, R > r, T(&v)[size_t(R)][size_t(C)],
		Maker&& maker = maker::std_t()
	){
		return make_matrix_i(c, r,
			mitrax::flat_iterator< T, size_t(R), size_t(C) >(&v),
			static_cast< Maker&& >(maker));
	}

	template < typename T, bool Cct, col_t C, bool Rct, row_t R,
		typename Maker = maker::std_t >
	constexpr auto make_matrix(
		dim_pair_t< Cct, C, Rct, R > const& d, T(&&v)[size_t(R)][size_t(C)],
		Maker&& maker = maker::std_t()
	){
		return make_matrix(d.cols(), d.rows(), std::move(v),
			static_cast< Maker&& >(maker));
	}

	template < typename T, bool Cct, col_t C, bool Rct, row_t R,
		typename Maker = maker::std_t >
	constexpr auto make_matrix(
		dim_pair_t< Cct, C, Rct, R > const& d, T(&v)[size_t(R)][size_t(C)],
		Maker&& maker = maker::std_t()
	){
		return make_matrix(d.cols(), d.rows(), v,
			static_cast< Maker&& >(maker));
	}

	template < typename T, bool Dct, dim_t D, typename Maker = maker::std_t >
	constexpr auto make_matrix(
		dim< Dct, D > d, T(&&v)[size_t(D)][size_t(D)],
		Maker&& maker = maker::std_t()
	){
		return make_matrix(d.as_col(), d.as_row(), std::move(v),
			static_cast< Maker&& >(maker));
	}

	template < typename T, bool Dct, dim_t D, typename Maker = maker::std_t >
	constexpr auto make_matrix(
		dim< Dct, D > d, T(&v)[size_t(D)][size_t(D)],
		Maker&& maker = maker::std_t()
	){
		return make_matrix(d.as_col(), d.as_row(), v,
			static_cast< Maker&& >(maker));
	}

	template < typename T, size_t C, size_t R, typename Maker = maker::std_t >
	constexpr auto make_matrix(
		T(&&v)[R][C], Maker&& maker = maker::std_t()
	){
		return make_matrix(cols< col_t(C) >(), rows< row_t(R) >(),
			std::move(v), static_cast< Maker&& >(maker));
	}

	template < typename T, size_t C, size_t R, typename Maker = maker::std_t >
	constexpr auto make_matrix(
		T(&v)[R][C], Maker&& maker = maker::std_t()
	){
		return make_matrix(cols< col_t(C) >(), rows< row_t(R) >(), v,
			static_cast< Maker&& >(maker));
	}

	template < typename T, bool Rct, row_t R, typename Maker = maker::std_t >
	constexpr auto make_vector(
		row< Rct, R > r, T(&&v)[size_t(R)], Maker&& maker = maker::std_t()
	){
		using namespace literals;
		return make_matrix_i(1_CS, r,
			mitrax::make_move_iterator(mitrax::begin(v)),
				static_cast< Maker&& >(maker));
	}

	template < typename T, bool Rct, row_t R, typename Maker = maker::std_t >
	constexpr auto make_vector(
		row< Rct, R > r, T(&v)[size_t(R)], Maker&& maker = maker::std_t()
	){
		using namespace literals;
		return make_matrix_i(1_CS, r, mitrax::begin(v),
			static_cast< Maker&& >(maker));
	}

	template < typename T, size_t D, typename Maker = maker::std_t >
	constexpr auto make_col_vector(
		T(&v)[D], Maker&& maker = maker::std_t()
	){
		return make_vector(rows< row_t(D) >(), v,
			static_cast< Maker&& >(maker));
	}

	template < typename T, size_t D, typename Maker = maker::std_t >
	constexpr auto make_col_vector(
		T(&&v)[D], Maker&& maker = maker::std_t()
	){
		return make_vector(rows< row_t(D) >(), std::move(v),
				static_cast< Maker&& >(maker));
	}

	template < typename T, bool Cct, col_t C, typename Maker = maker::std_t >
	constexpr auto make_vector(
		col< Cct, C > c, T(&&v)[size_t(C)], Maker&& maker = maker::std_t()
	){
		using namespace literals;
		return make_matrix_i(c, 1_RS,
			mitrax::make_move_iterator(mitrax::begin(v)),
			static_cast< Maker&& >(maker));
	}

	template < typename T, bool Cct, col_t C, typename Maker = maker::std_t >
	constexpr auto make_vector(
		col< Cct, C > c, T(&v)[size_t(C)], Maker&& maker = maker::std_t()
	){
		using namespace literals;
		return make_matrix_i(c, 1_RS, mitrax::begin(v),
			static_cast< Maker&& >(maker));
	}

	template < typename T, size_t D, typename Maker = maker::std_t >
	constexpr auto make_row_vector(
		T(&v)[D], Maker&& maker = maker::std_t()
	){
		return make_vector(cols< col_t(D) >(), v, static_cast< Maker&& >(maker));
	}

	template < typename T, size_t D, typename Maker = maker::std_t >
	constexpr auto make_row_vector(
		T(&&v)[D], Maker&& maker = maker::std_t()
	){
		return make_vector(cols< col_t(D) >(), std::move(v),
				static_cast< Maker&& >(maker));
	}

	template < typename T, bool Dct, dim_t D, typename Maker = maker::std_t >
	constexpr auto make_diag_matrix(
		dim< Dct, D > d, T(&&v)[size_t(D)], Maker&& maker = maker::std_t()
	){
		detail::init_diag_by_array< T(&&)[size_t(D)], std::decay_t< T > > init
			{std::move(v), std::decay_t< T >()};
		return make_matrix_fn(d, mitrax::ref(init),
			static_cast< Maker&& >(maker));
	}

	template < typename T, bool Dct, dim_t D, typename Maker = maker::std_t >
	constexpr auto make_diag_matrix(
		dim< Dct, D > d, T(&v)[size_t(D)], Maker&& maker = maker::std_t()
	){
		detail::init_diag_by_array< T(&)[size_t(D)], std::decay_t< T > > init
			{v, std::decay_t< T >()};
		return make_matrix_fn(d, mitrax::ref(init),
			static_cast< Maker&& >(maker));
	}

	template < typename T, size_t D, typename Maker = maker::std_t >
	constexpr auto make_diag_matrix(
		T(&&v)[D], Maker&& maker = maker::std_t()
	){
		return make_diag_matrix(dims< dim_t(D) >(), std::move(v),
			static_cast< Maker&& >(maker));
	}

	template < typename T, size_t D, typename Maker = maker::std_t >
	constexpr auto make_diag_matrix(
		T(&v)[D], Maker&& maker = maker::std_t()
	){
		return make_diag_matrix(dims< dim_t(D) >(), v,
			static_cast< Maker&& >(maker));
	}


}

#endif
