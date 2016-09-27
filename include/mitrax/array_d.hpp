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


} }


#endif
