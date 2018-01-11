//-----------------------------------------------------------------------------
// Copyright (c) 2016-2018 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__range__value_factory_range__hpp_INCLUDED_
#define _mitrax__range__value_factory_range__hpp_INCLUDED_

#include "../range.hpp"

#include <tuple>


namespace mitrax{


	template < typename T, typename ... Args >
	class value_factory_range{
	public:
		static_assert(!std::is_reference_v< T >);


		using value_type = T;


		constexpr value_factory_range(std::tuple< Args ... > const& args):
			args_(args) {}

		constexpr value_factory_range(std::tuple< Args ... >&& args):
			args_(std::move(args)) {}

		constexpr value_factory_range(value_factory_range const&) = default;

		constexpr value_factory_range(value_factory_range&&) = default;


		constexpr value_factory_range& operator=(value_factory_range const&)
			= default;

		constexpr value_factory_range& operator=(value_factory_range&&)
			= default;


		constexpr auto operator[](size_t)const{
			return std::make_from_tuple< T >(args_);
		}


	private:
		std::tuple< Args ... > args_;
	};


	template < typename T, typename ... Args >
	constexpr auto make_value_factory_range(std::tuple< Args ... > const& v){
		return value_factory_range< T, Args ... >(v);
	}

	template < typename T, typename ... Args >
	constexpr auto make_value_factory_range(std::tuple< Args ... >&& v){
		return value_factory_range< T, Args ... >(v);
	}


}

#endif
