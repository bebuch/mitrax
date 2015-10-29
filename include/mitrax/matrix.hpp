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


	template < typename ValueType, std::size_t Cols, std::size_t Rows >
	class matrix;

	template < typename T, std::size_t N >
	using square_matrix = matrix< T, N, N >;

	template < typename T, std::size_t Cols >
	using col_vector = matrix< T, Cols, 1 >;

	template < typename T, std::size_t Rows >
	using row_vector = matrix< T, 1, Rows >;



	template < typename ValueType, std::size_t Cols, std::size_t Rows >
	constexpr matrix< ValueType, Cols, Rows >
	to_matrix(ValueType(&&values)[Rows][Cols]);

	template < typename ValueType, std::size_t Cols, std::size_t Rows >
	constexpr matrix< ValueType, Cols, Rows >
	to_matrix(ValueType const(&values)[Rows][Cols]);


	template < typename ValueType, std::size_t Cols >
	constexpr col_vector< ValueType, Cols >
	to_col_vector(ValueType(&&values)[Cols]);

	template < typename ValueType, std::size_t Cols >
	constexpr col_vector< ValueType, Cols >
	to_col_vector(ValueType const(&values)[Cols]);


	template < typename ValueType, std::size_t Rows >
	constexpr row_vector< ValueType, Rows >
	to_row_vector(ValueType(&&values)[Rows]);

	template < typename ValueType, std::size_t Rows >
	constexpr row_vector< ValueType, Rows >
	to_row_vector(ValueType const(&values)[Rows]);



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



	template < typename ValueType, std::size_t Cols, std::size_t Rows >
	class matrix{
	public:
		/// \brief Type of the data that administrates the matrix
		using value_type = ValueType;

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


		template < std::size_t N >
		constexpr matrix(value_type(&&values)[N]):
			values_(to_array(std::move(values))){}

		template < std::size_t N >
		constexpr matrix(value_type const(&values)[N]):
			values_(to_array(values)){}


		template < typename T, std::size_t N >
		friend constexpr col_vector< T, N >
		to_col_vector(T const(&values)[N]);

		template < typename T, std::size_t N >
		friend constexpr col_vector< T, N >
		to_col_vector(T(&&values)[N]);


		template < typename T, std::size_t N >
		friend constexpr row_vector< T, N >
		to_row_vector(T const(&values)[N]);

		template < typename T, std::size_t N >
		friend constexpr row_vector< T, N >
		to_row_vector(T(&&values)[N]);
	};



	template < typename ValueType, std::size_t Cols, std::size_t Rows >
	constexpr matrix< ValueType, Cols, Rows >
	to_matrix(ValueType(&&values)[Rows][Cols]){
		return matrix< ValueType, Cols, Rows >(std::move(values));
	}

	template < typename ValueType, std::size_t Cols, std::size_t Rows >
	constexpr matrix< ValueType, Cols, Rows >
	to_matrix(ValueType const(&values)[Rows][Cols]){
		return matrix< ValueType, Cols, Rows >(values);
	}


	template < typename ValueType, std::size_t Cols >
	constexpr col_vector< ValueType, Cols >
	to_col_vector(ValueType(&&values)[Cols]){
		return col_vector< ValueType, Cols >(std::move(values));
	}

	template < typename ValueType, std::size_t Cols >
	constexpr col_vector< ValueType, Cols >
	to_col_vector(ValueType const(&values)[Cols]){
		return col_vector< ValueType, Cols >(values);
	}


	template < typename ValueType, std::size_t Rows >
	constexpr row_vector< ValueType, Rows >
	to_row_vector(ValueType(&&values)[Rows]){
		return row_vector< ValueType, Rows >(std::move(values));
	}

	template < typename ValueType, std::size_t Rows >
	constexpr row_vector< ValueType, Rows >
	to_row_vector(ValueType const(&values)[Rows]){
		return row_vector< ValueType, Rows >(values);
	}



}

#endif
