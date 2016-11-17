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


	template < typename T >
	using viewable = decltype(
		mitrax::begin(std::declval< T >()),
		mitrax::end(std::declval< T >())
	);


	template < typename T, bool RowOrder, size_t C, size_t R >
	class view_matrix_impl: public dims_t< C, R >{
	public:
		static_assert(!std::is_const_v< T >, "use const_view_matrix");
		static_assert(!std::is_reference_v< T >);
		static_assert(compiles< T&, viewable >(),
			"T must support std::begin(object) and std::end(object)");


		/// \brief Type with the make functions
		using maker_type = maker::view_t;

		/// \brief Type of the underlaying object type
		using object_type = T;

		/// \brief Type of the data that administrates the matrix
		using value_type = iter_type_t<
			decltype(mitrax::begin(std::declval< T& >())) >;


		static constexpr bool row_memory_order = RowOrder;


		constexpr view_matrix_impl() = delete;

		constexpr view_matrix_impl(view_matrix_impl&&) noexcept
			= default;

		constexpr view_matrix_impl(view_matrix_impl const& other) noexcept
			= default;

		constexpr view_matrix_impl(
			col_t< C != 0, C > c, row_t< R != 0, R > r,
			T& object
		)noexcept:
			dims_t< C, R >(c, r),
			object_(&object)
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


		constexpr decltype(auto) begin()
		noexcept(noexcept(mitrax::begin(std::declval< T& >()))){
			return mitrax::begin(*object_);
		}

		constexpr decltype(auto) begin()const
		noexcept(noexcept(mitrax::begin(std::declval< T const& >()))){
			return mitrax::begin(*object_);
		}

		constexpr decltype(auto) end()
		noexcept(noexcept(mitrax::end(std::declval< T& >()))){
			return mitrax::end(*object_);
		}

		constexpr decltype(auto) end()const
		noexcept(noexcept(mitrax::end(std::declval< T const& >()))){
			return mitrax::end(*object_);
		}


		template < typename dummy = int, std::enable_if_t<
				std::is_array_v< T > || has_data_v< value_type*, T >,
				dummy > = 0 >
		constexpr value_type* data()noexcept{
			if constexpr(std::is_array_v< T >){
				return *object_;
			}else{
				return object_->data();
			}
		}

		constexpr value_type const* data()const noexcept{
			if constexpr(std::is_array_v< T >){
				return *object_;
			}else{
				static_assert(
					has_data_v< value_type const*, T const >,
					"The underlaying object type doesn't support "
					"'value_type const* m.data()const'"
				);

				return object_->data();
			}
		}


	protected:
		T* object_;
	};


	template < typename T, bool RowOrder, size_t C, size_t R >
	class const_view_matrix_impl: public dims_t< C, R >{
	public:
		static_assert(!std::is_const_v< T >,
			"Use T without const qualifier");
		static_assert(!std::is_reference_v< T >);
		static_assert(compiles< T const&, viewable >(),
			"T must support std::begin(object) and std::end(object)");

		/// \brief Type with the make functions
		using maker_type = maker::const_view_t;

		/// \brief Type of the underlaying object type
		using object_type = T;

		/// \brief Type of the data that administrates the matrix
		using value_type = iter_type_t<
			decltype(mitrax::begin(std::declval< T const& >())) >;


		static constexpr bool row_memory_order = RowOrder;


		constexpr const_view_matrix_impl() = delete;

		constexpr const_view_matrix_impl(const_view_matrix_impl&&)
			noexcept = default;

		constexpr const_view_matrix_impl(const_view_matrix_impl const& other)
			noexcept = default;

		constexpr const_view_matrix_impl(
			col_t< C != 0, C > c, row_t< R != 0, R > r,
			T const& object
		)noexcept:
			dims_t< C, R >(c, r),
			object_(&object)
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


		constexpr decltype(auto) begin()const
		noexcept(noexcept(mitrax::begin(std::declval< T const& >()))){
			return mitrax::begin(*object_);
		}

		constexpr decltype(auto) end()const
		noexcept(noexcept(mitrax::end(std::declval< T const& >()))){
			return mitrax::end(*object_);
		}


		constexpr value_type const* data()const noexcept{
			if constexpr(std::is_array_v< T >){
				return *object_;
			}else{
				static_assert(
					has_data_v< value_type const*, T const >,
					"The underlaying object type doesn't support "
					"'value_type const* m.data()const'"
				);

				return object_->data();
			}
		}


	protected:
		T const* object_;
	};


}


namespace mitrax::maker{


	template < typename T, typename MemoryOrder,
		bool Cct, size_t C, bool Rct, size_t R >
	constexpr auto view_t::by_object(
		col_t< Cct, C > c, row_t< Rct, R > r, T& object, MemoryOrder
	)const{
		return view_matrix<
			T, static_cast< bool >(MemoryOrder()), Cct ? C : 0, Rct ? R : 0
		>{init, c, r, object};
	}

	constexpr auto view = view_t();


	template < typename T, typename MemoryOrder,
		bool Cct, size_t C, bool Rct, size_t R >
	constexpr auto const_view_t::by_object(
		col_t< Cct, C > c, row_t< Rct, R > r, T const& object, MemoryOrder
	)const{
		return const_view_matrix<
			T, static_cast< bool >(MemoryOrder()), Cct ? C : 0, Rct ? R : 0
		>{init, c, r, object};
	}

	constexpr auto const_view = const_view_t();


}


namespace mitrax{


	template < typename T, bool Cct, size_t C, bool Rct, size_t R >
	constexpr auto make_view_matrix(
		col_t< Cct, C > c, row_t< Rct, R > r, T& object
	){
		return maker::view.by_object(c, r, object);
	}

	template < typename T, bool Nct, size_t N >
	constexpr auto make_view_matrix(dim_t< Nct, N > n, T& object){
		return make_view_matrix(n.as_col(), n.as_row(), object);
	}

	template < typename T, size_t C, size_t R >
	constexpr auto make_view_matrix(dims_t< C, R > const& d, T& object){
		return make_view_matrix(d.cols(), d.rows(), object);
	}


	template < typename T, bool Cct, size_t C, bool Rct, size_t R >
	constexpr auto make_const_view_matrix(
		col_t< Cct, C > c, row_t< Rct, R > r, T const& object
	){
		return maker::const_view.by_object(c, r, object);
	}

	template < typename T, bool Nct, size_t N >
	constexpr auto make_const_view_matrix(
		dim_t< Nct, N > n, T const& object
	){
		return make_const_view_matrix(n.as_col(), n.as_row(), object);
	}

	template < typename T, size_t C, size_t R >
	constexpr auto make_const_view_matrix(
		dims_t< C, R > const& d, T const& object
	){
		return make_const_view_matrix(d.cols(), d.rows(), object);
	}


}


#endif
