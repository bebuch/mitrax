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
#include "to_array.hpp"
#include "to_vector.hpp"


namespace mitrax{



	template < typename T, size_t N >
	using raw_square_matrix = matrix< raw_matrix_impl< T, N, N >, N, N >;

	template < typename T, size_t Cols >
	using raw_col_vector = matrix< raw_matrix_impl< T, Cols, 1 >, Cols, 1 >;

	template < typename T, size_t Rows >
	using raw_row_vector = matrix< raw_matrix_impl< T, 1, Rows >, 1, Rows >;


	namespace detail{


		template <
			typename T,
			size_t Cols,
			size_t Rows,
			size_t ... I
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
			size_t Cols,
			size_t Rows,
			size_t ... I
		>
		constexpr auto to_array(
			T const(&values)[Rows][Cols],
			std::index_sequence< I ... >
		){
			return std::array< T, Cols * Rows >{{
				values[I / Cols][I % Cols] ...
			}};
		}


		template <
			typename T,
			size_t C1,
			size_t R1,
			typename M,
			size_t C2,
			size_t R2,
			size_t ... I
		>
		constexpr std::array< T, C1 * R1 > matrix_to_array(
			matrix< M, C2, R2 >&& m,
			std::index_sequence< I ... >
		){
			if(C1 != m.cols() || R1 != m.rows()){
				throw std::logic_error(
					"matrix dimensions not compatible while converting"
				);
			}

			return std::array< T, C1 * R1 >{{
				static_cast< T >(std::move(m(I % C1, I / C1))) ...
			}};
		}

		template <
			typename T,
			size_t C1,
			size_t R1,
			typename M,
			size_t C2,
			size_t R2,
			size_t ... I
		>
		constexpr std::array< T, C1 * R1 > matrix_to_array(
			matrix< M, C2, R2 > const& m,
			std::index_sequence< I ... >
		){
			if(C1 != m.cols() || R1 != m.rows()){
				throw std::logic_error(
					"matrix dimensions not compatible while converting"
				);
			}

			return std::array< T, C1 * R1 >{{
				static_cast< T >(m(I % C1, I / C1)) ...
			}};
		}

		template <
			typename T,
			size_t C1,
			size_t R1,
			typename M,
			size_t C2,
			size_t R2,
			size_t ... I
		>
		constexpr std::array< T, C1 * R1 > sub_matrix_to_array(
			matrix< M, C2, R2 > const& m,
			size_t x,
			size_t y,
			std::index_sequence< I ... >
		){
			return std::array< T, C1 * R1 >{{
				static_cast< T >(m(x + I % C1, y + I / C1)) ...
			}};
		}

		template <
			typename T,
			typename M,
			size_t C,
			size_t R
		>
		constexpr boost::container::vector< T > sub_matrix_to_vector(
			matrix< M, C, R > const& m,
			size_t x,
			size_t y,
			size_t cols,
			size_t rows
		){
			boost::container::vector< T > result;
			result.reserve(cols * rows);
			for(size_t yi = 0; yi < rows; ++yi){
				for(size_t xi = 0; xi < cols; ++xi){
					result.emplace_back(m(x + xi, y + yi));
				}
			}
			return result;
		}


		template <
			typename T,
			size_t Cols,
			size_t Rows,
			size_t ... I
		>
		constexpr auto to_vector(
			T(&&values)[Rows][Cols],
			std::index_sequence< I ... >
		){
			return boost::container::vector< T >{
				std::move(values[I / Cols][I % Cols]) ...
			};
		}

		template <
			typename T,
			size_t Cols,
			size_t Rows,
			size_t ... I
		>
		constexpr auto to_vector(
			T const(&values)[Rows][Cols],
			std::index_sequence< I ... >
		){
			return boost::container::vector< T >{
				values[I / Cols][I % Cols] ...
			};
		}


		template <
			typename T,
			size_t C1,
			size_t R1,
			typename M,
			size_t C2,
			size_t R2,
			size_t ... I
		>
		boost::container::vector< T > matrix_to_vector(
			matrix< M, C2, R2 >&& m
		){
			if(!(C1 == 0 || C1 == m.cols()) || !(R1 == 0 || R1 == m.rows())){
				throw std::logic_error(
					"matrix dimensions not compatible while converting"
				);
			}

			return {
				std::make_move_iterator(m.begin()),
				std::make_move_iterator(m.end())
			};
		}

