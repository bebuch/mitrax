//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__range__value_view_range__hpp_INCLUDED_
#define _mitrax__range__value_view_range__hpp_INCLUDED_

#include "../range.hpp"


namespace mitrax{


	template < typename T >
	class value_view_range{
	public:
		static_assert(!std::is_reference_v< T >);


		using value_type = T;


		constexpr value_view_range(T const& v): v_(v) {}

		constexpr value_view_range(T&& v): v_(std::move(v)) {}

		constexpr value_view_range(value_view_range const&) = default;

		constexpr value_view_range(value_view_range&&) = default;


		constexpr value_view_range& operator=(value_view_range const&)
			= default;

		constexpr value_view_range& operator=(value_view_range&&) = default;


		constexpr auto operator[](size_t)const{
			return v_;
		}


	private:
		T v_;
	};


	template < typename T >
	constexpr auto make_value_view_range(T const& v){
		return value_view_range< T >(v);
	}

	template < typename T >
	constexpr auto make_value_view_range(T&& v){
		return value_view_range< T >(std::move(v));
	}


}

#endif
