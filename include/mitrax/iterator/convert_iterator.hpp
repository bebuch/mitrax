//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__iterator__convert_iterator__hpp_INCLUDED_
#define _mitrax__iterator__convert_iterator__hpp_INCLUDED_

#include <iterator>


namespace mitrax{


	template < typename T, typename Iter >
	class convert_iterator{
	public:
		using iterator_type = Iter;

		using difference_type =
			typename std::iterator_traits< Iter >::difference_type;

		using value_type = T;

		using pointer = void;

		using iterator_category =
			typename std::iterator_traits< Iter >::iterator_category;

		using reference = value_type;


		constexpr convert_iterator() = default;

		constexpr explicit convert_iterator(Iter i): current_(i) {}

		template < typename U, typename I >
		constexpr convert_iterator(convert_iterator< U, I > const& u):
			current_(u) {}


		template < typename U, typename I >
		constexpr convert_iterator& operator=(
			convert_iterator< U, I > const& u
		){
			current_ = u;
			return *this;
		}


		constexpr iterator_type base()const{
			return current_;
		}

		constexpr value_type operator*()const{
			return static_cast< value_type >(*current_);
		}

		constexpr value_type operator[](difference_type n)const{
			return current_[n];
		}



		constexpr convert_iterator& operator++(){
			++current_;
			return *this;
		}

		constexpr convert_iterator operator++(int){
			return convert_iterator(current_++);
		}

		constexpr convert_iterator& operator--(){
			--current_;
			return *this;
		}

		constexpr convert_iterator operator--(int){
			return convert_iterator(current_--);
		}


		constexpr convert_iterator operator+(difference_type n)const{
			return convert_iterator(current_ + n);
		}

		constexpr convert_iterator& operator+=(difference_type n){
			current_ += n;
			return *this;
		}

		constexpr convert_iterator operator-(difference_type n)const{
			return convert_iterator(current_ - n);
		}

		constexpr convert_iterator& operator-=(difference_type n){
			current_ -= n;
			return *this;
		}


	private:
		Iter current_;
	};


	template < typename T1, typename Iter1, typename T2, typename Iter2 >
	constexpr bool operator==(
		convert_iterator< T1, Iter1 > const& lhs,
		convert_iterator< T2, Iter2 > const& rhs
	){
		return lhs.base() == rhs.base();
	}

	template < typename T1, typename Iter1, typename T2, typename Iter2 >
	constexpr bool operator!=(
		convert_iterator< T1, Iter1 > const& lhs,
		convert_iterator< T2, Iter2 > const& rhs
	){
		return lhs.base() != rhs.base();
	}

	template < typename T1, typename Iter1, typename T2, typename Iter2 >
	constexpr bool operator<(
		convert_iterator< T1, Iter1 > const& lhs,
		convert_iterator< T2, Iter2 > const& rhs
	){
		return lhs.base() < rhs.base();
	}

	template < typename T1, typename Iter1, typename T2, typename Iter2 >
	constexpr bool operator<=(
		convert_iterator< T1, Iter1 > const& lhs,
		convert_iterator< T2, Iter2 > const& rhs
	){
		return lhs.base() <= rhs.base();
	}

	template < typename T1, typename Iter1, typename T2, typename Iter2 >
	constexpr bool operator>(
		convert_iterator< T1, Iter1 > const& lhs,
		convert_iterator< T2, Iter2 > const& rhs
	){
		return lhs.base() > rhs.base();
	}

	template < typename T1, typename Iter1, typename T2, typename Iter2 >
	constexpr bool operator>=(
		convert_iterator< T1, Iter1 > const& lhs,
		convert_iterator< T2, Iter2 > const& rhs
	){
		return lhs.base() >= rhs.base();
	}

	template < typename T, typename Iter >
	constexpr convert_iterator< T, Iter > operator+(
		typename convert_iterator< T, Iter >::difference_type n,
		convert_iterator< T, Iter > const& iter
	){
		return convert_iterator< T, Iter >(iter + n);
	}

	template < typename T1, typename Iter1, typename T2, typename Iter2 >
	constexpr auto operator-(
		convert_iterator< T1, Iter1 > const& lhs,
		convert_iterator< T2, Iter2 > const& rhs
	){
		return lhs.base() - rhs.base();
	}


	template < typename T, typename Iter >
	constexpr convert_iterator< T, Iter > make_convert_iterator(Iter iter){
		return convert_iterator< T, Iter >(iter);
	}


}


#endif
