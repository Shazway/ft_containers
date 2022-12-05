#include "../../hdrs/vector_utils.hpp"

TEST_CASE("Vector iterator", "[vector][iterator]") {

	StdVec ref = Custom::mocking_value<StdVec>();
	Vec	vec(ref.begin(), ref.end());

	SECTION("same begin && end it") {
		REQUIRE(*ref.begin() == *vec.begin());
		REQUIRE(*(--ref.end()) == *(--vec.end()));
	}

	SECTION("same reverse_begin && reverse_end it") {
		REQUIRE(*ref.rbegin() == *vec.rbegin());
		REQUIRE(*(--ref.rend()) == *(--vec.rend()));
	}

	SECTION("constructor") {
		VecIt	it = vec.begin();

		VecIt	temp; // default constructor
		(void)temp;

		VecIt	it2(it);
		REQUIRE(*it == *it2); // copy constructor

		it++;
		it++;
		it2 = it;
		REQUIRE(*it == *it2); // assignement

		VecConstIt	const_it(it);
		REQUIRE(*const_it == *it); // construct iterator from const_iterator
	}

	SECTION("operator==() && operator!=()") {
		VecIt	it;
		it = vec.begin();

		REQUIRE((it == vec.begin()) == true);
		REQUIRE((it == vec.end()) == false);
		REQUIRE((it != vec.begin()) == false);
		REQUIRE((it != vec.end()) == true);
	}

	SECTION("mutable operator *it = a") {
		ValueType tmp = Custom::mocking_value<ValueType>();
		*ref.begin() = tmp;
		*vec.begin() = tmp;

		REQUIRE(*ref.begin() == *vec.begin());
	}

	StdVecConstIt	ref_tmp = ++(++(--(++(++ref.begin()))));
	VecConstIt		 tmp = ++(++(--(++(++vec.begin()))));

	StdVecConstRevIt	r_ref_tmp = ++(++(--(++(++ref.rbegin()))));
	VecConstRevIt		r_tmp = ++(++(--(++(++vec.rbegin()))));

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

	ref_tmp = ref.begin() + REF_SIZE / 2;
	tmp = vec.begin() + REF_SIZE / 2;

	r_ref_tmp = ref.rbegin() + REF_SIZE / 2;
	r_tmp = vec.rbegin() + REF_SIZE / 2;

	SECTION("it + n && n + it && it - n  && it - it2") {
		ref_tmp = ref_tmp + 15;
		tmp = tmp + 15;
		REQUIRE(*ref_tmp == *tmp);

		r_ref_tmp = r_ref_tmp + 15;
		r_tmp = r_tmp + 15;
		REQUIRE(*r_ref_tmp == *r_tmp);
	}

	SECTION("n + it") {
		ref_tmp = 30 + ref_tmp;
		tmp = 30 + tmp;
		REQUIRE(*ref_tmp == *tmp);

		r_ref_tmp = 30 + r_ref_tmp;
		r_tmp = 30 + r_tmp;
		REQUIRE(*r_ref_tmp == *r_tmp);
	}

	SECTION("it - n") {
		ref_tmp = ref_tmp - 5;
		tmp = tmp - 5;
		REQUIRE(*ref_tmp == *tmp);

		r_ref_tmp = r_ref_tmp - 5;
		r_tmp = r_tmp - 5;
		REQUIRE(*r_ref_tmp == *r_tmp);
	}

	SECTION("it - it2") {
		size_t ref_diff = ref_tmp - ref.begin();
		size_t diff = tmp - vec.begin();
		REQUIRE(ref_diff == diff); // it - it2

		size_t r_ref_diff = r_ref_tmp - ref.rbegin();
		size_t r_diff = r_tmp - vec.rbegin();
		REQUIRE(r_ref_diff == r_diff); // it - it2
	}

	SECTION("it += n") {
		ref_tmp += 30;
		tmp += 30;
		REQUIRE(*ref_tmp == *tmp);

		r_ref_tmp += 30;
		r_tmp += 30;
		REQUIRE(*r_ref_tmp == *r_tmp);
	}

	SECTION("it -= n") {
		ref_tmp -= 30;
		tmp -= 30;
		REQUIRE(*ref_tmp == *tmp);

		r_ref_tmp -= 30;
		r_tmp -= 30;
		REQUIRE(*r_ref_tmp == *r_tmp);
	}

	SECTION("it < it2 && it > it2") {
		REQUIRE((tmp > vec.begin()) == (ref_tmp > ref.begin()));
		REQUIRE((tmp > vec.end()) == (ref_tmp > ref.end()));
		REQUIRE((tmp < vec.begin()) == (ref_tmp < ref.begin()));
		REQUIRE((tmp < vec.end()) == (ref_tmp < ref.end()));

		// with equal it
		REQUIRE((vec.begin() > vec.begin()) == (ref.begin() > ref.begin()));
		REQUIRE((vec.end() > vec.end()) == (ref.end() > ref.end()));
		REQUIRE((vec.begin() < vec.begin()) == (ref.begin() < ref.begin()));
		REQUIRE((vec.end() < vec.end()) == (ref.end() < ref.end()));

		// REVERSE IT
		REQUIRE((r_tmp > vec.rbegin()) == (r_ref_tmp > ref.rbegin()));
		REQUIRE((r_tmp > vec.rend()) == (r_ref_tmp > ref.rend()));
		REQUIRE((r_tmp < vec.rbegin()) == (r_ref_tmp < ref.rbegin()));
		REQUIRE((r_tmp < vec.rend()) == (r_ref_tmp < ref.rend()));

		// with equal it
		REQUIRE((vec.rbegin() > vec.rbegin()) == (ref.rbegin() > ref.rbegin()));
		REQUIRE((vec.rend() > vec.rend()) == (ref.rend() > ref.rend()));
		REQUIRE((vec.rbegin() < vec.rbegin()) == (ref.rbegin() < ref.rbegin()));
		REQUIRE((vec.rend() < vec.rend()) == (ref.rend() < ref.rend()));
	}
	SECTION("it <= it2 && it >= it2") {
		REQUIRE((tmp >= vec.begin()) == (ref_tmp >= ref.begin()));
		REQUIRE((tmp >= vec.end()) == (ref_tmp >= ref.end()));
		REQUIRE((tmp <= vec.begin()) == (ref_tmp <= ref.begin()));
		REQUIRE((tmp <= vec.end()) == (ref_tmp <= ref.end()));
		// with equal it
		REQUIRE((vec.begin() >= vec.begin()) == (ref.begin() >= ref.begin()));
		REQUIRE((vec.end() >= vec.end()) == (ref.end() >= ref.end()));
		REQUIRE((vec.begin() <= vec.begin()) == (ref.begin() <= ref.begin()));
		REQUIRE((vec.end() <= vec.end()) == (ref.end() <= ref.end()));

		//REVERSE
		REQUIRE((r_tmp >= vec.rbegin()) == (r_ref_tmp >= ref.rbegin()));
		REQUIRE((r_tmp >= vec.rend()) == (r_ref_tmp >= ref.rend()));
		REQUIRE((r_tmp <= vec.rbegin()) == (r_ref_tmp <= ref.rbegin()));
		REQUIRE((r_tmp <= vec.rend()) == (r_ref_tmp <= ref.rend()));
		// with equal it
		REQUIRE((vec.rbegin() >= vec.rbegin()) == (ref.rbegin() >= ref.rbegin()));
		REQUIRE((vec.rend() >= vec.rend()) == (ref.rend() >= ref.rend()));
		REQUIRE((vec.rbegin() <= vec.rbegin()) == (ref.rbegin() <= ref.rbegin()));
		REQUIRE((vec.rend() <= vec.rend()) == (ref.rend() <= ref.rend()));
	}

	SECTION("it[n]") {
		REQUIRE(tmp[0] == ref_tmp[0]);
		REQUIRE(tmp[-100] == ref_tmp[-100]);
		REQUIRE(tmp[100] == ref_tmp[100]);

		REQUIRE(r_tmp[0] == r_ref_tmp[0]);
		REQUIRE(r_tmp[-100] == r_ref_tmp[-100]);
		REQUIRE(r_tmp[100] == r_ref_tmp[100]);
	}

}
