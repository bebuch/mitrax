//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__dim__hpp_INCLUDED_
#define _mitrax__dim__hpp_INCLUDED_

#include <cstddef>
#include <type_traits>
#include <functional>
#include <stdexcept>


namespace mitrax{


	using size_t = std::size_t;

	using ptrdiff_t = std::ptrdiff_t;


	template < typename F >
	using fn_xy =
		std::decay_t< decltype(std::declval< F >()(size_t(), size_t())) >;

	template < typename F >
	using fn_i = std::decay_t< decltype(std::declval< F >()(size_t())) >;


	template < typename T, typename Auto >
	using auto_t = std::conditional_t< std::is_void_v< T >, Auto, T >;

	template < typename T, typename Auto >
	constexpr auto auto_ref(Auto&& v)
	-> auto_t< T, decltype(static_cast< Auto&& >(v)) >{
		return static_cast< Auto&& >(v);
	}


	template < typename T >
	using value_type_t = typename T::value_type;

	template < bool I >
	using bool_t = std::integral_constant< bool, I >;


	template < typename ArrayRef >
	struct array_1d_element{
		using type = std::remove_extent_t<
			std::remove_reference_t< ArrayRef > >;
	};

	template < typename ArrayRef >
	using array_1d_element_t = typename array_1d_element< ArrayRef >::type;


	template < typename ArrayRef >
	struct array_2d_element{
		using type = std::remove_extent_t< std::remove_extent_t<
			std::remove_reference_t< ArrayRef > > >;
	};

	template < typename ArrayRef >
	using array_2d_element_t = typename array_2d_element< ArrayRef >::type;


	template < typename ArrayRef >
	struct array_1d_element_ref{
		using value_type = array_1d_element_t< ArrayRef >;

		using type = std::conditional_t<
				std::is_rvalue_reference< ArrayRef >::value,
				std::add_rvalue_reference_t< value_type >,
				std::add_lvalue_reference_t< value_type >
			>;
	};

	template < typename ArrayRef >
	using array_1d_element_ref_t =
		typename array_1d_element_ref< ArrayRef >::type;


	template < typename ArrayRef >
	struct array_2d_element_ref{
		using value_type = array_2d_element_t< ArrayRef >;

		using type = std::conditional_t<
				std::is_rvalue_reference< ArrayRef >::value,
				std::add_rvalue_reference_t< value_type >,
				std::add_lvalue_reference_t< value_type >
			>;
	};

	template < typename ArrayRef >
	using array_2d_element_ref_t =
		typename array_2d_element_ref< ArrayRef >::type;


	constexpr size_t dim(bool is_compile_time, size_t n)noexcept{
		return is_compile_time ? n : 0;
	}


	template < size_t V >
	struct size_ct{
		static constexpr size_t value = V;

		using value_type = size_t;


		constexpr operator size_t()const noexcept{ return value; }
		constexpr size_t operator()()const noexcept{ return value; }
	};


	struct size_rt{
	public:
		static constexpr size_t value = 0;

		using value_type = size_t;


		constexpr size_rt()noexcept: v_(0) {}
		constexpr size_rt(size_t v)noexcept: v_(v) {}


		constexpr operator size_t()const noexcept{ return v_; }
		constexpr size_t operator()()const noexcept{ return v_; }

	public:
		size_t v_;
	};


	template < bool CompileTimeTarget, size_t C >
	struct col_t;

	template < bool CompileTimeTarget, size_t R >
	struct row_t;

	template < bool CompileTimeTarget, size_t N >
	struct dim_t;


	template < size_t C >
	struct col_t< true, C >: size_ct< C >{
		constexpr auto as_row()const noexcept{ return row_t< true, C >(); }
		constexpr auto as_dim()const noexcept{ return dim_t< true, C >(); }
	};

	template < size_t C >
	struct col_t< false, C >: size_ct< C >{
		constexpr col_t()noexcept = default;

		constexpr col_t(col_t< true, C >&&)noexcept{}
		constexpr col_t(col_t< true, C > const&)noexcept{}

		constexpr auto as_row()const noexcept{ return row_t< false, C >(); }
		constexpr auto as_dim()const noexcept{ return dim_t< false, C >(); }
	};

	template <>
	struct col_t< false, 0 >: size_rt{
		constexpr col_t()noexcept = default;

		template < bool Cct, size_t C >
		constexpr col_t(col_t< Cct, C >&&)noexcept: size_rt(C) {}

