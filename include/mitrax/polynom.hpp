//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__array__hpp_INCLUDED_
#define _mitrax__array__hpp_INCLUDED_

#include "to_array.hpp"


namespace mitrax{


	template < typename T, size_t N >
	class polynom{
	public:
		using value_type = T;


		constexpr polynom(): coefficients_(init_array< N >(T())) {}

		constexpr polynom(T const(&)[N]): coefficients_(to_array< N >(T())) {}


		constexpr value_type& operator[](size_t i){
			return coefficients_[i];
		}

		constexpr value_type const& operator[](size_t i)const{
			return coefficients_[i];
		}


	private:
		std::array< T, N + 1 > coefficients_;
	};


}


#endif
