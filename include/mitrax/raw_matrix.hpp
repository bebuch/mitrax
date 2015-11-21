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
#include "sub_matrix.hpp"


namespace mitrax{


	namespace detail{


		template < size_t C, size_t R >
		struct is_static: std::true_type{};

		template < size_t R >
		struct is_static< 0, R >: std::false_type{};

		template < size_t C >
		struct is_static< C, 0 >: std::false_type{};

		template <>
		struct is_static< 0, 0 >: std::false_type{};


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

		template < typename T, size_t C, size_t R >
		constexpr auto to_raw_matrix_data(
			std::true_type, col_t< C >, row_t< R >, T const& v
		){
			return mitrax::init_array< C * R >(v);
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

		template < typename T, size_t C, size_t R >
		constexpr auto to_raw_matrix_data(
			std::false_type, col_t< C > c, row_t< R > r, T const& v
		){
			return boost::container::vector< T >(
				static_cast< size_t >(c) * static_cast< size_t >(r), v
			);
		}

		template < typename T, size_t C, size_t R >
		constexpr auto to_raw_matrix_data(
			col_t< C > c, row_t< R > r, T const& v
		){
			return to_raw_matrix_data(is_static< C, R >(), c, r, v);
		}


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


		constexpr raw_matrix_impl(raw_matrix_impl&&) = default;

		constexpr raw_matrix_impl(raw_matrix_impl const&) = default;

		constexpr raw_matrix_impl(
			col_t< Cols >, row_t< Rows >,
			std::array< value_type, Cols * Rows >&& values
		):
			values_(std::move(values))
			{}


		constexpr raw_matrix_impl& operator=(raw_matrix_impl&&) = default;

		constexpr raw_matrix_impl& operator=(raw_matrix_impl const&) = default;


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


		constexpr std::array< value_type, Cols * Rows >& data(){
			return values_;
		}

		constexpr std::array< value_type, Cols * Rows > const& data()const{
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


		raw_matrix_impl_base& operator=(raw_matrix_impl_base&&) = default;

		raw_matrix_impl_base& operator=(raw_matrix_impl_base const&) = default;


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


		boost::container::vector< value_type >& data(){
			return values_;
		}

		boost::container::vector< value_type > const& data()const{
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


	template < typename T, bool Cct, size_t C, bool Rct, size_t R >
	constexpr raw_matrix< std::remove_cv_t< T >, dim(Cct, C), dim(Rct, R) >
	make_matrix(col_init_t< Cct, C > c, row_init_t< Rct, R > r){
		return make_matrix(c, r, T());
	}

	template < typename T, size_t C, size_t R >
	constexpr raw_matrix< std::remove_cv_t< T >, C, R >
	make_matrix(dim_t< C, R > const& d){
		return make_matrix< T >(d.cols().init(), d.rows().init());
	}

	template < typename T, bool Cct, size_t C, bool Rct, size_t R >
	constexpr raw_matrix< std::remove_cv_t< T >, dim(Cct, C), dim(Rct, R) >
	make_matrix(col_init_t< Cct, C > c, row_init_t< Rct, R > r, T const& v){
		return raw_matrix_impl<
			std::remove_cv_t< T >, dim(Cct, C), dim(Rct, R)
		>(c.get(), r.get(), detail::to_raw_matrix_data(c.get(), r.get(), v));
	}

	template <
		typename T, bool Cct, size_t C, bool Rct, size_t R, typename F,
		decltype(std::declval< F >(size_t(), size_t()))* = nullptr
	> constexpr raw_matrix< std::remove_cv_t< T >, dim(Cct, C), dim(Rct, R) >
	make_matrix(col_init_t< Cct, C > c, row_init_t< Rct, R > r, F const& f){
		return raw_matrix_impl<
			std::remove_cv_t< T >, dim(Cct, C), dim(Rct, R)
		>(c.get(), r.get(), f(size_t(), size_t()));
	}

	template < typename T, size_t C, size_t R >
	constexpr raw_matrix< std::remove_cv_t< T >, C, R >
	make_matrix(dim_t< C, R > const& d, T const& v){
		return make_matrix(d.cols().init(), d.rows().init(), v);
	}

	template < typename T, bool Cct, size_t C, bool Rct, size_t R >
	constexpr raw_matrix< std::remove_cv_t< T >, dim(Cct, C), dim(Rct, R) >
	make_matrix(col_init_t< Cct, C > c, row_init_t< Rct, R > r, T(&&v)[R][C]){
		return raw_matrix_impl<
			std::remove_cv_t< T >, dim(Cct, C), dim(Rct, R)
		>(
			c.get(), r.get(),
			detail::to_raw_matrix_data(bool_t< Cct && Rct >(), std::move(v))
		);
	}

	template < typename T, bool Cct, size_t C, bool Rct, size_t R >
	constexpr raw_matrix< std::remove_cv_t< T >, dim(Cct, C), dim(Rct, R) >
	make_matrix(col_init_t< Cct, C > c, row_init_t< Rct, R > r, T(&v)[R][C]){
		return raw_matrix_impl<
			std::remove_cv_t< T >, dim(Cct, C), dim(Rct, R)
		>(
			c.get(), r.get(),
			detail::to_raw_matrix_data(bool_t< Cct && Rct >(), v)
		);
	}


	template < typename T, bool Nct, size_t N >
	constexpr auto make_square_matrix(dim_init_t< Nct, N > n){
		return make_matrix< T >(n.as_col(), n.as_row());
	}

	template < typename T, bool Nct, size_t N >
	constexpr auto make_square_matrix(dim_init_t< Nct, N > n, T const& v){
		return make_matrix(n.as_col(), n.as_row(), v);
	}

	template < typename T, bool Nct, size_t N >
	constexpr auto make_square_matrix(dim_init_t< Nct, N > n, T(&&v)[N][N]){
		return make_matrix(n.as_col(), n.as_row(), std::move(v));
	}

	template < typename T, bool Nct, size_t N >
	constexpr auto make_square_matrix(dim_init_t< Nct, N > n, T(&v)[N][N]){
		return make_matrix(n.as_col(), n.as_row(), v);
	}


	template < typename T, bool Nct, size_t N >
	constexpr raw_col_vector< std::remove_cv_t< T >, dim(Nct, N) >
	make_col_vector(row_init_t< Nct, N > r){
		return make_col_vector(r, T());
	}

	template < typename T, bool Nct, size_t N >
	constexpr raw_col_vector< std::remove_cv_t< T >, dim(Nct, N) >
	make_col_vector(row_init_t< Nct, N > r, T const& v){
		using namespace literals;
		return make_matrix(1_C, r, v);
	}

	template < typename T, bool Nct, size_t N >
	constexpr raw_col_vector< std::remove_cv_t< T >, dim(Nct, N) >
	make_col_vector(row_init_t< Nct, N > r, T(&&v)[N]){
		using namespace literals;
		return raw_matrix_impl< std::remove_cv_t< T >, 1, dim(Nct, N) >(
			1_C .get(), r.get(),
			detail::to_raw_matrix_data(bool_t< Nct >(), std::move(v))
		);
	}

	template < typename T, bool Nct, size_t N >
	constexpr raw_col_vector< std::remove_cv_t< T >, dim(Nct, N) >
	make_col_vector(row_init_t< Nct, N > r, T(&v)[N]){
		using namespace literals;
		return raw_matrix_impl< std::remove_cv_t< T >, 1, dim(Nct, N) >(
			1_C .get(), r.get(),
			detail::to_raw_matrix_data(bool_t< Nct >(), v)
		);
	}


	template < typename T, bool Nct, size_t N >
	constexpr raw_row_vector< std::remove_cv_t< T >, dim(Nct, N) >
	make_row_vector(col_init_t< Nct, N > c){
		using namespace literals;
		return make_row_vector(c, T());
	}

	template < typename T, bool Nct, size_t N >
	constexpr raw_row_vector< std::remove_cv_t< T >, dim(Nct, N) >
	make_row_vector(col_init_t< Nct, N > c, T const& v){
		using namespace literals;
		return make_matrix(c, 1_R, v);
	}

	template < typename T, bool Nct, size_t N >
	constexpr raw_row_vector< std::remove_cv_t< T >, dim(Nct, N) >
	make_row_vector(col_init_t< Nct, N > c, T(&&v)[N]){
		using namespace literals;
		return raw_matrix_impl< std::remove_cv_t< T >, dim(Nct, N), 1 >(
			c.get(), 1_R .get(),
			detail::to_raw_matrix_data(bool_t< Nct >(), std::move(v))
		);
	}

	template < typename T, bool Nct, size_t N >
	constexpr raw_row_vector< std::remove_cv_t< T >, dim(Nct, N) >
	make_row_vector(col_init_t< Nct, N > c, T(&v)[N]){
		using namespace literals;
		return raw_matrix_impl< std::remove_cv_t< T >, dim(Nct, N), 1 >(
			c.get(), 1_R .get(),
			detail::to_raw_matrix_data(bool_t< Nct >(), v)
		);
	}

	template < typename T, size_t C, size_t R >
	raw_matrix< std::remove_cv_t< T >, 0, 0 >
	make_bitmap(dim_t< C, R > const& d){
		return make_matrix< T >(
			col_t< 0 >(d.cols()).init(),
			row_t< 0 >(d.rows()).init()
		);
	}

	template < typename T, size_t C, size_t R >
	raw_matrix< std::remove_cv_t< T >, 0, 0 >
	make_bitmap(dim_t< C, R > const& d, T const& v){
		return make_matrix(
			col_t< 0 >(d.cols()).init(),
			row_t< 0 >(d.rows()).init(),
			v
		);
	}

	template < typename T >
	raw_matrix< std::remove_cv_t< T >, 0, 0 >
	make_bitmap(size_t c, size_t r){
		return make_matrix< T >(col_t< 0 >(c).init(), row_t< 0 >(r).init());
	}

	template < typename T >
	raw_matrix< std::remove_cv_t< T >, 0, 0 >
	make_bitmap(size_t c, size_t r, T const& v){
		return make_matrix(col_t< 0 >(c).init(), row_t< 0 >(r).init(), v);
	}


}

#endif
