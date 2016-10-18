//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__matrix__view__hpp_INCLUDED_
#define _mitrax__matrix__view__hpp_INCLUDED_

#include "view_fwd.hpp"
#include "../iterator/utility.hpp"
#include "../detail/concepts.hpp"


namespace mitrax::detail{


	template < typename Object >
	using viewable = decltype(
		mitrax::begin(std::declval< Object >()),
		mitrax::end(std::declval< Object >())
	);


	template < typename Object, bool RowOrder, size_t C, size_t R >
	class view_matrix_impl: public dims_t< C, R >{
	public:
		static_assert(!std::is_const_v< Object >, "use const_view_matrix");
		static_assert(!std::is_reference_v< Object >);
		static_assert(compiles< Object&, viewable >(),
			"Object must support std::begin(object) and std::end(object)");


		/// \brief Type with the make functions
		using maker_type = maker::view_t;

		/// \brief Type of the underlaying object type
		using object_type = Object&;

		/// \brief Type of the data that administrates the matrix
		using value_type = iter_type_t<
			decltype(mitrax::begin(std::declval< object_type >())) >;

		/// \brief Type of a iterator for data
		using iterator = decltype(mitrax::begin(std::declval< object_type >()));

		/// \brief Type of a iterator for const data
		using const_iterator =
			decltype(mitrax::begin(std::declval< Object const& >()));


		static constexpr bool row_memory_order = RowOrder;


		constexpr view_matrix_impl() = delete;

		constexpr view_matrix_impl(view_matrix_impl&&) = delete;

		constexpr view_matrix_impl(
			view_matrix_impl const& other
		)noexcept:
			dims_t< C, R >(other),
			object_(other.object_)
			{}

		constexpr view_matrix_impl(
			col_t< C != 0, C > c, row_t< R != 0, R > r,
			object_type object
		)noexcept:
			dims_t< C, R >(c, r),
			object_(object)
			{}


		constexpr view_matrix_impl&
		operator=(view_matrix_impl&&) = delete;

		constexpr view_matrix_impl&
		operator=(view_matrix_impl const& other) = delete;


		constexpr decltype(auto) operator()(size_t x, size_t y){
			if constexpr(row_memory_order){
				return *(begin() + (y * this->cols() + x));
			}else{
				return *(begin() + (x * this->rows() + y));
			}
		}

		constexpr decltype(auto) operator()(size_t x, size_t y)const{
			if constexpr(row_memory_order){
				return *(begin() + (y * this->cols() + x));
			}else{
				return *(begin() + (x * this->rows() + y));
			}
		}


		constexpr iterator begin(){
			return mitrax::begin(object_);
		}

		constexpr const_iterator begin()const{
			return mitrax::begin(object_);
		}

		constexpr iterator end(){
			return mitrax::end(object_);
		}

		constexpr const_iterator end()const{
			return mitrax::end(object_);
		}


	protected:
		object_type object_;
	};


	template < typename Object, bool RowOrder, size_t C, size_t R >
	class const_view_matrix_impl: public dims_t< C, R >{
	public:
		static_assert(!std::is_reference_v< Object >);
		static_assert(compiles< Object const&, viewable >(),
			"Object must support std::begin(object) and std::end(object)");

		/// \brief Type with the make functions
		using maker_type = maker::const_view_t;

		/// \brief Type of the underlaying object type
		using object_type = Object const&;

		/// \brief Type of the data that administrates the matrix
		using value_type = iter_type_t<
			decltype(mitrax::begin(std::declval< object_type >())) >;

		/// \brief Type of a iterator for data
		using iterator =
			decltype(mitrax::begin(std::declval< object_type >()));

		/// \brief Type of a iterator for const data
		using const_iterator = iterator;


		static constexpr bool row_memory_order = RowOrder;


		constexpr const_view_matrix_impl() = delete;

		constexpr const_view_matrix_impl(const_view_matrix_impl&&)
			= delete;

		constexpr const_view_matrix_impl(
			const_view_matrix_impl const& other
		)noexcept:
			dims_t< C, R >(other),
			object_(other.object_)
			{}

		constexpr const_view_matrix_impl(
			col_t< C != 0, C > c, row_t< R != 0, R > r,
			object_type object
		)noexcept:
			dims_t< C, R >(c, r),
			object_(object)
			{}


		constexpr const_view_matrix_impl&
		operator=(const_view_matrix_impl&&) = delete;

		constexpr const_view_matrix_impl&
		operator=(const_view_matrix_impl const& other) = delete;


		constexpr decltype(auto) operator()(size_t x, size_t y)const{
			if constexpr(row_memory_order){
				return *(begin() + (y * this->cols() + x));
			}else{
				return *(begin() + (x * this->rows() + y));
			}
		}


		constexpr const_iterator begin()const{
			return mitrax::begin(object_);
		}

		constexpr const_iterator end()const{
			return mitrax::end(object_);
		}


	protected:
		object_type object_;
	};


}


namespace mitrax::maker{


	template < typename Object, typename MemoryOrder,
		bool Cct, size_t C, bool Rct, size_t R >
	constexpr auto view_t::by_object(
		col_t< Cct, C > c, row_t< Rct, R > r, Object& object, MemoryOrder
	)const{
		return view_matrix<
			Object, static_cast< bool >(MemoryOrder()), Cct ? C : 0, Rct ? R : 0
		>{init, c, r, object};
	}

	constexpr auto view = view_t();


	template < typename Object, typename MemoryOrder,
		bool Cct, size_t C, bool Rct, size_t R >
	constexpr auto const_view_t::by_object(
		col_t< Cct, C > c, row_t< Rct, R > r, Object const& object, MemoryOrder
	)const{
		return const_view_matrix<
			Object, static_cast< bool >(MemoryOrder()), Cct ? C : 0, Rct ? R : 0
		>{init, c, r, object};
	}

	constexpr auto const_view = const_view_t();


}


namespace mitrax{


	template < typename Object, bool Cct, size_t C, bool Rct, size_t R >
	constexpr auto make_view_matrix(
		col_t< Cct, C > c, row_t< Rct, R > r, Object& object
	){
		return maker::view.by_object(c, r, object);
	}

	template < typename Object, bool Nct, size_t N >
	constexpr auto make_view_matrix(dim_t< Nct, N > n, Object& object){
		return make_view_matrix(n.as_col(), n.as_row(), object);
	}

	template < typename Object, size_t C, size_t R >
	constexpr auto make_view_matrix(dims_t< C, R > const& d, Object& object){
		return make_view_matrix(d.cols(), d.rows(), object);
	}


	template < typename Object, bool Cct, size_t C, bool Rct, size_t R >
	constexpr auto make_const_view_matrix(
		col_t< Cct, C > c, row_t< Rct, R > r, Object const& object
	){
		return maker::const_view.by_object(c, r, object);
	}

	template < typename Object, bool Nct, size_t N >
	constexpr auto make_const_view_matrix(
		dim_t< Nct, N > n, Object const& object
	){
		return make_const_view_matrix(n.as_col(), n.as_row(), object);
	}

	template < typename Object, size_t C, size_t R >
	constexpr auto make_const_view_matrix(
		dims_t< C, R > const& d, Object const& object
	){
		return make_const_view_matrix(d.cols(), d.rows(), object);
	}


}


#endif
