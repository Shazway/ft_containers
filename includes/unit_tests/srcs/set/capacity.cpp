#include "../../hdrs/set_utils.hpp"

TEST_CASE("Set capacity", "[set][capacity]") {

	StdSet		ref = Custom::mocking_value<StdSet>();
	Set			set(ref.begin(), ref.end());

	SECTION("size()") {
		REQUIRE(ref.size() == set.size());
	}
	SECTION("max_size()") {
		CHECK(ref.max_size() == set.max_size());
	}
	SECTION("empty()") {
		Set tmp_set;
		REQUIRE(tmp_set.empty());
		REQUIRE_FALSE(set.empty());
	}

}
