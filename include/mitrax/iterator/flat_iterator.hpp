//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__iterator__flat_iterator__hpp_INCLUDED_
#define _mitrax__iterator__flat_iterator__hpp_INCLUDED_

#include <iterator>


namespace mitrax{


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


}


#endif
