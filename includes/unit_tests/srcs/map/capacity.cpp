#include "../../hdrs/map_utils.hpp"

TEST_CASE("Map capacity", "[map][capacity]") {

	StdMap		ref = Custom::mocking_value<StdMap>();
	Map			map;
	Custom::copy_map(ref, map);
	ValueType	tmp = Custom::mocking_value<ValueType>();

	SECTION("size()") {
		REQUIRE(ref.size() == map.size());
	}
	SECTION("max_size()") {
		CHECK(ref.max_size() == map.max_size());
	}
	SECTION("empty()") {
		Map tmp_map;
		REQUIRE(tmp_map.empty());
		REQUIRE_FALSE(map.empty());
	}

}