		template < bool Cct, size_t C >
		constexpr col_t(col_t< Cct, C > const&)noexcept: size_rt(C) {}

		using size_rt::size_rt;


		constexpr auto as_row()const noexcept;
		constexpr auto as_dim()const noexcept;
	};


	template < size_t R >
	struct row_t< true, R >: size_ct< R >{
		constexpr auto as_col()const noexcept{ return col_t< true, R >(); }
		constexpr auto as_dim()const noexcept{ return dim_t< true, R >(); }
	};

	template < size_t R >
	struct row_t< false, R >: size_ct< R >{
		constexpr row_t()noexcept = default;

		constexpr row_t(row_t< true, R >&&)noexcept{}
		constexpr row_t(row_t< true, R > const&)noexcept{}


		constexpr auto as_col()const noexcept{ return col_t< false, R >(); }
		constexpr auto as_dim()const noexcept{ return dim_t< false, R >(); }
	};

	template <>
	struct row_t< false, 0 >: size_rt{
		constexpr row_t()noexcept = default;

		template < bool Rct, size_t R >
		constexpr row_t(row_t< Rct, R >&&)noexcept: size_rt(R) {}

		template < bool Rct, size_t R >
		constexpr row_t(row_t< Rct, R > const&)noexcept: size_rt(R) {}

		using size_rt::size_rt;


		constexpr auto as_col()const noexcept;
		constexpr auto as_dim()const noexcept;
	};


	template < size_t N >
	struct dim_t< true, N >: size_ct< N >{
		constexpr auto as_col()const noexcept{
			return col_t< true, N >();
		}

		constexpr auto as_row()const noexcept{
			return row_t< true, N >();
		}
	};

	template < size_t N >
	struct dim_t< false, N >: size_ct< N >{
		constexpr dim_t()noexcept = default;

		constexpr dim_t(dim_t< true, N >&&)noexcept{}
		constexpr dim_t(dim_t< true, N > const&)noexcept{}

		constexpr auto as_col()const noexcept{ return col_t< false, N >(); }
		constexpr auto as_row()const noexcept{ return row_t< false, N >(); }
	};

	template <>
	struct dim_t< false, 0 >: size_rt{
		constexpr dim_t()noexcept = default;

		template < bool Nct, size_t N >
		constexpr dim_t(dim_t< Nct, N >&&)noexcept: size_rt(N) {}

		template < bool Nct, size_t N >
		constexpr dim_t(dim_t< Nct, N > const&)noexcept: size_rt(N) {}

		using size_rt::size_rt;


		constexpr auto as_col()const noexcept;
		constexpr auto as_row()const noexcept;
	};


	constexpr auto col_t< false, 0 >::as_row()const noexcept{
		return row_t< false, 0 >(size_t(*this));
	}

	constexpr auto col_t< false, 0 >::as_dim()const noexcept{
		return dim_t< false, 0 >(size_t(*this));
	}


	constexpr auto row_t< false, 0 >::as_col()const noexcept{
		return col_t< false, 0 >(size_t(*this));
	}

	constexpr auto row_t< false, 0 >::as_dim()const noexcept{
		return dim_t< false, 0 >(size_t(*this));
	}


	constexpr auto dim_t< false, 0 >::as_col()const noexcept{
		return col_t< false, 0 >(size_t(*this));
	}

	constexpr auto dim_t< false, 0 >::as_row()const noexcept{
		return row_t< false, 0 >(size_t(*this));
	}


	template < size_t C, size_t R >
	class dims_t final: private col_t< C != 0, C >, private row_t< R != 0, R >{
	public:
		static constexpr size_t static_cols = C;
		static constexpr size_t static_rows = R;

		constexpr dims_t()noexcept = default;

		constexpr dims_t(
			col_t< C != 0, C > cols,
			row_t< R != 0, R > rows
		)noexcept: col_t< C != 0, C >(cols), row_t< R != 0, R >(rows) {}


		constexpr col_t< C != 0, C > const cols()const noexcept{
			return *this;
		}

		constexpr row_t< R != 0, R > const rows()const noexcept{
			return *this;
		}


		template < bool Cct >
		constexpr void set_cols(col_t< Cct, C > c)noexcept{
			static_cast< col_t< C != 0, C >& >(*this) = c;
		}

