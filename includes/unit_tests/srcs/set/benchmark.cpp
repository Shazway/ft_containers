#include "../../hdrs/set_utils.hpp"
#include <iostream>

typedef ft::set<size_t>	ft_set_type;
typedef std::set<size_t>	std_set_type;

template <typename SetType>
SetType	fill_inc_set(size_t n) {
	SetType	set;

	for(size_t i = 0; i < n; i++)
		set.insert(i);

	return (set);
}
template <typename SetType>
SetType	fill_dec_set(size_t n) {
	SetType	set;

	for(size_t i = n; i + 1 > 1; i--)
		set.insert(i);

	return (set);
}
template <typename SetType>
SetType	fill_rand_set(const std::vector<size_t>& rand_vec) {
	SetType	set;

	for(std::vector<size_t>::const_iterator it = rand_vec.begin(); it != rand_vec.end(); it++)
		set.insert(*it);

	return (set);
}



TEST_CASE("Set fill benchmarck", "[!hide][set][fill][benchmark]") {
	srand(SEED);

	size_t		n = BENCHMARK_SIZE >> 1;

	SECTION("inc fill ft::set") {
		ft_set_type tmp = fill_inc_set<ft_set_type>(n);
		std::cout << "\n\n" << BOLDBLUE << tmp.size() << " elements filled in ft::set increasingly" << RESET << std::endl;
	}
	SECTION("inc fill std::set") {
		std_set_type tmp = fill_inc_set<std_set_type>(n);
		std::cout << "\n" << BOLDGREEN << tmp.size() << " elements filled in std::set increasingly" << RESET << std::endl;
	}

	SECTION("dec fill ft::set") {
		ft_set_type tmp = fill_dec_set<ft_set_type>(n);
		std::cout << "\n\n" << BOLDBLUE << tmp.size() << " elements filled in ft::set decreasingly" << RESET << std::endl;
	}
	SECTION("dec fill std::set") {
		std_set_type tmp = fill_dec_set<std_set_type>(n);
		std::cout << "\n" << BOLDGREEN << tmp.size() << " elements filled in std::set decreasingly" << RESET << std::endl;
	}

	std::vector<size_t>		index_vec;

	for (size_t i = 0; i < n; i++)
		index_vec.push_back(rand() % n);

	SECTION("rand fill ft::set") {
		ft_set_type tmp = fill_rand_set<ft_set_type>(index_vec);
		std::cout << "\n\n" << BOLDBLUE << tmp.size() << " elements filled in ft::set randomly" << RESET << std::endl;
	}
	SECTION("rand fill std::set") {
		std_set_type tmp = fill_rand_set<std_set_type>(index_vec);
		std::cout << "\n" << BOLDGREEN << tmp.size() << " elements filled in std::set randomly" << RESET << std::endl;
	}
}

TEST_CASE("Set traversal benchmarck", "[!hide][set][traversal][benchmark]") {
	srand(SEED);

	size_t			n = BENCHMARK_SIZE >> 1;
	std_set_type	std_set = fill_inc_set<std_set_type>(n);
	ft_set_type		ft_set = fill_inc_set<ft_set_type>(n);

	SECTION("ft::set") {
		ft_set_type::const_iterator it = ft_set.begin();
		while(it != ft_set.end())
			ft_set.erase(*it++);

		std::cout << "\n\n" << BOLDBLUE << n << " elements were scanned and removed in ft::set using iterators" << RESET << std::endl;
	}
	SECTION("std::set") {
		std_set_type::const_iterator it = std_set.begin();
		while(it != std_set.end())
			std_set.erase(*it++);

		std::cout << "\n" << BOLDGREEN << n << " elements were scanned and removed in std::set using iterators" << RESET << std::endl;
	}
}

