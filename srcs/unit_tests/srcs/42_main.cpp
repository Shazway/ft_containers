#include <iostream>
#include <string>
#include <deque>
#include <stdlib.h>


#include "../hdrs/vector_utils.hpp"
#include "../hdrs/map_utils.hpp"
#include "../hdrs/stack_utils.hpp"


#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename StackType>
class MutantStack : public StackType
{
public:

	typedef typename StackType::value_type	T;

	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs)
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename StackType::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};



TEST_CASE("42 benchmarck", "[!hide][42][benchmark]") {
	srand(SEED);

	SECTION("your implementation") {
		std::cout << BOLDBLUE << "\n\n*** 42 main test using ft namespace ***" << RESET << std::endl;

		ft::vector<std::string> vector_str;
		ft::vector<int> vector_int;
		ft::stack<int> stack_int;
		ft::vector<Buffer> vector_buffer;
		ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
		ft::map<int, int> map_int;

		for (int i = 0; i < COUNT; i++)
		{
			vector_buffer.push_back(Buffer());
		}

		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer[idx].idx = 5;
		}
		ft::vector<Buffer>().swap(vector_buffer);

		try
		{
			for (int i = 0; i < COUNT; i++)
			{
				const int idx = rand() % COUNT;
				vector_buffer.at(idx);
				std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
			}
		}
		catch(const std::exception& e)
		{
			//NORMAL ! :P
		}

		for (int i = 0; i < COUNT; ++i)
		{
			map_int.insert(ft::make_pair(rand(), rand()));
		}

		int sum = 0;
		for (int i = 0; i < 10000; i++)
		{
			int access = rand();
			sum += map_int[access];
		}
		std::cout << "should be constant with the same seed: " << sum << std::endl;

		{
			ft::map<int, int> copy = map_int;
		}
		MutantStack<ft::stack<char> > iterable_stack;
		for (char letter = 'a'; letter <= 'z'; letter++)
			iterable_stack.push(letter);
		for (MutantStack<ft::stack<char> >::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
		{
			std::cout << *it;
		}
		std::cout << std::endl;
	}

	SECTION("std implementation") {
		std::cout << BOLDGREEN << "\n*** 42 main test using std namespace ***" << RESET << std::endl;

		std::vector<std::string> vector_str;
		std::vector<int> vector_int;
		std::stack<int> stack_int;
		std::vector<Buffer> vector_buffer;
		std::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
		std::map<int, int> map_int;

		for (int i = 0; i < COUNT; i++)
		{
			vector_buffer.push_back(Buffer());
		}

		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer[idx].idx = 5;
		}
		std::vector<Buffer>().swap(vector_buffer);

		try
		{
			for (int i = 0; i < COUNT; i++)
			{
				const int idx = rand() % COUNT;
				vector_buffer.at(idx);
				std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
			}
		}
		catch(const std::exception& e)
		{
			//NORMAL ! :P
		}

		for (int i = 0; i < COUNT; ++i)
		{
			map_int.insert(std::make_pair(rand(), rand()));
		}

		int sum = 0;
		for (int i = 0; i < 10000; i++)
		{
			int access = rand();
			sum += map_int[access];
		}
		std::cout << "should be constant with the same seed: " << sum << std::endl;

		{
			std::map<int, int> copy = map_int;
		}
		MutantStack<std::stack<char> > iterable_stack;
		for (char letter = 'a'; letter <= 'z'; letter++)
			iterable_stack.push(letter);
		for (MutantStack<std::stack<char> >::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
		{
			std::cout << *it;
		}
		std::cout << std::endl;
	}
}
