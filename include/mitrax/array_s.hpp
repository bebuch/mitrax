//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__detail__array_s__hpp_INCLUDED_
#define _mitrax__detail__array_s__hpp_INCLUDED_

#include <cstddef>


namespace mitrax{ namespace detail{


	template < typename T, size_t N >
	struct array_s{
		T elems[N]; // exposition only

		// element access:
		constexpr T& operator[](std::size_t n){ return elems[n]; }

		constexpr T const& operator[](std::size_t n)const{ return elems[n]; }

		constexpr T& at(std::size_t n){
			if(n >= N) throw std::out_of_range("array_s");
			return elems[n];
		}

		constexpr T const& at(std::size_t n)const{
			if(n >= N) throw std::out_of_range("array_s");
			return elems[n];
		}

		constexpr T& front(){ return elems[0]; }

		constexpr T const& front()const{ return elems[0]; }

		constexpr T& back(){ return elems[N - 1]; }

		constexpr T const& back()const{ return elems[N - 1]; }

		constexpr T* data()noexcept{ return elems; }

		constexpr T const* data()const noexcept{ return elems; }
	};


} }


#endif
