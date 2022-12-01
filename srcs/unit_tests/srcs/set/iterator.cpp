#include "../../hdrs/set_utils.hpp"

TEST_CASE("Set iterator", "[set][iterator]") {

	StdSet	ref = Custom::mocking_value<StdSet>();
	Set		set(ref.begin(), ref.end());

	SECTION("same begin && end it") {
		REQUIRE(*ref.begin() == *set.begin());
		REQUIRE(*(--ref.end()) == *(--set.end()));
	}

	SECTION("same reverse_begin && reverse_end it") {
		REQUIRE(*ref.rbegin() == *set.rbegin());
		REQUIRE(*(--ref.rend()) == *(--set.rend()));
	}

	SECTION("constructor") {
		SetIt	it = set.begin();

		SetIt	temp; // default constructor
		(void)temp;

		SetIt	it2(it);
		REQUIRE(*it == *it2); // copy constructor

		it++;
		it++;
		it2 = it;
		REQUIRE(*it == *it2); // assignement

		SetConstIt	const_it(it);
		REQUIRE(*const_it == *it); // construct iterator from const_iterator
	}

	SECTION("operator==() && operator!=()") {
		SetIt	it;
		it = set.begin();

		REQUIRE((it == set.begin()) == true);
		REQUIRE((it == set.end()) == false);
		REQUIRE((it != set.begin()) == false);
		REQUIRE((it != set.end()) == true);
	}

	StdSetConstIt	ref_tmp = ++(++(--(++(++ref.begin()))));
	SetConstIt		 tmp = ++(++(--(++(++set.begin()))));

	StdSetConstRevIt	r_ref_tmp = ++(++(--(++(++ref.rbegin()))));
	SetConstRevIt		r_tmp = ++(++(--(++(++set.rbegin()))));

	SECTION("++it && --it") {
		REQUIRE(*ref_tmp == *tmp);
		REQUIRE(*r_ref_tmp == *r_tmp);
	}
	SECTION("it++ && it--") {
		ref_tmp++;
		ref_tmp--;
		ref_tmp++;
		tmp++;
		tmp--;
		tmp++;
		REQUIRE(*ref_tmp == *tmp);

		r_ref_tmp++;
		r_ref_tmp--;
		r_ref_tmp++;
		r_tmp++;
		r_tmp--;
		r_tmp++;
		REQUIRE(*r_ref_tmp == *r_tmp);
	}
	SECTION("*it++ && *it--") {
		REQUIRE(*ref_tmp == *tmp);
		REQUIRE(*ref_tmp++ == *tmp++);
		REQUIRE(*ref_tmp-- == *tmp--);
		REQUIRE(*ref_tmp == *tmp);

		REQUIRE(*r_ref_tmp == *r_tmp);
		REQUIRE(*r_ref_tmp++ == *r_tmp++);
		REQUIRE(*r_ref_tmp-- == *r_tmp--);
		REQUIRE(*r_ref_tmp == *r_tmp);
	}

}
