//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__gaussian_elimination__hpp_INCLUDED_
#define _mitrax__gaussian_elimination__hpp_INCLUDED_

#include "raw_matrix.hpp"
#include "matrix_swap.hpp"


namespace mitrax{


	template < typename M, size_t C, size_t R >
	constexpr raw_matrix< value_type_t< M >, C, R >
	upper_triangular_matrix(matrix< M, C, R > const& in){
		if(in.rows() != in.cols()){
			throw std::logic_error(
				"lower_triangular_matrix with non square matrix"
			);
		}

		// Compiler may optimize with the compile time dimension
		size_t const size = C == 0 ? in.rows() : in.cols();

		auto m = in.template as_raw_matrix< value_type_t< M >, C, R >();

		for(size_t i = 0; i < size; ++i){
			if(m(i, i) == 0){
				// swap lines
				size_t y = i + 1;
				for(; y < size; ++y){
					if(m(i, y) == 0) continue;
					swap_rows(m, i, y);
					break;
				}

				// matrix is not invertible
				if(y == size){
					throw std::logic_error(
						"lower_triangular_matrix with non invertible matrix"
					);
				}
			}

			// eliminate col in lower rows
			for(size_t y = i + 1; y < size; ++y){
				auto factor = m(i, y) / m(i, i);
				m(i, y) = 0;
				for(size_t x = i + 1; x < size; ++x){
					m(x, y) -= factor * m(x, i);
				}
			}
		}

		return m;
	}
/*
	template < typename T >
	constexpr matrix< T > const gaussian_elimination(matrix< T > const& m){
		if(m.rows() != m.cols()){
			throw logic_error("mitrax::inverse<>()", m.dimension());
		}

		size_t const size = m.rows();
		matrix< T > original(m);

		// Einheitsmatrix erzeugen
		matrix< T > result(m.dimension());
		{
			typename matrix< T >::iterator iter = result.begin();
			for(size_t i = 0; i < size; ++i){
				*iter = 1;
				iter += size + 1;
			}
		}

		// Liste von Zeilen-Proxys erstellen
		std::vector< row_proxy > m;
		m.reserve(size);
		for(size_t i = 0; i < size; ++i){
			m.push_back(original.y(i));
		}

		detail::proxy_swap_functor< row_proxy > proxy_swap;

		// Obere Dreiecksmatrix bilden
		for(size_t i = 0; i < size; ++i){
			// Zeile mit einer folgenden tauschen, falls nötig
			if(m[i][i] == 0){
				bool status = proxy_swap;
				for(size_t y = i+1; y < size; ++y){
					if(m[y][i] == 0) continue;
					proxy_swap(m[i], m[y]);
					element_swap(result[i], result[y]);
					break;
				}
				// Kein Tausch durchgeführt? ja -> det == 0 -> nicht invertierbar
				if(status == proxy_swap){
					throw error::singular_matrix("mitrax::inverse<>()");
				}
			}
			// Alle folgenden Zeilen in dieser Spalte 0 machen
			// (Elemente dieser Spalte müssen nicht berechnet werden)
			for(size_t y = i+1; y < size; ++y){
				auto factor = m[y][i] / m[i][i];
				for(size_t x = i+1; x < size; ++x){
					m[y][x] -= factor * m[i][x];
				}
				for(size_t x = 0; x < size; ++x){
					result[y][x] -= factor * result[i][x];
				}
			}
			// Zeile normieren (Diagonalelemente müssen nicht berechnet werden)
			for(size_t x = i+1; x < size; ++x){
				m[i][x] /= m[i][i];
			}
			for(size_t x = 0; x < size; ++x){
				result[i][x] /= m[i][i];
			}
		}

		// Einheitsmatrix bilden (Elemente in m müssen nicht berechnet werden)
		for(size_t i = size-1; i > 0; --i){
			for(size_t y = 0; y < i; ++y){
				auto factor = m[y][i];
				for(size_t x = 0; x < size; ++x){
					result[y][x] -= factor * result[i][x];
				}
			}
		}

		return result;
	}
*/

}


#endif
