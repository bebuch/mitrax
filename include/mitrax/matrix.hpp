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

#include "integer.hpp"
#include "point.hpp"
#include "dimension.hpp"

#include <utility>
#include <cassert>


namespace mitrax{


	template < typename M, std::size_t Cols, std::size_t Rows >
	class matrix;

	template < typename T, std::size_t Cols, std::size_t Rows >
	class raw_matrix_impl;

	template < typename T, std::size_t Cols, std::size_t Rows >
	using raw_matrix = matrix< raw_matrix_impl< T, Cols, Rows >, Cols, Rows >;


	namespace detail{


		template <
			typename T,
			std::size_t C1,
			std::size_t R1,
			typename M,
			std::size_t C2,
			std::size_t R2
		> constexpr raw_matrix< T, C1, R1 >
		convert(matrix< M, C2, R2 >&& m);

		template <
			typename T,
			std::size_t C1,
			std::size_t R1,
			typename M,
			std::size_t C2,
			std::size_t R2
		> constexpr raw_matrix< T, C1, R1 >
		convert(matrix< M, C2, R2 > const& m);


		template <
			typename T,
			std::size_t C1,
			std::size_t R1,
			typename M,
			std::size_t C2,
			std::size_t R2
		>
		constexpr raw_matrix< T, C1, R1 > sub_matrix(
			matrix< M, C2, R2 > const& m,
			std::size_t x,
			std::size_t y,
			size_ct< C1 > cols,
			size_ct< R1 > rows
		);

		template <
			typename T,
			std::size_t R1,
			typename M,
			std::size_t C2,
			std::size_t R2
		>
		raw_matrix< T, 0, R1 > sub_matrix(
			matrix< M, C2, R2 > const& m,
			std::size_t x,
			std::size_t y,
			std::size_t cols,
			size_ct< R1 > rows
		);

		template <
			typename T,
			std::size_t C1,
			typename M,
			std::size_t C2,
			std::size_t R2
		>
		raw_matrix< T, C1, 0 > sub_matrix(
			matrix< M, C2, R2 > const& m,
			std::size_t x,
			std::size_t y,
			size_ct< C1 > cols,
			std::size_t rows
		);

		template <
			typename T,
			typename M,
			std::size_t C2,
			std::size_t R2
		>
		raw_matrix< T, 0, 0 > sub_matrix(
			matrix< M, C2, R2 > const& m,
			std::size_t x,
			std::size_t y,
			std::size_t cols,
			std::size_t rows
		);


	}



	template < typename M, std::size_t Cols, std::size_t Rows >
	class matrix_types{
	public:
		/// \brief Type of the data that administrates the matrix
		using value_type = typename M::value_type;

		/// \brief Unsigned integral type (std::size_t)
		using size_type = std::size_t;

		/// \brief Signed integer type (std::ptrdiff_t)
		using difference_type = std::ptrdiff_t;

		/// \brief Type of points in the matrix
		using point_type = point< std::size_t >;

		/// \brief Type of matrix dimensions (cols and rows)
		using dimension_type = dimension< std::size_t >;

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


		constexpr matrix_types() = default;

		constexpr matrix_types(M&& m): m_(std::move(m)) {}

		constexpr matrix_types(M const& m): m_(m) {}

		constexpr matrix_types(matrix_types&&) = default;

		constexpr matrix_types(matrix_types const&) = default;


		constexpr decltype(auto) operator()(
			std::size_t x, std::size_t y
		){
			assert(x < m_.cols());
			assert(y < m_.rows());
			return m_(x, y);
		}

		constexpr decltype(auto) operator()(
			std::size_t x, std::size_t y
		)const{
			assert(x < m_.cols());
			assert(y < m_.rows());
			return m_(x, y);
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


		template < typename T, std::size_t C, std::size_t R >
		constexpr raw_matrix< T, C, R > as_raw_matrix()&&{
			return detail::convert< T, C, R >(
				static_cast< matrix< M, Cols, Rows >&& >(*this)
			);
		}

		template < typename T, std::size_t C, std::size_t R >
		constexpr raw_matrix< T, C, R > as_raw_matrix()const&{
			return detail::convert< T, C, R >(
				static_cast< matrix< M, Cols, Rows > const& >(*this)
			);
		}


		template < std::size_t C, std::size_t R >
		constexpr raw_matrix< value_type, C, R > sub_matrix(
			std::size_t x,
			std::size_t y,
			size_ct< C > cols,
			size_ct< R > rows
		)const{
			return detail::sub_matrix< value_type >(
				static_cast< matrix< M, Cols, Rows > const& >(*this),
				x, y, cols, rows
			);
		}

		template < std::size_t R >
		raw_matrix< value_type, 0, R > sub_matrix(
			std::size_t x,
			std::size_t y,
			std::size_t cols,
			size_ct< R > rows
		)const{
			return detail::sub_matrix< value_type >(
				static_cast< matrix< M, Cols, Rows > const& >(*this),
				x, y, cols, rows
			);
		}

		template < std::size_t C >
		raw_matrix< value_type, C, 0 > sub_matrix(
			std::size_t x,
			std::size_t y,
			size_ct< C > cols,
			std::size_t rows
		)const{
			return detail::sub_matrix< value_type >(
				static_cast< matrix< M, Cols, Rows > const& >(*this),
				x, y, cols, rows
			);
		}

		raw_matrix< value_type, 0, 0 > sub_matrix(
			std::size_t x,
			std::size_t y,
			std::size_t cols,
			std::size_t rows
		)const{
			return detail::sub_matrix< value_type >(
				static_cast< matrix< M, Cols, Rows > const& >(*this),
				x, y, cols, rows
			);
		}


	protected:
		M m_;
	};


