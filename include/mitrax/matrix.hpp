//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__matrix__hpp_INCLUDED_
#define _mitrax__matrix__hpp_INCLUDED_

#include "to_array.hpp"
#include "point.hpp"
#include "size.hpp"


namespace mitrax{


	template < typename T, std::size_t Cols, std::size_t Rows >
	class matrix;

	template < typename T, std::size_t N >
	using square_matrix = matrix< T, N, N >;

	template < typename T, std::size_t Cols >
	using col_vector = matrix< T, Cols, 1 >;

	template < typename T, std::size_t Rows >
	using row_vector = matrix< T, 1, Rows >;



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
	class matrix{
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



		constexpr matrix():
			values_{{0}} {}

		constexpr matrix(matrix&&) = default;

		constexpr matrix(matrix const&) = default;



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



		constexpr matrix(value_type(&&values)[Rows][Cols]):
			values_(detail::to_array(
				std::move(values),
				std::make_index_sequence< Cols * Rows >()
			)){}

		constexpr matrix(value_type const(&values)[Rows][Cols]):
			values_(detail::to_array(
				values,
				std::make_index_sequence< Cols * Rows >()
			)){}

		template < std::size_t N >
		constexpr matrix(value_type(&&values)[N]):
			values_(to_array(std::move(values))){}

		template < std::size_t N >
		constexpr matrix(value_type const(&values)[N]):
			values_(to_array(values)){}



		template < typename U, std::size_t C, std::size_t R >
		friend constexpr matrix< U, C, R > to_matrix(U(&&values)[R][C]);

		template < typename U, std::size_t C, std::size_t R >
		friend constexpr matrix< U, C, R > to_matrix(U const(&values)[R][C]);


		template < typename U, std::size_t N >
		friend constexpr col_vector< U, N >
		to_col_vector(U const(&values)[N]);

		template < typename U, std::size_t N >
		friend constexpr col_vector< U, N >
		to_col_vector(U(&&values)[N]);


		template < typename U, std::size_t N >
		friend constexpr row_vector< U, N >
		to_row_vector(U const(&values)[N]);

		template < typename U, std::size_t N >
		friend constexpr row_vector< U, N >
		to_row_vector(U(&&values)[N]);
	};



	template < typename T, std::size_t Cols, std::size_t Rows >
	constexpr matrix< T, Cols, Rows > to_matrix(T(&&values)[Rows][Cols]){
		return matrix< T, Cols, Rows >(std::move(values));
	}

	template < typename T, std::size_t Cols, std::size_t Rows >
	constexpr matrix< T, Cols, Rows > to_matrix(T const(&values)[Rows][Cols]){
		return matrix< T, Cols, Rows >(values);
	}


	template < typename T, std::size_t N >
	constexpr matrix< T, N, N >
	to_square_matrix(T(&&values)[N][N]){
		return to_matrix< T, N, N >(std::move(values));
	}

	template < typename T, std::size_t N >
	constexpr matrix< T, N, N >
	to_square_matrix(T const(&values)[N][N]){
		return to_matrix< T, N, N >(values);
	}


	template < typename T, std::size_t N >
	constexpr col_vector< T, N >
	to_col_vector(T(&&values)[N]){
		return col_vector< T, N >(std::move(values));
	}

	template < typename T, std::size_t N >
	constexpr col_vector< T, N >
	to_col_vector(T const(&values)[N]){
		return col_vector< T, N >(values);
	}


	template < typename T, std::size_t N >
	constexpr row_vector< T, N >
	to_row_vector(T(&&values)[N]){
		return row_vector< T, N >(std::move(values));
	}

	template < typename T, std::size_t N >
	constexpr row_vector< T, N >
	to_row_vector(T const(&values)[N]){
		return row_vector< T, N >(values);
	}



}

#endif
