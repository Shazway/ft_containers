#pragma once
#ifndef COMMON_HPP_123
# define COMMON_HPP_123

#ifdef DEBUG
# define NS std
#else
# define NS ft
#endif

//
//	CONFIGURATION ->
//

// FOR VECTOR, SET AND STACK ->
#define VALUE_TYPE		std::string
// FOR MAP ->
#define KEY_TYPE		int
#define MAPPED_TYPE		std::string
// FOR STACK ->
#define CONT_TYPE		vector
// GENERATORS CONFIGURATION
#define REF_SIZE 500
// PATH USED FOR INPUT_ITERATOR GENERATION
#define FILE_PATH "./Makefile"

//
//	<- CONFIGURATION
//


// INCLUDE OF REQUIRED LIBS
#include "catch.hpp"
#include <string>
#include <fstream>
#include <iterator>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#define RESET				"\033[0m"
#define BOLDGREEN	 		"\033[1m\033[32m"      /* Bold Green */
#define BOLDBLUE			"\033[1m\033[34m"      /* Bold Blue */
#define BOLDWHITE			"\033[1m\033[37m"      /* Bold White */

#define BENCHMARK_SIZE		16777216
#define SEED 				123456789
typedef VALUE_TYPE			ValueType;

namespace Custom {

	template <class InputIterator1, class InputIterator2>
	bool equal( InputIterator1 first1, InputIterator1 last1,
					InputIterator2 first2, InputIterator2 last2) {
		while (first1!=last1 && first2!=last2) {
			if (*first1 != *first2)
				return false;
			++first1; ++first2;
		}
		if (first1 == last1 && first2 == last2)
			return true;
		return false;
	};

	template <typename T1, typename T2>
	bool same_vec(const T1& vec1, const T2& vec2) {
		if (vec1.size() != vec2.size())
			return (false);
		return (Custom::equal(vec1.begin(), vec1.end(), vec2.begin(), vec2.end()));
	}


	//
	//	SFINAE
	//
	// ENABLE IF
	template <bool Cond, typename Result=void>
	struct enable_if { };

	template <typename Result>
	struct enable_if<true, Result> {
		typedef Result	type;
	};

	struct false_type { static const bool value = false; };
	struct true_type { static const bool value = true; };

	// IS_INTEGRAL
	template<typename> struct is_integral: Custom::false_type {};
	template<> struct is_integral<bool>: Custom::true_type {};
	template<> struct is_integral<int>: Custom::true_type {};
	template<> struct is_integral<size_t>: Custom::true_type {};

	// IS CONT
	template <typename T>
	struct is_cont : Custom::false_type { };

	// REMOVE CONST
	template< class T > struct remove_const                { typedef T type; };
	template< class T > struct remove_const<const T>       { typedef T type; };

	//
	//	GENERATOR
	//
	template <typename T>
	typename Custom::enable_if<!Custom::is_cont<T>::value, T>::type
	mocking_value() {
		return (rand() % REF_SIZE);
	}

	template <>
	std::string mocking_value<std::string>();
}

#endif
