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


	template < typename M, std::size_t Cols, std::size_t Rows >
	class matrix{
	public:
		/// \brief Type of the data that administrates the matrix
		using value_type = typename M::value_type;

		/// \brief Unsigned integral type (std::size_t)
		using size_type = typename M::size_type;

		/// \brief Signed integer type (std::ptrdiff_t)
		using difference_type = typename M::difference_type;

		/// \brief Type of points in the matrix
		using point_type = typename M::point_type;

		/// \brief Type of matrix dimensions (cols and rows)
		using dimension_type = typename M::dimension_type;

		/// \brief Type of a iterator for data
		using iterator = typename M::iterator;

		/// \brief Type of a iterator for const data
		using const_iterator = typename M::const_iterator;

		/// \brief Type of a reverse iterator for data
		using reverse_iterator = typename M::reverse_iterator;

		/// \brief Type of a reverse iterator for const data
		using const_reverse_iterator = typename M::const_reverse_iterator;

		/// \brief Type of a reference to data
		using reference = typename M::reference;

		/// \brief Type of a reference to const data
		using const_reference = typename M::const_reference;

		/// \brief Type of a pointer to data
		using pointer = typename M::pointer;

		/// \brief Type of a pointer to const data
		using const_pointer = typename M::const_pointer;



		constexpr matrix() = default;

		constexpr matrix(M&& m): m_(std::move(m)) {}

		constexpr matrix(M const& m): m_(m) {}

		constexpr matrix(matrix&&) = default;

		constexpr matrix(matrix const&) = default;



		constexpr value_type& operator()(
			std::size_t x, std::size_t y
		){
			return m_(x, y);
		}

		constexpr value_type const& operator()(
			std::size_t x, std::size_t y
		)const{
			return m_(x, y);
		}



		static constexpr std::size_t cols(){
			return Cols;
		}

		static constexpr std::size_t rows(){
			return Rows;
		}



	private:
		M m_;
	};


	template < typename M, std::size_t N >
	using square_matrix = matrix< M, N, N >;

	template < typename M, std::size_t Cols >
	using col_vector = matrix< M, Cols, 1 >;

	template < typename M, std::size_t Rows >
	using row_vector = matrix< M, 1, Rows >;



}

#endif
