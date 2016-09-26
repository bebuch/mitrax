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


namespace mitrax{ namespace maker{


	struct std_t{
		template < typename T, bool Cct, size_t C, bool Rct, size_t R >
		constexpr
		raw_matrix< std::remove_cv_t< T >, Cct ? C : 0, Rct ? R : 0 >
		by_value(col_t< Cct, C > c, row_t< Rct, R > r, T const& v)const;

		template < typename I, bool Cct, size_t C, bool Rct, size_t R >
		constexpr
		raw_matrix< iter_type_t< I >, Cct ? C : 0, Rct ? R : 0 >
		by_sequence(col_t< Cct, C > c, row_t< Rct, R > r, I i)const;
	};


	struct heap_t{
		template < typename T, bool Cct, size_t C, bool Rct, size_t R >
		raw_heap_matrix< std::remove_cv_t< T >, Cct ? C : 0, Rct ? R : 0 >
		by_value(col_t< Cct, C > c, row_t< Rct, R > r, T const& v)const;

		template < typename I, bool Cct, size_t C, bool Rct, size_t R >
		raw_heap_matrix< iter_type_t< I >, Cct ? C : 0, Rct ? R : 0 >
		by_sequence(col_t< Cct, C > c, row_t< Rct, R > r, I i)const;
	};


} }


namespace mitrax{ namespace detail{


	template < typename T, size_t C, size_t R >
	class raw_matrix_impl: public dims_t< C, R >{
	public:
		static_assert(!std::is_const_v< T >);
		static_assert(!std::is_reference_v< T >);


		/// \brief Type of the data that administrates the matrix
		using value_type = T;

		/// \brief Type with the make functions
		using maker_type = maker::std_t;

		/// \brief Type of a iterator for data
		using iterator = value_type*;

		/// \brief Type of a iterator for const data
		using const_iterator = value_type const*;

		/// \brief Type of a reverse iterator for data
		using reverse_iterator = std::reverse_iterator< iterator >;

		/// \brief Type of a reverse iterator for const data
		using const_reverse_iterator = std::reverse_iterator< const_iterator >;


		constexpr raw_matrix_impl():
			values_(init_array< C * R >(value_type())) {}

		constexpr raw_matrix_impl(raw_matrix_impl&&) = default;

		constexpr raw_matrix_impl(raw_matrix_impl const&) = default;

		constexpr raw_matrix_impl(
			col_t< true, C >, row_t< true, R >,
			array_s< value_type, C * R >&& values
		):
			values_(std::move(values))
			{}


		constexpr raw_matrix_impl& operator=(raw_matrix_impl&&) = default;

		constexpr raw_matrix_impl& operator=(raw_matrix_impl const&) = default;


		constexpr value_type& operator()(size_t x, size_t y){
			return values_[y * this->cols() + x];
		}

		constexpr value_type const& operator()(size_t x, size_t y)const{
			return values_[y * this->cols() + x];
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


// 		template < typename F >
// 		constexpr void reinit_fn(F&& f){
// 			*this = maker_type().by_function
// 				(this->cols(), this->rows(), static_cast< F&& >(f)).impl();
// 		}

		template < typename U >
		constexpr void reinit_v(U const& v){
			*this = maker_type().by_value
				(this->cols(), this->rows(), v).impl();
		}

		template < typename Iter >
		constexpr void reinit_iter(Iter iter){
			*this = maker_type().by_sequence
				(this->cols(), this->rows(), iter).impl();
		}


	private:
		array_s< value_type, C * R > values_;
	};


	template < typename T, size_t C, size_t R >
	class raw_matrix_impl_base: public dims_t< C, R >{
	public:
		static_assert(!std::is_const_v< T >);
		static_assert(!std::is_reference_v< T >);


		/// \brief Type of the data that administrates the matrix
		using value_type = T;

		/// \brief Type with the make functions
		using maker_type = maker::heap_t;

		/// \brief Type of a iterator for data
		using iterator = value_type*;

		/// \brief Type of a iterator for const data
		using const_iterator = value_type const*;

		/// \brief Type of a reverse iterator for data
		using reverse_iterator = std::reverse_iterator< iterator >;

		/// \brief Type of a reverse iterator for const data
		using const_reverse_iterator = std::reverse_iterator< const_iterator >;


		raw_matrix_impl_base() = default;

		raw_matrix_impl_base(raw_matrix_impl_base&&) = default;

		raw_matrix_impl_base(raw_matrix_impl_base const&) = default;

		raw_matrix_impl_base(
			col_t< C != 0, C > c, row_t< R != 0, R > r,
			detail::array_d< value_type >&& values
		):
			dims_t< C, R >(c, r),
			values_(std::move(values))
			{}


		raw_matrix_impl_base& operator=(raw_matrix_impl_base&&) = default;

		raw_matrix_impl_base& operator=(raw_matrix_impl_base const&) = default;


		value_type& operator()(size_t x, size_t y){
			return values_[y * this->cols() + x];
		}

