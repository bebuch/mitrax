//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__detail__array_d__hpp_INCLUDED_
#define _mitrax__detail__array_d__hpp_INCLUDED_

#include "dim.hpp"
#include "array_s.hpp"

#include <memory>


namespace mitrax{ namespace detail{


	template < typename T >
	class array_d{
	public:
		array_d(): value_(nullptr) {}

		array_d(array_d&& a):
			value_(a.value_),
			size_(a.size_)
		{
			a.value_ = nullptr;
			a.size_ = 0;
		}

		array_d(array_d const& a):
			value_(alloc_.allocate(a.size_)),
			size_(a.size_)
		{
			init_by_iter(value_, size_, a.value_);
		}

		array_d(size_t size, T const& v = T()):
			value_(alloc_.allocate(size)),
			size_(size)
		{
			init_by_value(value_, size_, v);
		}

		template < typename U, size_t N >
		array_d(array_s< U, N >&& a):
			value_(alloc_.allocate(N)),
			size_(N)
		{
			init_by_iter(value_, size_, std::make_move_iterator(a.data()));
		}

		template < typename U, size_t N >
		array_d(array_s< U, N > const& a):
			value_(alloc_.allocate(N)),
			size_(N)
		{
			init_by_iter(value_, size_, a.data());
		}

		template < typename Iter >
		array_d(Iter iter, size_t n):
			value_(alloc_.allocate(n)),
			size_(n)
		{
			init_by_iter(value_, size_, iter);
		}


		template < typename F, bool Cct, size_t C, bool Rct, size_t R >
		array_d(col_t< Cct, C > c, row_t< Rct, R > r, fn_i< F >&& f):
			value_(alloc_.allocate(size_t(c) * size_t(r))),
			size_(size_t(c) * size_t(r))
		{
			init_by_fn(value_, size_, std::move(f));
		}

		template < typename F, bool Cct, size_t C, bool Rct, size_t R >
		array_d(col_t< Cct, C > c, row_t< Rct, R > r, fn_xy< F >&& f):
			value_(alloc_.allocate(size_t(c) * size_t(r))),
			size_(size_t(c) * size_t(r))
		{
			init_by_fn(value_, size_, c, std::move(f));
		}


		~array_d(){
			destroy();
		}


		array_d& operator=(array_d&& a){
			value_ = a.value_;
			size_ = a.size_;

			a.value_ = nullptr;
			a.size_ = 0;

			return *this;
		}

		array_d& operator=(array_d const& a){
			auto value = alloc_.allocate(a.size_);

			try{
				std::uninitialized_copy_n(a.value_, a.size_, value);
			}catch(...){
				alloc_.deallocate(value, a.size_);
				throw;
			}

			destroy();

			value_ = value;
			size_ = a.size_;

			return *this;
		}


		T* data()noexcept{
			return value_;
		}

		T const* data()const noexcept{
			return value_;
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
		T* value_;
		size_t size_;

		template < typename Iter >
		void init_by_iter(T*& value, size_t& size, Iter iter){
			try{
				std::uninitialized_copy_n(iter, size, value);
			}catch(...){
				alloc_.deallocate(value, size);
				value = nullptr;
				size = 0;
				throw;
			}
		}

		template < typename U >
		void init_by_value(T*& value, size_t& size, U const& v){
			try{
				std::uninitialized_fill_n(value, size, v);
			}catch(...){
				alloc_.deallocate(value, size);
				value = nullptr;
				size = 0;
				throw;
			}
		}

		template < typename F >
		void init_by_fn(T*& value, size_t& size, fn_i< F >&& f){
			size_t n = 0;
			try{
				for(; n < size; ++n){
					alloc_.construct(value + n, f(n));
				}
			}catch(...){
				for(size_t i = 0; i < n; ++i){
					alloc_.destroy(value + i);
				}

				alloc_.deallocate(value, size);
				value = nullptr;
				size = 0;
				throw;
			}
		}

		template < typename F >
		void init_by_fn(T*& value, size_t& size, size_t cols, fn_xy< F >&& f){
			size_t n = 0;
			try{
				for(; n < size; ++n){
					alloc_.construct(value + n, f(n % cols, n / cols));
				}
			}catch(...){
				for(size_t i = 0; i < n; ++i){
					alloc_.destroy(value + i);
				}

				alloc_.deallocate(value, size);
				value = nullptr;
				size = 0;
				throw;
			}
		}

		void destroy()noexcept{
			auto const last = value_ + size_;
			for(auto i = value_; i != last; ++i){
				alloc_.destroy(i);
			}

			alloc_.deallocate(value_, size_);
		}

	};


} }


#endif
