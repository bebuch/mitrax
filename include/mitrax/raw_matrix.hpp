//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__raw_matrix__hpp_INCLUDED_
#define _mitrax__raw_matrix__hpp_INCLUDED_

#include "matrix_interface.hpp"
#include "to_array.hpp"
#include "array_d.hpp"

#include <iterator>


namespace mitrax{


	template < typename T, size_t C, size_t R >
	class raw_matrix: matrix< raw_matrix< T, C, R > >{
	public:
		/// \brief Type of the data that administrates the matrix
		using value_type = T;

		/// \brief Type of matrix dimensions (cols and rows)
		using dimension_type = dims_t< C, R >;

		/// \brief Type of a iterator for data
		using iterator = value_type*;

		/// \brief Type of a iterator for const data
		using const_iterator = value_type const*;

		/// \brief Type of a reverse iterator for data
		using reverse_iterator = std::reverse_iterator< iterator >;

		/// \brief Type of a reverse iterator for const data
		using const_reverse_iterator = std::reverse_iterator< const_iterator >;


		constexpr raw_matrix():
			values_(detail::init_array< C * R >(value_type())) {}

		constexpr raw_matrix(raw_matrix&&) = default;

		constexpr raw_matrix(raw_matrix const&) = default;

		constexpr raw_matrix(
			col_t< true, C >, row_t< true, R >,
			detail::array_s< value_type, C * R >&& values
		):
			values_(std::move(values))
			{}


		constexpr raw_matrix& operator=(raw_matrix&&) = default;

		constexpr raw_matrix& operator=(raw_matrix const&) = default;


		constexpr value_type& operator()(size_t x, size_t y){
			return values_[y * cols() + x];
		}

		constexpr value_type const& operator()(size_t x, size_t y)const{
			return values_[y * cols() + x];
		}


		constexpr col_t< C != 0, C > cols()const noexcept{
			return col_t< C != 0, C >();
		}

		constexpr row_t< R != 0, R > rows()const noexcept{
			return row_t< R != 0, R >();
		}


		constexpr iterator begin(){
			return values_.data();
		}

		constexpr const_iterator begin()const{
			return values_.data();
		}

		constexpr iterator end(){
			return values_.data() + C * R;
		}

		constexpr const_iterator end()const{
			return values_.data() + C * R;
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


		constexpr value_type* data(){
			return values_.data();
		}

		constexpr value_type const* data()const{
			return values_.data();
		}


	private:
		detail::array_s< value_type, C * R > values_;
	};


	template < typename T, size_t C, size_t R >
	class raw_matrix_base: matrix< raw_matrix< T, C, R > >{
	public:
		/// \brief Type of the data that administrates the matrix
		using value_type = T;

		/// \brief Type of a iterator for data
		using iterator = value_type*;

		/// \brief Type of a iterator for const data
		using const_iterator = value_type const*;

		/// \brief Type of a reverse iterator for data
		using reverse_iterator = std::reverse_iterator< iterator >;

		/// \brief Type of a reverse iterator for const data
		using const_reverse_iterator = std::reverse_iterator< const_iterator >;


		raw_matrix_base() = default;

		raw_matrix_base(raw_matrix_base&&) = default;

		raw_matrix_base(raw_matrix_base const&) = default;

		raw_matrix_base(
			col_t< C != 0, C > c, row_t< R != 0, R > r,
			detail::array_d< value_type >&& values
		):
			values_(std::move(values)),
			cols_(c),
			rows_(r)
			{}


		raw_matrix_base& operator=(raw_matrix_base&&) = default;

		raw_matrix_base& operator=(raw_matrix_base const&) = default;


		value_type& operator()(size_t x, size_t y){
			return values_[y * cols() + x];
		}

		value_type const& operator()(size_t x, size_t y)const{
			return values_[y * cols() + x];
		}


		constexpr col_t< C != 0, C > cols()const noexcept{
			return cols_;
		}

		constexpr row_t< R != 0, R > rows()const noexcept{
			return rows_;
		}


		iterator begin(){
			return values_.data();
		}

		const_iterator begin()const{
			return values_.data();
		}

		iterator end(){
			return values_.data() + values_.size();
		}

		const_iterator end()const{
			return values_.data() + values_.size();
		}

		reverse_iterator rbegin(){
			return std::make_reverse_iterator(end());
		}

		const_reverse_iterator rbegin()const{
			return std::make_reverse_iterator(end());
		}

		reverse_iterator rend(){
			return std::make_reverse_iterator(begin());
		}

		const_reverse_iterator rend()const{
			return std::make_reverse_iterator(begin());
		}


		value_type* data(){
			return values_.data();
		}

		value_type const* data()const{
			return values_.data();
		}


	protected:
		detail::array_d< value_type > values_;
		col_t< C != 0, C > cols_;
		row_t< R != 0, R > rows_;
	};


	template < typename T, size_t R >
	class raw_matrix< T, 0, R >:
		public raw_matrix_base< T, 0, R >{
	public:
		using raw_matrix_base< T, 0, R >::raw_matrix_base;
	};


	template < typename T, size_t C >
	class raw_matrix< T, C, 0 >:
		public raw_matrix_base< T, C, 0 >{
	public:
		using raw_matrix_base< T, C, 0 >::raw_matrix_base;
	};


	template < typename T >
	class raw_matrix< T, 0, 0 >:
		public raw_matrix_base< T, 0, 0 >{
	public:
		using raw_matrix_base< T, 0, 0 >::raw_matrix_base;
	};


}


#endif
