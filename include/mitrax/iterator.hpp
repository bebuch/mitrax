//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__iterator__hpp_INCLUDED_
#define _mitrax__iterator__hpp_INCLUDED_

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



	template < typename T, size_t Dim, size_t ... Dims >
	class flat_iterator;


	namespace detail{


		template < typename T, size_t Dim >
		constexpr T& get_flat_iterator_element(
			typename flat_iterator< T, Dim >::array_type& array,
			typename flat_iterator< T, Dim >::difference_type n
		)noexcept{
			return array[n];
		}

		template < typename T, size_t D1, size_t D2, size_t ... Dims >
		constexpr T& get_flat_iterator_element(
			typename flat_iterator< T, D1, D2, Dims ... >::array_type& array,
			typename flat_iterator< T, D1, D2, Dims ... >::difference_type n
		)noexcept{
			auto D = (D2 * ... * Dims);
			return get_flat_iterator_element< T, D2, Dims ... >
				(array[n / D], n % D);
		}


	}


	template < typename T, size_t Dim, size_t ... Dims >
	class flat_iterator{
	public:
		using sub_type = typename flat_iterator< T, Dims ... >::array_type;

		using array_type = sub_type[Dim];

		using difference_type = ptrdiff_t;

		using pointer = T*;

		using value_type = std::remove_cv_t< T >;

		using iterator_category = std::random_access_iterator_tag;

		using reference = T&;


		constexpr explicit flat_iterator(
			array_type* array, difference_type n = 0
		)noexcept: array_(array), n_(n) {}


		constexpr array_type* array()const noexcept{
			return array_;
		}

		constexpr difference_type pos()const noexcept{
			return n_;
		}

		constexpr reference operator*()const noexcept{
			return operator[](n_);
		}

		constexpr pointer operator->()const noexcept{
			return &(operator*());
		}

		constexpr reference operator[](difference_type n)const noexcept{
			return detail::get_flat_iterator_element
				< T, Dim, Dims ... >(*array_, n);
		}



		constexpr flat_iterator& operator++()noexcept{
			++n_;
			return *this;
		}

		constexpr flat_iterator operator++(int)noexcept{
			return flat_iterator(array_, n_++);
		}

		constexpr flat_iterator& operator--()noexcept{
			--n_;
			return *this;
		}

		constexpr flat_iterator operator--(int)noexcept{
			return flat_iterator(array_, n_--);
		}


		constexpr flat_iterator operator+(difference_type n)const noexcept{
			return flat_iterator(array_, n_ + n);
		}

		constexpr flat_iterator& operator+=(difference_type n)noexcept{
			n_ += n;
			return *this;
		}

		constexpr flat_iterator operator-(difference_type n)const noexcept{
			return flat_iterator(array_, n_ - n);
		}

		constexpr flat_iterator& operator-=(difference_type n)noexcept{
			n_ -= n;
			return *this;
		}


	private:
		array_type* array_;
		size_t n_;
	};


	template < typename T, size_t Dim >
	class flat_iterator< T, Dim >{
	public:
		using array_type = T[Dim];

		using difference_type = ptrdiff_t;

		using pointer = T*;

		using value_type = std::remove_cv_t< T >;

		using iterator_category = std::random_access_iterator_tag;

		using reference = T&;


		constexpr flat_iterator()noexcept: iter_(nullptr) {}

		constexpr explicit flat_iterator(
			array_type* array, difference_type n = 0
		)noexcept: iter_(*array + n) {}


		constexpr pointer pos()const noexcept{
			return iter_;
		}

		constexpr reference operator*()const noexcept{
			return *iter_;
		}

		constexpr pointer operator->()const noexcept{
			return iter_;
		}

		constexpr reference operator[](difference_type n)const noexcept{
			return *(iter_ + n);
		}


		constexpr flat_iterator& operator++()noexcept{
			++iter_;
			return *this;
		}

		constexpr flat_iterator operator++(int)noexcept{
			return flat_iterator(iter_++);
		}

		constexpr flat_iterator& operator--()noexcept{
			--iter_;
			return *this;
		}

		constexpr flat_iterator operator--(int)noexcept{
			return flat_iterator(iter_--);
		}


		constexpr flat_iterator operator+(difference_type n)const noexcept{
			return flat_iterator(iter_ + n);
		}

		constexpr flat_iterator& operator+=(difference_type n)noexcept{
			iter_ += n;
			return *this;
		}

		constexpr flat_iterator operator-(difference_type n)const noexcept{
			return flat_iterator(iter_ - n);
		}

		constexpr flat_iterator& operator-=(difference_type n)noexcept{
			iter_ -= n;
			return *this;
		}


	private:
		T* iter_;

		constexpr explicit flat_iterator(T* iter)noexcept: iter_(iter) {}
	};


	template < typename T, size_t Dim, size_t ... Dims >
	constexpr bool operator==(
		flat_iterator< T, Dim, Dims ... > const& lhs,
		flat_iterator< T, Dim, Dims ... > const& rhs
	)noexcept{
		return lhs.pos() == rhs.pos();
	}

	template < typename T, size_t Dim, size_t ... Dims >
	constexpr bool operator!=(
		flat_iterator< T, Dim, Dims ... > const& lhs,
		flat_iterator< T, Dim, Dims ... > const& rhs
	)noexcept{
		return lhs.pos() == rhs.pos();
	}

	template < typename T, size_t Dim, size_t ... Dims >
	constexpr bool operator<(
		flat_iterator< T, Dim, Dims ... > const& lhs,
		flat_iterator< T, Dim, Dims ... > const& rhs
	)noexcept{
		return lhs.pos() == rhs.pos();
	}

	template < typename T, size_t Dim, size_t ... Dims >
	constexpr bool operator<=(
		flat_iterator< T, Dim, Dims ... > const& lhs,
		flat_iterator< T, Dim, Dims ... > const& rhs
	)noexcept{
		return lhs.pos() == rhs.pos();
	}

	template < typename T, size_t Dim, size_t ... Dims >
	constexpr bool operator>(
		flat_iterator< T, Dim, Dims ... > const& lhs,
		flat_iterator< T, Dim, Dims ... > const& rhs
	)noexcept{
		return lhs.pos() == rhs.pos();
	}

	template < typename T, size_t Dim, size_t ... Dims >
	constexpr bool operator>=(
		flat_iterator< T, Dim, Dims ... > const& lhs,
		flat_iterator< T, Dim, Dims ... > const& rhs
	)noexcept{
		return lhs.pos() == rhs.pos();
	}

	template < typename T, size_t Dim, size_t ... Dims >
	constexpr flat_iterator< T, Dim, Dims ... > operator+(
		typename flat_iterator< T, Dim, Dims ... >::difference_type n,
		flat_iterator< T, Dim, Dims ... > const& iter
	)noexcept{
		return iter + n;
	}

	template < typename T, size_t Dim, size_t ... Dims >
	constexpr auto operator-(
		flat_iterator< T, Dim, Dims ... > const& lhs,
		flat_iterator< T, Dim, Dims ... > const& rhs
	)noexcept{
		return lhs.pos() - rhs.pos();
	}


	template < typename C >
	constexpr auto begin(C& c){
		return c.begin();
	}

	template < typename C >
	constexpr auto begin(C const& c){
		return c.begin();
	}

	template < typename T, size_t N >
	constexpr T* begin(T(&array)[N])noexcept{
		return array;
	}

	template < typename C >
	constexpr auto cbegin(C const& c){
		return mitrax::begin(c);
	}


	template < typename C >
	constexpr auto end(C& c){
		return c.end();
	}

	template < typename C >
	constexpr auto end(C const& c){
		return c.end();
	}

	template < typename T, size_t N >
	constexpr T* end(T(&array)[N])noexcept{
		return array + N;
	}

	template < typename C >
	constexpr auto cend(C const& c){
		return mitrax::end(c);
	}


}


#endif
