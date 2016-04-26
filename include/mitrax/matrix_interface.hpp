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


namespace mitrax{


	template < typename M, size_t Cols, size_t Rows >
	class matrix{
	public:
		// TODO: Check if M is a matrix_impl type!!!

		/// \brief Type of the data that administrates the matrix
		using value_type = value_type_t< M >;

		/// \brief Unsigned integral type (size_t)
		using size_type = size_t;

		/// \brief Signed integer type (std::ptrdiff_t)
		using difference_type = std::ptrdiff_t;

		/// \brief Type of points in the matrix
		using point_type = point< size_t >;

		/// \brief Type of matrix dimensions (cols and rows)
		using dimension_type = dims_t< Cols, Rows >;

		/// \brief Type of a reference to data
		using reference = value_type&;

		/// \brief Type of a reference to const data
		using const_reference = value_type const&;

		/// \brief Type of a pointer to data
		using pointer = value_type*;

		/// \brief Type of a pointer to const data
		using const_pointer = value_type const*;

		/// \brief Type of a iterator for data
		using iterator = typename M::iterator;

		/// \brief Type of a iterator for const data
		using const_iterator = typename M::const_iterator;

		/// \brief Type of a reverse iterator for data
		using reverse_iterator = typename M::reverse_iterator;

		/// \brief Type of a reverse iterator for const data
		using const_reverse_iterator = typename M::const_reverse_iterator;


		constexpr matrix() = default;

		constexpr matrix(M&& m): m_(std::move(m)) {}

		constexpr matrix(matrix&&) = default;

		constexpr matrix(matrix const&) = default;


		constexpr matrix& operator=(matrix&&) = default;

		constexpr matrix& operator=(matrix const&) = default;


		constexpr col_t< Cols != 0, Cols > cols()const noexcept{
			return m_.cols();
		}

		constexpr row_t< Rows != 0, Rows > rows()const noexcept{
			return m_.rows();
		}

		constexpr dims_t< Cols, Rows > dims()const noexcept{
			return mitrax::dims(cols(), rows());
		}

		constexpr size_t point_count()const noexcept{
			return size_t(cols()) * size_t(rows());
		}


		constexpr decltype(auto) operator()(size_t x, size_t y){
			assert(x < m_.cols());
			assert(y < m_.rows());
			return m_(x, y);
		}

		constexpr decltype(auto) operator()(size_t x, size_t y)const{
			assert(x < m_.cols());
			assert(y < m_.rows());
			return m_(x, y);
		}


		constexpr decltype(auto) operator[](size_t i){
			static_assert(
				Cols == 1 || Rows == 1,
				"access operator only allowed for compile time dim vectors"
			);

			if(Cols == 1){
				if(Rows == 1){
					assert(i == 0);
					return m_(0, 0);
				}
				return m_(0, i);
			}
			return m_(i, 0);
		}

		constexpr decltype(auto) operator[](size_t i)const{
			static_assert(
				Cols == 1 || Rows == 1,
				"access operator only allowed for compile time dim vectors"
			);

			if(Cols == 1){
				if(Rows == 1){
					assert(i == 0);
					return m_(0, 0);
				}
				return m_(0, i);
			}
			return m_(i, 0);
		}


		constexpr operator value_type()const{
			static_assert(
				Cols == 1 && Rows == 1,
				"value conversion is only allowed for compile time dim "
				"matrices with one element"
			);

			return m_(0, 0);
		}


		constexpr iterator begin(){
			return m_.begin();
		}

		constexpr const_iterator begin()const{
			return m_.begin();
		}

		constexpr iterator end(){
			return m_.end();
		}

		constexpr const_iterator end()const{
			return m_.end();
		}

		constexpr reverse_iterator rbegin(){
			return m_.rbegin();
		}

		constexpr const_reverse_iterator rbegin()const{
			return m_.rbegin();
		}

		constexpr reverse_iterator rend(){
			return m_.rend();
		}

		constexpr const_reverse_iterator rend()const{
			return m_.rend();
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


		constexpr value_type* data(){
			static_assert(
				has_data< M >::value,
				"The underlaying matrix implementation doesn't support "
				"m.data()"
			);
			return m_.data();
		}

		constexpr value_type const* data()const{
			static_assert(
				has_data< M const >::value,
				"The underlaying matrix implementation doesn't support "
				"m.data()const"
			);
			return m_.data();
		}


	protected:
		M m_;

	private:
		template < bool Cct, size_t C, bool Rct, size_t R >
		constexpr void
		check_dims(col_t< Cct, C > c, row_t< Rct, R > r)const{
			static_assert(
				(Cols == 0 || !Cct || Cols == C) &&
				(Rows == 0 || !Rct || Rows == R),
				"matrix dimensions not compatible"
			);

			if(cols() != c || rows() != r){
				throw std::logic_error("matrix dimensions not compatible");
			}
		}

		template< typename T, typename = void >
		struct has_data: std::false_type{};

		template< typename T >
		struct has_data< T, decltype(
			static_cast< std::conditional_t<
				std::is_const< T >::value, value_type const*, value_type*
			> >(std::declval< T >().data()), void())
		>: std::true_type{};
	};


	template < typename ... M, size_t ... C, size_t ... R >
	constexpr auto get_cols(matrix< M, C, R > const& ... m){
		return get(m.cols() ...);
	}

	template < typename ... M, size_t ... C, size_t ... R >
	constexpr auto get_rows(matrix< M, C, R > const& ... m){
		return get(m.rows() ...);
	}

	template < typename ... M, size_t ... C, size_t ... R >
	constexpr auto get_dims(matrix< M, C, R > const& ... m){
		return get(m.dims() ...);
	}



}

#endif
