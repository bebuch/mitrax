//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__interger__hpp_INCLUDED_
#define _mitrax__interger__hpp_INCLUDED_

#include <cstddef>


namespace mitrax{


	using size_t = std::size_t;

	using ptrdiff_t = std::ptrdiff_t;


	template < typename T, T V >
	struct integral_constant{
		static constexpr T value = V;

		using value_type = T;

		using type = integral_constant;

		constexpr operator value_type()const noexcept{
			return value;
		}

		constexpr value_type operator()()const noexcept{
			return value;
		}
	};


	template < size_t I >
	using size_ct = integral_constant< size_t, I >;

	template < ptrdiff_t I >
	using ptrdiff_ct = integral_constant< ptrdiff_t, I >;


	namespace literals{


		namespace detail{


			// Adopted from Boost Hana
			template < typename T, size_t N >
			constexpr T parse(char const(&arr)[N]){
				T number = 0;
				T base = 1;
				for(size_t i = 0; i < N; ++i){
					number += (static_cast< int >(arr[N - 1 - i]) - 48) * base;
					base *= 10;
				}
				return number;
			}


		}


		// Adopted from Boost Hana
		template < char ... C >
		constexpr auto operator"" _dim(){
			return size_ct< detail::parse< size_t, sizeof...(C) >({C ...}) >();
		}

		// Adopted from Boost Hana
		template < char ... C >
		constexpr auto operator"" _diff(){
			return ptrdiff_ct< detail::parse< ptrdiff_t, sizeof...(C) >({C ...}) >();
		}


	}


}


#endif
