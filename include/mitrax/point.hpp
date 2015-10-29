//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__point__hpp_INCLUDED_
#define _mitrax__point__hpp_INCLUDED_


namespace mitrax{

	/// \brief A class for manipulating points
	/// \tparam ValueType Type of the position data
	template < typename ValueType >
	class point{
	public:
		/// \brief Type of the positions
		using value_type = ValueType;


		/// \brief The x
		constexpr value_type& x(){
			return x_;
		}

		/// \brief The y
		constexpr value_type& y(){
			return y_;
		}


		/// \brief The x
		constexpr value_type const& x()const{
			return x_;
		}

		/// \brief The y
		constexpr value_type const& y()const{
			return y_;
		}


		/// \brief Set x and y
		constexpr void set(value_type const& x, value_type const& y){
			x_ = x;
			y_ = y;
		}


		/// \brief Constructs a point by (0, 0)
		constexpr point() = default;

		/// \brief Copy constructor
		constexpr point(point const&) = default;

		/// \brief Move constructor
		constexpr point(point&&) = default;

		/// \brief Constructs a point by (x, y)
		constexpr point(value_type const& x, value_type const& y):
			x_(x), y_(y)
			{}


		/// \brief Copy assignment
		constexpr point& operator=(point const&) = default;

		/// \brief Move assignment
		constexpr point& operator=(point&&) = default;


		/// \brief Get true, if width and height are positiv
		constexpr bool is_positive()const{
			return x() >= value_type() && y() >= value_type();
		}


	private:
		value_type x_;
		value_type y_;
	};


}

#endif
