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


	template < typename ... T >
	constexpr bool one_of(T ... v){ return (... || v); }

	template < typename ... T >
	constexpr bool all_of(T ... v){ return (... && v); }


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


	template < typename Derived >
	struct dim_base;


	template < bool Cct, size_t C >
	struct col_t: dim_base< col_t< Cct, C > >{
		using dim_base< col_t< Cct, C > >::dim_base;
	};

	template < bool Rct, size_t R >
	struct row_t: dim_base< row_t< Rct, R > >{
		using dim_base< row_t< Rct, R > >::dim_base;
	};

	template < bool Nct, size_t N >
	struct dim_t: dim_base< dim_t< Nct, N > >{
		using dim_base< dim_t< Nct, N > >::dim_base;
	};


	template < template < bool, size_t > typename DimT, size_t N >
	struct dim_base< DimT< true, N > >{
		static constexpr size_t value = N;

		using value_type = size_t;

		constexpr dim_base()noexcept = default;

		constexpr operator size_t()const noexcept{ return value; }

		constexpr auto as_col()const noexcept{ return col_t< true, N >(); }
		constexpr auto as_row()const noexcept{ return row_t< true, N >(); }
		constexpr auto as_dim()const noexcept{ return dim_t< true, N >(); }
	};

	template < template < bool, size_t > typename DimT, size_t N >
	struct dim_base< DimT< false, N > >{
		static constexpr size_t value = N;

		using value_type = size_t;

		constexpr dim_base()noexcept = default;
		constexpr dim_base(DimT< true, N >&&)noexcept{}
		constexpr dim_base(DimT< true, N > const&)noexcept{}

		constexpr operator size_t()const noexcept{ return value; }

		constexpr auto as_col()const noexcept{ return col_t< false, N >(); }
		constexpr auto as_row()const noexcept{ return row_t< false, N >(); }
		constexpr auto as_dim()const noexcept{ return dim_t< false, N >(); }
	};

	template < template < bool, size_t > typename DimT >
	struct dim_base< DimT< false, 0 > >{
	public:
		static constexpr size_t value = 0;

		using value_type = size_t;

		constexpr dim_base(size_t n = 0)noexcept: v_(n) {}

		template < bool Nct, size_t N >
		constexpr dim_base(DimT< Nct, N >&&)noexcept: v_(N) {}

		template < bool Nct, size_t N >
		constexpr dim_base(DimT< Nct, N > const&)noexcept: v_(N) {}

		constexpr operator size_t()const noexcept{ return v_; }

		constexpr auto as_col()const noexcept{ return col_t< false, 0 >(v_); }
		constexpr auto as_row()const noexcept{ return row_t< false, 0 >(v_); }
		constexpr auto as_dim()const noexcept{ return dim_t< false, 0 >(v_); }

	private:
		size_t v_;
	};


	template < size_t C, size_t R >
	class dims_t: private col_t< C != 0, C >, private row_t< R != 0, R >{
	public:
		static constexpr size_t ct_cols = C;
		static constexpr size_t ct_rows = R;


		constexpr dims_t()noexcept = default;

		constexpr dims_t(
			col_t< C != 0, C > cols,
			row_t< R != 0, R > rows
		)noexcept: col_t< C != 0, C >(cols), row_t< R != 0, R >(rows) {}


		constexpr col_t< C != 0, C > cols()const noexcept{
			return *this;
		}

		constexpr row_t< R != 0, R > rows()const noexcept{
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
		return dims_t< Cct ? C : 0, 0 >(c, row_t< false, 0 >(r));
	}

	template < bool Rct, size_t R >
	constexpr auto dims(size_t c, row_t< Rct, R > r)noexcept{
		return dims_t< 0, Rct ? R : 0 >(col_t< false, 0 >(c), r);
	}

	template < bool Cct, size_t C, bool Rct, size_t R >
	constexpr auto dims(col_t< Cct, C > c, row_t< Rct, R > r)noexcept{
		return dims_t< Cct ? C : 0, Rct ? R : 0 >(c, r);
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


		template < template < bool, size_t > typename DimT, typename Op >
		struct arithmetic_op_t{
			template < bool Ict1, size_t I1, bool Ict2, size_t I2 >
			constexpr auto operator()(
				DimT< Ict1, I1 > /*d1*/, DimT< Ict2, I2 > /*d2*/
			)const noexcept{
				return DimT< Ict1 && Ict2, Op()(I1, I2) >();
			}

			template < bool Ict1, bool Ict2, size_t I2 >
			constexpr auto operator()(
				DimT< Ict1, 0 > d1, DimT< Ict2, I2 > d2
			)const noexcept{
				return DimT< Ict1 && Ict2, 0 >(Op()(size_t(d1), size_t(d2)));
			}

			template < bool Ict1, size_t I1, bool Ict2 >
			constexpr auto operator()(
				DimT< Ict1, I1 > d1, DimT< Ict2, 0 > d2
			)const noexcept{
				return DimT< Ict1 && Ict2, 0 >(Op()(size_t(d1), size_t(d2)));
			}

			template < bool Ict1, bool Ict2 >
			constexpr auto operator()(
				DimT< Ict1, 0 > d1, DimT< Ict2, 0 > d2
			)const noexcept{
				return DimT< Ict1 && Ict2, 0 >(Op()(size_t(d1), size_t(d2)));
			}

			template < bool Ict1, size_t I1 >
			constexpr auto operator()(
				DimT< Ict1, I1 > d1, size_t d2
			)const noexcept{
				return DimT< false, 0 >(Op()(size_t(d1), d2));
			}

			template < bool Ict2, size_t I2 >
			constexpr auto operator()(
				size_t d1, DimT< Ict2, I2 > d2
			)const noexcept{
				return DimT< false, 0 >(Op()(d1, size_t(d2)));
			}
		};


		template <
			template < bool, size_t > typename DimT1,
			template < bool, size_t > typename DimT2 >
		struct is_same_dim: std::false_type{};

		template < template < bool, size_t > typename DimT >
		struct is_same_dim< DimT, DimT >: std::true_type{};

		template <
			template < bool, size_t > typename DimT1,
			template < bool, size_t > typename DimT2 >
		constexpr auto is_same_dim_v = is_same_dim< DimT1, DimT2 >();


		template < typename Op,
			template < bool, size_t > typename DimT1, bool Cct1, size_t C1,
			template < bool, size_t > typename DimT2, bool Cct2, size_t C2 >
		constexpr auto
		arithmetic_op(DimT1< Cct1, C1 > c1, DimT2< Cct2, C2 > c2)noexcept{
			static_assert(is_same_dim_v< DimT1, DimT2 >,
				"You can not mix col_t, row_t and dim_t.");
			return detail::arithmetic_op_t< DimT1, Op >()(c1, c2);
		}

		template < typename Op,
			template < bool, size_t > typename DimT, bool Cct1, size_t C1,
			typename T, std::enable_if_t< std::is_integral_v< T > >* = nullptr >
		constexpr auto arithmetic_op(DimT< Cct1, C1 > c1, T c2)noexcept{
			return detail::arithmetic_op_t< DimT, Op >()(c1, c2);
		}

		template < typename Op,
			template < bool, size_t > typename DimT, bool Cct2, size_t C2,
			typename T, std::enable_if_t< std::is_integral_v< T > >* = nullptr >
		constexpr auto arithmetic_op(T c1, DimT< Cct2, C2 > c2)noexcept{
			return detail::arithmetic_op_t< DimT, Op >()(c1, c2);
		}


		template < typename T >
		struct is_a_dim: std::false_type{};

		template < bool Dct, size_t D >
		struct is_a_dim< col_t< Dct, D > >: std::true_type{};

		template < bool Dct, size_t D >
		struct is_a_dim< row_t< Dct, D > >: std::true_type{};

		template < bool Dct, size_t D >
		struct is_a_dim< dim_t< Dct, D > >: std::true_type{};

		template < typename T >
		constexpr auto is_a_dim_v = is_a_dim< T >();


		template < template < bool, size_t > typename DimT >
		struct is_a_dim_template: std::false_type{};

		template <>
		struct is_a_dim_template< col_t >: std::true_type{};

		template <>
		struct is_a_dim_template< row_t >: std::true_type{};

		template <>
		struct is_a_dim_template< dim_t >: std::true_type{};

		template < template < bool, size_t > typename DimT >
		constexpr auto is_a_dim_template_v = is_a_dim_template< DimT >();


		template < typename ... T >
		using enable_if_dim_op_t =
			std::enable_if_t<
				one_of(is_a_dim_v< T > ...) &&
				all_of(is_a_dim_v< T > || std::is_integral_v< T > ...) >;


	}



	template < typename L, typename R,
		detail::enable_if_dim_op_t< L, R >* = nullptr >
	constexpr auto operator+(L l, R r)noexcept{
		return detail::arithmetic_op< std::plus< size_t > >(l, r);
	}

	template < typename L, typename R,
		detail::enable_if_dim_op_t< L, R >* = nullptr >
	constexpr auto operator-(L l, R r)noexcept{
		return detail::arithmetic_op< std::minus< size_t > >(l, r);
	}

	template < typename L, typename R,
		detail::enable_if_dim_op_t< L, R >* = nullptr >
	constexpr auto operator*(L l, R r)noexcept{
		return detail::arithmetic_op< std::multiplies< size_t > >(l, r);
	}

	template < typename L, typename R,
		detail::enable_if_dim_op_t< L, R >* = nullptr >
	constexpr auto operator/(L l, R r)noexcept{
		return detail::arithmetic_op< std::divides< size_t > >(l, r);
	}

	template < typename L, typename R,
		detail::enable_if_dim_op_t< L, R >* = nullptr >
	constexpr auto operator%(L l, R r)noexcept{
		return detail::arithmetic_op< std::modulus< size_t > >(l, r);
	}

	template < typename L, typename R,
		detail::enable_if_dim_op_t< L, R >* = nullptr >
	constexpr auto operator==(L l, R r)noexcept{
		return size_t(l) == size_t(r);
	}

	template < typename L, typename R,
		detail::enable_if_dim_op_t< L, R >* = nullptr >
	constexpr auto operator!=(L l, R r)noexcept{
		return size_t(l) != size_t(r);
	}

	template < typename L, typename R,
		detail::enable_if_dim_op_t< L, R >* = nullptr >
	constexpr auto operator<(L l, R r)noexcept{
		return size_t(l) < size_t(r);
	}

	template < typename L, typename R,
		detail::enable_if_dim_op_t< L, R >* = nullptr >
	constexpr auto operator<=(L l, R r)noexcept{
		return size_t(l) <= size_t(r);
	}

	template < typename L, typename R,
		detail::enable_if_dim_op_t< L, R >* = nullptr >
	constexpr auto operator>(L l, R r)noexcept{
		return size_t(l) > size_t(r);
	}

	template < typename L, typename R,
		detail::enable_if_dim_op_t< L, R >* = nullptr >
	constexpr auto operator>=(L l, R r)noexcept{
		return size_t(l) >= size_t(r);
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

	template < size_t C, size_t R, bool Dct, size_t D >
	constexpr auto operator*(dims_t< C, R > d, dim_t< Dct, D > v)noexcept{
		return dims(d.cols() * v.as_col(), d.rows() * v.as_row());
	}

	template < size_t C, size_t R, bool Dct, size_t D >
	constexpr auto operator/(dims_t< C, R > d, dim_t< Dct, D > v)noexcept{
		return dims(d.cols() / v.as_col(), d.rows() / v.as_row());
	}

	template < size_t C, size_t R, bool Dct, size_t D >
	constexpr auto operator%(dims_t< C, R > d, dim_t< Dct, D > v)noexcept{
		return dims(d.cols() % v.as_col(), d.rows() % v.as_row());
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


		template <
			template < bool, size_t > typename DimT, size_t N1, size_t N2 >
		constexpr auto get_ct_if_available(
			DimT< true, N1 > a, DimT< true, N2 > b
		){
			return get_first_of_same_ct(a, b);
		}

		template <
			template < bool, size_t > typename DimT, size_t N1, size_t N2 >
		constexpr auto get_ct_if_available(
			DimT< false, N1 > a, DimT< false, N2 > b
		){
			return get_first_of_same_ct(a, b);
		}

		template <
			template < bool, size_t > typename DimT, size_t N1, size_t N2 >
		constexpr auto get_ct_if_available(
			DimT< true, N1 > a, DimT< false, N2 > b
		){
			return get_first_of_same_ct(a, b);
		}

		template <
			template < bool, size_t > typename DimT, size_t N1, size_t N2 >
		constexpr auto get_ct_if_available(
			DimT< false, N1 > a, DimT< true, N2 > b
		){
			return get_first_of_same_ct(b, a);
		}

		template < template < bool, size_t > typename DimT, size_t N1 >
		constexpr auto get_ct_if_available(
			DimT< true, N1 > a, DimT< false, 0 > b
		){
			return get_first_of_same_rt(a, b);
		}

		template < template < bool, size_t > typename DimT, size_t N1 >
		constexpr auto get_ct_if_available(
			DimT< false, N1 > a, DimT< false, 0 > b
		){
			return get_first_of_same_rt(a, b);
		}

		template < template < bool, size_t > typename DimT, size_t N2 >
		constexpr auto get_ct_if_available(
			DimT< false, 0 > a, DimT< true, N2 > b
		){
			return get_first_of_same_rt(b, a);
		}

		template < template < bool, size_t > typename DimT, size_t N2 >
		constexpr auto get_ct_if_available(
			DimT< false, 0 > a, DimT< false, N2 > b
		){
			return get_first_of_same_rt(b, a);
		}

		template < template < bool, size_t > typename DimT >
		constexpr auto get_ct_if_available(
			DimT< false, 0 > a, DimT< false, 0 > b
		){
			return get_first_of_same_rt(a, b);
		}

		template < template < bool, size_t > typename DimT, bool Nct, size_t N >
		constexpr auto get_same(DimT< Nct, N > d){
			return d;
		}

		template <
			template < bool, size_t > typename DimT,
			bool Nct1, size_t N1,
			bool Nct2, size_t N2,
			bool ... NctN, size_t ... Nn
		> constexpr auto get_same(
			DimT< Nct1, N1 > d1,
			DimT< Nct2, N2 > d2,
			DimT< NctN, Nn > ... dn
		){
			return get_same< DimT >(
				get_ct_if_available< DimT >(d1, d2), dn ...);
		}


	}


	template <
		template < bool, size_t > typename DimT, bool ... Nct, size_t ... N,
		std::enable_if_t< detail::is_a_dim_template_v< DimT > >* = nullptr >
	constexpr auto get(DimT< Nct, N > ... v){
		return detail::get_same< DimT >(v ...);
	}

	template < size_t ... C, size_t ... R >
	constexpr auto get(dims_t< C, R > ... v){
		return dims(get(v.cols() ...), get(v.rows() ...));
	}


}


#endif
