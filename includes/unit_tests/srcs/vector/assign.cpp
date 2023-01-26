#include "../../hdrs/vector_utils.hpp"

TEST_CASE("Vector assignement operator", "[vector]") {

	SECTION("simple assignation test") {
		Vec	foo(3);
		Vec	bar(5);

		bar = foo;

		REQUIRE(bar.size() == 3);
	}
}
