#include "../../hdrs/set_utils.hpp"

TEST_CASE("Set assignement operator", "[set][assign]") {

	SECTION("simple assignation test") {
		Set foo = Custom::mocking_value<Set>();
		Set	bar;

		bar = foo;

		REQUIRE_THAT(bar, Custom::SetEqual<Set>(foo));
	}
}
