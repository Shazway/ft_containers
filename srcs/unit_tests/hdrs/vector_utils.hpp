#pragma once
#ifndef VECTOR_UNIT_TEST_HPP
# define VECTOR_UNIT_TEST_HPP

#include "catch.hpp"
#include <vector.hpp>
#include <vector>
//
// StringMaker
//
namespace Catch {

	// StringMaker
	template<typename T> struct StringMaker<std::vector<T> > {
		static std::string convert(std::vector<T> const& value ) {
			std::string	out;
			typename std::vector<T>::const_iterator it = value.begin();

			if (it == value.end())
				return (out);
			out += "{ ";
			out += "\"";
			out += Catch::StringMaker<T>::convert(*it);
			out += "\"";
			it++;
			for (; it != value.end(); it++) {
				out += ", \"";
				out += Catch::StringMaker<T>::convert(*it);
				out += "\"";
			}
			out += " }";
			return (out);
		}
	};

	template<typename T> struct StringMaker<ft::vector<T> > {
		static std::string convert(ft::vector<T> const& value ) {
			std::string	out;
			typename ft::vector<T>::const_iterator it = value.begin();

			if (it == value.end())
				return (out);
			out += "{ ";
			out += "\"";
			out += Catch::StringMaker<T>::convert(*it);
			out += "\"";
			it++;
			for (; it != value.end(); it++) {
				out += ", \"";
				out += Catch::StringMaker<T>::convert(*it);
				out += "\"";
			}
			out += " }";
			return (out);
		}
	};
}

#include "common.hpp"
typedef NS::vector<ValueType>							Vec;
typedef Vec::iterator									VecIt;
typedef Vec::const_iterator								VecConstIt;
typedef Vec::const_reverse_iterator						VecConstRevIt;

typedef std::vector<ValueType>							StdVec;
typedef std::vector<ValueType>::iterator				StdVecIt;
typedef std::vector<ValueType>::const_iterator			StdVecConstIt;
typedef std::vector<ValueType>::const_reverse_iterator	StdVecConstRevIt;

namespace Custom {
	// IS CONTAINER
	template <typename T>
	struct is_cont<std::vector<T> > : Custom::true_type { };
	template <typename T>
	struct is_cont<ft::vector<T> > : Custom::true_type { };
	// IS VECTOR
	template <typename T>
	struct is_vector : Custom::false_type { };
	template <typename T>
	struct is_vector<std::vector<T> > : Custom::true_type { };
	template <typename T>
	struct is_vector<ft::vector<T> > : Custom::true_type { };

	// GENERATOR
	template <typename T>
	typename Custom::enable_if<Custom::is_vector<T>::value, T>::type
	mocking_value() {
		T		result;

		for (size_t i = 0; i < REF_SIZE; i++)
			result.push_back(Custom::mocking_value<typename T::value_type>());

		return (result);
	}


	//
	// EQUALITY CHECKS
	//
	template<typename VectorType>
	class VectorEqual : public Catch::MatcherBase<VectorType> {
	public:
		typedef typename VectorType::value_type		ValueType;
		typedef typename VectorType::allocator_type	AllocComp;


		VectorEqual(std::vector<ValueType, AllocComp> const &comparator) : m_comparator( comparator ) {}

		bool match(VectorType const &v) const {
			if (m_comparator.size() != v.size())
				return false;
			for (std::size_t i = 0; i < v.size(); ++i)
				if (m_comparator[i] != v[i])
					return false;
			return true;
		}
		std::string describe() const {
			std::ostringstream ss;
			ss << "\nEquality between ft::vector && std::vector: \n";

			// IF YOU GET A COMPILATION ERROR HERE, NEED TO IMPLEMENT : `std::ostream& operator<< (std::ostream& out, const YourType& rhs)`
			ss << Catch::StringMaker<std::vector<ValueType> >::convert(m_comparator);
			return ss.str();
		}
		std::vector<ValueType, AllocComp> const& m_comparator;
	};
}



#endif
