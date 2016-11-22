//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__matrix__eigen__hpp_INCLUDED_
#define _mitrax__matrix__eigen__hpp_INCLUDED_

#include "eigen_fwd.hpp"

#include <Eigen/Core>


namespace mitrax::detail{


	template < typename T, size_t C, size_t R >
	class eigen_matrix_impl: dims_t< C, R >{
	public:
		static_assert(!std::is_const_v< T >);
		static_assert(!std::is_reference_v< T >);


		/// \brief Type of the data that administrates the matrix
		using value_type = T;

		/// \brief Type with the make functions
		using maker_type = maker::eigen_t;

		/// \brief Type of the underlaying Eigen matrix
		using eigen_type = ::Eigen::Matrix< value_type,
			R == 0 ? ::Eigen::Dynamic : static_cast< int >(R),
			C == 0 ? ::Eigen::Dynamic : static_cast< int >(C) >;


		eigen_matrix_impl() = default;

		eigen_matrix_impl(eigen_matrix_impl&&) = default;

		eigen_matrix_impl(eigen_matrix_impl const&) = default;

		eigen_matrix_impl(
			col_t< C != 0, C > c, row_t< R != 0, R > r,
			eigen_type&& values
		):
			dims_t< C, R >(c, r),
			values_(std::move(values))
			{}


		eigen_matrix_impl& operator=(eigen_matrix_impl&&) = default;

		eigen_matrix_impl& operator=(eigen_matrix_impl const&) = default;


		using dims_t< C, R >::cols;
		using dims_t< C, R >::rows;


		value_type& operator()(size_t x, size_t y){
			return values_(y, x);
		}

		value_type const& operator()(size_t x, size_t y)const{
			return values_(y, x);
		}


		value_type* data(){
			return values_.data();
		}

		value_type const* data()const{
			return values_.data();
		}


		template < typename Iter >
		void reinit_iter(Iter iter){
			*this = maker_type().by_sequence
				(this->cols(), this->rows(), iter).impl();
		}


	protected:
		eigen_type values_;
	};


	template < typename Iter, bool Cct, size_t C, bool Rct, size_t R >
	auto to_eigen_matrix_data(col_t< Cct, C > c, row_t< Rct, R > r, Iter iter){
		::Eigen::Matrix< iter_type_t< Iter >,
			Rct ? static_cast< int >(R) : ::Eigen::Dynamic,
			Cct ? static_cast< int >(C) : ::Eigen::Dynamic > data(
				static_cast< int >(size_t(r)), static_cast< int >(size_t(c))
			);

		auto const count = size_t(c) * size_t(r);
		for(size_t i = 0; i < count; ++i, ++iter){
			data(i / size_t(c), i % size_t(c)) = *iter;
		}

		return data;
	}


}


namespace mitrax::maker{


	template < typename Iter, bool Cct, size_t C, bool Rct, size_t R >
	eigen_matrix< iter_type_t< Iter >, Cct ? C : 0, Rct ? R : 0 >
	eigen_t::by_sequence(col_t< Cct, C > c, row_t< Rct, R > r, Iter iter)const{
		return {init, c, r, detail::to_eigen_matrix_data(c, r, iter)};
	}

	constexpr auto eigen = eigen_t();


}


#endif