		value_type const& operator()(size_t x, size_t y)const{
			return values_[y * this->cols() + x];
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


		void resize(dims_t< C, R > const& /*d*/){
			// TODO: do the resize
		}


// 		template < typename F >
// 		void reinit_fn(F&& f){
// 			*this = maker_type().by_function
// 				(this->cols(), this->rows(), static_cast< F&& >(f)).impl();
// 		}

		template < typename U >
		void reinit_v(U const& v){
			*this = maker_type().by_value
				(this->cols(), this->rows(), v).impl();
		}

		template < typename Iter >
		void reinit_iter(Iter iter){
			*this = maker_type().by_sequence
				(this->cols(), this->rows(), iter).impl();
		}


	protected:
		detail::array_d< value_type > values_;
	};


	template < typename T, size_t R >
	class raw_matrix_impl< T, 0, R >:
		public raw_matrix_impl_base< T, 0, R >{
	public:
		using raw_matrix_impl_base< T, 0, R >::raw_matrix_impl_base;
	};


	template < typename T, size_t C >
	class raw_matrix_impl< T, C, 0 >:
		public raw_matrix_impl_base< T, C, 0 >{
	public:
		using raw_matrix_impl_base< T, C, 0 >::raw_matrix_impl_base;
	};


	template < typename T >
	class raw_matrix_impl< T, 0, 0 >:
		public raw_matrix_impl_base< T, 0, 0 >{
	public:
		using raw_matrix_impl_base< T, 0, 0 >::raw_matrix_impl_base;
	};


	template < typename T, size_t C, size_t R >
	class raw_heap_matrix_impl:
		public raw_matrix_impl_base< T, C, R >{
	public:
		static_assert(
			C > 0 && R > 0,
			"raw_heap_matrix_impl< T, C, R > is for static dimensions only, "
			"use raw_matrix_impl< T, C, R > instead"
		);

		using raw_matrix_impl_base< T, C, R >::raw_matrix_impl_base;
	};


} }


namespace mitrax{ namespace detail{


	template < typename I, bool Cct, size_t C, bool Rct, size_t R >
	constexpr auto to_raw_matrix_data(
		std::true_type, col_t< Cct, C >, row_t< Rct, R >, I i
	){
		return to_array< C * R >(i);
	}

	template < typename I, bool Cct, size_t C, bool Rct, size_t R >
	constexpr auto to_raw_matrix_data(
		std::false_type, col_t< Cct, C > c, row_t< Rct, R > r, I i
	){
		return array_d< iter_type_t< I > >(i, size_t(c) * size_t(r));
	}

	template < typename T, bool Cct, size_t C, bool Rct, size_t R >
	constexpr auto init_raw_matrix_data(
		std::true_type, col_t< Cct, C >, row_t< Rct, R >, T const& v
	){
		return init_array(v, std::make_index_sequence< C * R >());
	}

	template < typename T, bool Cct, size_t C, bool Rct, size_t R >
	constexpr auto init_raw_matrix_data(
		std::false_type, col_t< Cct, C > c, row_t< Rct, R > r, T const& v
	){
		return array_d< std::remove_cv_t< T > >(size_t(c) * size_t(r), v);
	}


} }


namespace mitrax{ namespace maker{


	template < typename T, bool Cct, size_t C, bool Rct, size_t R >
	constexpr
	raw_matrix< std::remove_cv_t< T >, Cct ? C : 0, Rct ? R : 0 >
	std_t::by_value(col_t< Cct, C > c, row_t< Rct, R > r, T const& v)const{
		return {init, c, r, detail::init_raw_matrix_data(
			bool_t< Cct && Rct >(), c, r, v
		)};
	}

	template < typename I, bool Cct, size_t C, bool Rct, size_t R >
	constexpr
	raw_matrix< iter_type_t< I >, Cct ? C : 0, Rct ? R : 0 >
	std_t::by_sequence(col_t< Cct, C > c, row_t< Rct, R > r, I i)const{
		return {init, c, r, detail::to_raw_matrix_data(
			bool_t< Cct && Rct >(), c, r, i
		)};
	}

	constexpr auto std = std_t();


	template < typename T, bool Cct, size_t C, bool Rct, size_t R >
	raw_heap_matrix< std::remove_cv_t< T >, Cct ? C : 0, Rct ? R : 0 >
	heap_t::by_value(col_t< Cct, C > c, row_t< Rct, R > r, T const& v)const{
		return {init, c, r, detail::init_raw_matrix_data(
			std::false_type(), c, r, v
		)};
	}

	template < typename I, bool Cct, size_t C, bool Rct, size_t R >
	raw_heap_matrix< iter_type_t< I >, Cct ? C : 0, Rct ? R : 0 >
	heap_t::by_sequence(col_t< Cct, C > c, row_t< Rct, R > r, I i)const{
		return {init, c, r, detail::to_raw_matrix_data(
			std::false_type(), c, r, i
		)};
	}

	constexpr heap_t heap{};


} }


#endif
