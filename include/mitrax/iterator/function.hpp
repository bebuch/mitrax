//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__iterator__function__hpp_INCLUDED_
#define _mitrax__iterator__function__hpp_INCLUDED_

#include "../dim.hpp"

#include <iterator>


namespace mitrax{


	template < typename F >
	class function_iterator{
	public:
		static_assert(!std::is_reference_v< F >);


		using function_type = F;

		using difference_type = std::ptrdiff_t;

		using pointer = void;

		using value_type =
			std::decay_t< decltype(std::declval< F >()(size_t())) >;

		using iterator_category = std::random_access_iterator_tag;

		using reference = value_type;


		constexpr explicit function_iterator(F& f, size_t i = 0):
			f_(f), n_(i) {}

		constexpr explicit function_iterator(F&& f, size_t i = 0):
			f_(std::move(f)), n_(i) {}

		constexpr function_iterator(function_iterator&& u) = default;

		constexpr function_iterator(function_iterator const& u) = default;


		constexpr function_iterator& operator=(function_iterator&& u)
			= default;

		constexpr function_iterator& operator=(function_iterator const& u)
			= default;


		constexpr size_t pos()const{
			return n_;
		}

		constexpr decltype(auto) operator*()const{
			return f_(n_);
		}

		constexpr decltype(auto) operator[](difference_type n)const{
			return f_(n_ + n);
		}



		constexpr function_iterator& operator++(){
			++n_;
			return *this;
		}

		constexpr function_iterator operator++(int){
			return ++function_iterator(*this);
		}

		constexpr function_iterator& operator--(){
			--n_;
			return *this;
		}

		constexpr function_iterator operator--(int){
			return --function_iterator(*this);
		}


		constexpr function_iterator operator+(difference_type n)const{
			return function_iterator(*this) += n;
		}

		constexpr function_iterator& operator+=(difference_type n){
			n_ += n;
			return *this;
		}

		constexpr function_iterator operator-(difference_type n)const{
			return function_iterator(*this) -= n;
		}

		constexpr function_iterator& operator-=(difference_type n){
			n_ -= n;
			return *this;
		}


	private:
		F f_;
		size_t n_;
	};


	template < typename F1, typename F2 >
	constexpr bool operator==(
		function_iterator< F1 > const& lhs, function_iterator< F2 > const& rhs
	){
		return lhs.pos() == rhs.pos();
	}

	template < typename F1, typename F2 >
	constexpr bool operator!=(
		function_iterator< F1 > const& lhs, function_iterator< F2 > const& rhs
	){
		return lhs.pos() != rhs.pos();
	}

	template < typename F1, typename F2 >
	constexpr bool operator<(
		function_iterator< F1 > const& lhs, function_iterator< F2 > const& rhs
	){
		return lhs.pos() < rhs.pos();
	}

	template < typename F1, typename F2 >
	constexpr bool operator<=(
		function_iterator< F1 > const& lhs, function_iterator< F2 > const& rhs
	){
		return lhs.pos() <= rhs.pos();
	}

	template < typename F1, typename F2 >
	constexpr bool operator>(
		function_iterator< F1 > const& lhs, function_iterator< F2 > const& rhs
	){
		return lhs.pos() > rhs.pos();
	}

	template < typename F1, typename F2 >
	constexpr bool operator>=(
		function_iterator< F1 > const& lhs, function_iterator< F2 > const& rhs
	){
		return lhs.pos() >= rhs.pos();
	}

	template < typename F >
	constexpr function_iterator< F > operator+(
		typename function_iterator< F >::difference_type n,
		function_iterator< F > const& iter
	){
		return function_iterator< F >(iter + n);
	}

	template < typename F1, typename F2 >
	constexpr auto operator-(
		function_iterator< F1 > const& lhs, function_iterator< F2 > const& rhs
	){
		return lhs.pos() - rhs.pos();
	}


	template < typename F >
	constexpr auto make_function_iterator(F&& f, size_t n = 0){
		return function_iterator< std::remove_reference_t< F > >
			(static_cast< F&& >(f), n);
	}


	template < typename F, bool Cct, size_t C >
	struct function_xy_adapter{
		static_assert(!std::is_reference_v< F >);

		constexpr decltype(auto) operator()(size_t i)const
		noexcept(noexcept(std::declval< F >()(size_t(), size_t()))){
			return f(i % size_t(cols), i / size_t(cols));
		}

		F f;
		col_t< Cct, C > cols;
	};

	template < typename F, bool Cct, size_t C >
	constexpr auto make_function_xy_adapter(F&& f, col_t< Cct, C > cols){
		return function_xy_adapter< std::remove_reference_t< F >, Cct, C >
			{static_cast< F&& >(f), cols};
	}


}


#endif
