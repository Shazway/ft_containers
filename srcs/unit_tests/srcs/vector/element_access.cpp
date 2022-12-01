#include "../../hdrs/vector_utils.hpp"
#include <stdexcept>

TEST_CASE("Vector element access", "[vector][access]") {

	const StdVec			ref = Custom::mocking_value<StdVec>();
	const Vec	vec(ref.begin(), ref.end());

	SECTION("operator[]") {
		REQUIRE(ref[0] == vec[0]);
		REQUIRE(ref[ref.size() /2 ] == vec[vec.size() / 2]);
		REQUIRE(ref[ref.size() - 1] == vec[vec.size() - 1]);

		const ValueType& tmp = vec[REF_SIZE / 2];
		REQUIRE(ref[REF_SIZE /2 ] == tmp);
	}

	SECTION("at()") {
		Vec	empty_vec;

		REQUIRE(ref.at(0) == vec.at(0));
		REQUIRE(ref.at(REF_SIZE / 2) == vec.at(REF_SIZE / 2));
		REQUIRE(ref.at(REF_SIZE - 1) == vec.at(REF_SIZE - 1));

		const ValueType& tmp = vec.at(REF_SIZE / 2);
		REQUIRE(ref.at(REF_SIZE / 2) == tmp);

		REQUIRE_THROWS_AS(vec.at(-1), std::out_of_range const&);
		REQUIRE_THROWS_AS(vec.at(REF_SIZE), std::out_of_range const&);
		REQUIRE_THROWS_AS(empty_vec.at(0), std::out_of_range const&);
	}
	SECTION("front()") {
		REQUIRE(vec.front() == ref.front());
	}
	SECTION("back()") {
		REQUIRE(vec.back() == ref.back());
	}
}
