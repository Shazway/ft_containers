#include "../../hdrs/set_utils.hpp"

TEST_CASE("Set operation", "[set][operation]") {
	typedef Set::key_type	key_type;

	StdSet			ref = Custom::mocking_value<StdSet>();
	Set				set(ref.begin(), ref.end());

	StdSetIt		std_it;
	SetIt			it;
	StdSetConstIt	std_const_it;
	SetConstIt		const_it;
	key_type		tmp_key;

	SECTION("find(k)") {
		std_it = ref.find(*(++ref.begin()));
		it = set.find(*(++ref.begin()));

		REQUIRE(*std_it == *it);
	}
	SECTION("find(k) const") {
		std_const_it = ref.find(*(++ref.begin()));
		const_it = set.find(*(++ref.begin()));

		REQUIRE(*std_const_it == *const_it);
	}
	SECTION("find(k), with value not present in set") {
		tmp_key = Custom::mocking_value<key_type>();
		set.erase(tmp_key);

		REQUIRE(set.find(tmp_key) == set.end());
	}
	SECTION("find(k) const, with value not present in set") {
		tmp_key = Custom::mocking_value<key_type>();
		set.erase(tmp_key);
		const_it = set.find(tmp_key);

		REQUIRE(const_it == set.end());
	}

	SECTION("count(k)") {
		for (size_t i = 0; i < REF_SIZE / 10; i++)
		{
			tmp_key = Custom::mocking_value<key_type>();
			REQUIRE(ref.count(tmp_key) == set.count(tmp_key));
		}
	}

	SECTION("lower_bound(k)") {
		for (size_t i = 0; i < REF_SIZE / 10; i++)
		{
			tmp_key = Custom::mocking_value<key_type>();
			std_it = ref.lower_bound(tmp_key);
			it = set.lower_bound(tmp_key);

			if (std_it == ref.end())
				REQUIRE(it == set.end());
			else
				REQUIRE(*std_it == *it);
		}
	}
	SECTION("lower_bound(k) const") {
		for (size_t i = 0; i < REF_SIZE / 10; i++)
		{
			tmp_key = Custom::mocking_value<key_type>();
			std_const_it = ref.lower_bound(tmp_key);
			const_it = set.lower_bound(tmp_key);

			if (std_const_it == ref.end())
				REQUIRE(const_it == set.end());
			else
				REQUIRE(*std_const_it == *const_it);
		}
	}

	SECTION("upper_bound(k)") {
		for (size_t i = 0; i < REF_SIZE / 10; i++)
		{
			tmp_key = Custom::mocking_value<key_type>();
			std_it = ref.upper_bound(tmp_key);
			it = set.upper_bound(tmp_key);

			if (std_it == ref.end())
				REQUIRE(it == set.end());
			else
				REQUIRE(*std_it == *it);
		}
	}
	SECTION("upper_bound(k)") {
		for (size_t i = 0; i < REF_SIZE / 10; i++)
		{
			tmp_key = Custom::mocking_value<key_type>();
			std_const_it = ref.upper_bound(tmp_key);
			const_it = set.upper_bound(tmp_key);

			if (std_const_it == ref.end())
				REQUIRE(const_it == set.end());
			else
				REQUIRE(*std_const_it == *const_it);
		}
	}

	SECTION("equal_pair(k)") {
		typedef std::pair<StdSetIt, StdSetIt>	std_eq_pair_type;
		typedef NS::pair<SetIt, SetIt>			eq_pair_type;

		std_eq_pair_type	std_eq_pair;
		eq_pair_type		eq_pair;

		for (size_t i = 0; i < REF_SIZE / 10; i++)
		{
			tmp_key = Custom::mocking_value<key_type>();
			std_eq_pair = ref.equal_range(tmp_key);
			eq_pair = set.equal_range(tmp_key);

			if (std_eq_pair.first == ref.end())
				REQUIRE(eq_pair.first == set.end());
			else if (std_eq_pair.second ==  ref.end())
				REQUIRE(eq_pair.second == set.end());
			else
			{
				REQUIRE(*std_eq_pair.first == *eq_pair.first);
				REQUIRE(*std_eq_pair.second == *eq_pair.second);
			}
		}
	}
	SECTION("equal_pair(k) const") {
		typedef std::pair<StdSetConstIt, StdSetConstIt>	std_const_eq_pair_type;
		typedef NS::pair<SetConstIt, SetConstIt>		const_eq_pair_type;

		std_const_eq_pair_type	std_const_eq_pair;
		const_eq_pair_type		const_eq_pair;
		for (size_t i = 0; i < REF_SIZE / 10; i++)
		{
			tmp_key = Custom::mocking_value<key_type>();
			std_const_eq_pair = ref.equal_range(tmp_key);
			const_eq_pair = set.equal_range(tmp_key);

			if (std_const_eq_pair.first == ref.end())
				REQUIRE(const_eq_pair.first == set.end());
			else if (std_const_eq_pair.second ==  ref.end())
				REQUIRE(const_eq_pair.second == set.end());
			else
			{
				REQUIRE(*std_const_eq_pair.first == *const_eq_pair.first);
				REQUIRE(*std_const_eq_pair.second == *const_eq_pair.second);
			}
		}
	}
};
