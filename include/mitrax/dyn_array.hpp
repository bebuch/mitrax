//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__dyn_array__hpp_INCLUDED_
#define _mitrax__dyn_array__hpp_INCLUDED_

#include "dim.hpp"

#include <memory>


namespace mitrax{


	template < typename T >
	class dyn_array{
	public:
		dyn_array(): value_(nullptr) {}

		dyn_array(dyn_array&& a):
			value_(a.value_),
			size_(a.size_)
		{
			a.value_ = nullptr;
			a.size_ = 0;
		}

		dyn_array(dyn_array const& a):
			value_(alloc_.allocate(a.size_)),
			size_(0)
		{
			std::uninitialized_copy_n(a.value_, a.size_, value_);
			size_ = a.size_;
		}

		dyn_array(size_t size, T const& v = T()):
			value_(alloc_.allocate(size)),
			size_(0)
		{
			std::uninitialized_fill_n(value_, size, v);
			size_ = size;
		}

		template < typename U >
		dyn_array(dyn_array< U >&& a):
			value_(alloc_.allocate(a.size())),
			size_(0)
		{
			std::uninitialized_copy_n(
				std::make_move_iterator(a.data()), a.size(), value_
			);
			size_ = a.size();
		}

		template < typename U >
		dyn_array(dyn_array< U >& a):
			value_(alloc_.allocate(a.size())),
			size_(0)
		{
			std::uninitialized_copy_n(a.data(), a.size(), value_);
			size_ = a.size();
		}

		template < typename U >
		dyn_array(dyn_array< U > const& a):
			value_(alloc_.allocate(a.size())),
			size_(0)
		{
			std::uninitialized_copy_n(a.data(), a.size(), value_);
			size_ = a.size();
		}

		template < typename U, size_t N >
		dyn_array(std::array< U, N >&& a):
			value_(alloc_.allocate(N)),
			size_(0)
		{
			std::uninitialized_copy_n(
				std::make_move_iterator(a.data()), N, value_
			);
			size_ = N;
		}

		template < typename U, size_t N >
		dyn_array(std::array< U, N >& a):
			value_(alloc_.allocate(N)),
			size_(0)
		{
			std::uninitialized_copy_n(a.data(), N, value_);
			size_ = N;
		}

		template < typename U, size_t N >
		dyn_array(std::array< U, N > const& a):
			value_(alloc_.allocate(N)),
			size_(0)
		{
			std::uninitialized_copy_n(a.data(), N, value_);
			size_ = N;
		}

		template < size_t N >
		dyn_array(T(&&v)[N]):
			value_(alloc_.allocate(N)),
			size_(0)
		{
			std::uninitialized_copy_n(std::make_move_iterator(v), N, value_);
			size_ = N;
		}

		template < size_t N >
		dyn_array(T const(&v)[N]):
			value_(alloc_.allocate(N)),
			size_(0)
		{
			std::uninitialized_copy_n(v, N, value_);
			size_ = N;
		}

		template < size_t C, size_t R >
		dyn_array(T(&&v)[R][C]):
			value_(alloc_.allocate(C * R)),
			size_(0)
		{
			for(size_t i = 0; i < R; ++i){
				std::uninitialized_copy_n(
					std::make_move_iterator(v[i]), C, value_ + i * C
				);
				size_ += C;
			}
		}

		template < size_t C, size_t R >
		dyn_array(T const(&v)[R][C]):
			value_(alloc_.allocate(C * R)),
			size_(0)
		{
			for(size_t i = 0; i < R; ++i){
				std::uninitialized_copy_n(v[i], C, value_ + i * C);
				size_ += C;
			}
		}

		template < typename F, bool Nct, size_t N >
		dyn_array(dim_t< Nct, N > n, F const& f):
			value_(alloc_.allocate(n)),
			size_(0)
		{
			for(size_t i = 0; i < n; ++i){
				alloc_.construct(value_ + i, f(i));
				++size_;
			}
		}

		template < typename F, bool Cct, size_t C, bool Rct, size_t R >
		dyn_array(col_t< Cct, C > c, row_t< Rct, R > r, F const& f):
			value_(alloc_.allocate(size_t(c) * size_t(r))),
			size_(0)
		{
			for(size_t ir = 0; ir < r; ++ir){
				for(size_t ic = 0; ic < c; ++ic){
					alloc_.construct(value_ + ir * c + ic, f(ic, ir));
					++size_;
				}
			}
		}


		~dyn_array(){
			destroy();
		}


		dyn_array& operator=(dyn_array&& a){
			value_ = a.value_;
			size_ = a.size_;

			a.value_ = nullptr;
			a.size_ = 0;

			return *this;
		}

		dyn_array& operator=(dyn_array const& a){
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

		void destroy()noexcept{
			auto first = reinterpret_cast< T* >(value_);
			auto const last = value_ + size_;

			for(; first != last; ++first){
				alloc_.destroy(first);
			}

			alloc_.deallocate(value_, size_);
		}

	};


}


#endif