	template < typename M, std::size_t Cols, std::size_t Rows >
	class matrix: public matrix_types< M, Cols, Rows >{
	public:
		using typename matrix_types< M, Cols, Rows >::value_type;

		using matrix_types< M, Cols, Rows >::matrix_types;


		static constexpr std::size_t cols(){
			return M::cols();
		}

		static constexpr std::size_t rows(){
			return M::rows();
		}


	private:
		using matrix_types< M, Cols, Rows >::m_;
	};


	template < typename M, std::size_t Rows >
	class matrix< M, 1, Rows >: public matrix_types< M, 1, Rows >{
	public:
		using typename matrix_types< M, 1, Rows >::value_type;

		using matrix_types< M, 1, Rows >::matrix_types;


		static constexpr std::size_t cols(){
			return M::cols();
		}

		static constexpr std::size_t rows(){
			return M::rows();
		}


		constexpr decltype(auto) operator[](std::size_t i){
			return m_(0, i);
		}

		constexpr decltype(auto) operator[](std::size_t i)const{
			return m_(0, i);
		}


	private:
		using matrix_types< M, 1, Rows >::m_;
	};


	template < typename M, std::size_t Cols >
	class matrix< M, Cols, 1 >: public matrix_types< M, Cols, 1 >{
	public:
		using typename matrix_types< M, Cols, 1 >::value_type;

		using matrix_types< M, Cols, 1 >::matrix_types;


		static constexpr std::size_t cols(){
			return M::cols();
		}

		static constexpr std::size_t rows(){
			return M::rows();
		}


		constexpr decltype(auto) operator[](std::size_t i){
			return m_(i, 0);
		}

		constexpr decltype(auto) operator[](std::size_t i)const{
			return m_(i, 0);
		}


	private:
		using matrix_types< M, Cols, 1 >::m_;
	};


	template < typename M >
	class matrix< M, 1, 1 >: public matrix_types< M, 1, 1 >{
	public:
		using typename matrix_types< M, 1, 1 >::value_type;

		using matrix_types< M, 1, 1 >::matrix_types;


		static constexpr std::size_t cols(){
			return M::cols();
		}

		static constexpr std::size_t rows(){
			return M::rows();
		}


		constexpr decltype(auto) operator[](std::size_t i){
			assert(i == 0); (void)i;
			return m_(0, 0);
		}

		constexpr decltype(auto) operator[](std::size_t i)const{
			assert(i == 0); (void)i;
			return m_(0, 0);
		}


		constexpr operator value_type()const{
			return m_(0, 0);
		}


	private:
		using matrix_types< M, 1, 1 >::m_;
	};


	template < typename M, std::size_t Rows >
	class matrix< M, 0, Rows >: public matrix_types< M, 0, Rows >{
	public:
		using typename matrix_types< M, 0, Rows >::value_type;

		using matrix_types< M, 0, Rows >::matrix_types;


		constexpr std::size_t cols()const{
			return m_.cols();
		}

		static constexpr std::size_t rows(){
			return M::rows();
		}


	private:
		using matrix_types< M, 0, Rows >::m_;
	};


	template < typename M, std::size_t Cols >
	class matrix< M, Cols, 0 >: public matrix_types< M, Cols, 0 >{
	public:
		using typename matrix_types< M, Cols, 0 >::value_type;

		using matrix_types< M, Cols, 0 >::matrix_types;


		static constexpr std::size_t cols(){
			return M::cols();
		}

		constexpr std::size_t rows()const{
			return m_.rows();
		}


	private:
		using matrix_types< M, Cols, 0 >::m_;
	};


	template < typename M >
	class matrix< M, 0, 0 >: public matrix_types< M, 0, 0 >{
	public:
		using typename matrix_types< M, 0, 0 >::value_type;

		using matrix_types< M, 0, 0 >::matrix_types;


		constexpr std::size_t cols()const{
			return m_.cols();
		}

		constexpr std::size_t rows()const{
			return m_.rows();
		}


	private:
		using matrix_types< M, 0, 0 >::m_;
	};


	template < typename M >
	class matrix< M, 1, 0 >: public matrix_types< M, 1, 0 >{
	public:
		using typename matrix_types< M, 1, 0 >::value_type;

		using matrix_types< M, 1, 0 >::matrix_types;


		static constexpr std::size_t cols(){
			return M::cols();
		}

		constexpr std::size_t rows()const{
			return m_.rows();
		}


		constexpr decltype(auto) operator[](std::size_t i){
			return m_(0, i);
		}

		constexpr decltype(auto) operator[](std::size_t i)const{
			return m_(0, i);
		}


	private:
		using matrix_types< M, 1, 0 >::m_;
	};


	template < typename M >
	class matrix< M, 0, 1 >: public matrix_types< M, 0, 1 >{
	public:
		using typename matrix_types< M, 0, 1 >::value_type;

		using matrix_types< M, 0, 1 >::matrix_types;


		constexpr std::size_t cols()const{
			return m_.cols();
		}

		static constexpr std::size_t rows(){
			return M::rows();
		}


		constexpr decltype(auto) operator[](std::size_t i){
			return m_(i, 0);
		}

		constexpr decltype(auto) operator[](std::size_t i)const{
			return m_(i, 0);
		}


	private:
		using matrix_types< M, 0, 1 >::m_;
	};


	template < typename M, std::size_t N >
	using square_matrix = matrix< M, N, N >;

	template < typename M, std::size_t Cols >
	using col_vector = matrix< M, Cols, 1 >;

	template < typename M, std::size_t Rows >
	using row_vector = matrix< M, 1, Rows >;

	template < typename M >
	using bitmap = matrix< M, 0, 0 >;



}

#endif
