//-----------------------------------------------------------------------------
// Copyright (c) 2016-2018 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__iterator__move__hpp_INCLUDED_
#define _mitrax__iterator__move__hpp_INCLUDED_

#include <iterator>


namespace mitrax{


	template < typename Iter >
	class move_iterator{
	public:
		using iterator_type = Iter;

		using difference_type =
			typename std::iterator_traits< Iter >::difference_type;

		using pointer = Iter;

		using value_type = typename std::iterator_traits< Iter >::value_type;

		using iterator_category =
			typename std::iterator_traits< Iter >::iterator_category;

		using reference = value_type&&;


		constexpr move_iterator() = default;

		constexpr explicit move_iterator(Iter i): current_(i) {}

		template < typename U >
		constexpr move_iterator(move_iterator< U > const& u): current_(u) {}


		template < typename U >
		constexpr move_iterator& operator=(move_iterator< U > const& u){
			current_ = u;
			return *this;
		}


		constexpr iterator_type base()const{
			return current_;
		}

		constexpr reference operator*()const{
			return static_cast< reference >(*current_);
		}

		constexpr pointer operator->()const{
			return current_;
		}

		constexpr reference operator[](difference_type n)const{
			return std::move(current_[n]);
		}



		constexpr move_iterator& operator++(){
			++current_;
			return *this;
		}

		constexpr move_iterator operator++(int){
			return move_iterator(current_++);
		}

		constexpr move_iterator& operator--(){
			--current_;
			return *this;
		}

		constexpr move_iterator operator--(int){
			return move_iterator(current_--);
		}


		constexpr move_iterator operator+(difference_type n)const{
			return move_iterator(current_ + n);
		}

		constexpr move_iterator& operator+=(difference_type n){
			current_ += n;
			return *this;
		}

		constexpr move_iterator operator-(difference_type n)const{
			return move_iterator(current_ - n);
		}

		constexpr move_iterator& operator-=(difference_type n){
			current_ -= n;
			return *this;
		}


	private:
		Iter current_;
	};


	template < typename Iter1, typename Iter2 >
	constexpr bool operator==(
		move_iterator< Iter1 > const& lhs, move_iterator< Iter2 > const& rhs
	){
		return lhs.base() == rhs.base();
	}

	template < typename Iter1, typename Iter2 >
	constexpr bool operator!=(
		move_iterator< Iter1 > const& lhs, move_iterator< Iter2 > const& rhs
	){
		return lhs.base() != rhs.base();
	}

	template < typename Iter1, typename Iter2 >
	constexpr bool operator<(
		move_iterator< Iter1 > const& lhs, move_iterator< Iter2 > const& rhs
	){
		return lhs.base() < rhs.base();
	}

	template < typename Iter1, typename Iter2 >
	constexpr bool operator<=(
		move_iterator< Iter1 > const& lhs, move_iterator< Iter2 > const& rhs
	){
		return lhs.base() <= rhs.base();
	}

	template < typename Iter1, typename Iter2 >
	constexpr bool operator>(
		move_iterator< Iter1 > const& lhs, move_iterator< Iter2 > const& rhs
	){
		return lhs.base() > rhs.base();
	}

	template < typename Iter1, typename Iter2 >
	constexpr bool operator>=(
		move_iterator< Iter1 > const& lhs, move_iterator< Iter2 > const& rhs
	){
		return lhs.base() >= rhs.base();
	}

	template < typename Iter >
	constexpr move_iterator< Iter > operator+(
		typename move_iterator< Iter >::difference_type n,
		move_iterator< Iter > const& iter
	){
		return move_iterator< Iter >(iter + n);
	}

	template < typename Iter1, typename Iter2 >
	constexpr auto operator-(
		move_iterator< Iter1 > const& lhs, move_iterator< Iter2 > const& rhs
	){
		return lhs.base() - rhs.base();
	}


	template < typename Iter >
	constexpr move_iterator< Iter > make_move_iterator(Iter iter){
		return move_iterator< Iter >(iter);
	}


}


#endif
