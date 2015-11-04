//-----------------------------------------------------------------------------
// Copyright (c) 2009-2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__dimension__hpp_INCLUDED_
#define _mitrax__dimension__hpp_INCLUDED_


namespace mitrax{


	/// \brief A class for manipulating dimensions
	/// \tparam ValueType Type of the dimension data
	template < typename ValueType >
	class dimension{
	public:
		/// \brief Type of the positions
		using value_type = ValueType;


		/// \brief The width
		constexpr value_type& width(){
			return width_;
		}

		/// \brief The height
		constexpr value_type& height(){
			return height_;
		}


		/// \brief The width
		constexpr value_type const& width()const{
			return width_;
		}

		/// \brief The height
		constexpr value_type const& height()const{
			return height_;
		}


		/// \brief Set width and height
		constexpr void set(value_type const& width, value_type const& height){
			width_ = width;
			height_ = height;
		}


		/// \brief Constructs a dimension with width 0 and height 0
		constexpr dimension() = default;

		/// \brief Constructs a copy
		constexpr dimension(dimension const&) = default;

		/// \brief Constructs a copy
		constexpr dimension(dimension&&) = default;

		/// \brief Constructs a dimension width width and height
		constexpr dimension(value_type const& width, value_type const& height):
			width_(width), height_(height) {}


		/// \brief Copy assignment
		constexpr dimension& operator=(dimension const&) = default;

		/// \brief Move assignment
		constexpr dimension& operator=(dimension&&) = default;


		/// \brief Get true, if width and height are positiv
		constexpr bool is_positive()const{
			return width() >= value_type() && height() >= value_type();
		}


		/// \brief Get width * height
		constexpr value_type const point_count()const{
			return width() * height();
		}

	private:
		value_type width_;
		value_type height_;
	};

	template < typename ValueType >
	constexpr bool operator==(
		dimension< ValueType > const& a,
		dimension< ValueType > const& b
	){
		return a.width() == b.width() && a.height() == b.height();
	}

	template < typename ValueType >
	constexpr bool operator!=(
		dimension< ValueType > const& a,
		dimension< ValueType > const& b
	){
		return !(a == b);
	}


	template < typename ValueType >
	constexpr dimension< ValueType >& operator+=(
		dimension< ValueType >& a,
		dimension< ValueType > const& b
	){
		a.width()  += b.width();
		a.height() += b.height();
		return a;
	}

	template < typename ValueType >
	constexpr dimension< ValueType >& operator-=(
		dimension< ValueType >& a,
		dimension< ValueType > const& b
	){
		a.width()  -= b.width();
		a.height() -= b.height();
		return a;
	}

	template < typename ValueType >
	constexpr dimension< ValueType >& operator*=(
		dimension< ValueType >& a,
		dimension< ValueType > const& b
	){
		a.width()  *= b.width();
		a.height() *= b.height();
		return a;
	}

	template < typename ValueType >
	constexpr dimension< ValueType >& operator/=(
		dimension< ValueType >& a,
		dimension< ValueType > const& b
	){
		a.width()  /= b.width();
		a.height() /= b.height();
		return a;
	}

	template < typename ValueType >
	constexpr dimension< ValueType >& operator%=(
		dimension< ValueType >& a,
		dimension< ValueType > const& b
	){
		a.width()  %= b.width();
		a.height() %= b.height();
		return a;
	}

	template < typename ValueType >
	constexpr dimension< ValueType > operator+(
		dimension< ValueType > a,
		dimension< ValueType > const& b
	){
		return a += b;
	}

	template < typename ValueType >
	constexpr dimension< ValueType > operator-(
		dimension< ValueType > a,
		dimension< ValueType > const& b
	){
		return a -= b;
	}

	template < typename ValueType >
	constexpr dimension< ValueType > operator*(
		dimension< ValueType > a,
		dimension< ValueType > const& b
	){
		return a *= b;
	}

	template < typename ValueType >
	constexpr dimension< ValueType > operator/(
		dimension< ValueType > a,
		dimension< ValueType > const& b
	){
		return a /= b;
	}

	template < typename ValueType >
	constexpr dimension< ValueType > operator%(
		dimension< ValueType > a,
		dimension< ValueType > const& b
	){
		return a %= b;
	}


}

#endif
