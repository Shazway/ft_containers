#include "../../hdrs/map_utils.hpp"

TEST_CASE("Map operation", "[map][operation]") {
	typedef Map::key_type	key_type;

	StdMap			ref = Custom::mocking_value<StdMap>();
	Map				map;
	Custom::copy_map(ref, map);

	StdMapIt		std_it;
	MapIt			it;
	StdMapConstIt	std_const_it;
	MapConstIt		const_it;
	key_type		tmp_key;

	SECTION("find(k)") {
		std_it = ref.find((++ref.begin())->first);
		it = map.find((++ref.begin())->first);

		REQUIRE(*std_it == *it);
	}
	SECTION("find(k) const") {
		std_const_it = ref.find((++ref.begin())->first);
		const_it = map.find((++ref.begin())->first);

		REQUIRE(*std_const_it == *const_it);
	}
	SECTION("find(k), with value not present in map") {
		tmp_key = Custom::mocking_value<key_type>();
		map.erase(tmp_key);

		REQUIRE(map.find(tmp_key) == map.end());
	}
	SECTION("find(k) const, with value not present in map") {
		tmp_key = Custom::mocking_value<key_type>();
		map.erase(tmp_key);
		const_it = map.find(tmp_key);

		REQUIRE(const_it == map.end());
	}

	SECTION("count(k)") {
		for (size_t i = 0; i < REF_SIZE / 10; i++)
		{
			tmp_key = Custom::mocking_value<key_type>();
			REQUIRE(ref.count(tmp_key) == map.count(tmp_key));
		}
	}

	SECTION("lower_bound(k)") {
		for (size_t i = 0; i < REF_SIZE / 10; i++)
		{
			tmp_key = Custom::mocking_value<key_type>();
			std_it = ref.lower_bound(tmp_key);
			it = map.lower_bound(tmp_key);

			if (std_it == ref.end())
				REQUIRE(it == map.end());
			else
				REQUIRE(*std_it == *it);
		}
	}
	SECTION("lower_bound(k) const") {
		for (size_t i = 0; i < REF_SIZE / 10; i++)
		{
			tmp_key = Custom::mocking_value<key_type>();
			std_const_it = ref.lower_bound(tmp_key);
			const_it = map.lower_bound(tmp_key);

			if (std_const_it == ref.end())
				REQUIRE(const_it == map.end());
			else
				REQUIRE(*std_const_it == *const_it);
		}
	}

	SECTION("upper_bound(k)") {
		for (size_t i = 0; i < REF_SIZE / 10; i++)
		{
			tmp_key = Custom::mocking_value<key_type>();
			std_it = ref.upper_bound(tmp_key);
			it = map.upper_bound(tmp_key);

			if (std_it == ref.end())
				REQUIRE(it == map.end());
			else
				REQUIRE(*std_it == *it);
		}
	}
	SECTION("upper_bound(k)") {
		for (size_t i = 0; i < REF_SIZE / 10; i++)
		{
			tmp_key = Custom::mocking_value<key_type>();
			std_const_it = ref.upper_bound(tmp_key);
			const_it = map.upper_bound(tmp_key);

			if (std_const_it == ref.end())
				REQUIRE(const_it == map.end());
			else
				REQUIRE(*std_const_it == *const_it);
		}
	}

	SECTION("equal_pair(k)") {
		typedef std::pair<StdMapIt, StdMapIt>	std_eq_pair_type;
		typedef NS::pair<MapIt, MapIt>			eq_pair_type;

		std_eq_pair_type	std_eq_pair;
		eq_pair_type		eq_pair;

		for (size_t i = 0; i < REF_SIZE / 10; i++)
		{
			tmp_key = Custom::mocking_value<key_type>();
			std_eq_pair = ref.equal_range(tmp_key);
			eq_pair = map.equal_range(tmp_key);

			if (std_eq_pair.first == ref.end())
				REQUIRE(eq_pair.first == map.end());
			else if (std_eq_pair.second ==  ref.end())
				REQUIRE(eq_pair.second == map.end());
			else
			{
				REQUIRE(*std_eq_pair.first == *eq_pair.first);
				REQUIRE(*std_eq_pair.second == *eq_pair.second);
			}
		}
	}
	SECTION("equal_pair(k) const") {
		typedef std::pair<StdMapConstIt, StdMapConstIt>	std_const_eq_pair_type;
		typedef NS::pair<MapConstIt, MapConstIt>		const_eq_pair_type;

		std_const_eq_pair_type	std_const_eq_pair;
		const_eq_pair_type		const_eq_pair;
		for (size_t i = 0; i < REF_SIZE / 10; i++)
		{
			tmp_key = Custom::mocking_value<key_type>();
			std_const_eq_pair = ref.equal_range(tmp_key);
			const_eq_pair = map.equal_range(tmp_key);

			if (std_const_eq_pair.first == ref.end())
				REQUIRE(const_eq_pair.first == map.end());
			else if (std_const_eq_pair.second ==  ref.end())
				REQUIRE(const_eq_pair.second == map.end());
			else
			{
				REQUIRE(*std_const_eq_pair.first == *const_eq_pair.first);
				REQUIRE(*std_const_eq_pair.second == *const_eq_pair.second);
			}
		}
	}
};
