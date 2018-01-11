//-----------------------------------------------------------------------------
// Copyright (c) 2016-2018 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__range__iterator_range__hpp_INCLUDED_
#define _mitrax__range__iterator_range__hpp_INCLUDED_

#include "../range.hpp"
#include "../iterator/flat_iterator.hpp"


namespace mitrax{


	template < typename Iter >
	class iterator_range{
	public:
		using value_type = T;


		constexpr iterator_range(Iter first, Iter last):
			first_(first), last_(last) {}

		constexpr iterator_range(iterator_range const&) = default;

		constexpr iterator_range(iterator_range&&) = default;


		constexpr iterator_range& operator=(iterator_range const&) = default;

		constexpr iterator_range& operator=(iterator_range&&) = default;


		constexpr auto operator[](size_t n)const{
			auto i = first;
			std::advance(i, n);
			return *i;
		}


	private:
		Iter first;
		Iter last;
	};


	template < typename Iter >
	constexpr auto make_range(Iter first, Iter last){
		return iterator_range< Iter >(first, last);
	}

	template < typename Container >
	constexpr auto make_iterator_range(Container& c){
		return make_range(mitrax::begin(c), mitrax::end(c));
	}

	template < typename Container >
	constexpr auto make_iterator_range(Container&& c){
		return make_range(
			mitrax::make_move_iterator(mitrax::begin(c)),
			mitrax::make_move_iterator(mitrax::end(c)));
	}


	namespace detail{


		template < typename T, size_t ... Dims >
		constexpr auto make_flat_range(
			typename flat_iterator< T, Dims ... >::array_type
		){

		}


	}


	template < size_t N, typename T >
	constexpr auto make_flat_range(){

	}


}

#endif
