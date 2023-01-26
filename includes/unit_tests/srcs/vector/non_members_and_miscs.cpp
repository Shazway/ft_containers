#include "../../hdrs/vector_utils.hpp"

TEST_CASE("Vector non-members functions", "[vector][operator]") {

	Vec		ref = Custom::mocking_value<Vec>();
	Vec		vec(ref);

	SECTION("operator == && !=") {
		REQUIRE(ref == vec);
		REQUIRE(ref <= vec);
		REQUIRE(ref >= vec);
		vec.pop_back();
		REQUIRE(ref != vec);
		REQUIRE_FALSE(ref < vec);
	}
	SECTION("operator < && >") {
		for(size_t i = 0; i < REF_SIZE / 10; i++) {
			if (ref.back() < vec.back())
				REQUIRE(ref < vec);
			else if (ref.back() > vec.back())
				REQUIRE(ref > vec);
			else {
				REQUIRE_FALSE(ref < vec);
				REQUIRE_FALSE(ref > vec);
			}
			ref.pop_back();
			vec.pop_back();
		}
	}
	SECTION("operator <= && >=") {
		for(size_t i = 0; i < REF_SIZE / 10; i++) {
			if (ref.back() < vec.back())
				REQUIRE(ref <= vec);
			else if (ref.back() > vec.back())
				REQUIRE(ref >= vec);
			else {
				REQUIRE(ref <= vec);
				REQUIRE(ref >= vec);
			}
			ref.pop_back();
			vec.pop_back();
		}
	}

	SECTION("swap()") {
		VecConstIt	it;
		VecConstIt	it2;

		it = ref.begin();
		it2 = vec.begin();

		ref.swap(vec);
		REQUIRE(it == vec.begin());
		REQUIRE(it2 == ref.begin());
	}
}
