#include "../../hdrs/map_utils.hpp"

TEST_CASE("Map assignement operator", "[map][assign]") {

	SECTION("simple assignation test") {
		Map foo = Custom::mocking_value<Map>();
		Map	bar;

		bar = foo;

		REQUIRE_THAT(bar, Custom::MapEqual<Map>(foo));
	}
}