		template < bool Rct >
		constexpr void set_rows(row_t< Rct, R > r)noexcept{
			static_cast< row_t< R != 0, R >& >(*this) = r;
		}

		template < bool Cct, bool Rct >
		constexpr void set(col_t< Cct, C > c, row_t< Rct, R > r)noexcept{
			set_cols(c);
			set_rows(r);
		}


		size_t point_count()const{
			return size_t(cols()) * size_t(rows());
		}
	};


	constexpr auto dims(size_t c, size_t r)noexcept{
		return dims_t< 0, 0 >(col_t< false, 0 >(c), row_t< false, 0 >(r));
	}

	template < size_t C, size_t R >
	constexpr auto dims()noexcept{
		return dims_t< C, R >();
	}

	template < bool Cct, size_t C >
	constexpr auto dims(col_t< Cct, C > c, size_t r)noexcept{
		return dims_t< dim(Cct, C), 0 >(c, row_t< false, 0 >(r));
	}

	template < bool Rct, size_t R >
	constexpr auto dims(size_t c, row_t< Rct, R > r)noexcept{
		return dims_t< 0, dim(Rct, R) >(col_t< false, 0 >(c), r);
	}

	template < bool Cct, size_t C, bool Rct, size_t R >
	constexpr auto dims(col_t< Cct, C > c, row_t< Rct, R > r)noexcept{
		return dims_t< dim(Cct, C), dim(Rct, R) >(c, r);
	}

	template < bool Dct, size_t D >
	constexpr auto dims(dim_t< Dct, D > d)noexcept{
		return dims(d.as_col(), d.as_row());
	}

	template < typename T, bool Cct, size_t C >
	void dims(T, col_t< Cct, C >) = delete;

	template < typename T, bool Rct, size_t R >
	void dims(row_t< Rct, R >, T) = delete;

	template < bool Cct, size_t C, bool Rct, size_t R >
	void dims(row_t< Rct, R >, col_t< Cct, C >) = delete;

	template < bool Cct, size_t C, bool Rct, size_t R >
	void dims(col_t< Rct, R >, col_t< Cct, C >) = delete;

	template < bool Cct, size_t C, bool Rct, size_t R >
	void dims(row_t< Rct, R >, row_t< Cct, C >) = delete;


	constexpr auto cols(size_t c)noexcept{ return col_t< false, 0 >(c); }
	constexpr auto rows(size_t r)noexcept{ return row_t< false, 0 >(r); }
	constexpr auto dims(size_t d)noexcept{ return dim_t< false, 0 >(d); }


	template < size_t I >
	constexpr auto cols()noexcept{ return col_t< true, I >(); }

	template < size_t I >
	constexpr auto rows()noexcept{ return row_t< true, I >(); }

	template < size_t I >
	constexpr auto dims()noexcept{ return dim_t< true, I >(); }


	template < size_t I >
	constexpr auto cols_rt()noexcept{ return col_t< false, I >(); }

	template < size_t I >
	constexpr auto rows_rt()noexcept{ return row_t< false, I >(); }

	template < size_t I >
	constexpr auto dims_rt()noexcept{ return dim_t< false, I >(); }


	namespace detail{


		template < typename Op >
		struct col_op{
			template < bool Ict1, size_t I1, bool Ict2, size_t I2 >
			constexpr auto operator()(
				col_t< Ict1, I1 > /*d1*/, col_t< Ict2, I2 > /*d2*/
			)const noexcept{
				return col_t< Ict1 && Ict2, Op()(I1, I2) >();
			}

			template < bool Ict1, bool Ict2, size_t I2 >
			constexpr auto operator()(
				col_t< Ict1, 0 > d1, col_t< Ict2, I2 > d2
			)const noexcept{
				return col_t< Ict1 && Ict2, 0 >(Op()(size_t(d1), size_t(d2)));
			}

			template < bool Ict1, size_t I1, bool Ict2 >
			constexpr auto operator()(
				col_t< Ict1, I1 > d1, col_t< Ict2, 0 > d2
			)const noexcept{
				return col_t< Ict1 && Ict2, 0 >(Op()(size_t(d1), size_t(d2)));
			}

			template < bool Ict1, bool Ict2 >
			constexpr auto operator()(
				col_t< Ict1, 0 > d1, col_t< Ict2, 0 > d2
			)const noexcept{
				return col_t< Ict1 && Ict2, 0 >(Op()(size_t(d1), size_t(d2)));
			}

