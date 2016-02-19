//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__matrix_interface__hpp_INCLUDED_
#define _mitrax__matrix_interface__hpp_INCLUDED_

#include "point.hpp"
#include "to_array.hpp"
#include "to_vector.hpp"
#include "convert.hpp"
#include "sub_matrix.hpp"

#include <utility>
#include <cassert>
#include <algorithm>


namespace mitrax{


	template < typename M, size_t Cols, size_t Rows >
	class matrix_base{
	public:
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


		constexpr matrix_base() = default;

		constexpr matrix_base(M&& m): m_(std::move(m)) {}

		constexpr matrix_base(matrix_base&&) = default;

		constexpr matrix_base(matrix_base const&) = default;


		constexpr matrix_base& operator=(matrix_base&&) = default;

		constexpr matrix_base& operator=(matrix_base const&) = default;


		constexpr col_t< Cols != 0, Cols > cols()const noexcept{
			return m_.cols();
		}

		constexpr row_t< Rows != 0, Rows > rows()const noexcept{
			return m_.rows();
		}

		constexpr dims_t< Cols, Rows > dims()const noexcept{
			col_t< Cols != 0, Cols > c = cols();
			row_t< Rows != 0, Rows > r = rows();
			dims_t< Cols, Rows > d = mitrax::dims(c, r);
			return d;
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


		template < typename V >
		constexpr raw_matrix< V, Cols, Rows > convert_by_move(){
			return raw_matrix_impl< V, Cols, Rows >(
				cols(), rows(), mitrax::convert< V >(std::move(m_.data()))
			);
		}

		template < typename V >
		constexpr raw_matrix< V, Cols, Rows > convert(){
			return raw_matrix_impl< V, Cols, Rows >(
				cols(), rows(), mitrax::convert< V >(m_.data())
			);
		}

		template < typename V >
		constexpr raw_matrix< V, Cols, Rows > convert()const{
			return raw_matrix_impl< V, Cols, Rows >(
				cols(), rows(), mitrax::convert< V >(m_.data())
			);
		}


		template < bool Cct, size_t C, bool Rct, size_t R >
		constexpr raw_matrix< value_type, dim(Cct, C), dim(Rct, R) >
		convert_by_move(col_t< Cct, C > c, row_t< Rct, R > r){
			return convert_by_move< value_type >(c, r);
		}

		template < size_t C, size_t R >
		constexpr raw_matrix< value_type, C, R >
		convert_by_move(dims_t< C, R > d){
			return convert_by_move< value_type >(d);
		}

		template < bool Cct, size_t C, bool Rct, size_t R >
		constexpr raw_matrix< value_type, dim(Cct, C), dim(Rct, R) >
		convert(col_t< Cct, C > c, row_t< Rct, R > r){
			return convert< value_type >(c, r);
		}

		template < size_t C, size_t R >
		constexpr raw_matrix< value_type, C, R >
		convert(dims_t< C, R > d){
			return convert< value_type >(d);
		}

		template < bool Cct, size_t C, bool Rct, size_t R >
		constexpr raw_matrix< value_type, dim(Cct, C), dim(Rct, R) >
		convert(col_t< Cct, C > c, row_t< Rct, R > r)const{
			return convert< value_type >(c, r);
		}

		template < size_t C, size_t R >
		constexpr raw_matrix< value_type, C, R >
		convert(dims_t< C, R > d)const{
			return convert< value_type >(d);
		}


		template < typename V, bool Cct, size_t C, bool Rct, size_t R >
		constexpr raw_matrix< V, dim(Cct, C), dim(Rct, R) >
		convert_by_move(col_t< Cct, C > c, row_t< Rct, R > r){
			check_dims(c, r);
			return raw_matrix_impl< V, dim(Cct, C), dim(Rct, R) >(
				c, r, mitrax::convert<
					V,
					value_type,
					std::max(dim(Cct, C) * dim(Rct, R), Cols * Rows)
				>(
					bool_t< dim(Cct, C) * dim(Rct, R) != 0 >(),
					std::move(m_.data())
				)
			);
		}

		template < typename V, bool Cct, size_t C, bool Rct, size_t R >
		constexpr raw_matrix< V, dim(Cct, C), dim(Rct, R) >
		convert(col_t< Cct, C > c, row_t< Rct, R > r){
			check_dims(c, r);
			return raw_matrix_impl< V, dim(Cct, C), dim(Rct, R) >(
				c, r, mitrax::convert<
					V,
					value_type,
					std::max(dim(Cct, C) * dim(Rct, R), Cols * Rows)
				>(
					bool_t< dim(Cct, C) * dim(Rct, R) != 0 >(),
					m_.data()
				)
			);
		}

		template < typename V, bool Cct, size_t C, bool Rct, size_t R >
		constexpr raw_matrix< V, dim(Cct, C), dim(Rct, R) >
		convert(col_t< Cct, C > c, row_t< Rct, R > r)const{
			check_dims(c, r);
			return raw_matrix_impl< V, dim(Cct, C), dim(Rct, R) >(
				c, r, mitrax::convert<
					V,
					value_type,
					std::max(dim(Cct, C) * dim(Rct, R), Cols * Rows)
				>(
					bool_t< dim(Cct, C) * dim(Rct, R) != 0 >(),
					m_.data()
				)
			);
		}


		constexpr raw_matrix< value_type, Cols, Rows > as_raw_matrix_by_move(){
			return convert_by_move< value_type >();
		}

		constexpr raw_matrix< value_type, Cols, Rows > as_raw_matrix(){
			return convert< value_type >();
		}

		constexpr raw_matrix< value_type, Cols, Rows > as_raw_matrix()const{
			return convert< value_type >();
		}


		template < bool Cct, size_t C, bool Rct, size_t R >
		constexpr raw_matrix< value_type, dim(Cct, C), dim(Rct, R) >
		sub_matrix(
			size_t x, size_t y,
			col_t< Cct, C > c, row_t< Rct, R > r
		){
			return sub_matrix< value_type >(x, y, c, r);
		}

		template < size_t C, size_t R >
		constexpr raw_matrix< value_type, C, R >
		sub_matrix(size_t x, size_t y, dims_t< C, R > d){
			return sub_matrix< value_type >(x, y, d);
		}

		template < bool Cct, size_t C, bool Rct, size_t R >
		constexpr raw_matrix< value_type, dim(Cct, C), dim(Rct, R) >
		sub_matrix(
			size_t x, size_t y,
			col_t< Cct, C > c, row_t< Rct, R > r
		)const{
			return sub_matrix< value_type >(x, y, c, r);
		}

		template < size_t C, size_t R >
		constexpr raw_matrix< value_type, C, R >
		sub_matrix(size_t x, size_t y, dims_t< C, R > d)const{
			return sub_matrix< value_type >(x, y, d);
		}

		template < typename V, bool Cct, size_t C, bool Rct, size_t R >
		constexpr raw_matrix< V, dim(Cct, C), dim(Rct, R) >
		sub_matrix(
			size_t x, size_t y,
			col_t< Cct, C > c, row_t< Rct, R > r
		){
			return raw_matrix_impl< V, dim(Cct, C), dim(Rct, R) >(
				c, r,
				mitrax::sub_matrix< V >(
					x, y, c, r,
					static_cast< matrix< M, Cols, Rows >& >(*this)
				)
			);
		}

		template < typename V, size_t C, size_t R >
		constexpr raw_matrix< V, C, R >
		sub_matrix(size_t x, size_t y, dims_t< C, R > d){
			return sub_matrix< V >(x, y, d.cols().init(), d.rows().init());
		}

		template < typename V, bool Cct, size_t C, bool Rct, size_t R >
		constexpr raw_matrix< V, dim(Cct, C), dim(Rct, R) >
		sub_matrix(
			size_t x, size_t y,
			col_t< Cct, C > c, row_t< Rct, R > r
		)const{
			return raw_matrix_impl< V, dim(Cct, C), dim(Rct, R) >(
				c, r,
				mitrax::sub_matrix< V >(
					x, y, c, r,
					static_cast< matrix< M, Cols, Rows > const& >(*this)
				)
			);
		}

		template < typename V, size_t C, size_t R >
		constexpr raw_matrix< V, C, R >
		sub_matrix(size_t x, size_t y, dims_t< C, R > d)const{
			return sub_matrix< V >(x, y, d.cols().init(), d.rows().init());
		}


		constexpr M& impl(){
			return m_;
		}

		constexpr M const& impl()const{
			return m_;
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
	};


	template < typename M, size_t Cols, size_t Rows >
	class matrix: public matrix_base< M, Cols, Rows >{
	public:
		using value_type = value_type_t< matrix_base< M, Cols, Rows > >;

		using matrix_base< M, Cols, Rows >::matrix_base;


	private:
		using matrix_base< M, Cols, Rows >::m_;
	};


	template < typename M, size_t Rows >
	class matrix< M, 1, Rows >: public matrix_base< M, 1, Rows >{
	public:
		using value_type = value_type_t< matrix_base< M, 1, Rows > >;

		using matrix_base< M, 1, Rows >::matrix_base;


		constexpr decltype(auto) operator[](size_t i){
			return m_(0, i);
		}

		constexpr decltype(auto) operator[](size_t i)const{
			return m_(0, i);
		}


	private:
		using matrix_base< M, 1, Rows >::m_;
	};


	template < typename M, size_t Cols >
	class matrix< M, Cols, 1 >: public matrix_base< M, Cols, 1 >{
	public:
		using value_type = value_type_t< matrix_base< M, Cols, 1 > >;

		using matrix_base< M, Cols, 1 >::matrix_base;


		constexpr decltype(auto) operator[](size_t i){
			return m_(i, 0);
		}

		constexpr decltype(auto) operator[](size_t i)const{
			return m_(i, 0);
		}


	private:
		using matrix_base< M, Cols, 1 >::m_;
	};


	template < typename M >
	class matrix< M, 1, 1 >: public matrix_base< M, 1, 1 >{
	public:
		using value_type = value_type_t< matrix_base< M, 1, 1 > >;

		using matrix_base< M, 1, 1 >::matrix_base;


		constexpr decltype(auto) operator[](size_t i){
			assert(i == 0); (void)i;
			return m_(0, 0);
		}

		constexpr decltype(auto) operator[](size_t i)const{
			assert(i == 0); (void)i;
			return m_(0, 0);
		}


		constexpr operator value_type()const{
			return m_(0, 0);
		}


	private:
		using matrix_base< M, 1, 1 >::m_;
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
