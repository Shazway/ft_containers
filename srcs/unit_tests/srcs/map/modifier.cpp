#include "../../hdrs/map_utils.hpp"

TEST_CASE("Map modifiers", "[map][modifier]") {

	Map				map;
	StdMap 			ref;

	Custom::remove_const<MapFirstType>::type	tmp_first = Custom::mocking_value<Custom::remove_const<MapFirstType>::type>();
	MapSecondType	tmp_second = Custom::mocking_value<MapSecondType>();

	StdMapIt		std_it;
	MapIt			it;

	typedef NS::pair<MapIt, bool>		MapReturn;
	typedef std::pair<StdMapIt, bool>	StdMapReturn;

	SECTION("insert(val)") {
		tmp_first = Custom::mocking_value<Custom::remove_const<MapFirstType>::type>();
		tmp_second = Custom::mocking_value<MapSecondType>();

		MapReturn		tmp_return;
		StdMapReturn	tmp_std_return;

		tmp_return = map.insert(MapPair(tmp_first, tmp_second));
		tmp_std_return = ref.insert(StdMapPair(tmp_first, tmp_second));

		REQUIRE(*tmp_return.first == *tmp_std_return.first);
		REQUIRE(tmp_return.second == tmp_std_return.second);

		// TRY TO REINSERT, bool must be false
		tmp_return = map.insert(MapPair(tmp_first, tmp_second));
		tmp_std_return = ref.insert(StdMapPair(tmp_first, tmp_second));

		REQUIRE(*tmp_return.first == *tmp_std_return.first);
		REQUIRE(tmp_return.second == tmp_std_return.second);
	}

	SECTION("insert(position, val)") {
		for (size_t i = 0; i < REF_SIZE; i++)
		{
			tmp_first = Custom::mocking_value<Custom::remove_const<MapFirstType>::type>();
			tmp_second = Custom::mocking_value<MapSecondType>();
			if (i % 3 == 0) {
				std_it = ref.insert(ref.begin(), StdMapPair(tmp_first, tmp_second));
				it = map.insert(map.begin(), MapPair(tmp_first, tmp_second));
			}
			if (i % 3 == 1) {
				std_it = ref.insert(++ref.begin(), StdMapPair(tmp_first, tmp_second));
				it = map.insert(++map.begin(), MapPair(tmp_first, tmp_second));
			}
			else {
				std_it = ref.insert(ref.end(), StdMapPair(tmp_first, tmp_second));
				it = map.insert(map.end(), MapPair(tmp_first, tmp_second));
			}
			if (std_it == ref.end())
				REQUIRE(it == map.end());
			else
				REQUIRE(*std_it == *it);
		}
		REQUIRE_THAT(map, Custom::MapEqual<Map>(ref));
	}

	SECTION("insert(first, last)") {
		Map	tmp_map = Custom::mocking_value<Map>();

		map.insert(tmp_map.begin(), tmp_map.end());
		REQUIRE_THAT(map, Custom::MapEqual<Map>(tmp_map));

		map.insert(map.begin(), map.end());
		REQUIRE_THAT(map, Custom::MapEqual<Map>(tmp_map));
	}

	SECTION("erase(position)") {
		ref = Custom::mocking_value<StdMap>();
		Custom::copy_map(ref, map);
		for (size_t i = 0; i < REF_SIZE / 10; i++) {
			if (i % 3 == 0) {
				ref.erase(ref.begin());
				map.erase(map.begin());
			}
			else if (i % 3 == 1) {
				ref.erase((++(++ref.begin())));
				map.erase((++(++map.begin())));
			}
			else {
				ref.erase((--(--ref.end())));
				map.erase((--(--map.end())));
			}
		}
		REQUIRE_THAT(map, Custom::MapEqual<Map>(ref));
	}
	SECTION("erase(val)") {
		size_t	std_remove;
		size_t	map_remove;

		ref = Custom::mocking_value<StdMap>();
		Custom::copy_map(ref, map);
		for (size_t i = 0; i < REF_SIZE / 10; i++) {
			if (i % 3 == 0)
				REQUIRE(ref.erase(ref.begin()->first) == map.erase(map.begin()->first));
			else if (i % 3 == 1)
				REQUIRE(ref.erase((++(++ref.begin()))->first) == map.erase((++(++map.begin()))->first));
			else
				REQUIRE(ref.erase((--(--ref.end()))->first) == map.erase((--(--map.end()))->first));
		}
		REQUIRE_THAT(map, Custom::MapEqual<Map>(ref));
	}
	SECTION("erase(first, last)") {
		ref = Custom::mocking_value<StdMap>();
		Custom::copy_map(ref, map);
		for (size_t i = 0; i < REF_SIZE / 100; i++)
		{
			if (i % 2) {
				ref.erase(ref.begin(), ++(++ref.begin()));
				map.erase(map.begin(), ++(++map.begin()));
			}
			else {
				ref.erase(--(--ref.end()), ref.end());
				map.erase(--(--map.end()), map.end());
			}
		}
		REQUIRE_THAT(map, Custom::MapEqual<Map>(ref));
	}

	SECTION("swap(a)") {
		Map					tmp_test_map;
		MapIt				it2;

		map.insert(MapPair(
			Custom::mocking_value<Map::key_type>(),
			Custom::mocking_value<Map::mapped_type>()
			)
		);
		tmp_test_map.insert(MapPair(
			Custom::mocking_value<StdMap::key_type>(),
			Custom::mocking_value<StdMap::mapped_type>()
			)
		);
		it = map.begin();
		it2 = tmp_test_map.begin();

		tmp_test_map.swap(map);
		REQUIRE(it == tmp_test_map.begin());
		REQUIRE(it2 == map.begin());
	}

	SECTION("clear()") {
		map = Custom::mocking_value<Map>();
		map.clear();
		REQUIRE((map.size() == 0 && map.empty()));
	}
}