			template < bool Ict1, size_t I1 >
			constexpr auto operator()(
				col_t< Ict1, I1 > d1, size_t d2
			)const noexcept{
				return col_t< false, 0 >(Op()(size_t(d1), d2));
			}

			template < bool Ict2, size_t I2 >
			constexpr auto operator()(
				size_t d1, col_t< Ict2, I2 > d2
			)const noexcept{
				return col_t< false, 0 >(Op()(d1, size_t(d2)));
			}
		};


		template < typename Op >
		struct row_op{
			template < bool Ict1, size_t I1, bool Ict2, size_t I2 >
			constexpr auto operator()(
				row_t< Ict1, I1 > /*d1*/, row_t< Ict2, I2 > /*d2*/
			)const noexcept{
				return row_t< Ict1 && Ict2, Op()(I1, I2) >();
			}

			template < bool Ict1, bool Ict2, size_t I2 >
			constexpr auto operator()(
				row_t< Ict1, 0 > d1, row_t< Ict2, I2 > d2
			)const noexcept{
				return row_t< Ict1 && Ict2, 0 >(Op()(size_t(d1), size_t(d2)));
			}

			template < bool Ict1, size_t I1, bool Ict2 >
			constexpr auto operator()(
				row_t< Ict1, I1 > d1, row_t< Ict2, 0 > d2
			)const noexcept{
				return row_t< Ict1 && Ict2, 0 >(Op()(size_t(d1), size_t(d2)));
			}

			template < bool Ict1, bool Ict2 >
			constexpr auto operator()(
				row_t< Ict1, 0 > d1, row_t< Ict2, 0 > d2
			)const noexcept{
				return row_t< Ict1 && Ict2, 0 >(Op()(size_t(d1), size_t(d2)));
			}

			template < bool Ict1, size_t I1 >
			constexpr auto operator()(
				row_t< Ict1, I1 > d1, size_t d2
			)const noexcept{
				return row_t< false, 0 >(Op()(size_t(d1), d2));
			}

			template < bool Ict2, size_t I2 >
			constexpr auto operator()(
				size_t d1, row_t< Ict2, I2 > d2
			)const noexcept{
				return row_t< false, 0 >(Op()(d1, size_t(d2)));
			}
		};


	}


