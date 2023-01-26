#include "../../hdrs/map_utils.hpp"

TEST_CASE("Map observer", "[map][observer]") {

	Map				map;

	typedef Map::key_type	key_type;

	key_type		tmp_first = Custom::mocking_value<key_type>();
	MapSecondType	tmp_second = Custom::mocking_value<MapSecondType>();

	SECTION("key_comp()") {
		Map::key_compare	tmp_key_comp = map.key_comp();

		map.insert(MapPair(
			Custom::mocking_value<Map::key_type>(),
			Custom::mocking_value<Map::mapped_type>()
			)
		);
		map.insert(MapPair(
			Custom::mocking_value<Map::key_type>(),
			Custom::mocking_value<Map::mapped_type>()
			)
		);
		REQUIRE(tmp_key_comp(map.begin()->first, (++map.begin())->first) == true);
	}
	SECTION("value_comp()") {
		Map::value_compare	tmp_value_comp = map.value_comp();

		map.insert(MapPair(
			Custom::mocking_value<Map::key_type>(),
			Custom::mocking_value<Map::mapped_type>()
			)
		);
		map.insert(MapPair(
			Custom::mocking_value<Map::key_type>(),
			Custom::mocking_value<Map::mapped_type>()
			)
		);
		REQUIRE(tmp_value_comp(*map.begin(), *(++map.begin())) == true);
	}

};
