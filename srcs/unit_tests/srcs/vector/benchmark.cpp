#include "../../hdrs/vector_utils.hpp"
#include <iostream>

template <typename Vector>
void	fill_vector(size_t n, const typename Vector::value_type& k) {
	Vector	vec;

	for(size_t i = 0; i < n; i++)
		vec.push_back(k);
}

TEST_CASE("Vector fill benchmarck", "[!hide][vector][fill][benchmark]") {
	srand(SEED);
	ValueType	tmp_val = Custom::mocking_value<ValueType>();
	size_t		n = BENCHMARK_SIZE;

	SECTION("small ft::vector") {
		fill_vector<Vec>(n, tmp_val);
		std::cout << "\n\n" << BOLDBLUE << n << " elements filled in ft::vector" << RESET << std::endl;
	}
	SECTION("small std::vector") {
		fill_vector<StdVec>(n, tmp_val);
		std::cout << "\n" << BOLDGREEN << n << " elements filled in std::vector" << RESET << std::endl;
	}

	n = n << 1;

	SECTION("medium ft::vector") {
		fill_vector<Vec>(n, tmp_val);
		std::cout << "\n\n" << BOLDBLUE << n << " elements filled in ft::vector" << RESET << std::endl;
	}
	SECTION("medium std::vector") {
		fill_vector<StdVec>(n, tmp_val);
		std::cout << "\n" << BOLDGREEN << n << " elements filled in std::vector" << RESET << std::endl;
	}

	n = n << 1;

	SECTION("large ft::vector") {
		fill_vector<Vec>(n, tmp_val);
		std::cout << "\n\n" << BOLDBLUE << n << " elements filled in ft::vector" << RESET << std::endl;
	}
	SECTION("large std::vector") {
		fill_vector<StdVec>(n, tmp_val);
		std::cout << "\n" << BOLDGREEN << n << " elements filled in std::vector" << RESET << std::endl;
	}
}

TEST_CASE("Vector erase benchmarck", "[!hide][vector][erase][benchmark]") {
	srand(SEED);

	StdVec	std_vec;
	for(size_t i = 0; i < BENCHMARK_SIZE; i++)
		std_vec.push_back(Custom::mocking_value<ValueType>());
	Vec		vec(std_vec.begin(), std_vec.end());

	SECTION("ft::vector") {
		while(vec.size() > 10)
			vec.erase(vec.begin() + vec.size() / 3, vec.begin() + vec.size() / 2);

		std::cout << "\n\n" << BOLDBLUE << BENCHMARK_SIZE - vec.size() << " elements were erased in ft::vector using erase()" << RESET << std::endl;
	}
	SECTION("std::vector") {
		while(std_vec.size() > 10)
			std_vec.erase(std_vec.begin() + std_vec.size() / 3, std_vec.begin() + std_vec.size() / 2);

		std::cout << "\n" << BOLDGREEN << BENCHMARK_SIZE - std_vec.size() << " elements were erased in std::vector using erase()" << RESET << std::endl;
	}
}

