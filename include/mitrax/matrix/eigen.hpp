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


	template < typename T, col_t C, row_t R >
	class eigen_matrix_impl final: auto_dim_pair_t< C, R >{
	public:
		static_assert(!std::is_const_v< T >);
		static_assert(!std::is_reference_v< T >);


		/// \brief Type of the data that administrates the matrix
		using value_type = T;

		/// \brief Type with the make functions
		using maker_type = maker::eigen_t;

		/// \brief Type of the underlaying Eigen matrix
		using eigen_type = ::Eigen::Matrix< value_type,
			R == 0_R ? ::Eigen::Dynamic : static_cast< int >(R),
			C == 0_C ? ::Eigen::Dynamic : static_cast< int >(C) >;


		eigen_matrix_impl(default_constructor_key)
			// TODO: Initialize Elements???
			{}

		eigen_matrix_impl(eigen_matrix_impl&&) = default;

		eigen_matrix_impl(eigen_matrix_impl const&) = default;

		eigen_matrix_impl(
			col< C != 0_C, C > c, row< R != 0_R, R > r,
			eigen_type&& values
		):
			auto_dim_pair_t< C, R >(c, r),
			values_(std::move(values))
			{}


		eigen_matrix_impl& operator=(eigen_matrix_impl&&) = default;

		eigen_matrix_impl& operator=(eigen_matrix_impl const&) = default;


		using auto_dim_pair_t< C, R >::cols;
		using auto_dim_pair_t< C, R >::rows;


		value_type& operator()(c_t c, r_t r){
			return values_(size_t(r), size_t(c));
		}

		value_type const& operator()(c_t c, r_t r)const{
			return values_(size_t(r), size_t(c));
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


	private:
		eigen_type values_;
	};


	template < typename Iter, bool Cct, col_t C, bool Rct, row_t R >
	auto to_eigen_matrix_data(col< Cct, C > c, row< Rct, R > r, Iter iter){
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


	template < typename Iter, bool Cct, col_t C, bool Rct, row_t R >
	eigen_matrix< iter_type_t< Iter >, Cct ? C : 0_C, Rct ? R : 0_R >
	eigen_t::by_sequence(col< Cct, C > c, row< Rct, R > r, Iter iter)const{
		return {init, c, r, detail::to_eigen_matrix_data(c, r, iter)};
	}

	constexpr auto eigen = eigen_t();


}


#endif