		template <
			typename T,
			size_t C1,
			size_t R1,
			typename M,
			size_t C2,
			size_t R2,
			size_t ... I
		>
		boost::container::vector< T > matrix_to_vector(
			matrix< M, C2, R2 > const& m
		){
			if(!(C1 == 0 || C1 == m.cols()) || !(R1 == 0 || R1 == m.rows())){
				throw std::logic_error(
					"matrix dimensions not compatible while converting"
				);
			}

			return {m.begin(), m.end()};
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


		constexpr raw_matrix_impl():
			values_{{0}} {}

		constexpr raw_matrix_impl(raw_matrix_impl&&) = default;

		constexpr raw_matrix_impl(raw_matrix_impl const&) = default;


		constexpr value_type& operator()(
			size_t x, size_t y
		){
			return values_[y * cols() + x];
		}

		constexpr value_type const& operator()(
			size_t x, size_t y
		)const{
			return values_[y * cols() + x];
		}


		constexpr size_t cols()const{
			return Cols;
		}

		constexpr size_t rows()const{
			return Rows;
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


	private:
		std::array< value_type, Cols * Rows > values_;


		template <
			typename V,
			size_t C1,
			size_t R1,
			typename M,
			size_t C2,
			size_t R2
		> friend constexpr raw_matrix< V, C1, R1 >
		detail::convert(matrix< M, C2, R2 >&& m);

		template <
			typename V,
			size_t C1,
			size_t R1,
			typename M,
			size_t C2,
			size_t R2
		> friend constexpr raw_matrix< V, C1, R1 >
		detail::convert(matrix< M, C2, R2 > const& m);

		template <
			typename V,
			size_t C1,
			size_t R1,
			typename M,
			size_t C2,
			size_t R2
		> friend constexpr raw_matrix< V, C1, R1 > detail::sub_matrix(
			matrix< M, C2, R2 > const& m,
			size_t x,
			size_t y,
			size_ct< C1 > /*cols*/,
			size_ct< R1 > /*rows*/
		);


		template < typename M, size_t C, size_t R >
		constexpr raw_matrix_impl(matrix< M, C, R >&& m):
			values_(detail::matrix_to_array< T, Cols, Rows >(
				std::move(m),
				std::make_index_sequence< Cols * Rows >()
			)){}

		template < typename M, size_t C, size_t R >
		constexpr raw_matrix_impl(matrix< M, C, R > const& m):
			values_(detail::matrix_to_array< T, Cols, Rows >(
				m,
				std::make_index_sequence< Cols * Rows >()
			)){}

		template < typename M, size_t C, size_t R >
		constexpr raw_matrix_impl(
			matrix< M, C, R > const& m,
			size_t x,
			size_t y
		):
			values_(detail::sub_matrix_to_array< T, Cols, Rows >(
				m, x, y,
				std::make_index_sequence< Cols * Rows >()
			)){}


		constexpr raw_matrix_impl(value_type(&&values)[Rows][Cols]):
			values_(detail::to_array(
				std::move(values),
				std::make_index_sequence< Cols * Rows >()
			)){}

		constexpr raw_matrix_impl(value_type const(&values)[Rows][Cols]):
			values_(detail::to_array(
				values,
				std::make_index_sequence< Cols * Rows >()
			)){}

		template < size_t N >
		constexpr raw_matrix_impl(value_type(&&values)[N]):
			values_(to_array(std::move(values))){}

		template < size_t N >
		constexpr raw_matrix_impl(value_type const(&values)[N]):
			values_(to_array(values)){}


		template < typename U, size_t C, size_t R >
		friend constexpr raw_matrix< U, C, R >
		to_matrix(U(&&values)[R][C]);

		template < typename U, size_t C, size_t R >
		friend constexpr raw_matrix< U, C, R >
		to_matrix(U const(&values)[R][C]);


		template < typename U, size_t N >
		friend constexpr raw_col_vector< U, N >
		to_col_vector(U(&&values)[N]);

		template < typename U, size_t N >
		friend constexpr raw_col_vector< U, N >
		to_col_vector(U const(&values)[N]);


		template < typename U, size_t N >
		friend constexpr raw_row_vector< U, N >
		to_row_vector(U(&&values)[N]);

		template < typename U, size_t N >
		friend constexpr raw_row_vector< U, N >
		to_row_vector(U const(&values)[N]);
	};


	template < typename T >
	class dynamic_raw_matrix_impl_base{
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


		dynamic_raw_matrix_impl_base() = default;

		dynamic_raw_matrix_impl_base(dynamic_raw_matrix_impl_base&&) = default;

		dynamic_raw_matrix_impl_base(dynamic_raw_matrix_impl_base const&)
			= default;


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


	protected:
		boost::container::vector< value_type > values_;


		dynamic_raw_matrix_impl_base(
			boost::container::vector< value_type >&& values
		):
			values_(std::move(values))
			{}
	};


	template < typename T, size_t Cols >
	class raw_matrix_impl< T, Cols, 0 >:
		public dynamic_raw_matrix_impl_base< T >{
	public:
		using value_type = value_type_t< dynamic_raw_matrix_impl_base< T > >;


		raw_matrix_impl() = default;

		raw_matrix_impl(raw_matrix_impl&&) = default;

		raw_matrix_impl(raw_matrix_impl const&) = default;


		using dynamic_raw_matrix_impl_base< T >::dynamic_raw_matrix_impl_base;


		value_type& operator()(
			size_t x, size_t y
		){
			return values_[y * cols() + x];
		}

		value_type const& operator()(
			size_t x, size_t y
		)const{
			return values_[y * cols() + x];
		}


		constexpr size_t cols()const{
			return Cols;
		}

		size_t rows()const{
			return values_.size() / cols();
		}


	private:
		using dynamic_raw_matrix_impl_base< T >::values_;


		template < typename M, size_t C, size_t R >
		raw_matrix_impl(matrix< M, C, R >&& m):
			dynamic_raw_matrix_impl_base< T >(
				detail::matrix_to_vector< T, Cols, 0 >(std::move(m))
			) {}

		template < typename M, size_t C, size_t R >
		raw_matrix_impl(matrix< M, C, R > const& m):
			dynamic_raw_matrix_impl_base< T >(
				detail::matrix_to_vector< T, Cols, 0 >(m)
			) {}

		template < typename M, size_t C, size_t R >
		constexpr raw_matrix_impl(
			matrix< M, C, R > const& m,
			size_t x,
			size_t y,
			size_t rows
		):
			dynamic_raw_matrix_impl_base< T >(
				detail::sub_matrix_to_vector< T >(m, x, y, Cols, rows)
			) {}


		template <
			typename V,
			size_t C1,
			size_t R1,
			typename M,
			size_t C2,
			size_t R2
		> friend constexpr raw_matrix< V, C1, R1 >
		detail::convert(matrix< M, C2, R2 >&& m);

		template <
			typename V,
			size_t C1,
			size_t R1,
			typename M,
			size_t C2,
			size_t R2
		> friend constexpr raw_matrix< V, C1, R1 >
		detail::convert(matrix< M, C2, R2 > const& m);

		template <
			typename V,
			size_t C1,
			typename M,
			size_t C2,
			size_t R2
		> friend raw_matrix< V, C1, 0 > detail::sub_matrix(
			matrix< M, C2, R2 > const& m,
			size_t x,
			size_t y,
			size_ct< C1 > cols,
			size_t rows
		);
	};


	template < typename T, size_t Rows >
	class raw_matrix_impl< T, 0, Rows >:
		public dynamic_raw_matrix_impl_base< T >{
	public:
		using value_type = value_type_t< dynamic_raw_matrix_impl_base< T > >;


		raw_matrix_impl() = default;

		raw_matrix_impl(raw_matrix_impl&&) = default;

		raw_matrix_impl(raw_matrix_impl const&) = default;


		using dynamic_raw_matrix_impl_base< T >::dynamic_raw_matrix_impl_base;


		value_type& operator()(
			size_t x, size_t y
		){
			return values_[y * cols() + x];
		}

		value_type const& operator()(
			size_t x, size_t y
		)const{
			return values_[y * cols() + x];
		}


		size_t cols()const{
			return values_.size() / rows();
		}

		constexpr size_t rows()const{
			return Rows;
		}


	private:
		using dynamic_raw_matrix_impl_base< T >::values_;


		template < typename M, size_t C, size_t R >
		raw_matrix_impl(matrix< M, C, R >&& m):
			dynamic_raw_matrix_impl_base< T >(
				detail::matrix_to_vector< T, 0, Rows >(std::move(m))
			) {}

		template < typename M, size_t C, size_t R >
		raw_matrix_impl(matrix< M, C, R > const& m):
			dynamic_raw_matrix_impl_base< T >(
				detail::matrix_to_vector< T, 0, Rows >(m)
			) {}

		template < typename M, size_t C, size_t R >
		constexpr raw_matrix_impl(
			matrix< M, C, R > const& m,
			size_t x,
			size_t y,
			size_t cols
		):
			dynamic_raw_matrix_impl_base< T >(
				detail::sub_matrix_to_vector< T >(m, x, y, cols, Rows)
			) {}


		template <
			typename V,
			size_t C1,
			size_t R1,
			typename M,
			size_t C2,
			size_t R2
		> friend constexpr raw_matrix< V, C1, R1 >
		detail::convert(matrix< M, C2, R2 >&& m);

		template <
			typename V,
			size_t C1,
			size_t R1,
			typename M,
			size_t C2,
			size_t R2
		> friend constexpr raw_matrix< V, C1, R1 >
		detail::convert(matrix< M, C2, R2 > const& m);

		template <
			typename V,
			size_t R1,
			typename M,
			size_t C2,
			size_t R2
		> friend raw_matrix< V, 0, R1 > detail::sub_matrix(
			matrix< M, C2, R2 > const& m,
			size_t x,
			size_t y,
			size_t cols,
			size_ct< R1 > rows
		);
	};

	template < typename T >
	class raw_matrix_impl< T, 0, 0 >:
		public dynamic_raw_matrix_impl_base< T >{
	public:
		using value_type = value_type_t< dynamic_raw_matrix_impl_base< T > >;


		raw_matrix_impl(): cols_{0} {}

		raw_matrix_impl(raw_matrix_impl&&) = default;

		raw_matrix_impl(raw_matrix_impl const&) = default;


		using dynamic_raw_matrix_impl_base< T >::dynamic_raw_matrix_impl_base;


		value_type& operator()(
			size_t x, size_t y
		){
			return values_[y * cols() + x];
		}

		value_type const& operator()(
			size_t x, size_t y
		)const{
			return values_[y * cols() + x];
		}


		size_t cols()const{
			return cols_;
		}

		size_t rows()const{
			return values_.size() / cols();
		}


	private:
		using dynamic_raw_matrix_impl_base< T >::values_;
		size_t cols_;


		template < typename M, size_t C, size_t R >
		raw_matrix_impl(matrix< M, C, R >&& m):
			dynamic_raw_matrix_impl_base< T >(
				detail::matrix_to_vector< T, 0, 0 >(std::move(m))
			), cols_(m.cols()) {}

		template < typename M, size_t C, size_t R >
		raw_matrix_impl(matrix< M, C, R > const& m):
			dynamic_raw_matrix_impl_base< T >(
				detail::matrix_to_vector< T, 0, 0 >(m)
			), cols_(m.cols()) {}

		template < typename M, size_t C, size_t R >
		constexpr raw_matrix_impl(
			matrix< M, C, R > const& m,
			size_t x,
			size_t y,
			size_t cols,
			size_t rows
		):
			dynamic_raw_matrix_impl_base< T >(
				detail::sub_matrix_to_vector< T >(m, x, y, cols, rows)
			), cols_(cols) {}


		template <
			typename V,
			size_t C1,
			size_t R1,
			typename M,
			size_t C2,
			size_t R2
		> friend constexpr raw_matrix< V, C1, R1 >
		detail::convert(matrix< M, C2, R2 >&& m);

		template <
			typename V,
			size_t C1,
			size_t R1,
			typename M,
			size_t C2,
			size_t R2
		> friend constexpr raw_matrix< V, C1, R1 >
		detail::convert(matrix< M, C2, R2 > const& m);

		template <
			typename V,
			typename M,
			size_t C2,
			size_t R2
		> friend raw_matrix< V, 0, 0 > detail::sub_matrix(
			matrix< M, C2, R2 > const& m,
			size_t x,
			size_t y,
			size_t cols,
			size_t rows
		);
	};



	template < typename T, size_t C, size_t R >
	constexpr raw_matrix< T, C, R > to_matrix(T(&&values)[R][C]){
		return raw_matrix_impl< T, C, R >(std::move(values));
	}

	template < typename T, size_t C, size_t R >
	constexpr raw_matrix< T, C, R > to_matrix(T const(&values)[R][C]){
		return raw_matrix_impl< T, C, R >(values);
	}


	template < typename T, size_t N >
	constexpr raw_matrix< T, N, N > to_square_matrix(T(&&values)[N][N]){
		return to_matrix< T, N, N >(std::move(values));
	}

	template < typename T, size_t N >
	constexpr raw_matrix< T, N, N > to_square_matrix(T const(&values)[N][N]){
		return to_matrix< T, N, N >(values);
	}


	template < typename T, size_t N >
	constexpr raw_col_vector< T, N > to_col_vector(T(&&values)[N]){
		return raw_matrix_impl< T, N, 1 >(std::move(values));
	}

	template < typename T, size_t N >
	constexpr raw_col_vector< T, N > to_col_vector(T const(&values)[N]){
		return raw_matrix_impl< T, N, 1 >(values);
	}


	template < typename T, size_t N >
	constexpr raw_row_vector< T, N > to_row_vector(T(&&values)[N]){
		return raw_matrix_impl< T, 1, N >(std::move(values));
	}

	template < typename T, size_t N >
	constexpr raw_row_vector< T, N > to_row_vector(T const(&values)[N]){
		return raw_matrix_impl< T, 1, N >(values);
	}


	template <
		typename T,
		size_t C1,
		size_t R1,
		typename M,
		size_t C2,
		size_t R2
	> constexpr raw_matrix< T, C1, R1 >
	detail::convert(matrix< M, C2, R2 >&& m){
		static_assert(
			(C1 == 0 || C2 == 0 || C1 == C2) &&
			(R1 == 0 || R2 == 0 || R1 == R2),
			"Matrix dimensions not compatible"
		);

		return raw_matrix_impl< T, C1, R1 >(std::move(m));
	}

	template <
		typename T,
		size_t C1,
		size_t R1,
		typename M,
		size_t C2,
		size_t R2
	> constexpr raw_matrix< T, C1, R1 >
	detail::convert(matrix< M, C2, R2 > const& m){
		static_assert(
			(C1 == 0 || C2 == 0 || C1 == C2) &&
			(R1 == 0 || R2 == 0 || R1 == R2),
			"Matrix dimensions not compatible"
		);

		return raw_matrix_impl< T, C1, R1 >(m);
	}


	template <
		typename T,
		size_t C1,
		size_t R1,
		typename M,
		size_t C2,
		size_t R2
	>
	constexpr raw_matrix< T, C1, R1 > detail::sub_matrix(
		matrix< M, C2, R2 > const& m,
		size_t x,
		size_t y,
		size_ct< C1 > /*cols*/,
		size_ct< R1 > /*rows*/
	){
		static_assert(
			C1 > 0 && R1 > 0,
			"Matrix dimension must be greater than 0"
		);
		return raw_matrix_impl< T, C1, R1 >(m, x, y);
	}

	template <
		typename T,
		size_t R1,
		typename M,
		size_t C2,
		size_t R2
	>
	raw_matrix< T, 0, R1 > detail::sub_matrix(
		matrix< M, C2, R2 > const& m,
		size_t x,
		size_t y,
		size_t cols,
		size_ct< R1 > /*rows*/
	){
		static_assert(R1 > 0, "Matrix rows must be greater than 0");
		return raw_matrix_impl< T, 0, R1 >(m, x, y, cols);
	}

	template <
		typename T,
		size_t C1,
		typename M,
		size_t C2,
		size_t R2
	>
	raw_matrix< T, C1, 0 > detail::sub_matrix(
		matrix< M, C2, R2 > const& m,
		size_t x,
		size_t y,
		size_ct< C1 > /*cols*/,
		size_t rows
	){
		static_assert(C1 > 0, "Matrix cols must be greater than 0");
		return raw_matrix_impl< T, C1, 0 >(m, x, y, rows);
	}

	template <
		typename T,
		typename M,
		size_t C2,
		size_t R2
	>
	raw_matrix< T, 0, 0 > detail::sub_matrix(
		matrix< M, C2, R2 > const& m,
		size_t x,
		size_t y,
		size_t cols,
		size_t rows
	){
		return raw_matrix_impl< T, 0, 0 >(m, x, y, cols, rows);
	}


	template < typename T, size_t C, size_t R >
	raw_matrix< T, 0, R > with_dynamic_cols(raw_matrix< T, C, R >&& m){
		return std::move(m).template as_raw_matrix< T, 0, R >();
	}

	template < typename T, size_t C, size_t R >
	raw_matrix< T, 0, R > with_dynamic_cols(raw_matrix< T, C, R > const& m){
		return m.template as_raw_matrix< T, 0, R >();
	}


	template < typename T, size_t C, size_t R >
	raw_matrix< T, C, 0 > with_dynamic_rows(raw_matrix< T, C, R >&& m){
		return std::move(m).template as_raw_matrix< T, C, 0 >();
	}

	template < typename T, size_t C, size_t R >
	raw_matrix< T, C, 0 > with_dynamic_rows(raw_matrix< T, C, R > const& m){
		return m.template as_raw_matrix< T, C, 0 >();
	}


	template < typename T, size_t C, size_t R >
	raw_matrix< T, 0, 0 > with_dynamic_dims(raw_matrix< T, C, R >&& m){
		return std::move(m).template as_raw_matrix< T, 0, 0 >();
	}

	template < typename T, size_t C, size_t R >
	raw_matrix< T, 0, 0 > with_dynamic_dims(raw_matrix< T, C, R > const& m){
		return m.template as_raw_matrix< T, 0, 0 >();
	}



}

#endif
