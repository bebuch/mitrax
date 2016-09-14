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
			size_(0)
		{
			std::uninitialized_copy_n(a.value_, a.size_, value_);
			size_ = a.size_;
		}

		array_d(size_t size, T const& v = T()):
			value_(alloc_.allocate(size)),
			size_(0)
		{
			std::uninitialized_fill_n(value_, size, v);
			size_ = size;
		}

		template < typename U >
		array_d(array_d< U >&& a):
			value_(alloc_.allocate(a.size())),
			size_(0)
		{
			std::uninitialized_copy_n(
				std::make_move_iterator(a.data()), a.size(), value_
			);
			size_ = a.size();
		}

		template < typename U >
		array_d(array_d< U >& a):
			value_(alloc_.allocate(a.size())),
			size_(0)
		{
			std::uninitialized_copy_n(a.data(), a.size(), value_);
			size_ = a.size();
		}

		template < typename U >
		array_d(array_d< U > const& a):
			value_(alloc_.allocate(a.size())),
			size_(0)
		{
			std::uninitialized_copy_n(a.data(), a.size(), value_);
			size_ = a.size();
		}

		template < typename U, size_t N >
		array_d(array_s< U, N >&& a):
			value_(alloc_.allocate(N)),
			size_(0)
		{
			std::uninitialized_copy_n(
				std::make_move_iterator(a.data()), N, value_
			);
			size_ = N;
		}

		template < typename U, size_t N >
		array_d(array_s< U, N >& a):
			value_(alloc_.allocate(N)),
			size_(0)
		{
			std::uninitialized_copy_n(a.data(), N, value_);
			size_ = N;
		}

		template < typename U, size_t N >
		array_d(array_s< U, N > const& a):
			value_(alloc_.allocate(N)),
			size_(0)
		{
			std::uninitialized_copy_n(a.data(), N, value_);
			size_ = N;
		}

		template < typename Iter >
		array_d(Iter iter, size_t n):
			value_(alloc_.allocate(n)),
			size_(0)
		{
			std::uninitialized_copy_n(iter, n, value_);
			size_ = n;
		}


		template < typename F, bool Cct, size_t C, bool Rct, size_t R >
		array_d(col_t< Cct, C > c, row_t< Rct, R > r, fn_i< F >&& f):
			value_(alloc_.allocate(size_t(c) * size_t(r))),
			size_(0)
		{
			auto n = size_t(c) * size_t(r);
			for(size_t i = 0; i < n; ++i){
				alloc_.construct(value_ + i, f(i));
				++size_;
			}
		}

		template < typename F, bool Cct, size_t C, bool Rct, size_t R >
		array_d(col_t< Cct, C > c, row_t< Rct, R > r, fn_xy< F >&& f):
			value_(alloc_.allocate(size_t(c) * size_t(r))),
			size_(0)
		{
			for(size_t y = 0; y < r; ++y){
				for(size_t x = 0; x < c; ++x){
					alloc_.construct(value_ + y * c + x, f(x, y));
					++size_;
				}
			}
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

		void destroy()noexcept{
			auto first = reinterpret_cast< T* >(value_);
			auto const last = value_ + size_;

			for(; first != last; ++first){
				alloc_.destroy(first);
			}

			alloc_.deallocate(value_, size_);
		}

	};


} }


#endif
