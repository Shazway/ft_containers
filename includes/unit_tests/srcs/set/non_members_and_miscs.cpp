#include "../../hdrs/set_utils.hpp"

TEST_CASE("Set non-members functions", "[set][operator]") {

	Set		ref = Custom::mocking_value<Set>();
	Set		set(ref);

	SECTION("operator == && !=") {
		REQUIRE(ref == set);
		REQUIRE(ref <= set);
		REQUIRE(ref >= set);
		ref.erase(--ref.end());
		REQUIRE(ref != set);
	}
	SECTION("operator < && >") {
		for(size_t i = 0; i < REF_SIZE / 10; i++) {
			if (*--ref.end() < *--set.end())
				REQUIRE(ref < set);
			else if (*--ref.end() > *--set.end())
				REQUIRE(ref > set);
			else {
				REQUIRE_FALSE(ref < set);
				REQUIRE_FALSE(ref > set);
			}
			ref.erase(--ref.end());
			set.erase(--set.end());
		}
	}
	SECTION("operator <= && >=") {
		for(size_t i = 0; i < REF_SIZE / 10; i++) {
			if (*--ref.end() < *--set.end())
				REQUIRE(ref <= set);
			else if (*--ref.end() > *--set.end())
				REQUIRE(ref >= set);
			else {
				REQUIRE(ref <= set);
				REQUIRE(ref >= set);
			}
			ref.erase(--ref.end());
			set.erase(--set.end());
		}
	}

	SECTION("swap()") {
		SetConstIt	it;
		SetConstIt	it2;

		it = ref.begin();
		it2 = set.begin();

		ref.swap(set);
		REQUIRE(it == set.begin());
		REQUIRE(it2 == ref.begin());
	}
}
