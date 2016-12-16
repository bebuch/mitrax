//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__matrix_interface__hpp_INCLUDED_
#define _mitrax__matrix_interface__hpp_INCLUDED_

#include "dim.hpp"
#include "point.hpp"
#include "matrix_fwd.hpp"

#include <utility>
#include <cassert>
#include <algorithm>


namespace mitrax::maker{


	class key;

	class init_t final{
		friend class key;
		constexpr init_t()noexcept = default;
	};

	class key{
	protected:
		static constexpr auto init = init_t();
	};


}


namespace mitrax{


	struct default_constructor_key{};


	template < typename M, col_ct Cols, row_ct Rows >
	class matrix final{
	public:
		// TODO: Check if M is a matrix_impl type!!!

		static_assert(std::is_class_v< M > && !std::is_const_v< M >);
		static_assert(!std::is_const_v< value_type_t< M > >);
		static_assert(!std::is_reference_v< value_type_t< M > >);
		static_assert(!std::is_default_constructible_v< M >,
			"Matrix implementation must not be default constructible, "
			"the 'default constructor' must have "
			"::mitrax::default_constructor_key as first parameter");


		static constexpr col_ct ct_cols = Cols;
		static constexpr row_ct ct_rows = Rows;


		/// \brief Type of the matrix implementation
		using impl_type = M;

		/// \brief Type of the data that administrates the matrix
		using value_type = value_type_t< M >;


		static_assert(
			has_iterator_fn_v< M const > ||
			has_data_v< value_type const*, M const >,
			"Matrix impl must provide at least begin() and end() or data()"
		);


		/// \brief Type with the make functions
		using maker_type = typename M::maker_type;

		/// \brief Unsigned integral type (size_t)
		using size_type = size_t;

		/// \brief Signed integer type (std::ptrdiff_t)
		using difference_type = std::ptrdiff_t;

		/// \brief Type of points in the matrix
		using point_type = point< size_t >;

		/// \brief Type of matrix dimensions (cols and rows)
		using dimension_type = auto_dim_pair_t< Cols, Rows >;

		/// \brief Type of a reference to data
		using reference = value_type&;

		/// \brief Type of a reference to const data
		using const_reference = value_type const&;

		/// \brief Type of a pointer to data
		using pointer = value_type*;

		/// \brief Type of a pointer to const data
		using const_pointer = value_type const*;

		/// \brief Type of a iterator for data
		using iterator = iterator_fn_t< M >;

		/// \brief Type of a iterator for const data
		using const_iterator = iterator_fn_t< M const >;

		/// \brief Type of a reverse iterator for data
		using reverse_iterator = std::reverse_iterator< iterator >;

		/// \brief Type of a reverse iterator for const data
		using const_reverse_iterator = std::reverse_iterator< const_iterator >;


		constexpr matrix():
			m_(default_constructor_key()) {}

		constexpr matrix(matrix&&) = default;

		constexpr matrix(matrix const&) = default;

		template < typename ... T >
		constexpr matrix(maker::init_t, T&& ... v): // Use []{ return M{}; } instead
			m_(static_cast< T&& >(v) ...) {}


		constexpr matrix& operator=(matrix&&) = default;

		constexpr matrix& operator=(matrix const&) = default;


		constexpr col< Cols != 0_C, Cols > cols()const noexcept{
			return m_.cols();
		}

		constexpr row< Rows != 0_R, Rows > rows()const noexcept{
			return m_.rows();
		}

		constexpr auto dims()const noexcept{
			return auto_dim_pair_t< Cols, Rows >(m_.cols(), m_.rows());
		}

		constexpr size_t point_count()const noexcept{
			return size_t(cols()) * size_t(rows());
		}


		constexpr decltype(auto) operator()(size_t x, size_t y){
			assert(x < size_t(cols()) && y < size_t(rows()));
			return m_(x, y);
		}

		constexpr decltype(auto) operator()(size_t x, size_t y)const{
			assert(x < size_t(cols()) && y < size_t(rows()));
			return m_(x, y);
		}


		constexpr decltype(auto) operator[](size_t i){
			static_assert(
				Cols == 1_C || Rows == 1_R,
				"access operator only allowed for compile time dim vectors"
			);

			if constexpr(Cols == 1_C && Rows == 1_R){
				assert(i == 0);
				return m_(0, 0);
			}else if(Cols == 1_C){
				assert(i < size_t(rows()));
				return m_(0, i);
			}else{
				assert(i < size_t(cols()));
				return m_(i, 0);
			}
		}

