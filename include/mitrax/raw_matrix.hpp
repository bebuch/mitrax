//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__raw_matrix__hpp_INCLUDED_
#define _mitrax__raw_matrix__hpp_INCLUDED_

#include "matrix.hpp"


namespace mitrax{



	template < typename T, std::size_t Cols, std::size_t Rows >
	class raw_matrix_impl;

	template < typename T, std::size_t Cols, std::size_t Rows >
	using raw_matrix = matrix< raw_matrix_impl< T, Cols, Rows >, Cols, Rows >;

	template < typename T, std::size_t N >
	using raw_square_matrix = matrix< raw_matrix_impl< T, N, N >, N, N >;

	template < typename T, std::size_t Cols >
	using raw_col_vector = matrix< raw_matrix_impl< T, Cols, 1 >, Cols, 1 >;

	template < typename T, std::size_t Rows >
	using raw_row_vector = matrix< raw_matrix_impl< T, 1, Rows >, 1, Rows >;


	namespace detail{


		template <
			typename T,
			std::size_t Cols,
			std::size_t Rows,
			std::size_t ... I
		>
		constexpr auto to_array(
			T(&&values)[Rows][Cols],
			std::index_sequence< I ... >
		){
			return std::array< T, Cols * Rows >{{
				std::move(values[I / Cols][I % Cols]) ...
			}};
		}

		template <
			typename T,
			std::size_t Cols,
			std::size_t Rows,
			std::size_t ... I
		>
		constexpr auto to_array(
			T const(&values)[Rows][Cols],
			std::index_sequence< I ... >
		){
			return std::array< T, Cols * Rows >{{
				values[I / Cols][I % Cols] ...
			}};
		}


	}



	template < typename T, std::size_t Cols, std::size_t Rows >
	class raw_matrix_impl{
	public:
		/// \brief Type of the data that administrates the matrix
		using value_type = T;

		/// \brief Unsigned integral type (std::size_t)
		using size_type = std::size_t;

		/// \brief Signed integer type (std::ptrdiff_t)
		using difference_type = std::ptrdiff_t;

		/// \brief Type of points in the matrix
		using point_type = point< std::size_t >;

		/// \brief Type of matrix dimensions (cols and rows)
		using dimension_type = size< std::size_t >;

		/// \brief Type of a iterator for data
		using iterator = typename
			std::array< value_type, Cols * Rows >::iterator;

		/// \brief Type of a iterator for const data
		using const_iterator = typename
			std::array< value_type, Cols * Rows >::const_iterator;

		/// \brief Type of a reverse iterator for data
		using reverse_iterator = typename
			std::array< value_type, Cols * Rows >::reverse_iterator;

		/// \brief Type of a reverse iterator for const data
		using const_reverse_iterator = typename
			std::array< value_type, Cols * Rows >::const_reverse_iterator;

		/// \brief Type of a reference to data
		using reference = value_type&;

		/// \brief Type of a reference to const data
		using const_reference = value_type const&;

		/// \brief Type of a pointer to data
		using pointer = value_type*;

		/// \brief Type of a pointer to const data
		using const_pointer = value_type const*;



		constexpr raw_matrix_impl():
			values_{{0}} {}

		constexpr raw_matrix_impl(raw_matrix_impl&&) = default;

		constexpr raw_matrix_impl(raw_matrix_impl const&) = default;



		constexpr value_type& operator()(
			std::size_t x, std::size_t y
		){
			return values_[y * Cols + x];
		}

		constexpr value_type const& operator()(
			std::size_t x, std::size_t y
		)const{
			return values_[y * Cols + x];
		}



		static constexpr std::size_t width(){
			return Cols;
		}

		static constexpr std::size_t height(){
			return Rows;
		}



	private:
		std::array< value_type, Cols * Rows > values_;



		constexpr raw_matrix_impl(value_type(&&values)[Rows][Cols]):
			values_(detail::to_array(
				std::move(values),
				std::make_index_sequence< Cols * Rows >()
			)){}

		constexpr raw_matrix_impl(value_type const(&values)[Rows][Cols]):
			values_(detail::to_array(
				values,
				std::make_index_sequence< Cols * Rows >()
			)){}

		template < std::size_t N >
		constexpr raw_matrix_impl(value_type(&&values)[N]):
			values_(to_array(std::move(values))){}

		template < std::size_t N >
		constexpr raw_matrix_impl(value_type const(&values)[N]):
			values_(to_array(values)){}



		template < typename U, std::size_t C, std::size_t R >
		friend constexpr raw_matrix< U, C, R >
		to_matrix(U(&&values)[R][C]);

		template < typename U, std::size_t C, std::size_t R >
		friend constexpr raw_matrix< U, C, R >
		to_matrix(U const(&values)[R][C]);


		template < typename U, std::size_t N >
		friend constexpr raw_col_vector< U, N >
		to_col_vector(U(&&values)[N]);

		template < typename U, std::size_t N >
		friend constexpr raw_col_vector< U, N >
		to_col_vector(U const(&values)[N]);


		template < typename U, std::size_t N >
		friend constexpr raw_row_vector< U, N >
		to_row_vector(U(&&values)[N]);

		template < typename U, std::size_t N >
		friend constexpr raw_row_vector< U, N >
		to_row_vector(U const(&values)[N]);
	};



	template < typename T, std::size_t C, std::size_t R >
	constexpr raw_matrix< T, C, R > to_matrix(T(&&values)[R][C]){
		return raw_matrix_impl< T, C, R >(std::move(values));
	}

	template < typename T, std::size_t C, std::size_t R >
	constexpr raw_matrix< T, C, R > to_matrix(T const(&values)[R][C]){
		return raw_matrix_impl< T, C, R >(values);
	}


	template < typename T, std::size_t N >
	constexpr raw_matrix< T, N, N > to_square_matrix(T(&&values)[N][N]){
		return to_matrix< T, N, N >(std::move(values));
	}

	template < typename T, std::size_t N >
	constexpr raw_matrix< T, N, N > to_square_matrix(T const(&values)[N][N]){
		return to_matrix< T, N, N >(values);
	}


	template < typename T, std::size_t N >
	constexpr raw_col_vector< T, N > to_col_vector(T(&&values)[N]){
		return raw_matrix_impl< T, N, 1 >(std::move(values));
	}

	template < typename T, std::size_t N >
	constexpr raw_col_vector< T, N > to_col_vector(T const(&values)[N]){
		return raw_matrix_impl< T, N, 1 >(values);
	}


	template < typename T, std::size_t N >
	constexpr raw_row_vector< T, N > to_row_vector(T(&&values)[N]){
		return raw_matrix_impl< T, 1, N >(std::move(values));
	}

	template < typename T, std::size_t N >
	constexpr raw_row_vector< T, N > to_row_vector(T const(&values)[N]){
		return raw_matrix_impl< T, 1, N >(values);
	}



}

#endif
