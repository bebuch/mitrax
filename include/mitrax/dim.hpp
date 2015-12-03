//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
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


namespace mitrax{


	using size_t = std::size_t;

	using ptrdiff_t = std::ptrdiff_t;


	template < typename F >
	using fn_xy =
		std::decay_t< decltype(std::declval< F >()(size_t(), size_t())) >;

	template < typename F >
	using fn_i = std::decay_t< decltype(std::declval< F >()(size_t())) >;


	template < typename T >
	using value_type_t = typename T::value_type;

	template < bool I >
	using bool_t = std::integral_constant< bool, I >;


	constexpr size_t dim(bool is_compile_time, size_t n)noexcept{
		return is_compile_time ? n : 0;
	}


	template < size_t V >
	struct size_ct{
		static constexpr size_t value = V;

		using value_type = size_t;

		using type = size_ct;

		constexpr operator size_t()const noexcept{
			return value;
		}

		constexpr size_t operator()()const noexcept{
			return value;
		}
	};


	struct size_rt: size_ct< 0 >{
	public:
		constexpr size_rt()noexcept: v_(0) {}

		constexpr size_rt(size_t v)noexcept: v_(v) {}


		constexpr operator size_t()const noexcept{
			return v_;
		}

		constexpr size_t operator()()const noexcept{
			return v_;
		}

	public:
		size_t v_;
	};


	template < size_t I >
	struct col_t;

	template < size_t I >
	struct row_t;

	template < size_t C, size_t R >
	class dim_t;


	template < bool CompileTimeTarget, size_t I >
	struct col_init_t;

	template < bool CompileTimeTarget, size_t I >
	struct row_init_t;

	template < bool CompileTimeTarget, size_t I >
	struct dim_init_t;


	template < size_t I >
	struct col_t: size_ct< I >{
		using size_ct< I >::size_ct;

		constexpr auto init()const noexcept{
			return col_init_t< true, I >();
		}

		constexpr auto as_row()const noexcept{
			return row_t< I >();
		}
	};

	template <>
	struct col_t< 0 >: size_rt{
		using size_rt::size_rt;

		constexpr auto init()const noexcept;
		constexpr auto as_row()const noexcept;
	};


	template < size_t I >
	struct row_t: size_ct< I >{
		using size_ct< I >::size_ct;

		constexpr auto init()const noexcept{
			return row_init_t< true, I >();
		}

		constexpr auto as_col()const noexcept{
			return col_t< I >();
		}
	};

	template <>
	struct row_t< 0 >: size_rt{
		using size_rt::size_rt;

		constexpr auto init()const noexcept;
		constexpr auto as_col()const noexcept;
	};


	template < size_t C, size_t R >
	class dim_t{
	public:
		constexpr dim_t(col_t< C > cols, row_t< R > rows)noexcept:
			cols_(cols), rows_(rows) {}

		constexpr dim_t(dim_t const&)noexcept = default;

		constexpr dim_t(dim_t&&)noexcept = default;


		constexpr dim_t& operator=(dim_t const&)noexcept = default;

		constexpr dim_t& operator=(dim_t&&)noexcept = default;


		constexpr col_t< C > cols()const noexcept{
			return cols_;
		}

		constexpr row_t< R > rows()const noexcept{
			return rows_;
		}


		constexpr void set_cols(col_t< C > c)noexcept{
			cols_ = c;
		}

		constexpr void set_rows(row_t< R > r)noexcept{
			rows_ = r;
		}

		constexpr void set(col_t< C > c, row_t< R > r)noexcept{
			cols_ = c;
			rows_ = r;
		}


	private:
		col_t< C > cols_;
		row_t< R > rows_;
	};


	constexpr auto dims(size_t c, size_t r)noexcept{
		return dim_t< 0, 0 >(col_t< 0 >(c), row_t< 0 >(r));
	}

	template < size_t C >
	constexpr auto dims(col_t< C > c, size_t r)noexcept{
		return dim_t< C, 0 >(c, row_t< 0 >(r));
	}

	template < bool Cct, size_t C >
	constexpr auto dims(col_init_t< Cct, C > c, size_t r)noexcept{
		return dim_t< dim(Cct, C), 0 >(c.get(), row_t< 0 >(r));
	}

	template < bool Cct, size_t C, size_t R >
	constexpr auto dims(col_init_t< Cct, C > c, row_t< R > r)noexcept{
		return dim_t< dim(Cct, C), R >(c.get(), r);
	}

	template < size_t R >
	constexpr auto dims(size_t c, row_t< R > r)noexcept{
		return dim_t< 0, R >(col_t< 0 >(c), r);
	}

	template < bool Rct, size_t R >
	constexpr auto dims(size_t c, row_init_t< Rct, R > r)noexcept{
		return dim_t< 0, dim(Rct, R) >(col_t< 0 >(c), r.get());
	}

