#include "../../hdrs/map_utils.hpp"

TEST_CASE("Map non-members functions", "[map][operator]") {

	Map		ref = Custom::mocking_value<Map>();
	Map		map(ref);

	SECTION("operator == && !=") {
		REQUIRE(ref == map);
		REQUIRE(ref <= map);
		REQUIRE(ref >= map);
		ref.erase(--ref.end());
		REQUIRE(ref != map);
	}
	SECTION("operator < && >") {
		for(size_t i = 0; i < REF_SIZE / 10; i++) {
			if (*--ref.end() < *--map.end())
				REQUIRE(ref < map);
			else if (*--ref.end() > *--map.end())
				REQUIRE(ref > map);
			else {
				REQUIRE_FALSE(ref < map);
				REQUIRE_FALSE(ref > map);
			}
			ref.erase(--ref.end());
			map.erase(--map.end());
		}
	}
	SECTION("operator <= && >=") {
		for(size_t i = 0; i < REF_SIZE / 10; i++) {
			if (*--ref.end() < *--map.end())
				REQUIRE(ref <= map);
			else if (*--ref.end() > *--map.end())
				REQUIRE(ref >= map);
			else {
				REQUIRE(ref <= map);
				REQUIRE(ref >= map);
			}
			ref.erase(--ref.end());
			map.erase(--map.end());
		}
	}

	SECTION("swap()") {
		MapConstIt	it;
		MapConstIt	it2;

		it = ref.begin();
		it2 = map.begin();

		ref.swap(map);
		REQUIRE(it == map.begin());
		REQUIRE(it2 == ref.begin());
	}
}