	template < bool Cct1, size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator+(
		col_t< Cct1, C1 > c1, col_t< Cct2, C2 > c2
	)noexcept{
		return detail::col_op< std::plus<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, typename T,
		typename = std::enable_if_t< std::is_integral_v< T > > >
	constexpr auto operator+(col_t< Cct1, C1 > c1, T c2)noexcept{
		return detail::col_op< std::plus<> >()(c1, c2);
	}

	template < bool Cct2, size_t C2, typename T,
		typename = std::enable_if_t< std::is_integral_v< T > > >
	constexpr auto operator+(T c1, col_t< Cct2, C2 > c2)noexcept{
		return detail::col_op< std::plus<> >()(c1, c2);
	}


	template < bool Cct1, size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator-(
		col_t< Cct1, C1 > c1, col_t< Cct2, C2 > c2
	)noexcept{
		return detail::col_op< std::minus<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, typename T,
		typename = std::enable_if_t< std::is_integral_v< T > > >
	constexpr auto operator-(col_t< Cct1, C1 > c1, T c2)noexcept{
		return detail::col_op< std::minus<> >()(c1, c2);
	}

	template < bool Cct2, size_t C2, typename T,
		typename = std::enable_if_t< std::is_integral_v< T > > >
	constexpr auto operator-(T c1, col_t< Cct2, C2 > c2)noexcept{
		return detail::col_op< std::minus<> >()(c1, c2);
	}


	template < bool Cct1, size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator*(
		col_t< Cct1, C1 > c1, col_t< Cct2, C2 > c2
	)noexcept{
		return detail::col_op< std::multiplies<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, typename T,
		typename = std::enable_if_t< std::is_integral_v< T > > >
	constexpr auto operator*(col_t< Cct1, C1 > c1, T c2)noexcept{
		return detail::col_op< std::multiplies<> >()(c1, c2);
	}

	template < bool Cct2, size_t C2, typename T,
		typename = std::enable_if_t< std::is_integral_v< T > > >
	constexpr auto operator*(T c1, col_t< Cct2, C2 > c2)noexcept{
		return detail::col_op< std::multiplies<> >()(c1, c2);
	}


	template < bool Cct1, size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator/(
		col_t< Cct1, C1 > c1, col_t< Cct2, C2 > c2
	)noexcept{
		return detail::col_op< std::divides<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, typename T,
		typename = std::enable_if_t< std::is_integral_v< T > > >
	constexpr auto operator/(col_t< Cct1, C1 > c1, T c2)noexcept{
		return detail::col_op< std::divides<> >()(c1, c2);
	}

	template < bool Cct2, size_t C2, typename T,
		typename = std::enable_if_t< std::is_integral_v< T > > >
	constexpr auto operator/(T c1, col_t< Cct2, C2 > c2)noexcept{
		return detail::col_op< std::divides<> >()(c1, c2);
	}


	template < bool Cct1, size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator%(
		col_t< Cct1, C1 > c1, col_t< Cct2, C2 > c2
	)noexcept{
		return detail::col_op< std::modulus<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, typename T,
		typename = std::enable_if_t< std::is_integral_v< T > > >
	constexpr auto operator%(col_t< Cct1, C1 > c1, T c2)noexcept{
		return detail::col_op< std::modulus<> >()(c1, c2);
	}

	template < bool Cct2, size_t C2, typename T,
		typename = std::enable_if_t< std::is_integral_v< T > > >
	constexpr auto operator%(T c1, col_t< Cct2, C2 > c2)noexcept{
		return detail::col_op< std::modulus<> >()(c1, c2);
	}


	template < bool Cct1, size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator+(
		row_t< Cct1, C1 > c1, row_t< Cct2, C2 > c2
	)noexcept{
		return detail::row_op< std::plus<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, typename T,
		typename = std::enable_if_t< std::is_integral_v< T > > >
	constexpr auto operator+(row_t< Cct1, C1 > c1, T c2)noexcept{
		return detail::row_op< std::plus<> >()(c1, c2);
	}

	template < bool Cct2, size_t C2, typename T,
		typename = std::enable_if_t< std::is_integral_v< T > > >
	constexpr auto operator+(T c1, row_t< Cct2, C2 > c2)noexcept{
		return detail::row_op< std::plus<> >()(c1, c2);
	}


	template < bool Cct1, size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator-(
		row_t< Cct1, C1 > c1, row_t< Cct2, C2 > c2
	)noexcept{
		return detail::row_op< std::minus<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, typename T,
		typename = std::enable_if_t< std::is_integral_v< T > > >
	constexpr auto operator-(row_t< Cct1, C1 > c1, T c2)noexcept{
		return detail::row_op< std::minus<> >()(c1, c2);
	}

	template < bool Cct2, size_t C2, typename T,
		typename = std::enable_if_t< std::is_integral_v< T > > >
	constexpr auto operator-(T c1, row_t< Cct2, C2 > c2)noexcept{
		return detail::row_op< std::minus<> >()(c1, c2);
	}


	template < bool Cct1, size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator*(
		row_t< Cct1, C1 > c1, row_t< Cct2, C2 > c2
	)noexcept{
		return detail::row_op< std::multiplies<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, typename T,
		typename = std::enable_if_t< std::is_integral_v< T > > >
	constexpr auto operator*(row_t< Cct1, C1 > c1, T c2)noexcept{
		return detail::row_op< std::multiplies<> >()(c1, c2);
	}

	template < bool Cct2, size_t C2, typename T,
		typename = std::enable_if_t< std::is_integral_v< T > > >
	constexpr auto operator*(T c1, row_t< Cct2, C2 > c2)noexcept{
		return detail::row_op< std::multiplies<> >()(c1, c2);
	}


	template < bool Cct1, size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator/(
		row_t< Cct1, C1 > c1, row_t< Cct2, C2 > c2
	)noexcept{
		return detail::row_op< std::divides<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, typename T,
		typename = std::enable_if_t< std::is_integral_v< T > > >
	constexpr auto operator/(row_t< Cct1, C1 > c1, T c2)noexcept{
		return detail::row_op< std::divides<> >()(c1, c2);
	}

	template < bool Cct2, size_t C2, typename T,
		typename = std::enable_if_t< std::is_integral_v< T > > >
	constexpr auto operator/(T c1, row_t< Cct2, C2 > c2)noexcept{
		return detail::row_op< std::divides<> >()(c1, c2);
	}


	template < bool Cct1, size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator%(
		row_t< Cct1, C1 > c1, row_t< Cct2, C2 > c2
	)noexcept{
		return detail::row_op< std::modulus<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, typename T,
		typename = std::enable_if_t< std::is_integral_v< T > > >
	constexpr auto operator%(row_t< Cct1, C1 > c1, T c2)noexcept{
		return detail::row_op< std::modulus<> >()(c1, c2);
	}

	template < bool Cct2, size_t C2, typename T,
		typename = std::enable_if_t< std::is_integral_v< T > > >
	constexpr auto operator%(T c1, row_t< Cct2, C2 > c2)noexcept{
		return detail::row_op< std::modulus<> >()(c1, c2);
	}


	template < size_t C1, size_t R1, size_t C2, size_t R2 >
	constexpr auto operator+(dims_t< C1, R1 > d1, dims_t< C2, R2 > d2)noexcept{
		return dims(d1.cols() + d2.cols(), d1.rows() + d2.rows());
	}

	template < size_t C1, size_t R1, size_t C2, size_t R2 >
	constexpr auto operator-(dims_t< C1, R1 > d1, dims_t< C2, R2 > d2)noexcept{
		return dims(d1.cols() - d2.cols(), d1.rows() - d2.rows());
	}

	template < size_t C1, size_t R1, size_t C2, size_t R2 >
	constexpr auto operator*(dims_t< C1, R1 > d1, dims_t< C2, R2 > d2)noexcept{
		return dims(d1.cols() * d2.cols(), d1.rows() * d2.rows());
	}

	template < size_t C1, size_t R1, size_t C2, size_t R2 >
	constexpr auto operator/(dims_t< C1, R1 > d1, dims_t< C2, R2 > d2)noexcept{
		return dims(d1.cols() / d2.cols(), d1.rows() / d2.rows());
	}

	template < size_t C1, size_t R1, size_t C2, size_t R2 >
	constexpr auto operator%(dims_t< C1, R1 > d1, dims_t< C2, R2 > d2)noexcept{
		return dims(d1.cols() % d2.cols(), d1.rows() % d2.rows());
	}

	template < size_t C, size_t R, typename T,
		typename = std::enable_if_t< std::is_integral_v< T > > >
	constexpr auto operator*(dims_t< C, R > d, T v)noexcept{
		return dims(d.cols() * v, d.rows() * v);
	}

	template < size_t C, size_t R, typename T,
		typename = std::enable_if_t< std::is_integral_v< T > > >
	constexpr auto operator/(dims_t< C, R > d, T v)noexcept{
		return dims(d.cols() / v, d.rows() / v);
	}

	template < size_t C, size_t R, typename T,
		typename = std::enable_if_t< std::is_integral_v< T > > >
	constexpr auto operator%(dims_t< C, R > d, T v)noexcept{
		return dims(d.cols() % v, d.rows() % v);
	}


	template < size_t C1, size_t R1, size_t C2, size_t R2 >
	constexpr bool operator==(dims_t< C1, R1 > a, dims_t< C2, R2 > b)noexcept{
		return a.cols() == b.cols() || a.rows() == b.rows();
	}

	template < size_t C1, size_t R1, size_t C2, size_t R2 >
	constexpr bool operator!=(dims_t< C1, R1 > a, dims_t< C2, R2 > b)noexcept{
		return !(a == b);
	}


	namespace detail{


		template < size_t N >
		constexpr size_t parse_int(char const(&arr)[N])noexcept{
			size_t number = 0;
			size_t base = 1;
			for(size_t i = 0; i < N; ++i){
				number += (static_cast< int >(arr[N - 1 - i]) - 48) * base;
				base *= 10;
			}
			return number;
		}


	}


	namespace literals{


		template < char ... C >
		constexpr auto operator"" _C()noexcept{
			static_assert(
				detail::parse_int< sizeof...(C) >({C ...}),
				"Compile time cols can not be 0, use '_C_rt' prefix instead"
			);
			return cols< detail::parse_int< sizeof...(C) >({C ...}) >();
		}

		template < char ... C >
		constexpr auto operator"" _C_rt()noexcept{
			return cols_rt< detail::parse_int< sizeof...(C) >({C ...}) >();
		}

		template < char ... C >
		constexpr auto operator"" _R()noexcept{
			static_assert(
				detail::parse_int< sizeof...(C) >({C ...}),
				"Compile time rows can not be 0, use '_R_rt' prefix instead"
			);
			return rows< detail::parse_int< sizeof...(C) >({C ...}) >();
		}

		template < char ... C >
		constexpr auto operator"" _R_rt()noexcept{
			return rows_rt< detail::parse_int< sizeof...(C) >({C ...}) >();
		}

		template < char ... C >
		constexpr auto operator"" _D()noexcept{
			static_assert(
				detail::parse_int< sizeof...(C) >({C ...}),
				"Compile time dims can not be 0, use '_D_rt' prefix instead"
			);
			return dims< detail::parse_int< sizeof...(C) >({C ...}) >();
		}

		template < char ... C >
		constexpr auto operator"" _D_rt()noexcept{
			return dims_rt< detail::parse_int< sizeof...(C) >({C ...}) >();
		}


	}


	namespace detail{


		template < typename T, typename U >
		constexpr auto get_first_of_same_ct(T a, U b){
			static_assert(a == b, "dimensions are not the same");
			return a;
		}

		template < typename T, typename U >
		constexpr auto get_first_of_same_rt(T a, U b){
			if(a != b){
				throw std::logic_error("dimensions are not the same");
			}
			return a;
		}


		template < template < bool, size_t > class init, size_t N1, size_t N2 >
		constexpr auto get_ct_if_available(
			init< true, N1 > a, init< true, N2 > b
		){
			return get_first_of_same_ct(a, b);
		}

		template < template < bool, size_t > class init, size_t N1, size_t N2 >
		constexpr auto get_ct_if_available(
			init< false, N1 > a, init< false, N2 > b
		){
			return get_first_of_same_ct(a, b);
		}

		template < template < bool, size_t > class init, size_t N1, size_t N2 >
		constexpr auto get_ct_if_available(
			init< true, N1 > a, init< false, N2 > b
		){
			return get_first_of_same_ct(a, b);
		}

		template < template < bool, size_t > class init, size_t N1, size_t N2 >
		constexpr auto get_ct_if_available(
			init< false, N1 > a, init< true, N2 > b
		){
			return get_first_of_same_ct(b, a);
		}

		template < template < bool, size_t > class init, size_t N1 >
		constexpr auto get_ct_if_available(
			init< true, N1 > a, init< false, 0 > b
		){
			return get_first_of_same_rt(a, b);
		}

		template < template < bool, size_t > class init, size_t N1 >
		constexpr auto get_ct_if_available(
			init< false, N1 > a, init< false, 0 > b
		){
			return get_first_of_same_rt(a, b);
		}

		template < template < bool, size_t > class init, size_t N2 >
		constexpr auto get_ct_if_available(
			init< false, 0 > a, init< true, N2 > b
		){
			return get_first_of_same_rt(b, a);
		}

		template < template < bool, size_t > class init, size_t N2 >
		constexpr auto get_ct_if_available(
			init< false, 0 > a, init< false, N2 > b
		){
			return get_first_of_same_rt(b, a);
		}

		template < template < bool, size_t > class init >
		constexpr auto get_ct_if_available(
			init< false, 0 > a, init< false, 0 > b
		){
			return get_first_of_same_rt(a, b);
		}

		template < template < bool, size_t > class init, bool Nct, size_t N >
		constexpr auto get_same(init< Nct, N > d){
			return d;
		}

		template <
			template < bool, size_t > class init,
			bool Nct1, size_t N1,
			bool Nct2, size_t N2,
			bool ... NctN, size_t ... Nn
		> constexpr auto get_same(
			init< Nct1, N1 > d1,
			init< Nct2, N2 > d2,
			init< NctN, Nn > ... dn
		){
			return get_same< init >(
				get_ct_if_available< init >(d1, d2), dn ...);
		}


	}


	template < bool ... Nct, size_t ... N >
	constexpr auto get(col_t< Nct, N > ... v){
		return detail::get_same< col_t >(v ...);
	}

	template < bool ... Nct, size_t ... N >
	constexpr auto get(row_t< Nct, N > ... v){
		return detail::get_same< row_t >(v ...);
	}

	template < bool ... Nct, size_t ... N >
	constexpr auto get(dim_t< Nct, N > ... v){
		return detail::get_same< dim_t >(v ...);
	}

	template < size_t ... C, size_t ... R >
	constexpr auto get(dims_t< C, R > ... v){
		return dims(get(v.cols() ...), get(v.rows() ...));
	}


}


#endif
