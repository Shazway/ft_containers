#include "../../hdrs/map_utils.hpp"
#include <iostream>

typedef ft::map<size_t, MapSecondType>		ft_map_type;
typedef std::map<size_t, MapSecondType>	std_map_type;

template <typename MapType>
MapType	fill_inc_map(size_t n, const MapSecondType& k) {
	MapType	map;

	for(size_t i = 0; i < n; i++)
		map[i] = k;

	return (map);
}
template <typename MapType>
MapType	fill_dec_map(size_t n, const MapSecondType& k) {
	MapType	map;

	for(size_t i = n; i + 1 > 1; i--)
		map[i] = k;

	return (map);
}
template <typename MapType>
MapType	fill_rand_map(const std::vector<size_t>& rand_vec, const MapSecondType& k) {
	MapType	map;

	for(std::vector<size_t>::const_iterator it = rand_vec.begin(); it != rand_vec.end(); it++)
		map[*it] = k;

	return (map);
}



TEST_CASE("Map fill benchmarck", "[!hide][map][fill][benchmark]") {
	srand(SEED);

	MapSecondType	tmp_second = Custom::mocking_value<MapSecondType>();
	size_t		n = BENCHMARK_SIZE >> 1;

	SECTION("inc fill ft::map") {
		fill_inc_map<ft_map_type>(n, tmp_second);
		std::cout << "\n\n" << BOLDBLUE << n << " elements filled in ft::map increasingly" << RESET << std::endl;
	}
	SECTION("inc fill std::map") {
		fill_inc_map<std_map_type>(n, tmp_second);
		std::cout << "\n" << BOLDGREEN << n << " elements filled in std::map increasingly" << RESET << std::endl;
	}

	SECTION("dec fill ft::map") {
		fill_dec_map<ft_map_type>(n, tmp_second);
		std::cout << "\n\n" << BOLDBLUE << n << " elements filled in ft::map decreasingly" << RESET << std::endl;
	}
	SECTION("dec fill std::map") {
		fill_dec_map<std_map_type>(n, tmp_second);
		std::cout << "\n" << BOLDGREEN << n << " elements filled in std::map decreasingly" << RESET << std::endl;
	}

	std::vector<size_t>		index_vec;

	for (size_t i = 0; i < n; i++)
		index_vec.push_back(rand() % n);

	SECTION("rand fill ft::map") {
		fill_rand_map<ft_map_type>(index_vec, tmp_second);
		std::cout << "\n\n" << BOLDBLUE << n << " elements filled in ft::map randomly" << RESET << std::endl;
	}
	SECTION("rand fill std::map") {
		fill_rand_map<std_map_type>(index_vec, tmp_second);
		std::cout << "\n" << BOLDGREEN << n << " elements filled in std::map randomly" << RESET << std::endl;
	}
}

TEST_CASE("Map traversal benchmarck", "[!hide][map][traversal][benchmark]") {
	srand(SEED);

	MapSecondType	tmp_second = Custom::mocking_value<MapSecondType>();
	size_t			n = BENCHMARK_SIZE >> 1;
	std_map_type	std_map = fill_inc_map<std_map_type>(n, tmp_second);
	ft_map_type		ft_map = fill_inc_map<ft_map_type>(n, tmp_second);

	SECTION("ft::map") {
		ft_map_type::const_iterator it = ft_map.begin();
		while(it != ft_map.end())
			ft_map.erase((it++)->first);

		std::cout << "\n\n" << BOLDBLUE << n << " elements were scanned and removed in ft::map using iterators" << RESET << std::endl;
	}
	SECTION("std::map") {
		std_map_type::const_iterator it = std_map.begin();
		while(it != std_map.end())
			std_map.erase((it++)->first);

		std::cout << "\n" << BOLDGREEN << n << " elements were scanned and removed in std::map using iterators" << RESET << std::endl;
	}
}

