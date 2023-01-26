#include "../../hdrs/stack_utils.hpp"

TEST_CASE("Stack constructors", "[stack][constructor]") {

	StdStackCont	std_cont = Custom::mocking_value<StdStackCont>();
	StackCont		cont(std_cont.begin(), std_cont.end());

	StdStack		std_stack(std_cont);
	Stack			stack(cont);

	ValueType		tmp_val;

	SECTION("default constructor") {
		REQUIRE_THAT(stack, Custom::StackEqual<Stack>(std_stack));
	}

	SECTION("empty()") {
		REQUIRE(stack.empty() ==  std_stack.empty());

		StackCont	tmp_cont;
		Stack		tmp_stack(tmp_cont);
		REQUIRE(tmp_stack.size() == 0);
	}

	SECTION("size(), push(), pop(), top()") {
		REQUIRE(stack.size() ==  std_stack.size());

		tmp_val = Custom::mocking_value<ValueType>();
		stack.push(tmp_val);
		std_stack.push(tmp_val);
		REQUIRE(stack.size() ==  std_stack.size());
		REQUIRE(stack.top() == std_stack.top());

		stack.pop();
		stack.pop();
		std_stack.pop();
		std_stack.pop();
		REQUIRE(stack.size() ==  std_stack.size());
		REQUIRE(stack.top() == std_stack.top());
	}

	StackCont		cont1(std_cont.begin(), std_cont.end());
	StackCont		cont2(std_cont.begin(), std_cont.end());

	Stack			stack1(cont1);
	Stack			stack2(cont2);

	SECTION("operator == && !=") {
		REQUIRE(stack1 == stack2);
		REQUIRE(stack1 <= stack2);
		REQUIRE(stack1 >= stack2);
		stack1.pop();
		REQUIRE(stack1 != stack2);
	}
	SECTION("operator < && >") {
		for(size_t i = 0; i < REF_SIZE / 10; i++) {
			if (stack1.top() < stack2.top())
				REQUIRE(stack1 < stack2);
			else if (stack1.top() > stack2.top())
				REQUIRE(stack1 > stack2);
			else {
				REQUIRE_FALSE(stack1 < stack2);
				REQUIRE_FALSE(stack1 > stack2);
			}
			stack1.pop();
			stack2.pop();
		}
	}
	SECTION("operator <= && >=") {
		for(size_t i = 0; i < REF_SIZE / 10; i++) {
			if (stack1.top() < stack2.top())
				REQUIRE(stack1 <= stack2);
			else if (stack1.top() > stack2.top())
				REQUIRE(stack1 >= stack2);
			else {
				REQUIRE(stack1 <= stack2);
				REQUIRE(stack1 >= stack2);
			}
			stack1.pop();
			stack2.pop();
		}
	}
}
