#include "../../hdrs/vector_utils.hpp"

TEST_CASE("Vector modifiers", "[vector][modifier]") {

	StdVec 				ref = Custom::mocking_value<StdVec>();
	StdVec				tmp;
	Vec	vec;
	ValueType		tmp_val = Custom::mocking_value<ValueType>();

	SECTION("assign(first, last)") {
		vec.assign(ref.begin(), ref.end());
		REQUIRE_THAT(vec, Custom::VectorEqual<Vec>(ref)); // assign all of other container

		{
			StdVec		tmp;
			tmp.assign(ref.begin() + REF_SIZE / 4, ref.end() - REF_SIZE / 4);
			vec.assign(ref.begin() + REF_SIZE / 4, ref.end() - REF_SIZE / 4);
			REQUIRE_THAT(vec, Custom::VectorEqual<Vec>(tmp)); // assign middle of other container
		}
		{
			StdVec		tmp;
			VecIt		it = vec.begin();
			tmp.assign(ref.begin(), ref.begin());
			vec.assign(ref.begin(), ref.begin());
			REQUIRE_THAT(vec, Custom::VectorEqual<Vec>(tmp)); // assign am empty container
			REQUIRE(it == vec.begin());
		}
	}
	SECTION("assing(first, last) with input_iterator") {
		typedef std::istream_iterator<char>	is_iterator;
		std::ifstream		file;
		is_iterator			file_it;

		file.open(FILE_PATH);
		file_it = is_iterator(file);
		ft::vector<char>	vec;
		vec.assign(file_it, is_iterator());

		file.close();
		file.open(FILE_PATH);
		file_it = is_iterator(file);
		REQUIRE(Custom::equal(file_it, is_iterator(), vec.begin(), vec.end()) == true);
		file.close();
	}

	SECTION("assign(n, val)") {
		StdVec		tmp;
		VecIt		it = vec.begin();

		REQUIRE_THROWS(vec.assign(-5, tmp_val));

		{
			tmp.assign(REF_SIZE, tmp_val);
			vec.assign(REF_SIZE, tmp_val);
			REQUIRE_THAT(vec, Custom::VectorEqual<Vec>(tmp));
		}
		{
			it = vec.begin();
			tmp.assign(0, tmp_val);
			vec.assign(0, tmp_val);
			REQUIRE_THAT(vec, Custom::VectorEqual<Vec>(tmp));
			REQUIRE(it == vec.begin());
		}
		{
			it = vec.begin();
			tmp.assign(REF_SIZE / 2, tmp_val);
			vec.assign(REF_SIZE / 2, tmp_val);
			REQUIRE_THAT(vec, Custom::VectorEqual<Vec>(tmp));
			REQUIRE(it == vec.begin());
		}
	}

	SECTION("push_back() && pop_back()") {
		ref.clear();
		for (size_t i = 0; i < REF_SIZE + 100; i++)
		{
			tmp_val = Custom::mocking_value<ValueType>();
			ref.push_back(tmp_val);
			vec.push_back(tmp_val);
		}
		REQUIRE_THAT(vec, Custom::VectorEqual<Vec>(ref));

		for (size_t i = 0; i < REF_SIZE; i++)
		{
			ref.pop_back();
			vec.pop_back();
		}
		REQUIRE_THAT(vec, Custom::VectorEqual<Vec>(ref));
	}

	StdVecConstIt	std_it;
	VecConstIt		it;

	SECTION("insert(position, val)") {
		for (size_t i = 0; i < REF_SIZE; i++)
		{
			tmp_val = Custom::mocking_value<ValueType>();
			if (i % 3 == 0) {
				std_it = tmp.insert(tmp.begin(), tmp_val);
				it = vec.insert(vec.begin(), tmp_val);
			}
			else if (i % 3 == 1) {
				std_it = tmp.insert(tmp.begin() + tmp.size() / 2, tmp_val);
				it = vec.insert(vec.begin() + vec.size() / 2, tmp_val);
			}
			else {
				std_it = tmp.insert(tmp.end(), tmp_val);
				it = vec.insert(vec.end(), tmp_val);
			}
			if (std_it == tmp.end())
				REQUIRE(it == vec.end());
			else
				REQUIRE(*std_it == *it);
		}
		REQUIRE_THAT(vec, Custom::VectorEqual<Vec>(tmp));
	}
	SECTION("insert(position, n, val)") {
		size_t		n;

		for (size_t i = 0; i < REF_SIZE; i++)
		{
			tmp_val = Custom::mocking_value<ValueType>();
			n = Custom::mocking_value<size_t>();
			if (i % 3 == 0) {
				tmp.insert(tmp.begin(), n, tmp_val);
				vec.insert(vec.begin(), n, tmp_val);
			}
			else if (i % 3 == 1) {
				tmp.insert(tmp.begin() + tmp.size() / 2, n, tmp_val);
				vec.insert(vec.begin() + vec.size() / 2, n, tmp_val);
			}
			else {
				tmp.insert(tmp.end(), n, tmp_val);
				vec.insert(vec.end(), n, tmp_val);
			}
		}
		REQUIRE_THAT(vec, Custom::VectorEqual<Vec>(tmp));
	}

	SECTION("insert(position, first, last)") {
		StdVecConstIt	first;
		StdVecConstIt	last;


		for (size_t i = 0; i < REF_SIZE; i++)
		{
			ref = Custom::mocking_value<StdVec>();
			first = ref.begin();
			last = ref.end();
			if (i % 2 == 0)
				first = ref.begin() + ref.size() / 3;
			if (i % 3 == 0)
				last = ref.end() - ref.size() / 3;

			tmp.insert(tmp.end(), first, last);
			vec.insert(vec.end(), first, last);
		}
		REQUIRE_THAT(vec, Custom::VectorEqual<Vec>(tmp));
	}

	SECTION("erase(position)") {
		tmp.assign(ref.begin(), ref.end());
		vec.assign(ref.begin(), ref.end());
		for (size_t i = 0; i < REF_SIZE / 10; i++) {
			if (i % 3 == 0) {
				std_it = tmp.erase(tmp.begin());
				it = vec.erase(vec.begin());
			}
			else if (i % 3 == 1) {
				std_it = tmp.erase(tmp.begin() + tmp.size() / 2);
				it = vec.erase(vec.begin() + vec.size() / 2);
			}
			else {
				std_it = tmp.erase(tmp.end() - 2);
				it = vec.erase(vec.end() - 2);
			}
			if (std_it == tmp.end())
				REQUIRE(it == vec.end());
			else
				REQUIRE(*std_it == *it);
		}
		REQUIRE_THAT(vec, Custom::VectorEqual<Vec>(tmp));
	}
	SECTION("erase(first, last)") {
		size_t	begin_offset;
		size_t	end_offset;

		tmp.assign(ref.begin(), ref.end());
		vec.assign(ref.begin(), ref.end());
		for (size_t i = 0; i < REF_SIZE / 100; i++)
		{
			begin_offset = tmp.size() / 10;
			end_offset = tmp.size() / 10;
			if (i % 2 == 0)
				begin_offset += tmp.size() / 3;
			if (i % 3 == 0)
				end_offset += tmp.size() / 3;

			std_it = tmp.erase(tmp.begin() + begin_offset, tmp.end() - end_offset);
			it = vec.erase(vec.begin() + begin_offset, vec.end() - end_offset);

			if (std_it == tmp.end())
				REQUIRE(it == vec.end());
			else
				REQUIRE(*std_it == *it);
		}
		REQUIRE_THAT(vec, Custom::VectorEqual<Vec>(tmp));
	}

	SECTION("swap(a)") {
		VecIt				it2;
		Vec	tmp_test_vec;

		tmp_val = Custom::mocking_value<ValueType>();

		vec.assign(ref.begin(), ref.end());
		tmp_test_vec.insert(tmp_test_vec.begin(), 10, tmp_val);
		it2 = tmp_test_vec.begin();
		it = vec.begin();

		tmp_test_vec.swap(vec);
		REQUIRE(it == tmp_test_vec.begin());
		REQUIRE(it2 == vec.begin());
	}

	SECTION("clear()") {
		vec.assign(ref.begin(), ref.end());
		vec.clear();
		REQUIRE((vec.size() == 0 && vec.empty()));
	}
}
