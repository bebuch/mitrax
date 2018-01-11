//-----------------------------------------------------------------------------
// Copyright (c) 2015-2018 Benjamin Buch
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


	/// \brief A class for representing points
	/// \tparam TX Type of the x position data
	/// \tparam TY Type of the y position data
	template < typename TX, typename TY = TX >
	class point: public detail::point::point_base< TX, TY >{
	public:
		/// \brief Type of the x positions
		using x_value_type = TX;

		/// \brief Type of the y positions
		using y_value_type = TY;


		/// \brief The x
		constexpr x_value_type& x(){ return x_; }

		/// \brief The y
		constexpr y_value_type& y(){ return y_; }


		/// \brief The x
		constexpr x_value_type const& x()const{ return x_; }

		/// \brief The y
		constexpr y_value_type const& y()const{ return y_; }


		/// \brief Set x and y
		constexpr void set(x_value_type const& x, y_value_type const& y){
			x_ = x;
			y_ = y;
		}


		/// \brief Constructs a point by (0, 0)
		constexpr point(): x_(), y_() {}

		/// \brief Copy constructor
		constexpr point(point const&) = default;

		/// \brief Move constructor
		constexpr point(point&&) = default;

		/// \brief Constructs a point by (x, y)
		constexpr point(x_value_type const& x, y_value_type const& y):
			x_(x), y_(y)
			{}


		/// \brief Copy assignment
		constexpr point& operator=(point const&) = default;

		/// \brief Move assignment
		constexpr point& operator=(point&&) = default;


		/// \brief Get true, if x and y are positiv
		constexpr bool is_positive()const{
			return x() >= x_value_type() && y() >= y_value_type();
		}


	private:
		x_value_type x_;
		y_value_type y_;
	};


	template < typename TX, typename TY >
	constexpr bool operator==(
		point< TX, TY > const& a,
		point< TX, TY > const& b
	){
		return a.x() == b.x() && a.y() == b.y();
	}

	template < typename TX, typename TY >
	constexpr bool operator!=(
		point< TX, TY > const& a,
		point< TX, TY > const& b
	){
		return !(a == b);
	}


	template < typename TX, typename TY >
	constexpr point< TX, TY >& operator+=(
		point< TX, TY >& a,
		point< TX, TY > const& b
	){
		a.x() += b.x();
		a.y() += b.y();
		return a;
	}

	template < typename TX, typename TY >
	constexpr point< TX, TY >& operator-=(
		point< TX, TY >& a,
		point< TX, TY > const& b
	){
		a.x() -= b.x();
		a.y() -= b.y();
		return a;
	}

	template < typename TX, typename TY >
	constexpr point< TX, TY >& operator*=(
		point< TX, TY >& a,
		point< TX, TY > const& b
	){
		a.x() *= b.x();
		a.y() *= b.y();
		return a;
	}

	template < typename TX, typename TY >
	constexpr point< TX, TY >& operator/=(
		point< TX, TY >& a,
		point< TX, TY > const& b
	){
		a.x() /= b.x();
		a.y() /= b.y();
		return a;
	}

	template < typename TX, typename TY >
	constexpr point< TX, TY >& operator%=(
		point< TX, TY >& a,
		point< TX, TY > const& b
	){
		a.x() %= b.x();
		a.y() %= b.y();
		return a;
	}


	template < typename TX, typename TY >
	constexpr point< TX, TY > operator+(
		point< TX, TY > a,
		point< TX, TY > const& b
	){
		return a += b;
	}

	template < typename TX, typename TY >
	constexpr point< TX, TY > operator-(
		point< TX, TY > a,
		point< TX, TY > const& b
	){
		return a -= b;
	}

	template < typename TX, typename TY >
	constexpr point< TX, TY > operator*(
		point< TX, TY > a,
		point< TX, TY > const& b
	){
		return a *= b;
	}

	template < typename TX, typename TY >
	constexpr point< TX, TY > operator/(
		point< TX, TY > a,
		point< TX, TY > const& b
	){
		return a /= b;
	}

	template < typename TX, typename TY >
	constexpr point< TX, TY > operator%(
		point< TX, TY > a,
		point< TX, TY > const& b
	){
		return a %= b;
	}


}

#endif
