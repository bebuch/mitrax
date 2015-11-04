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


	namespace detail{ namespace point{


		template < typename TX, typename TY >
		struct point_base{};

		template < typename T >
		struct point_base< T, T >{
			/// \brief Type of the positions
			using value_type = T;
		};


	} }


	/// \brief A class for manipulating points
	/// \tparam TX Type of the x position data
	/// \tparam TY Type of the y position data
	template < typename TX, typename TY = TX >
	class point: public detail::point::point_base< TX, TY >{
	public:
		/// \brief Type of the x positions
		using value_type_x = TX;

		/// \brief Type of the y positions
		using value_type_y = TY;


		/// \brief The x
		constexpr value_type_x& x(){
			return x_;
		}

		/// \brief The y
		constexpr value_type_y& y(){
			return y_;
		}


		/// \brief The x
		constexpr value_type_x const& x()const{
			return x_;
		}

		/// \brief The y
		constexpr value_type_y const& y()const{
			return y_;
		}


		/// \brief Set x and y
		constexpr void set(value_type_x const& x, value_type_y const& y){
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
		constexpr point(value_type_x const& x, value_type_y const& y):
			x_(x), y_(y)
			{}


		/// \brief Copy assignment
		constexpr point& operator=(point const&) = default;

		/// \brief Move assignment
		constexpr point& operator=(point&&) = default;


		/// \brief Get true, if width and height are positiv
		constexpr bool is_positive()const{
			return x() >= value_type_x() && y() >= value_type_y();
		}


	private:
		value_type_x x_;
		value_type_y y_;
	};


}

#endif
