//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__variable__hpp_INCLUDED_
#define _mitrax__variable__hpp_INCLUDED_

#include <boost/optional.hpp>

#include <type_traits>
#include <utility>
#include <ostream>


namespace mitrax{


	template < typename T >
	class variable{
	public:
		static_assert(
			!std::is_same< T, bool >::value,
			"bool is not supported"
		);

		variable() = default;

		variable(variable&&) = default;

		variable(variable const&) = default;

		variable(T&& v): value_(std::move(v)) {}

		variable(T const& v): value_(v) {}


		operator T()&&{
			return value_ ? std::move(*value_) : T();
		}

		operator T()const&{
			return value_ ? *value_ : T();
		}

		operator bool()const{
			return static_cast< bool >(value_);
		}


		variable& operator=(variable&&) = default;

		variable& operator=(variable const&) = default;

		variable& operator=(T&& v){
			value_ = std::move(v);
			return *this;
		}

		variable& operator=(T const& v){
			value_ = v;
			return *this;
		}


	private:
		boost::optional< T > value_;
	};


	template < typename T >
	std::ostream& operator<<(std::ostream& os, variable< T > const& value){
		os << static_cast< T >(value);
		return os;
	}


}


#endif
