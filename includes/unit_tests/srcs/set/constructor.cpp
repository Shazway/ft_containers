#include "../../hdrs/set_utils.hpp"

TEST_CASE("Set constructors", "[set][constructor]") {

	SECTION("default constructor") {
		Set	set;

		REQUIRE(set.size() == 0);
	}

	StdSet range = Custom::mocking_value<StdSet>();

	StdSetIt	range_begin = range.begin();
	StdSetIt	range_end = range.end();

	SECTION("range constructor begin-end") {
		Set	set(range_begin, range_end);

		REQUIRE_THAT(set, Custom::SetEqual<Set>(range));
	}
	SECTION("range constructor somwhere-end") {
		++(++(range_begin));
		StdSet		ref(range_begin, range_end);
		Set	set(range_begin, range_end);

		REQUIRE_THAT(set, Custom::SetEqual<Set>(ref));
	}
	SECTION("range constructor somwhere-end") {
		--(--(range_end));
		StdSet		ref(range_begin, range_end);
		Set	set(range_begin, range_end);

		REQUIRE_THAT(set, Custom::SetEqual<Set>(ref));
	}

	SECTION("copy constructor") {
		Set	origin_set(++(++range_begin), --(--(--range_end)));
		Set	copy_set(origin_set);

		REQUIRE_THAT(origin_set, Custom::SetEqual<Set>(copy_set));
	}
}
