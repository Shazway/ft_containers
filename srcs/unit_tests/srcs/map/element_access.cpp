#include "../../hdrs/map_utils.hpp"
#include <stdexcept>

TEST_CASE("Map element access", "[map][access]") {

	StdMap			ref = Custom::mocking_value<StdMap>();
	Map				map;
	Custom::copy_map(ref, map);

	SECTION("operator[]") {
		MapIt			tmp_it = map.begin();

		REQUIRE(ref[tmp_it->first] == map[tmp_it->first]);
		tmp_it++;
		tmp_it++;
		REQUIRE(ref[tmp_it->first] == map[tmp_it->first]);
		tmp_it = map.end();
		tmp_it--;
		tmp_it--;
		REQUIRE(ref[tmp_it->first] == map[tmp_it->first]);

		MapFirstType	tmp_first = Custom::mocking_value<Custom::remove_const<MapFirstType>::type>();
		MapSecondType	tmp_second = Custom::mocking_value<MapSecondType>();

		ref[tmp_first] = tmp_second;
		map[tmp_first] = tmp_second;

		REQUIRE(ref[tmp_first] == map[tmp_first]);
	}
}
