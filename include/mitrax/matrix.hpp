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

#include "point.hpp"
#include "dimension.hpp"

#include <utility>
#include <cassert>


namespace mitrax{


	template < typename M >
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


		constexpr value_type& operator()(
			std::size_t x, std::size_t y
		){
			assert(x < m_.cols());
			assert(y < m_.rows());
			return m_(x, y);
		}

		constexpr value_type const& operator()(
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


	protected:
		M m_;
	};


	template < typename M, std::size_t Cols, std::size_t Rows >
	class matrix: public matrix_types< M >{
	public:
		using typename matrix_types< M >::value_type;

		using matrix_types< M >::matrix_types;


		static constexpr std::size_t cols(){
			return M::cols();
		}

		static constexpr std::size_t rows(){
			return M::rows();
		}


	private:
		using matrix_types< M >::m_;
	};


	template < typename M, std::size_t Rows >
	class matrix< M, 1, Rows >: public matrix_types< M >{
	public:
		using typename matrix_types< M >::value_type;

		using matrix_types< M >::matrix_types;


		static constexpr std::size_t cols(){
			return M::cols();
		}

		static constexpr std::size_t rows(){
			return M::rows();
		}


		constexpr value_type& operator[](std::size_t i){
			return m_(0, i);
		}

		constexpr value_type const& operator[](std::size_t i)const{
			return m_(0, i);
		}


	private:
		using matrix_types< M >::m_;
	};


	template < typename M, std::size_t Cols >
	class matrix< M, Cols, 1 >: public matrix_types< M >{
	public:
		using typename matrix_types< M >::value_type;

		using matrix_types< M >::matrix_types;


		static constexpr std::size_t cols(){
			return M::cols();
		}

		static constexpr std::size_t rows(){
			return M::rows();
		}


		constexpr value_type& operator[](std::size_t i){
			return m_(i, 0);
		}

		constexpr value_type const& operator[](std::size_t i)const{
			return m_(i, 0);
		}


	private:
		using matrix_types< M >::m_;
	};


	template < typename M >
	class matrix< M, 1, 1 >: public matrix_types< M >{
	public:
		using typename matrix_types< M >::value_type;

		using matrix_types< M >::matrix_types;


		static constexpr std::size_t cols(){
			return M::cols();
		}

		static constexpr std::size_t rows(){
			return M::rows();
		}


		constexpr value_type& operator[](std::size_t i){
			assert(i == 0); (void)i;
			return m_(0, 0);
		}

		constexpr value_type const& operator[](std::size_t i)const{
			assert(i == 0); (void)i;
			return m_(0, 0);
		}


		constexpr operator value_type()const{
			return m_(0, 0);
		}


	private:
		using matrix_types< M >::m_;
	};


	template < typename M, std::size_t Rows >
	class matrix< M, 0, Rows >: public matrix_types< M >{
	public:
		using typename matrix_types< M >::value_type;

		using matrix_types< M >::matrix_types;


		constexpr std::size_t cols(){
			return m_.cols();
		}

		static constexpr std::size_t rows(){
			return M::rows();
		}


	private:
		using matrix_types< M >::m_;
	};


	template < typename M, std::size_t Cols >
	class matrix< M, Cols, 0 >: public matrix_types< M >{
	public:
		using typename matrix_types< M >::value_type;

		using matrix_types< M >::matrix_types;


		constexpr std::size_t cols(){
			return m_.cols();
		}

		static constexpr std::size_t rows(){
			return M::rows();
		}


	private:
		using matrix_types< M >::m_;
	};


	template < typename M >
	class matrix< M, 0, 0 >: public matrix_types< M >{
	public:
		using typename matrix_types< M >::value_type;

		using matrix_types< M >::matrix_types;


		constexpr std::size_t cols(){
			return m_.cols();
		}

		constexpr std::size_t rows(){
			return m_.rows();
		}


	private:
		using matrix_types< M >::m_;
	};


	template < typename M >
	class matrix< M, 1, 0 >: public matrix_types< M >{
	public:
		using typename matrix_types< M >::value_type;

		using matrix_types< M >::matrix_types;


		static constexpr std::size_t cols(){
			return M::cols();
		}

		constexpr std::size_t rows(){
			return m_.rows();
		}


		constexpr value_type& operator[](std::size_t i){
			return m_(0, i);
		}

		constexpr value_type const& operator[](std::size_t i)const{
			return m_(0, i);
		}


	private:
		using matrix_types< M >::m_;
	};


	template < typename M >
	class matrix< M, 0, 1 >: public matrix_types< M >{
	public:
		using typename matrix_types< M >::value_type;

		using matrix_types< M >::matrix_types;


		constexpr std::size_t cols(){
			return m_.cols();
		}

		static constexpr std::size_t rows(){
			return M::rows();
		}


		constexpr value_type& operator[](std::size_t i){
			return m_(i, 0);
		}

		constexpr value_type const& operator[](std::size_t i)const{
			return m_(i, 0);
		}


	private:
		using matrix_types< M >::m_;
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
