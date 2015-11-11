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



	template < typename T, size_t N >
	using raw_square_matrix = matrix< raw_matrix_impl< T, N, N >, N, N >;

	template < typename T, size_t Rows >
	using raw_col_vector = matrix< raw_matrix_impl< T, 1, Rows >, 1, Rows >;

	template < typename T, size_t Cols >
	using raw_row_vector = matrix< raw_matrix_impl< T, Cols, 1 >, Cols, 1 >;


	namespace detail{


		template < typename T, size_t N >
		constexpr auto to_raw_matrix_data(std::true_type, T(&&v)[N]){
			return mitrax::to_array(std::move(v));
		}

		template < typename T, size_t N >
		constexpr auto to_raw_matrix_data(std::true_type, T(&v)[N]){
			return mitrax::to_array(v);
		}

		template < typename T, size_t C, size_t R >
		constexpr auto to_raw_matrix_data(std::true_type, T(&&v)[R][C]){
			return mitrax::to_array(std::move(v));
		}

		template < typename T, size_t C, size_t R >
		constexpr auto to_raw_matrix_data(std::true_type, T(&v)[R][C]){
			return mitrax::to_array(v);
		}

		template < typename T, size_t N >
		constexpr auto to_raw_matrix_data(std::false_type, T(&&v)[N]){
			return mitrax::to_vector(std::move(v));
		}

		template < typename T, size_t N >
		constexpr auto to_raw_matrix_data(std::false_type, T(&v)[N]){
			return mitrax::to_vector(v);
		}

		template < typename T, size_t C, size_t R >
		constexpr auto to_raw_matrix_data(std::false_type, T(&&v)[R][C]){
			return mitrax::to_vector(std::move(v));
		}

		template < typename T, size_t C, size_t R >
		constexpr auto to_raw_matrix_data(std::false_type, T(&v)[R][C]){
			return mitrax::to_vector(v);
		}


		template < size_t C, size_t R >
		struct is_static: std::true_type{};

		template < size_t R >
		struct is_static< 0, R >: std::false_type{};

		template < size_t C >
		struct is_static< C, 0 >: std::false_type{};

		template <>
		struct is_static< 0, 0 >: std::false_type{};


	}


	template < typename T, size_t Cols, size_t Rows >
	class raw_matrix_impl{
	public:
		/// \brief Type of the data that administrates the matrix
		using value_type = T;

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


		constexpr raw_matrix_impl(col_t< Cols >, row_t< Rows >):
			values_{} {}

		constexpr raw_matrix_impl(raw_matrix_impl&&) = default;

		constexpr raw_matrix_impl(raw_matrix_impl const&) = default;

		constexpr raw_matrix_impl(
			col_t< Cols >, row_t< Rows >,
			std::array< value_type, Cols * Rows >&& values
		):
			values_(std::move(values))
			{}

		constexpr raw_matrix_impl(
			col_t< Cols >, row_t< Rows >,
			std::array< value_type, Cols * Rows > const& values
		):
			values_(values)
			{}


		constexpr value_type& operator()(size_t x, size_t y){
			return values_[y * cols() + x];
		}

		constexpr value_type const& operator()(size_t x, size_t y)const{
			return values_[y * cols() + x];
		}


		constexpr col_t< Cols > cols()const{
			return col_t< Cols >();
		}

		constexpr row_t< Rows > rows()const{
			return row_t< Rows >();
		}


		constexpr iterator begin(){
			return values_.begin();
		}

		constexpr const_iterator begin()const{
			return values_.begin();
		}

		constexpr iterator end(){
			return values_.end();
		}

		constexpr const_iterator end()const{
			return values_.end();
		}

		constexpr reverse_iterator rbegin(){
			return values_.rbegin();
		}

		constexpr const_reverse_iterator rbegin()const{
			return values_.rbegin();
		}

		constexpr reverse_iterator rend(){
			return values_.rend();
		}

		constexpr const_reverse_iterator rend()const{
			return values_.rend();
		}


		constexpr std::array< value_type, Cols * Rows >&& data()&&{
			return std::move(values_);
		}

		constexpr std::array< value_type, Cols * Rows > const& data()const&{
			return values_;
		}


	private:
		std::array< value_type, Cols * Rows > values_;
	};


	template < typename T, size_t Cols, size_t Rows >
	class raw_matrix_impl_base{
	public:
		/// \brief Type of the data that administrates the matrix
		using value_type = T;

		/// \brief Type of a iterator for data
		using iterator = typename
			boost::container::vector< value_type >::iterator;

		/// \brief Type of a iterator for const data
		using const_iterator = typename
			boost::container::vector< value_type >::const_iterator;

		/// \brief Type of a reverse iterator for data
		using reverse_iterator = typename
			boost::container::vector< value_type >::reverse_iterator;

		/// \brief Type of a reverse iterator for const data
		using const_reverse_iterator = typename
			boost::container::vector< value_type >::const_reverse_iterator;


		raw_matrix_impl_base(col_t< Cols > c, row_t< Rows > r):
			cols_(c), rows_(r) {}

		raw_matrix_impl_base(raw_matrix_impl_base&&) = default;

		raw_matrix_impl_base(raw_matrix_impl_base const&) = default;

		raw_matrix_impl_base(
			col_t< Cols > c, row_t< Rows > r,
			boost::container::vector< value_type >&& values
		):
			values_(std::move(values)),
			cols_(c),
			rows_(r)
			{}

		raw_matrix_impl_base(
			col_t< Cols > c, row_t< Rows > r,
			boost::container::vector< value_type > const& values
		):
			values_(values),
			cols_(c),
			rows_(r)
			{}


		value_type& operator()(size_t x, size_t y){
			return values_[y * cols() + x];
		}

		value_type const& operator()(size_t x, size_t y)const{
			return values_[y * cols() + x];
		}


		constexpr col_t< Cols > cols()const{
			return cols_;
		}

		constexpr row_t< Rows > rows()const{
			return rows_;
		}


		iterator begin(){
			return values_.begin();
		}

		const_iterator begin()const{
			return values_.begin();
		}

		iterator end(){
			return values_.end();
		}

		const_iterator end()const{
			return values_.end();
		}

		reverse_iterator rbegin(){
			return values_.rbegin();
		}

		const_reverse_iterator rbegin()const{
			return values_.rbegin();
		}

		reverse_iterator rend(){
			return values_.rend();
		}

		const_reverse_iterator rend()const{
			return values_.rend();
		}


		boost::container::vector< value_type >&& data()&&{
			return std::move(values_);
		}

		boost::container::vector< value_type > const& data()const&{
			return values_;
		}


	protected:
		boost::container::vector< value_type > values_;
		col_t< Cols > cols_;
		row_t< Rows > rows_;
	};


	template < typename T, size_t Rows >
	class raw_matrix_impl< T, 0, Rows >:
		public raw_matrix_impl_base< T, 0, Rows >{
	public:
		using raw_matrix_impl_base< T, 0, Rows >::raw_matrix_impl_base;
	};


	template < typename T, size_t Cols >
	class raw_matrix_impl< T, Cols, 0 >:
		public raw_matrix_impl_base< T, Cols, 0 >{
	public:
		using raw_matrix_impl_base< T, Cols, 0 >::raw_matrix_impl_base;
	};


	template < typename T >
	class raw_matrix_impl< T, 0, 0 >:
		public raw_matrix_impl_base< T, 0, 0 >{
	public:
		using raw_matrix_impl_base< T, 0, 0 >::raw_matrix_impl_base;
	};


	template < typename T, bool Cb, size_t C, bool Rb, size_t R >
	constexpr raw_matrix< std::remove_cv_t< T >, dim(Cb, C), dim(Rb, R) >
	make_matrix(
		col_lit< Cb, C > c,
		row_lit< Rb, R > r
	){
		return raw_matrix_impl< std::remove_cv_t< T >, dim(Cb, C), dim(Rb, R) >(c, r);
	}

	template < typename T, bool Cb, size_t C, bool Rb, size_t R >
	constexpr raw_matrix< std::remove_cv_t< T >, dim(Cb, C), dim(Rb, R) >
	make_matrix(
		col_lit< Cb, C > c,
		row_lit< Rb, R > r,
		T(&&v)[R][C]
	){
		return raw_matrix_impl< std::remove_cv_t< T >, dim(Cb, C), dim(Rb, R) >(c, r,
			detail::to_raw_matrix_data(bool_t< Cb && Rb >(), std::move(v)));
	}

	template < typename T, bool Cb, size_t C, bool Rb, size_t R >
	constexpr raw_matrix< std::remove_cv_t< T >, dim(Cb, C), dim(Rb, R) >
	make_matrix(
		col_lit< Cb, C > c,
		row_lit< Rb, R > r,
		T(&v)[R][C]
	){
		return raw_matrix_impl< std::remove_cv_t< T >, dim(Cb, C), dim(Rb, R) >(c, r,
			detail::to_raw_matrix_data(bool_t< Cb && Rb >(), v));
	}


	template < typename T, bool Nb, size_t N >
	constexpr auto make_square_matrix(dim_lit< Nb, N > n){
		return make_matrix(n.col(), n.row());
	}

	template < typename T, bool Nb, size_t N >
	constexpr auto make_square_matrix(dim_lit< Nb, N > n, T(&&v)[N][N]){
		return make_matrix(n.col(), n.row(), std::move(v));
	}

	template < typename T, bool Nb, size_t N >
	constexpr auto make_square_matrix(dim_lit< Nb, N > n, T(&v)[N][N]){
		return make_matrix(n.col(), n.row(), v);
	}


	template < typename T, bool Nb, size_t N >
	constexpr raw_col_vector< std::remove_cv_t< T >, dim(Nb, N) >
	make_col_vector(
		row_lit< Nb, N > r
	){
		using namespace literals;
		return raw_matrix_impl< std::remove_cv_t< T >, 1, dim(Nb, N) >(1_C, r);
	}

	template < typename T, bool Nb, size_t N >
	constexpr raw_col_vector< std::remove_cv_t< T >, dim(Nb, N) >
	make_col_vector(
		row_lit< Nb, N > r,
		T(&&v)[N]
	){
		using namespace literals;
		return raw_matrix_impl< std::remove_cv_t< T >, 1, dim(Nb, N) >(1_C, r,
			detail::to_raw_matrix_data(bool_t< Nb >(), std::move(v)));
	}

	template < typename T, bool Nb, size_t N >
	constexpr raw_col_vector< std::remove_cv_t< T >, dim(Nb, N) >
	make_col_vector(
		row_lit< Nb, N > r,
		T(&v)[N]
	){
		using namespace literals;
		return raw_matrix_impl< std::remove_cv_t< T >, 1, dim(Nb, N) >(1_C, r,
			detail::to_raw_matrix_data(bool_t< Nb >(), v));
	}


	template < typename T, bool Nb, size_t N >
	constexpr raw_row_vector< std::remove_cv_t< T >, dim(Nb, N) >
	make_row_vector(
		col_lit< Nb, N > c
	){
		using namespace literals;
		return raw_matrix_impl< std::remove_cv_t< T >, dim(Nb, N), 1 >(c, 1_R);
	}

	template < typename T, bool Nb, size_t N >
	constexpr raw_row_vector< std::remove_cv_t< T >, dim(Nb, N) >
	make_row_vector(
		col_lit< Nb, N > c,
		T(&&v)[N]
	){
		using namespace literals;
		return raw_matrix_impl< std::remove_cv_t< T >, dim(Nb, N), 1 >(c, 1_R,
			detail::to_raw_matrix_data(bool_t< Nb >(), std::move(v)));
	}

	template < typename T, bool Nb, size_t N >
	constexpr raw_row_vector< std::remove_cv_t< T >, dim(Nb, N) >
	make_row_vector(
		col_lit< Nb, N > c,
		T(&v)[N]
	){
		using namespace literals;
		return raw_matrix_impl< std::remove_cv_t< T >, dim(Nb, N), 1 >(c, 1_R,
			detail::to_raw_matrix_data(bool_t< Nb >(), v));
	}


// 	template < typename M, size_t C, size_t R >
// 	constexpr raw_matrix< value_type_t< M >, C, R >
// 	matrix< M, C, R >::as_raw_matrix()&&{
// 		return std::move(m_).data();
// 	}
// 
// 	template < typename M, size_t C, size_t R >
// 	constexpr raw_matrix< value_type_t< M >, C, R >
// 	matrix< M, C, R >::as_raw_matrix()const&{
// 		return m_.data();
// 	}


}

#endif