	template < size_t C, bool Rct, size_t R >
	constexpr auto dims(col_t< C > c, row_init_t< Rct, R > r)noexcept{
		return dim_t< C, dim(Rct, R) >(c, r.get());
	}

	template < size_t C, size_t R >
	constexpr auto dims(col_t< C > c, row_t< R > r)noexcept{
		return dim_t< C, R >(c, r);
	}

	template < bool Cct, size_t C, bool Rct, size_t R >
	constexpr auto dims(
		col_init_t< Cct, C > c,
		row_init_t< Rct, R > r
	)noexcept{
		return dim_t< dim(Cct, C), dim(Rct, R) >(c.get(), r.get());
	}

	template < bool Dct, size_t D >
	constexpr auto dims(dim_init_t< Dct, D > d)noexcept{
		return dims(d.as_col(), d.as_row());
	}

	template < typename T, size_t C >
	void dims(T, col_t< C >) = delete;

	template < typename T, size_t R >
	void dims(row_t< R >, T) = delete;

	template < size_t C, size_t R >
	void dims(row_t< R >, col_t< C >) = delete;

	template < size_t C, size_t R >
	void dims(col_t< R >, col_t< C >) = delete;

	template < size_t C, size_t R >
	void dims(row_t< R >, row_t< C >) = delete;

	template < typename T, bool Cct, size_t C >
	void dims(T, col_init_t< Cct, C >) = delete;

	template < typename T, bool Rct, size_t R >
	void dims(row_init_t< Rct, R >, T) = delete;

	template < bool Cct, size_t C, bool Rct, size_t R >
	void dims(row_init_t< Rct, R >, col_init_t< Cct, C >) = delete;

	template < bool Cct, size_t C, bool Rct, size_t R >
	void dims(col_init_t< Rct, R >, col_init_t< Cct, C >) = delete;

	template < bool Cct, size_t C, bool Rct, size_t R >
	void dims(row_init_t< Rct, R >, row_init_t< Cct, C >) = delete;

	template < size_t C, bool Rct, size_t R >
	void dims(row_init_t< Rct, R >, col_t< C >) = delete;

	template < bool Cct, size_t C, size_t R >
	void dims(row_t< R >, col_init_t< Cct, C >) = delete;


	template < size_t I >
	struct col_init_t< true, I >: size_ct< I >{
		constexpr auto get()const noexcept{
			return col_t< I >();
		}

		constexpr auto as_row()const noexcept{
			return row_init_t< true, I >();
		}

		constexpr auto as_dim()const noexcept{
			return dim_init_t< true, I >();
		}
	};

	template < size_t I >
	struct col_init_t< false, I >: size_ct< I >{
		constexpr auto get()const noexcept{
			return col_t< 0 >(I);
		}

		constexpr auto as_row()const noexcept{
			return row_init_t< false, I >();
		}

		constexpr auto as_dim()const noexcept{
			return dim_init_t< false, I >();
		}
	};

	template <>
	struct col_init_t< false, 0 >: size_rt{
		using size_rt::size_rt;

		constexpr auto get()const noexcept;
		constexpr auto as_row()const noexcept;
		constexpr auto as_dim()const noexcept;
	};


	template < size_t I >
	struct row_init_t< true, I >: size_ct< I >{
		constexpr auto get()const noexcept{
			return row_t< I >();
		}

		constexpr auto as_col()const noexcept{
			return col_init_t< true, I >();
		}

		constexpr auto as_dim()const noexcept{
			return dim_init_t< true, I >();
		}
	};

	template < size_t I >
	struct row_init_t< false, I >: size_ct< I >{
		constexpr auto get()const noexcept{
			return row_t< 0 >(I);
		}

		constexpr auto as_col()const noexcept{
			return col_init_t< false, I >();
		}

		constexpr auto as_dim()const noexcept{
			return dim_init_t< false, I >();
		}
	};

	template <>
	struct row_init_t< false, 0 >: size_rt{
		using size_rt::size_rt;

		constexpr auto get()const noexcept;
		constexpr auto as_col()const noexcept;
		constexpr auto as_dim()const noexcept;
	};


	template < size_t I >
	struct dim_init_t< true, I >: size_ct< I >{
		constexpr auto get()const noexcept{
			return dims(col_t< I >(), row_t< I >());
		}

		constexpr auto as_col()const noexcept{
			return col_init_t< true, I >();
		}

		constexpr auto as_row()const noexcept{
			return row_init_t< true, I >();
		}
	};

	template < size_t I >
	struct dim_init_t< false, I >: size_ct< I >{
		constexpr auto get()const noexcept{
			return dims(I, I);
		}

		constexpr auto as_col()const noexcept{
			return col_init_t< false, I >();
		}

		constexpr auto as_row()const noexcept{
			return row_init_t< false, I >();
		}
	};

