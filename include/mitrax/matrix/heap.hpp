//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__matrix__heap__hpp_INCLUDED_
#define _mitrax__matrix__heap__hpp_INCLUDED_

#include "heap_fwd.hpp"

#include <memory>


namespace mitrax::detail{


	template < typename T >
	class array_d{
	public:
		static_assert(!std::is_const_v< T >);

		array_d(): data_(nullptr) {}

		array_d(array_d&& a):
			data_(a.data_),
			size_(a.size_)
		{
			a.data_ = nullptr;
			a.size_ = 0;
		}

		array_d(array_d const& a):
			data_(alloc_.allocate(a.size_)),
			size_(a.size_)
		{
			init_by_iter(data_, size_, a.data_);
		}

		template < typename U, size_t N >
		array_d(array_s< U, N >&& a):
			data_(alloc_.allocate(N)),
			size_(N)
		{
			init_by_iter(data_, size_, std::make_move_iterator(a.data()));
		}

		template < typename U, size_t N >
		array_d(array_s< U, N > const& a):
			data_(alloc_.allocate(N)),
			size_(N)
		{
			init_by_iter(data_, size_, a.data());
		}

		template < typename Iter >
		array_d(Iter iter, size_t n):
			data_(alloc_.allocate(n)),
			size_(n)
		{
			init_by_iter(data_, size_, iter);
		}


		~array_d(){
			destroy();
		}


		array_d& operator=(array_d&& a){
			data_ = a.data_;
			size_ = a.size_;

			a.data_ = nullptr;
			a.size_ = 0;

			return *this;
		}

		array_d& operator=(array_d const& a){
			auto data = alloc_.allocate(a.size_);
			auto size = a.size_;

			init_by_iter(data, size, a.data_);

			destroy();

			data_ = data;
			size_ = a.size_;

			return *this;
		}


		T* data()noexcept{
			return data_;
		}

		T const* data()const noexcept{
			return data_;
		}

		size_t size()const noexcept{
			return size_;
		}


		T& operator[](size_t i){
			return *(data() + i);
		}

		T const& operator[](size_t i)const{
			return *(data() + i);
		}


	private:
		std::allocator< T > alloc_;
		T* data_;
		size_t size_;

		template < typename Iter >
		void init_by_iter(T*& data, size_t& size, Iter iter){
			try{
				std::uninitialized_copy_n(iter, size, data);
			}catch(...){
				alloc_.deallocate(data, size);
				data = nullptr;
				size = 0;
				throw;
			}
		}


		void destroy()noexcept{
			auto const last = data_ + size_;
			for(auto i = data_; i != last; ++i){
				alloc_.destroy(i);
			}

			alloc_.deallocate(data_, size_);
		}
	};


	template < typename T, size_t C, size_t R >
	class heap_matrix_impl: public dims_t< C, R >{
	public:
		static_assert(!std::is_const_v< T >);
		static_assert(!std::is_reference_v< T >);


		/// \brief Type of the data that administrates the matrix
		using value_type = T;

		/// \brief Type with the make functions
		using maker_type = maker::heap_t;


		heap_matrix_impl() = default;

		heap_matrix_impl(heap_matrix_impl&&) = default;

		heap_matrix_impl(heap_matrix_impl const&) = default;

		heap_matrix_impl(
			col_t< C != 0, C > c, row_t< R != 0, R > r,
			detail::array_d< value_type >&& values
		):
			dims_t< C, R >(c, r),
			values_(std::move(values))
			{}


		heap_matrix_impl& operator=(heap_matrix_impl&&) = default;

		heap_matrix_impl& operator=(heap_matrix_impl const&) = default;


		value_type& operator()(size_t x, size_t y){
			return values_[y * this->cols() + x];
		}

		value_type const& operator()(size_t x, size_t y)const{
			return values_[y * this->cols() + x];
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
		array_d< value_type > values_;
	};


}


namespace mitrax::maker{


	template < typename Iter, bool Cct, size_t C, bool Rct, size_t R >
	heap_matrix< iter_type_t< Iter >, Cct ? C : 0, Rct ? R : 0 >
	heap_t::by_sequence(col_t< Cct, C > c, row_t< Rct, R > r, Iter iter)const{
		return {
			init, c, r,
			detail::array_d< iter_type_t< Iter > >(iter, size_t(c) * size_t(r))
		};
	}

	constexpr auto heap = heap_t();


}


#endif
