#include "../../hdrs/map_utils.hpp"

typedef std::istream_iterator<char>	is_iterator;

bool	check_input_it(is_iterator file_it, const NS::map<size_t, char>& map) {
	NS::map<size_t, char>::const_iterator	it = map.begin();

	while (file_it!=is_iterator() && it!=map.end()) {
		if (*file_it != it->second)
			return false;
		++file_it; ++it;
	}
	if (file_it == is_iterator() && it == map.end())
		return true;
	return false;
}

TEST_CASE("Map constructors", "[map][constructor]") {

	SECTION("default constructor") {
		Map	map;

		REQUIRE(map.size() == 0);
	}


	Map ref = Custom::mocking_value<Map>();

	MapIt	ref_begin = ref.begin();
	MapIt	ref_end = ref.end();

	SECTION("range constructor begin-end") {
		Map	map(ref_begin, ref_end);

		REQUIRE_THAT(map, Custom::MapEqual<Map>(ref));
	}
	SECTION("range constructor somewhere-end") {
		++(++(ref_begin));
		Map	map(ref_begin, ref_end);
		ref.erase(ref.begin(), ref_begin);

		REQUIRE_THAT(map, Custom::MapEqual<Map>(ref));
	}
	SECTION("range constructor begin-somewhere") {
		--(--(ref_end));
		Map	map(ref_begin, ref_end);
		ref.erase(ref_end, ref.end());

		REQUIRE_THAT(map, Custom::MapEqual<Map>(ref));
	}
	SECTION("copy constructor") {
		Map	map(ref);

		REQUIRE_THAT(map, Custom::MapEqual<Map>(ref));
	}

	// SECTION("copy constructor") {
	// 	Map	origin_map(++(++range_begin), --(--(--range_end)));
	// 	Map	copy_map(origin_map);

	// 	REQUIRE(Custom::same_map(origin_map, copy_map) == true);
	// }
}