	template <>
	struct dim_init_t< false, 0 >: size_rt{
		using size_rt::size_rt;

		constexpr auto get()const noexcept;
		constexpr auto as_col()const noexcept;
		constexpr auto as_row()const noexcept;
	};


	constexpr auto col_init_t< false, 0 >::get()const noexcept{
		return col_t< 0 >(static_cast< size_t >(*this));
	}

	constexpr auto col_init_t< false, 0 >::as_row()const noexcept{
		return row_init_t< false, 0 >(static_cast< size_t >(*this));
	}

	constexpr auto col_init_t< false, 0 >::as_dim()const noexcept{
		return dim_init_t< false, 0 >(static_cast< size_t >(*this));
	}


	constexpr auto row_init_t< false, 0 >::get()const noexcept{
		return row_t< 0 >(static_cast< size_t >(*this));
	}

	constexpr auto row_init_t< false, 0 >::as_col()const noexcept{
		return col_init_t< false, 0 >(static_cast< size_t >(*this));
	}

	constexpr auto row_init_t< false, 0 >::as_dim()const noexcept{
		return dim_init_t< false, 0 >(static_cast< size_t >(*this));
	}


	constexpr auto dim_init_t< false, 0 >::get()const noexcept{
		auto v = static_cast< size_t >(*this);
		return dims(v, v);
	}

	constexpr auto dim_init_t< false, 0 >::as_col()const noexcept{
		return col_init_t< false, 0 >(static_cast< size_t >(*this));
	}

	constexpr auto dim_init_t< false, 0 >::as_row()const noexcept{
		return row_init_t< false, 0 >(static_cast< size_t >(*this));
	}


	constexpr auto col_t< 0 >::as_row()const noexcept{
		return row_t< 0 >(static_cast< size_t >(*this));
	}

	constexpr auto col_t< 0 >::init()const noexcept{
		return col_init_t< false, 0 >(static_cast< size_t >(*this));
	}


	constexpr auto row_t< 0 >::as_col()const noexcept{
		return col_t< 0 >(static_cast< size_t >(*this));
	}

	constexpr auto row_t< 0 >::init()const noexcept{
		return row_init_t< false, 0 >(static_cast< size_t >(*this));
	}


	constexpr auto cols(size_t c)noexcept{
		return col_init_t< false, 0 >(c);
	}

	constexpr auto rows(size_t r)noexcept{
		return row_init_t< false, 0 >(r);
	}

	constexpr auto dims(size_t d)noexcept{
		return dim_init_t< false, 0 >(d);
	}


	template < size_t I >
	constexpr auto cols()noexcept{
		return col_init_t< true, I >();
	}

	template < size_t I >
	constexpr auto rows()noexcept{
		return row_init_t< true, I >();
	}

	template < size_t I >
	constexpr auto dims()noexcept{
		return dim_init_t< true, I >();
	}


	template < size_t I >
	constexpr auto cols_rt()noexcept{
		return col_init_t< false, I >();
	}

	template < size_t I >
	constexpr auto rows_rt()noexcept{
		return row_init_t< false, I >();
	}

	template < size_t I >
	constexpr auto dims_rt()noexcept{
		return dim_init_t< false, I >();
	}


	namespace detail{


		template < typename Op >
		struct col_op{
			template < size_t I1, size_t I2 >
			constexpr auto operator()(col_t< I1 >, col_t< I2 >)const noexcept{
				return col_t< Op()(I1, I2) >().init();
			}

			template < size_t I >
			constexpr auto
			operator()(col_t< 0 > d1, col_t< I > d2)const noexcept{
				return col_t< 0 >(
					Op()(static_cast< size_t >(d1), static_cast< size_t >(d2))
				).init();
			}

			template < size_t I >
			constexpr auto
			operator()(col_t< I > d1, col_t< 0 > d2)const noexcept{
				return col_t< 0 >(
					Op()(static_cast< size_t >(d1), static_cast< size_t >(d2))
				).init();
			}

			constexpr auto
			operator()(col_t< 0 > d1, col_t< 0 > d2)const noexcept{
				return col_t< 0 >(
					Op()(static_cast< size_t >(d1), static_cast< size_t >(d2))
				).init();
			}

			template < size_t I >
			constexpr auto operator()(col_t< I > d1, size_t d2)const noexcept{
				return col_t< 0 >(Op()(static_cast< size_t >(d1), d2)).init();
			}

			template < size_t I >
			constexpr auto operator()(size_t d1, col_t< I > d2)const noexcept{
				return col_t< 0 >(Op()(d1, static_cast< size_t >(d2))).init();
			}


			template < bool Ict1, size_t I1, bool Ict2, size_t I2 >
			constexpr auto operator()(
				col_init_t< Ict1, I1 > d1, col_init_t< Ict2, I2 > d2
			)const noexcept{
				return (*this)(d1.get(), d2.get());
			}

