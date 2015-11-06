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


	namespace detail{ namespace dimension{


		template < typename TX, typename TY >
		struct dimension_base{};

		template < typename T >
		struct dimension_base< T, T >{
			/// \brief Type of the dimension
			using value_type = T;
		};


	} }


	/// \brief A class for representing dimensions
	/// \tparam TX Type of the x dimension data
	/// \tparam TY Type of the y dimension data
	template < typename TX, typename TY = TX >
	class dimension: public detail::dimension::dimension_base< TX, TY >{
	public:
		/// \brief Type of the x positions
		using x_value_type = TX;

		/// \brief Type of the y positions
		using y_value_type = TY;


		/// \brief The cols
		constexpr x_value_type& cols(){
			return cols_;
		}

		/// \brief The rows
		constexpr y_value_type& rows(){
			return rows_;
		}


		/// \brief The cols
		constexpr x_value_type const& cols()const{
			return cols_;
		}

		/// \brief The rows
		constexpr y_value_type const& rows()const{
			return rows_;
		}


		/// \brief Set cols and rows
		constexpr void set(x_value_type const& cols, y_value_type const& rows){
			cols_ = cols;
			rows_ = rows;
		}


		/// \brief Constructs a dimension with cols 0 and rows 0
		constexpr dimension() = default;

		/// \brief Constructs a copy
		constexpr dimension(dimension const&) = default;

		/// \brief Constructs a copy
		constexpr dimension(dimension&&) = default;

		/// \brief Constructs a dimension cols and rows
		constexpr dimension(
			x_value_type const& cols,
			y_value_type const& rows
		):
			cols_(cols), rows_(rows) {}


		/// \brief Copy assignment
		constexpr dimension& operator=(dimension const&) = default;

		/// \brief Move assignment
		constexpr dimension& operator=(dimension&&) = default;


		/// \brief Get true, if cols and rows are positiv
		constexpr bool is_positive()const{
			return cols() >= x_value_type() && rows() >= y_value_type();
		}


		/// \brief Get cols * rows
		constexpr auto point_count()const{
			return cols() * rows();
		}

	private:
		x_value_type cols_;
		y_value_type rows_;
	};


	template < typename TX, typename TY >
	constexpr bool operator==(
		dimension< TX, TY > const& a,
		dimension< TX, TY > const& b
	){
		return a.cols() == b.cols() && a.rows() == b.rows();
	}

	template < typename TX, typename TY >
	constexpr bool operator!=(
		dimension< TX, TY > const& a,
		dimension< TX, TY > const& b
	){
		return !(a == b);
	}


	template < typename TX, typename TY >
	constexpr dimension< TX, TY >& operator+=(
		dimension< TX, TY >& a,
		dimension< TX, TY > const& b
	){
		a.cols() += b.cols();
		a.rows() += b.rows();
		return a;
	}

	template < typename TX, typename TY >
	constexpr dimension< TX, TY >& operator-=(
		dimension< TX, TY >& a,
		dimension< TX, TY > const& b
	){
		a.cols() -= b.cols();
		a.rows() -= b.rows();
		return a;
	}

	template < typename TX, typename TY >
	constexpr dimension< TX, TY >& operator*=(
		dimension< TX, TY >& a,
		dimension< TX, TY > const& b
	){
		a.cols() *= b.cols();
		a.rows() *= b.rows();
		return a;
	}

	template < typename TX, typename TY >
	constexpr dimension< TX, TY >& operator/=(
		dimension< TX, TY >& a,
		dimension< TX, TY > const& b
	){
		a.cols() /= b.cols();
		a.rows() /= b.rows();
		return a;
	}

	template < typename TX, typename TY >
	constexpr dimension< TX, TY >& operator%=(
		dimension< TX, TY >& a,
		dimension< TX, TY > const& b
	){
		a.cols() %= b.cols();
		a.rows() %= b.rows();
		return a;
	}


	template < typename TX, typename TY >
	constexpr dimension< TX, TY > operator+(
		dimension< TX, TY > a,
		dimension< TX, TY > const& b
	){
		return a += b;
	}

	template < typename TX, typename TY >
	constexpr dimension< TX, TY > operator-(
		dimension< TX, TY > a,
		dimension< TX, TY > const& b
	){
		return a -= b;
	}

	template < typename TX, typename TY >
	constexpr dimension< TX, TY > operator*(
		dimension< TX, TY > a,
		dimension< TX, TY > const& b
	){
		return a *= b;
	}

	template < typename TX, typename TY >
	constexpr dimension< TX, TY > operator/(
		dimension< TX, TY > a,
		dimension< TX, TY > const& b
	){
		return a /= b;
	}

	template < typename TX, typename TY >
	constexpr dimension< TX, TY > operator%(
		dimension< TX, TY > a,
		dimension< TX, TY > const& b
	){
		return a %= b;
	}


}

#endif
