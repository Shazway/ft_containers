#pragma once
#ifndef MAP_UNIT_TEST_HPP
# define MAP_UNIT_TEST_HPP

#include "catch.hpp"

#include <map.hpp>
#include <map>
//
// StringMaker
//
namespace Catch {

	// STD PAIR
	template<typename T1, typename T2>
	struct StringMaker<std::pair<T1, T2> > {
		static std::string convert(std::pair<T1, T2> const& value ) {
			typedef typename std::pair<T1, T2>::first_type	first_type;
			typedef typename std::pair<T1, T2>::second_type	second_type;
			std::string	out;

			out += "[\"";
			out += Catch::StringMaker<first_type>::convert(value.first);
			out += "\", ";
			out += Catch::StringMaker<second_type>::convert(value.second);
			out += "]";
			return (out);
		}
	};
	// PAIR
	template<typename T1, typename T2>
	struct StringMaker<ft::pair<T1, T2> > {
		static std::string convert(ft::pair<T1, T2> const& value ) {
			typedef typename ft::pair<T1, T2>::first_type	first_type;
			typedef typename ft::pair<T1, T2>::second_type	second_type;
			std::string	out;

			out += "[\"";
			out += Catch::StringMaker<first_type>::convert(value.first);
			out += "\", ";
			out += Catch::StringMaker<second_type>::convert(value.second);
			out += "]";
			return (out);
		}
	};

	// STD MAP
	template<typename T1, typename T2, typename T3, typename T4>
	struct StringMaker<std::map<T1, T2, T3, T4> > {
		static std::string convert(std::map<T1, T2, T3, T4> const& value ) {
			typedef typename std::pair<const T1, T2> pair_type;

			std::string	out;
			typename std::map<T1, T2, T3, T4>::const_iterator it = value.begin();

			if (it == value.end())
				return (out);
			out += "{ ";
			out += Catch::StringMaker<pair_type>::convert(*it);
			it++;
			for (; it != value.end(); it++) {
				out += ", ";
				out += Catch::StringMaker<pair_type>::convert(*it);
			}
			out += " }";
			return (out);
		}
	};

	// MAP
	template<typename T1, typename T2, typename T3, typename T4>
	struct StringMaker<ft::map<T1, T2, T3, T4> > {
		static std::string convert(ft::map<T1, T2, T3, T4> const& value ) {
			typedef typename ft::pair<const T1, T2> pair_type;

			std::string	out;
			typename ft::map<T1, T2, T3, T4>::const_iterator it = value.begin();

			if (it == value.end())
				return (out);
			out += "{ ";
			out += Catch::StringMaker<pair_type>::convert(*it);
			it++;
			for (; it != value.end(); it++) {
				out += ", ";
				out += Catch::StringMaker<pair_type>::convert(*it);
			}
			return (out);
		}
	};
}

#include "common.hpp"
typedef const KEY_TYPE									MapFirstType;
typedef MAPPED_TYPE										MapSecondType;

typedef NS::map<KEY_TYPE, MAPPED_TYPE, std::less<KEY_TYPE>, std::allocator<NS::pair<const KEY_TYPE, MAPPED_TYPE> > >		Map;
typedef Map::iterator									MapIt;
typedef Map::const_iterator								MapConstIt;
typedef Map::const_reverse_iterator						MapConstRevIt;
typedef NS::pair<const KEY_TYPE, MAPPED_TYPE>			MapPair;

typedef std::map<KEY_TYPE, MAPPED_TYPE, std::less<KEY_TYPE>, std::allocator<std::pair<const KEY_TYPE, MAPPED_TYPE> > >		StdMap;
typedef StdMap::iterator								StdMapIt;
typedef StdMap::const_iterator							StdMapConstIt;
typedef StdMap::const_reverse_iterator					StdMapConstRevIt;
typedef std::pair<const KEY_TYPE, MAPPED_TYPE>			StdMapPair;

namespace ft {
	template <typename T1, typename T2>
	bool operator==(const ft::pair<const T1, T2>& lhs, const std::pair<const T1, T2>& rhs) {
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}
	template <typename T1, typename T2>
	bool operator==(const std::pair<const T1, T2>& lhs, const ft::pair<const T1, T2>& rhs) {
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}
}