			template < bool Ict1, size_t I1, size_t I2 >
			constexpr auto operator()(
				col_init_t< Ict1, I1 > d1, col_t< I2 > d2
			)const noexcept{
				return (*this)(d1.get(), d2);
			}

			template < size_t I1, bool Ict2, size_t I2 >
			constexpr auto operator()(
				col_t< I1 > d1, col_init_t< Ict2, I2 > d2
			)const noexcept{
				return (*this)(d1, d2.get());
			}

			template < bool Ict1, size_t I1 >
			constexpr auto operator()(
				col_init_t< Ict1, I1 > d1, size_t d2
			)const noexcept{
				return (*this)(d1.get(), d2);
			}

			template < bool Ict2, size_t I2 >
			constexpr auto operator()(
				size_t d1, col_init_t< Ict2, I2 > d2
			)const noexcept{
				return (*this)(d1, d2.get());
			}
		};


		template < typename Op >
		struct row_op{
			template < size_t I1, size_t I2 >
			constexpr auto operator()(row_t< I1 >, row_t< I2 >)const noexcept{
				return row_t< Op()(I1, I2) >().init();
			}

			template < size_t I >
			constexpr auto
			operator()(row_t< 0 > d1, row_t< I > d2)const noexcept{
				return row_t< 0 >(
					Op()(static_cast< size_t >(d1), static_cast< size_t >(d2))
				).init();
			}

			template < size_t I >
			constexpr auto
			operator()(row_t< I > d1, row_t< 0 > d2)const noexcept{
				return row_t< 0 >(
					Op()(static_cast< size_t >(d1), static_cast< size_t >(d2))
				).init();
			}

			constexpr auto
			operator()(row_t< 0 > d1, row_t< 0 > d2)const noexcept{
				return row_t< 0 >(
					Op()(static_cast< size_t >(d1), static_cast< size_t >(d2))
				).init();
			}

			template < size_t I >
			constexpr auto operator()(row_t< I > d1, size_t d2)const noexcept{
				return row_t< 0 >(Op()(static_cast< size_t >(d1), d2)).init();
			}

			template < size_t I >
			constexpr auto operator()(size_t d1, row_t< I > d2)const noexcept{
				return row_t< 0 >(Op()(d1, static_cast< size_t >(d2))).init();
			}


			template < bool Ict1, size_t I1, bool Ict2, size_t I2 >
			constexpr auto operator()(
				row_init_t< Ict1, I1 > d1, row_init_t< Ict2, I2 > d2
			)const noexcept{
				return (*this)(d1.get(), d2.get());
			}

			template < bool Ict1, size_t I1, size_t I2 >
			constexpr auto operator()(
				row_init_t< Ict1, I1 > d1, row_t< I2 > d2
			)const noexcept{
				return (*this)(d1.get(), d2);
			}

			template < size_t I1, bool Ict2, size_t I2 >
			constexpr auto operator()(
				row_t< I1 > d1, row_init_t< Ict2, I2 > d2
			)const noexcept{
				return (*this)(d1, d2.get());
			}

			template < bool Ict1, size_t I1 >
			constexpr auto operator()(
				row_init_t< Ict1, I1 > d1, size_t d2
			)const noexcept{
				return (*this)(d1.get(), d2);
			}

			template < bool Ict2, size_t I2 >
			constexpr auto operator()(
				size_t d1, row_init_t< Ict2, I2 > d2
			)const noexcept{
				return (*this)(d1, d2.get());
			}
		};


	}


