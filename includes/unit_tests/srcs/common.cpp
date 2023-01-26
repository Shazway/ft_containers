#include "../hdrs/common.hpp"

template <>
std::string Custom::mocking_value<std::string>() {
	size_t string_size = rand() % 50;
	std::string result;

	for (size_t i = 0; i < string_size; i++)
		result.push_back(rand() % 26 + 97);

	return (result);
}

// template <T1, T2>
// const ft::pair<T1, T2>	operator=(const std::pair<T1, T2>&	rhs) {
// 	return (ft::pair<T1, T2>(rhs.first, rhs.second));
// }