		constexpr decltype(auto) operator[](size_t i)const{
			static_assert(
				Cols == 1_C || Rows == 1_R,
				"access operator only allowed for compile time dim vectors"
			);

			if constexpr(Cols == 1_C && Rows == 1_R){
				assert(i == 0);
				return m_(0, 0);
			}else if(Cols == 1_C){
				assert(i < size_t(rows()));
				return m_(0, i);
			}else{
				assert(i < size_t(cols()));
				return m_(i, 0);
			}
		}


		constexpr operator value_type const&()const{
			static_assert(
				Cols == 1_C && Rows == 1_R,
				"value conversion is only allowed for compile time dim "
				"matrices with one element"
			);

			return m_(0, 0);
		}

		constexpr operator value_type&(){
			static_assert(
				Cols == 1_C && Rows == 1_R,
				"value conversion is only allowed for compile time dim "
				"matrices with one element"
			);

			return m_(0, 0);
		}


		constexpr iterator begin(){
			if constexpr(
				has_iterator_fn_v< M > || has_iterator_fn_v< M const >
			){
				return m_.begin();
			}else{
				return data();
			}
		}

		constexpr const_iterator begin()const{
			if constexpr(has_iterator_fn_v< M const >){
				return m_.begin();
			}else{
				return data();
			}
		}

		constexpr iterator end(){
			if constexpr(
				has_iterator_fn_v< M > || has_iterator_fn_v< M const >
			){
				return m_.end();
			}else{
				return data() + point_count();
			}
		}

		constexpr const_iterator end()const{
			if constexpr(has_iterator_fn_v< M const >){
				return m_.end();
			}else{
				return data() + point_count();
			}
		}

		constexpr reverse_iterator rbegin(){
			return std::make_reverse_iterator(end());
		}

		constexpr const_reverse_iterator rbegin()const{
			return std::make_reverse_iterator(end());
		}

		constexpr reverse_iterator rend(){
			return std::make_reverse_iterator(begin());
		}

		constexpr const_reverse_iterator rend()const{
			return std::make_reverse_iterator(begin());
		}

		constexpr const_iterator cbegin()const{
			return begin();
		}

		constexpr const_iterator cend()const{
			return end();
		}

		constexpr const_reverse_iterator crbegin()const{
			return rbegin();
		}

		constexpr const_reverse_iterator crend()const{
			return rend();
		}


		constexpr M& impl(){
			return m_;
		}

		constexpr M const& impl()const{
			return m_;
		}


		template <
			typename dummy = int,
			std::enable_if_t< has_data_v< value_type*, M >, dummy > = 0 >
		constexpr value_type* data(){
			return m_.data();
		}

		constexpr value_type const* data()const{
			static_assert(
				has_data_v< value_type const*, M const >,
				"The underlaying matrix implementation doesn't support "
				"'value_type const* m.data()const'"
			);
			return m_.data();
		}


	private:
		M m_;
	};

// 	TODO: The implementation shall only be constructible by matrix
// 		–– (or only by implementation maker type???) –– <- no, copy and move is by matrix …
// 	Priority: Default-Constructor! It can by protected by keypass :-D
// 	class matrix_impl_base{
// 		template < typename M, col_ct C, row_ct R > friend class matrix;
// 	protected:
// 		constexpr matrix_impl_base()noexcept = default;
// 		constexpr matrix_impl_base(matrix_impl_base const&)noexcept = default;
// 		constexpr matrix_impl_base(matrix_impl_base&&)noexcept = default;
//
// 		constexpr matrix_impl_base& operator=(matrix_impl_base const&)noexcept = default;
// 		constexpr matrix_impl_base& operator=(matrix_impl_base&&)noexcept = default;
// 	};


	template < typename ... M, col_ct ... C, row_ct ... R >
	constexpr auto get_cols(matrix< M, C, R > const& ... m){
		return get(m.cols() ...);
	}

	template < typename ... M, col_ct ... C, row_ct ... R >
	constexpr auto get_rows(matrix< M, C, R > const& ... m){
		return get(m.rows() ...);
	}

	template < typename ... M, col_ct ... C, row_ct ... R >
	constexpr auto get_dims(matrix< M, C, R > const& ... m){
		return get(m.dims() ...);
	}



}


#endif