	template < size_t C1, size_t C2 >
	constexpr auto operator+(col_t< C1 > c1, col_t< C2 > c2)noexcept{
		return detail::col_op< std::plus<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, size_t C2 >
	constexpr auto operator+(
		col_init_t< Cct1, C1 > c1, col_t< C2 > c2
	)noexcept{
		return detail::col_op< std::plus<> >()(c1, c2);
	}

	template < size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator+(
		col_t< C1 > c1, col_init_t< Cct2, C2 > c2
	)noexcept{
		return detail::col_op< std::plus<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator+(
		col_init_t< Cct1, C1 > c1, col_init_t< Cct2, C2 > c2
	)noexcept{
		return detail::col_op< std::plus<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, size_t C2 >
	constexpr auto operator+(col_init_t< Cct1, C1 > c1, size_t c2)noexcept{
		return detail::col_op< std::plus<> >()(c1, c2);
	}

	template < size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator+(size_t c1, col_init_t< Cct2, C2 > c2)noexcept{
		return detail::col_op< std::plus<> >()(c1, c2);
	}

	template < size_t C >
	constexpr auto operator+(size_t c1, col_t< C > c2)noexcept{
		return detail::col_op< std::plus<> >()(c1, c2);
	}

	template < size_t C >
	constexpr auto operator+(col_t< C > c1, size_t c2)noexcept{
		return detail::col_op< std::plus<> >()(c1, c2);
	}


	template < size_t C1, size_t C2 >
	constexpr auto operator-(col_t< C1 > c1, col_t< C2 > c2)noexcept{
		return detail::col_op< std::minus<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, size_t C2 >
	constexpr auto operator-(
		col_init_t< Cct1, C1 > c1, col_t< C2 > c2
	)noexcept{
		return detail::col_op< std::minus<> >()(c1, c2);
	}

	template < size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator-(
		col_t< C1 > c1, col_init_t< Cct2, C2 > c2
	)noexcept{
		return detail::col_op< std::minus<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator-(
		col_init_t< Cct1, C1 > c1, col_init_t< Cct2, C2 > c2
	)noexcept{
		return detail::col_op< std::minus<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, size_t C2 >
	constexpr auto operator-(col_init_t< Cct1, C1 > c1, size_t c2)noexcept{
		return detail::col_op< std::minus<> >()(c1, c2);
	}

	template < size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator-(size_t c1, col_init_t< Cct2, C2 > c2)noexcept{
		return detail::col_op< std::minus<> >()(c1, c2);
	}

	template < size_t C >
	constexpr auto operator-(size_t c1, col_t< C > c2)noexcept{
		return detail::col_op< std::minus<> >()(c1, c2);
	}

	template < size_t C >
	constexpr auto operator-(col_t< C > c1, size_t c2)noexcept{
		return detail::col_op< std::minus<> >()(c1, c2);
	}


	template < size_t C1, size_t C2 >
	constexpr auto operator*(col_t< C1 > c1, col_t< C2 > c2)noexcept{
		return detail::col_op< std::multiplies<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, size_t C2 >
	constexpr auto operator*(
		col_init_t< Cct1, C1 > c1, col_t< C2 > c2
	)noexcept{
		return detail::col_op< std::multiplies<> >()(c1, c2);
	}

	template < size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator*(
		col_t< C1 > c1, col_init_t< Cct2, C2 > c2
	)noexcept{
		return detail::col_op< std::multiplies<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator*(
		col_init_t< Cct1, C1 > c1, col_init_t< Cct2, C2 > c2
	)noexcept{
		return detail::col_op< std::multiplies<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, size_t C2 >
	constexpr auto operator*(col_init_t< Cct1, C1 > c1, size_t c2)noexcept{
		return detail::col_op< std::multiplies<> >()(c1, c2);
	}

	template < size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator*(size_t c1, col_init_t< Cct2, C2 > c2)noexcept{
		return detail::col_op< std::multiplies<> >()(c1, c2);
	}

	template < size_t C >
	constexpr auto operator*(size_t c1, col_t< C > c2)noexcept{
		return detail::col_op< std::multiplies<> >()(c1, c2);
	}

	template < size_t C >
	constexpr auto operator*(col_t< C > c1, size_t c2)noexcept{
		return detail::col_op< std::multiplies<> >()(c1, c2);
	}


	template < size_t C1, size_t C2 >
	constexpr auto operator/(col_t< C1 > c1, col_t< C2 > c2)noexcept{
		return detail::col_op< std::divides<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, size_t C2 >
	constexpr auto operator/(
		col_init_t< Cct1, C1 > c1, col_t< C2 > c2
	)noexcept{
		return detail::col_op< std::divides<> >()(c1, c2);
	}

	template < size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator/(
		col_t< C1 > c1, col_init_t< Cct2, C2 > c2
	)noexcept{
		return detail::col_op< std::divides<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator/(
		col_init_t< Cct1, C1 > c1, col_init_t< Cct2, C2 > c2
	)noexcept{
		return detail::col_op< std::divides<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, size_t C2 >
	constexpr auto operator/(col_init_t< Cct1, C1 > c1, size_t c2)noexcept{
		return detail::col_op< std::divides<> >()(c1, c2);
	}

	template < size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator/(size_t c1, col_init_t< Cct2, C2 > c2)noexcept{
		return detail::col_op< std::divides<> >()(c1, c2);
	}

	template < size_t C >
	constexpr auto operator/(size_t c1, col_t< C > c2)noexcept{
		return detail::col_op< std::divides<> >()(c1, c2);
	}

	template < size_t C >
	constexpr auto operator/(col_t< C > c1, size_t c2)noexcept{
		return detail::col_op< std::divides<> >()(c1, c2);
	}


	template < size_t C1, size_t C2 >
	constexpr auto operator%(col_t< C1 > c1, col_t< C2 > c2)noexcept{
		return detail::col_op< std::modulus<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, size_t C2 >
	constexpr auto operator%(
		col_init_t< Cct1, C1 > c1, col_t< C2 > c2
	)noexcept{
		return detail::col_op< std::modulus<> >()(c1, c2);
	}

	template < size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator%(
		col_t< C1 > c1, col_init_t< Cct2, C2 > c2
	)noexcept{
		return detail::col_op< std::modulus<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator%(
		col_init_t< Cct1, C1 > c1, col_init_t< Cct2, C2 > c2
	)noexcept{
		return detail::col_op< std::modulus<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, size_t C2 >
	constexpr auto operator%(col_init_t< Cct1, C1 > c1, size_t c2)noexcept{
		return detail::col_op< std::modulus<> >()(c1, c2);
	}

	template < size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator%(size_t c1, col_init_t< Cct2, C2 > c2)noexcept{
		return detail::col_op< std::modulus<> >()(c1, c2);
	}

	template < size_t C >
	constexpr auto operator%(size_t c1, col_t< C > c2)noexcept{
		return detail::col_op< std::modulus<> >()(c1, c2);
	}

	template < size_t C >
	constexpr auto operator%(col_t< C > c1, size_t c2)noexcept{
		return detail::col_op< std::modulus<> >()(c1, c2);
	}


	template < size_t C1, size_t C2 >
	constexpr auto operator+(row_t< C1 > c1, row_t< C2 > c2)noexcept{
		return detail::row_op< std::plus<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, size_t C2 >
	constexpr auto operator+(
		row_init_t< Cct1, C1 > c1, row_t< C2 > c2
	)noexcept{
		return detail::row_op< std::plus<> >()(c1, c2);
	}

	template < size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator+(
		row_t< C1 > c1, row_init_t< Cct2, C2 > c2
	)noexcept{
		return detail::row_op< std::plus<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator+(
		row_init_t< Cct1, C1 > c1, row_init_t< Cct2, C2 > c2
	)noexcept{
		return detail::row_op< std::plus<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, size_t C2 >
	constexpr auto operator+(row_init_t< Cct1, C1 > c1, size_t c2)noexcept{
		return detail::row_op< std::plus<> >()(c1, c2);
	}

	template < size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator+(size_t c1, row_init_t< Cct2, C2 > c2)noexcept{
		return detail::row_op< std::plus<> >()(c1, c2);
	}

	template < size_t C >
	constexpr auto operator+(size_t c1, row_t< C > c2)noexcept{
		return detail::row_op< std::plus<> >()(c1, c2);
	}

	template < size_t C >
	constexpr auto operator+(row_t< C > c1, size_t c2)noexcept{
		return detail::row_op< std::plus<> >()(c1, c2);
	}


	template < size_t C1, size_t C2 >
	constexpr auto operator-(row_t< C1 > c1, row_t< C2 > c2)noexcept{
		return detail::row_op< std::minus<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, size_t C2 >
	constexpr auto operator-(
		row_init_t< Cct1, C1 > c1, row_t< C2 > c2
	)noexcept{
		return detail::row_op< std::minus<> >()(c1, c2);
	}

	template < size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator-(
		row_t< C1 > c1, row_init_t< Cct2, C2 > c2
	)noexcept{
		return detail::row_op< std::minus<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator-(
		row_init_t< Cct1, C1 > c1, row_init_t< Cct2, C2 > c2
	)noexcept{
		return detail::row_op< std::minus<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, size_t C2 >
	constexpr auto operator-(row_init_t< Cct1, C1 > c1, size_t c2)noexcept{
		return detail::row_op< std::minus<> >()(c1, c2);
	}

	template < size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator-(size_t c1, row_init_t< Cct2, C2 > c2)noexcept{
		return detail::row_op< std::minus<> >()(c1, c2);
	}

	template < size_t C >
	constexpr auto operator-(size_t c1, row_t< C > c2)noexcept{
		return detail::row_op< std::minus<> >()(c1, c2);
	}

	template < size_t C >
	constexpr auto operator-(row_t< C > c1, size_t c2)noexcept{
		return detail::row_op< std::minus<> >()(c1, c2);
	}


	template < size_t C1, size_t C2 >
	constexpr auto operator*(row_t< C1 > c1, row_t< C2 > c2)noexcept{
		return detail::row_op< std::multiplies<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, size_t C2 >
	constexpr auto operator*(
		row_init_t< Cct1, C1 > c1, row_t< C2 > c2
	)noexcept{
		return detail::row_op< std::multiplies<> >()(c1, c2);
	}

	template < size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator*(
		row_t< C1 > c1, row_init_t< Cct2, C2 > c2
	)noexcept{
		return detail::row_op< std::multiplies<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator*(
		row_init_t< Cct1, C1 > c1, row_init_t< Cct2, C2 > c2
	)noexcept{
		return detail::row_op< std::multiplies<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, size_t C2 >
	constexpr auto operator*(row_init_t< Cct1, C1 > c1, size_t c2)noexcept{
		return detail::row_op< std::multiplies<> >()(c1, c2);
	}

	template < size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator*(size_t c1, row_init_t< Cct2, C2 > c2)noexcept{
		return detail::row_op< std::multiplies<> >()(c1, c2);
	}

	template < size_t C >
	constexpr auto operator*(size_t c1, row_t< C > c2)noexcept{
		return detail::row_op< std::multiplies<> >()(c1, c2);
	}

	template < size_t C >
	constexpr auto operator*(row_t< C > c1, size_t c2)noexcept{
		return detail::row_op< std::multiplies<> >()(c1, c2);
	}


	template < size_t C1, size_t C2 >
	constexpr auto operator/(row_t< C1 > c1, row_t< C2 > c2)noexcept{
		return detail::row_op< std::divides<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, size_t C2 >
	constexpr auto operator/(
		row_init_t< Cct1, C1 > c1, row_t< C2 > c2
	)noexcept{
		return detail::row_op< std::divides<> >()(c1, c2);
	}

	template < size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator/(
		row_t< C1 > c1, row_init_t< Cct2, C2 > c2
	)noexcept{
		return detail::row_op< std::divides<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator/(
		row_init_t< Cct1, C1 > c1, row_init_t< Cct2, C2 > c2
	)noexcept{
		return detail::row_op< std::divides<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, size_t C2 >
	constexpr auto operator/(row_init_t< Cct1, C1 > c1, size_t c2)noexcept{
		return detail::row_op< std::divides<> >()(c1, c2);
	}

	template < size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator/(size_t c1, row_init_t< Cct2, C2 > c2)noexcept{
		return detail::row_op< std::divides<> >()(c1, c2);
	}

	template < size_t C >
	constexpr auto operator/(size_t c1, row_t< C > c2)noexcept{
		return detail::row_op< std::divides<> >()(c1, c2);
	}

	template < size_t C >
	constexpr auto operator/(row_t< C > c1, size_t c2)noexcept{
		return detail::row_op< std::divides<> >()(c1, c2);
	}


	template < size_t C1, size_t C2 >
	constexpr auto operator%(row_t< C1 > c1, row_t< C2 > c2)noexcept{
		return detail::row_op< std::modulus<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, size_t C2 >
	constexpr auto operator%(
		row_init_t< Cct1, C1 > c1, row_t< C2 > c2
	)noexcept{
		return detail::row_op< std::modulus<> >()(c1, c2);
	}

	template < size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator%(
		row_t< C1 > c1, row_init_t< Cct2, C2 > c2
	)noexcept{
		return detail::row_op< std::modulus<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator%(
		row_init_t< Cct1, C1 > c1, row_init_t< Cct2, C2 > c2
	)noexcept{
		return detail::row_op< std::modulus<> >()(c1, c2);
	}

	template < bool Cct1, size_t C1, size_t C2 >
	constexpr auto operator%(row_init_t< Cct1, C1 > c1, size_t c2)noexcept{
		return detail::row_op< std::modulus<> >()(c1, c2);
	}

	template < size_t C1, bool Cct2, size_t C2 >
	constexpr auto operator%(size_t c1, row_init_t< Cct2, C2 > c2)noexcept{
		return detail::row_op< std::modulus<> >()(c1, c2);
	}

	template < size_t C >
	constexpr auto operator%(size_t c1, row_t< C > c2)noexcept{
		return detail::row_op< std::modulus<> >()(c1, c2);
	}

	template < size_t C >
	constexpr auto operator%(row_t< C > c1, size_t c2)noexcept{
		return detail::row_op< std::modulus<> >()(c1, c2);
	}


	template < size_t C1, size_t R1, size_t C2, size_t R2 >
	constexpr auto operator+(dim_t< C1, R1 > d1, dim_t< C2, R2 > d2)noexcept{
		return dims(d1.cols() + d2.cols(), d1.rows() + d2.rows());
	}

	template < size_t C1, size_t R1, size_t C2, size_t R2 >
	constexpr auto operator-(dim_t< C1, R1 > d1, dim_t< C2, R2 > d2)noexcept{
		return dims(d1.cols() - d2.cols(), d1.rows() - d2.rows());
	}

	template < size_t C1, size_t R1, size_t C2, size_t R2 >
	constexpr auto operator*(dim_t< C1, R1 > d1, dim_t< C2, R2 > d2)noexcept{
		return dims(d1.cols() * d2.cols(), d1.rows() * d2.rows());
	}

	template < size_t C1, size_t R1, size_t C2, size_t R2 >
	constexpr auto operator/(dim_t< C1, R1 > d1, dim_t< C2, R2 > d2)noexcept{
		return dims(d1.cols() / d2.cols(), d1.rows() / d2.rows());
	}

	template < size_t C1, size_t R1, size_t C2, size_t R2 >
	constexpr auto operator%(dim_t< C1, R1 > d1, dim_t< C2, R2 > d2)noexcept{
		return dims(d1.cols() % d2.cols(), d1.rows() % d2.rows());
	}

	template < size_t C, size_t R >
	constexpr auto operator*(dim_t< C, R > d, size_t v)noexcept{
		return dims(d.cols() * v, d.rows() * v);
	}

	template < size_t C, size_t R >
	constexpr auto operator/(dim_t< C, R > d, size_t v)noexcept{
		return dims(d.cols() / v, d.rows() / v);
	}

	template < size_t C, size_t R >
	constexpr auto operator%(dim_t< C, R > d, size_t v)noexcept{
		return dims(d.cols() % v, d.rows() % v);
	}


	template < size_t C1, size_t R1, size_t C2, size_t R2 >
	constexpr bool operator==(dim_t< C1, R1 > a, dim_t< C2, R2 > b)noexcept{
		static_assert(
			(C1 == 0 || C2 == 0 || C1 == C2) &&
			(R1 == 0 || R2 == 0 || R1 == R2),
			"Matrix dimensions are not compatible"
		);

		return a.cols() == b.cols() || a.rows() == b.rows();
	}

	template < size_t C1, size_t R1, size_t C2, size_t R2 >
	constexpr bool operator!=(dim_t< C1, R1 > a, dim_t< C2, R2 > b)noexcept{
		return !(a == b);
	}


	namespace detail{


		// Adopted from Boost Hana
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


		// Adopted from Boost Hana
		template < char ... C >
		constexpr auto operator"" _C()noexcept{
			static_assert(
				detail::parse_int< sizeof...(C) >({C ...}),
				"Compile time cols can not be 0, use '_C_rt' prefix instead"
			);
			return cols< detail::parse_int< sizeof...(C) >({C ...}) >();
		}

		// Adopted from Boost Hana
		template < char ... C >
		constexpr auto operator"" _C_rt()noexcept{
			return cols_rt< detail::parse_int< sizeof...(C) >({C ...}) >();
		}

		// Adopted from Boost Hana
		template < char ... C >
		constexpr auto operator"" _R()noexcept{
			static_assert(
				detail::parse_int< sizeof...(C) >({C ...}),
				"Compile time rows can not be 0, use '_R_rt' prefix instead"
			);
			return rows< detail::parse_int< sizeof...(C) >({C ...}) >();
		}

		// Adopted from Boost Hana
		template < char ... C >
		constexpr auto operator"" _R_rt()noexcept{
			return rows_rt< detail::parse_int< sizeof...(C) >({C ...}) >();
		}

		// Adopted from Boost Hana
		template < char ... C >
		constexpr auto operator"" _D()noexcept{
			static_assert(
				detail::parse_int< sizeof...(C) >({C ...}),
				"Compile time dims can not be 0, use '_D_rt' prefix instead"
			);
			return dims< detail::parse_int< sizeof...(C) >({C ...}) >();
		}

		// Adopted from Boost Hana
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
		constexpr auto get(init< Nct, N > d){
			return d;
		}

		template <
			template < bool, size_t > class init,
			bool Nct1, size_t N1, bool Nct2, size_t N2
		> constexpr auto get(
			init< Nct1, N1 > d1,
			init< Nct2, N2 > d2
		){
			return get_ct_if_available< init >(d1, d2);
		}

		template <
			template < bool, size_t > class init,
			bool Nct1, size_t N1,
			bool Nct2, size_t N2,
			bool ... NctN, size_t ... Nn
		> constexpr auto get(
			init< Nct1, N1 > d1,
			init< Nct2, N2 > d2,
			init< NctN, Nn > ... dn
		){
			return get< init >(get_ct_if_available< init >(d1, d2), dn ...);
		}


	}


	template < bool ... Nct, size_t ... N >
	constexpr auto get(col_init_t< Nct, N > ... v){
		return detail::get< col_init_t >(v ...);
	}

	template < bool ... Nct, size_t ... N >
	constexpr auto get(row_init_t< Nct, N > ... v){
		return detail::get< row_init_t >(v ...);
	}

	template < bool ... Nct, size_t ... N >
	constexpr auto get(dim_init_t< Nct, N > ... v){
		return detail::get< dim_init_t >(v ...);
	}

	template < size_t ... N >
	constexpr auto get(col_t< N > ... v){
		return get(v.init() ...).get();
	}

	template < size_t ... N >
	constexpr auto get(row_t< N > ... v){
		return get(v.init() ...).get();
	}

	template < size_t ... C, size_t ... R >
	constexpr auto get(dim_t< C, R > ... v){
		return dims(get(v.cols() ...), get(v.rows() ...));
	}


}


#endif
