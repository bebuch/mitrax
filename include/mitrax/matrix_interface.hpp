//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__matrix_interface__hpp_INCLUDED_
#define _mitrax__matrix_interface__hpp_INCLUDED_

#include "dim.hpp"
#include "point.hpp"
#include "matrix_fwd.hpp"

#include <utility>
#include <cassert>
#include <algorithm>


namespace mitrax{


	template < typename M >
	class matrix{
	public:
// 		static_assert(
// 			std::is_base_of_v< matrix, M >,
// 			"M must be derived from matrix"
// 		);

		/// M needs:
		/// - a typedef dimension_type of type dims_t

		// TODO: Check if M is a matrix_impl type!!!

		/// \brief Type of derived class
		using self_type = M;

		/// \brief Unsigned integral type (size_t)
		using size_type = size_t;

		/// \brief Signed integer type (std::ptrdiff_t)
		using difference_type = std::ptrdiff_t;

		/// \brief Type of points in the matrix
		using point_type = point< size_t >;

		/// \brief Type of a reference to data
		using reference = typename M::value_type&;

		/// \brief Type of a reference to const data
		using const_reference = typename M::value_type const&;

		/// \brief Type of a pointer to data
		using pointer = typename M::value_type*;

		/// \brief Type of a pointer to const data
		using const_pointer = typename M::value_type const*;

		/// \brief Type of a iterator for data
		using iterator = typename M::iterator;

		/// \brief Type of a iterator for const data
		using const_iterator = typename M::const_iterator;

		/// \brief Type of a reverse iterator for data
		using reverse_iterator = typename M::reverse_iterator;

		/// \brief Type of a reverse iterator for const data
		using const_reverse_iterator = typename M::const_reverse_iterator;


		constexpr matrix() = default;

		constexpr matrix(matrix&&) = default;

		constexpr matrix(matrix const&) = default;


		constexpr matrix& operator=(matrix&&) = default;

		constexpr matrix& operator=(matrix const&) = default;


		constexpr auto cols()const noexcept{
			return m().cols();
		}

		constexpr auto rows()const noexcept{
			return m().rows();
		}

		constexpr auto dims()const noexcept{
			return mitrax::dims(cols(), rows());
		}

		constexpr size_t point_count()const noexcept{
			return size_t(cols()) * size_t(rows());
		}


		constexpr decltype(auto) operator()(size_t x, size_t y){
			assert(x < cols());
			assert(y < rows());
			return m()(x, y);
		}

		constexpr decltype(auto) operator()(size_t x, size_t y)const{
			assert(x < cols());
			assert(y < rows());
			return m()(x, y);
		}


		constexpr decltype(auto) operator[](size_t i){
			static_assert(
				is_vector_v< M >,
				"access operator only allowed for compile time dim vectors"
			);

			if(is_value_v< M >){
				assert(i == 0);
				return m()(0, 0);
			}else if(is_col_vector_v< M >){
				return m()(0, i);
			}else{
				return m()(i, 0);
			}
		}

		constexpr decltype(auto) operator[](size_t i)const{
			static_assert(
				is_vector_v< M >,
				"access operator only allowed for compile time dim vectors"
			);

			if(is_value_v< M >){
				assert(i == 0);
				return m()(0, 0);
			}else if(is_col_vector_v< M >){
				return m()(0, i);
			}else{
				return m()(i, 0);
			}
		}


		constexpr operator typename M::value_type()const{
			static_assert(
				is_value_v< M >,
				"value conversion is only allowed for compile time dim "
				"matrices with one element"
			);

			return m()(0, 0);
		}


		constexpr iterator begin(){
			return m().begin();
		}

		constexpr const_iterator begin()const{
			return m().begin();
		}

		constexpr iterator end(){
			return m().end();
		}

		constexpr const_iterator end()const{
			return m().end();
		}

		constexpr reverse_iterator rbegin(){
			return m().rbegin();
		}

		constexpr const_reverse_iterator rbegin()const{
			return m().rbegin();
		}

		constexpr reverse_iterator rend(){
			return m().rend();
		}

		constexpr const_reverse_iterator rend()const{
			return m().rend();
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


		constexpr auto data(){
			static_assert(
				has_data< M >::value,
				"The underlaying matrix implementation doesn't support "
				"m.data()"
			);
			return m().data();
		}

		constexpr auto data()const{
			static_assert(
				has_data< M const >::value,
				"The underlaying matrix implementation doesn't support "
				"m.data()const"
			);
			return m().data();
		}


	private:
		template < bool Cct, size_t C, bool Rct, size_t R >
		constexpr void check_dims(col_t< Cct, C > c, row_t< Rct, R > r)const{
			static_assert(
				(M::dimension_type::ct_cols == 0 || !Cct ||
					M::dimension_type::ct_cols == C) &&
				(M::dimension_type::ct_rows == 0 || !Rct ||
					M::dimension_type::ct_rows == R),
				"matrix dimensions not compatible"
			);

			if(cols() != c || rows() != r){
				throw std::logic_error("matrix dimensions not compatible");
			}
		}


		constexpr M& m(){
			return static_cast< M& >(*this);
		}

		constexpr M const& m()const{
			return static_cast< M const& >(*this);
		}


		template< typename T, typename = void >
		struct has_data: std::false_type{};

		template< typename T >
		struct has_data< T, decltype(
			static_cast< std::conditional_t<
				std::is_const< T >::value, value_type const*, value_type*
			> >(std::declval< T >().data()), void())
		>: std::true_type{};
	};


	template < typename M >
	struct is_matrix:
		std::bool_constant< std::is_base_of_v< matrix< M >, M > >{};

	template < typename M >
	constexpr bool is_matrix_v = is_matrix< M >::value;


	template < typename M >
	struct enable_matrix: std::enable_if< is_matrix_v< M > >{};

	template < typename M >
	using enable_matrix_t = typename enable_matrix< M >::type;


	template < typename ... M >
	constexpr auto get_cols(M const& ... m){
		return get(m.cols() ...);
	}

	template < typename ... M >
	constexpr auto get_rows(M const& ... m){
		return get(m.rows() ...);
	}

	template < typename ... M >
	constexpr auto get_dims(M const& ... m){
		return get(m.dims() ...);
	}



}

#endif
