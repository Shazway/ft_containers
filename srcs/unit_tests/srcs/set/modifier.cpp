#include "../../hdrs/set_utils.hpp"

TEST_CASE("Set modifiers", "[set][modifier]") {

	Set				set;
	StdSet 			ref;

	StdSetIt		std_it;
	SetIt			it;

	typedef NS::pair<SetIt, bool>		SetReturn;
	typedef std::pair<StdSetIt, bool>	StdSetReturn;

	ValueType tmp_value;

	SECTION("insert(val)") {
		tmp_value = Custom::mocking_value<ValueType>();

		SetReturn		tmp_return;
		StdSetReturn	tmp_std_return;

		tmp_return = set.insert(tmp_value);
		tmp_std_return = ref.insert(tmp_value);

		REQUIRE(*tmp_return.first == *tmp_std_return.first);
		REQUIRE(tmp_return.second == tmp_std_return.second);

		// TRY TO REINSERT, bool must be false
		tmp_return = set.insert(tmp_value);
		tmp_std_return = ref.insert(tmp_value);

		REQUIRE(*tmp_return.first == *tmp_std_return.first);
		REQUIRE(tmp_return.second == tmp_std_return.second);
	}

	SECTION("insert(position, val)") {
		for (size_t i = 0; i < REF_SIZE; i++)
		{
			tmp_value = Custom::mocking_value<ValueType>();
			if (i % 3 == 0) {
				std_it = ref.insert(ref.begin(), tmp_value);
				it = set.insert(set.begin(), tmp_value);
			}
			if (i % 3 == 1) {
				std_it = ref.insert(++ref.begin(), tmp_value);
				it = set.insert(++set.begin(), tmp_value);
			}
			else {
				std_it = ref.insert(ref.end(), tmp_value);
				it = set.insert(set.end(), tmp_value);
			}
			if (std_it == ref.end())
				REQUIRE(it == set.end());
			else
				REQUIRE(*std_it == *it);
		}
		REQUIRE_THAT(set, Custom::SetEqual<Set>(ref));
	}

	SECTION("insert(first, last)") {
		Set	tmp_set = Custom::mocking_value<Set>();

		set.insert(tmp_set.begin(), tmp_set.end());
		REQUIRE_THAT(set, Custom::SetEqual<Set>(tmp_set));

		set.insert(set.begin(), set.end());
		REQUIRE_THAT(set, Custom::SetEqual<Set>(tmp_set));
	}

	SECTION("erase(position)") {
		ref = Custom::mocking_value<StdSet>();
		Set set(ref.begin(), ref.end());
		for (size_t i = 0; i < REF_SIZE / 10; i++) {
			if (i % 3 == 0) {
				ref.erase(ref.begin());
				set.erase(set.begin());
			}
			else if (i % 3 == 1) {
				ref.erase((++(++ref.begin())));
				set.erase((++(++set.begin())));
			}
			else {
				ref.erase((--(--ref.end())));
				set.erase((--(--set.end())));
			}
		}
		REQUIRE_THAT(set, Custom::SetEqual<Set>(ref));
	}
	SECTION("erase(val)") {
		size_t	std_remove;
		size_t	set_remove;

		ref = Custom::mocking_value<StdSet>();
		Set set(ref.begin(), ref.end());
		for (size_t i = 0; i < REF_SIZE / 10; i++) {
			if (i % 3 == 0)
				REQUIRE(ref.erase(*ref.begin()) == set.erase(*set.begin()));
			else if (i % 3 == 1)
				REQUIRE(ref.erase(*(++(++ref.begin()))) == set.erase(*(++(++set.begin()))));
			else
				REQUIRE(ref.erase(*(--(--ref.end()))) == set.erase(*(--(--set.end()))));
		}
		REQUIRE_THAT(set, Custom::SetEqual<Set>(ref));
	}
	SECTION("erase(first, last)") {
		ref = Custom::mocking_value<StdSet>();
		Set set(ref.begin(), ref.end());
		for (size_t i = 0; i < REF_SIZE / 100; i++)
		{
			if (i % 2) {
				ref.erase(ref.begin(), ++(++ref.begin()));
				set.erase(set.begin(), ++(++set.begin()));
			}
			else {
				ref.erase(--(--ref.end()), ref.end());
				set.erase(--(--set.end()), set.end());
			}
		}
		REQUIRE_THAT(set, Custom::SetEqual<Set>(ref));
	}

	SECTION("swap(a)") {
		Set					tmp_test_set;
		SetIt				it2;

		set.insert(Custom::mocking_value<ValueType>());
		tmp_test_set.insert(Custom::mocking_value<ValueType>());
		it = set.begin();
		it2 = tmp_test_set.begin();

		tmp_test_set.swap(set);
		REQUIRE(it == tmp_test_set.begin());
		REQUIRE(it2 == set.begin());
	}

	SECTION("clear()") {
		set = Custom::mocking_value<Set>();
		set.clear();
		REQUIRE((set.size() == 0 && set.empty()));
	}
}