//
// SFINAE AND GENERATORS
//
namespace Custom {
	// IS CONTAINER
	template <typename T1, typename T2, typename T3, typename T4>
	struct is_cont<std::map<T1, T2, T3, T4> > : Custom::true_type { };
	template <typename T1, typename T2, typename T3, typename T4>
	struct is_cont<ft::map<T1, T2, T3, T4> > : Custom::true_type { };
	// IS MAP
	template <typename T>
	struct is_map : Custom::false_type { };
	template <typename T1, typename T2, typename T3, typename T4>
	struct is_map<std::map<T1, T2, T3, T4> > : Custom::true_type { };
	template <typename T1, typename T2, typename T3, typename T4>
	struct is_map<ft::map<T1, T2, T3, T4> > : Custom::true_type { };

	// GENERATOR
	template <typename T>
	typename Custom::enable_if<Custom::is_map<T>::value, T>::type
	mocking_value() {
		typedef typename T::value_type	value_type;
		typedef typename T::key_type	Key;
		typedef typename T::mapped_type	Value;

		T		result;

		for (size_t i = 0; i < REF_SIZE; i++)
			result.insert(
				value_type(
					Custom::mocking_value<Key>(),
					Custom::mocking_value<Value>()
				)
			);

		return (result);
	}


	template <typename T1, typename T2, typename T3, typename T4>
	void	copy_map(const std::map<T1, T2, T3, T4>& from, std::map<T1, T2, T3, T4>&	to) {
		to = from;
	}

	template <typename T1, typename T2, typename T3, typename T4,
				typename T5, typename T6, typename T7, typename T8>
	void	copy_map(const std::map<T1, T2, T3, T4>& from, ft::map<T5, T6, T7, T8>&	to) {
		typedef typename std::map<T1, T2, T3, T4>::const_iterator	const_it;
		typedef typename std::map<T1, T2, T3, T4>::key_type			first_type;
		typedef typename std::map<T1, T2, T3, T4>::mapped_type		second_type;

		to.clear();
		for (const_it it = from.begin(); it != from.end(); it++)
			to.insert(ft::pair<first_type, second_type>(it->first, it->second));
	}


	//
	// EQUALITY CHECKS
	//
	template<typename MapType>
	class MapEqual : public Catch::MatcherBase<MapType> {
	public:
		typedef typename MapType::key_type			key_type;
		typedef typename MapType::mapped_type		mapped_type;
		typedef typename MapType::key_compare		key_compare;
		typedef typename MapType::allocator_type	allocator_type;
		typedef typename MapType::const_iterator	ConstIt;

		typedef std::map<key_type, mapped_type, key_compare, allocator_type>	std_map_type;
		typedef typename std_map_type::const_iterator	StdConstIt;

		// MapEqual(std_map_type const& comparator) : std_map(&comparator), ft_map(NULL) {}
		MapEqual(Map const& comparator) : map(&comparator), std_map(NULL) {}
		#ifndef DEBUG
		MapEqual(StdMap const& comparator) : map(NULL), std_map(&comparator) {}
		#endif

		bool match(MapType const &v) const {
			if (map) {
				ConstIt mapFirst = v.begin(), mapLast = v.end();
				ConstIt refFirst = map->begin(), refLast = map->end();

				while (mapFirst!=mapLast && refFirst!=refLast) {
					if (*mapFirst != *refFirst)
						return false;
					++mapFirst; ++refFirst;
				}
				if (mapFirst == mapLast && refFirst == refLast)
					return true;
				return false;
			}
			else {
				ConstIt mapFirst = v.begin(), mapLast = v.end();
				StdConstIt refFirst = std_map->begin(), refLast = std_map->end();

				while (mapFirst!=mapLast && refFirst!=refLast) {
					if (!(*mapFirst == *refFirst))
						return false;
					++mapFirst; ++refFirst;
				}
				if (mapFirst == mapLast && refFirst == refLast)
					return true;
				return false;
			}
		}
		std::string describe() const {
			std::ostringstream ss;
			ss << "\nEquality two maps: \n";

			// IF YOU GET A COMPILATION ERROR HERE, NEED TO IMPLEMENT : `std::ostream& operator<< (std::ostream& out, const YourType& rhs)`
			if (map)
				ss << Catch::StringMaker<Map>::convert(*map);
			else
				ss << Catch::StringMaker<StdMap>::convert(*std_map);
			return ss.str();
		}
		Map	const		*map;
		StdMap const	*std_map;
	};
}



#endif
