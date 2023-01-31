/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 00:16:44 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/19 01:22:03 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

template <typename T>
std::ostream &operator<<(std::ostream &os, NAMESPACE::vector<T> const& x)
{
	if (x.empty() && PRINT)
		return os << "is empty";
	else if (x.empty())
		return os;
	for (typename NAMESPACE::vector<T>::const_iterator it = x.begin(), it1 = ++x.begin(); it != x.end(); ++it)
	{
		os << *it;
		if (it1 != x.end())
		{
			os << " ";
			it1++;
		}
	}
	return os;
}

void vector_constructors()
{
	std::cout << C_GREEN << "====VECTOR CONSTRUCTORS TESTS====" << C_WHITE << std::endl;
	{
		title("Default constructor");
		NAMESPACE::vector<int> v;
		std::cout << "The vector : " << v << std::endl;
	}
	{
		title("Fill constructor (with default value)");
		NAMESPACE::vector<int>::size_type size = 5;
		NAMESPACE::vector<int> v(size);
		std::cout << "The vector (should contain " << size << " element(s)) : " << v << std::endl;
	}
	{
		title("Fill constructor (with given value)");
		NAMESPACE::vector<int>::size_type size = 5;
		int value = 55;
		NAMESPACE::vector<int> v(size, value);
		std::cout << "The vector (should contain " << size << " " << value << ") : " << v << std::endl;
	}
	{
		title("Range constructor");
		NAMESPACE::vector<int>::size_type size = 10;
		NAMESPACE::vector<int> v(size, 25);
		NAMESPACE::vector<int> vt(v.begin(), v.end());

		std::cout << "The vector constructed by fill constructor  : " << v << std::endl;
		std::cout << "The vector constructed by range constructor : " << vt << std::endl;
	}
	std::cout << C_GREEN << "====END OF CONSTRUCTORS TESTS====" << C_WHITE << std::endl << std::endl;
}

void vector_copy()
{
	std::cout << C_GREEN << "====VECTOR COPY TESTS====" << C_WHITE << std::endl;
	NAMESPACE::vector<std::string> v(5, "bonjour");
	NAMESPACE::vector<std::string> v1;
	v1 = v;
	std::cout << "The vector constructed by fill constructor	: " << v << std::endl;
	std::cout << "The vector after the copy						: " << v1 << std::endl;
	std::cout << C_GREEN << "====END OF COPY TESTS====" << C_WHITE << std::endl << std::endl;
}

void vector_capacity()
{
	std::cout << C_GREEN << "====VECTOR CAPACITY TESTS====" << C_WHITE << std::endl;

	{
		title("Is the vector empty ?");
		NAMESPACE::vector<int> v;
		std::cout << "The vector (" << v << ") is " << (v.empty() ? "empty" : "not empty") << std::endl;
		NAMESPACE::vector<int> v1(5, 10);
		std::cout << "The vector (" << v1 << ") is " << (v1.empty() ? "empty" : "not empty") << std::endl;
	}
	{
		title("The size of the vector");
		NAMESPACE::vector<int> l;
		std::cout << "The vector (" << l << ") has " << l.size() << " element(s)" << std::endl;
		NAMESPACE::vector<int> l1(5, 10);
		std::cout << "The vector (" << l1 << ") has " << l1.size() << " element(s)" << std::endl;
		NAMESPACE::vector<int> l2(1, 100);
		std::cout << "The vector (" << l2 << ") has " << l2.size() << " element(s)" << std::endl;
	}
	{
		title("The capacity of the vector");
		NAMESPACE::vector<int> v;
		NAMESPACE::vector<int>::size_type oldCapacity = -1;
		for (int i = 0; i < 1000; i++)
		{
			if (oldCapacity != v.capacity())
				std::cout	<< "Size : " << v.size() << ", "
							<< "Capacity : " << (oldCapacity = v.capacity()) << std::endl;
			v.push_back(i);
		}
	}
	{
		title("The maximum size of a vector is :");
		std::cout << "max_size : " << NAMESPACE::vector<int>().max_size() << std::endl;
	}
	std::cout << C_GREEN << "====END OF CAPACITY TESTS====" << C_WHITE << std::endl << std::endl;
}

void vector_relational()
{
	std::cout << C_GREEN << "====VECTOR RELATIONAL_OPERATORS TESTS====" << C_WHITE << std::endl;
	NAMESPACE::vector<int> a;
	NAMESPACE::vector<int> b;
	NAMESPACE::vector<int> c;

	a.push_back(10);
	a.push_back(20);
	a.push_back(30);

	b.push_back(10);
	b.push_back(20);
	b.push_back(30);

	c.push_back(30);
	c.push_back(20);
	c.push_back(10);

	if (a == b)
		std::cout << "a and b are equal\n";
	if (b != c)
		std::cout << "b and c are not equal\n";
	if (b < c)
		std::cout << "b is less than c\n";
	if (c > b)
		std::cout << "c is greater than b\n";
	if (a <= b)
		std::cout << "a is less than or equal to b\n";
	if (a >= b)
		std::cout << "a is greater than or equal to b\n";
	std::cout << C_GREEN << "====END OF RELATIONAL_OPERATORS TESTS====" << C_WHITE << std::endl << std::endl;
}

void vector_swap_non_member()
{
	std::cout << C_GREEN << "====VECTOR NON_MEMBER_SWAP TESTS====" << C_WHITE << std::endl;
	NAMESPACE::vector<int> foo(3, 100); // three ints with a value of 100
	NAMESPACE::vector<int> bar(5, 200); // five ints with a value of 200

	title("Before swapping :");
	std::cout << "foo contains: " << foo << std::endl;
	std::cout << "bar contains: " << bar << std::endl;

	NAMESPACE::swap(foo, bar);

	title("After swapping :");
	std::cout << "foo contains: " << foo << std::endl;
	std::cout << "bar contains: " << bar << std::endl;
	std::cout << C_GREEN << "====END OF NON_MEMBER_SWAP TESTS====" << C_WHITE << std::endl << std::endl;
}

void vector_swap()
{
	std::cout << C_GREEN << "====VECTOR MEMBER_SWAP TESTS====" << C_WHITE << std::endl;
	NAMESPACE::vector<int> foo(3, 100); // three ints with a value of 100
	NAMESPACE::vector<int> bar(5, 200); // five ints with a value of 200

	title("Before swapping :");
	std::cout << "foo contains: " << foo << std::endl;
	std::cout << "bar contains: " << bar << std::endl;

	foo.swap(bar);

	title("After swapping :");
	std::cout << "foo contains: " << foo << std::endl;
	std::cout << "bar contains: " << bar << std::endl;
	std::cout << C_GREEN << "====END OF MEMBER_SWAP TESTS====" << C_WHITE << std::endl << std::endl;
}

void vector_modifiers_insertions()
{
	std::cout << C_GREEN << "====VECTOR INSERTIONS_MODIFIERS TESTS====" << C_WHITE << std::endl;
	{
		title("Testing push_back");
		NAMESPACE::vector<int> v;
		for (int i = 0; i <= 5; i++)
		{
			std::cout << "The vector :\t\t" << v << std::endl;
			v.push_back(i);
		}
		std::cout << "The final vector :\t" << v << std::endl;
	}
	{
		title("Testing insert");
		{
			title("Inserting a single element");
			NAMESPACE::vector<int> v(5, 10);
			std::cout << "The vector before the insertion : " << v << std::endl;
			NAMESPACE::vector<int>::iterator it = v.begin() + (v.end() - v.begin() - 1);
			NAMESPACE::vector<int>::iterator res = v.insert(it, 111);
			std::cout << "The vector after the insertion : " << v << std::endl;
			std::cout << "iterator returned : " << *res << std::endl;
			res = v.insert(v.begin(), 222);
			std::cout << "The vector after the insertion : " << v << std::endl;
			std::cout << "iterator returned = " << *res << std::endl;
			res = v.insert(v.end(), 5784);
			std::cout << "The vector after the insertion : " << v << std::endl;
			std::cout << "iterator returned = " << *res << std::endl;
		}
		{
			title("Inserting new elements");
			NAMESPACE::vector<int> v(5, 10);
			std::cout << "The vector before the insertion : " << v << std::endl;
			NAMESPACE::vector<int>::iterator it = v.begin();
			for (NAMESPACE::vector<int>::size_type i = 0; i < v.size() - 1; i++)
				it++;
			v.insert(it, 5, -11);
			std::cout << "The vector after the insertion : " << v << std::endl;
			v.insert(v.begin(), 3, 100);
			std::cout << "The vector after the insertion : " << v << std::endl;
			v.insert(v.end(), 7, 189);
			std::cout << "The vector after the insertion : " << v << std::endl;
		}
		{
			title("Inserting a range of new elements");
			NAMESPACE::vector<int> v;
			v.push_back(1);
			v.push_back(2);
			v.push_back(3);
			NAMESPACE::vector<int> v1(5, 10);
			std::cout << "The vector before the insertion : " << v1 << std::endl;
			v1.insert(v1.end(), v.rbegin(), v.rend());
			std::cout << "The vector after the insertion : " << v1 << std::endl;
		}
	}
	std::cout << C_GREEN << "====END OF INSERTIONS_MODIFIERS TESTS====" << C_WHITE << std::endl << std::endl;
}

void vector_accessors()
{
	std::cout << C_GREEN << "====VECTOR ACCESSORS TESTS====" << C_WHITE << std::endl;
	NAMESPACE::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	const NAMESPACE::vector<int> v1 = v;
	std::cout << "The vector of the test : " << v << std::endl;

	{
		title("Testing front and back");

		{
			title("Accessing the front element");
			std::cout << "Front element : " << v.front() << std::endl;
		}
		{
			title("Accessing the back element");
			std::cout << "Back element : " << v.back() << std::endl;
		}
		{
			title("Modifying the front element");
			v.front() = 3;
			std::cout << "Front element : " << v.front() << std::endl;
		}
		{
			title("Modifying the back element");
			v.back() = 1;
			std::cout << "Back element : " << v.back() << std::endl;
		}
		{
			title("Accessing the front element for const vector");
			std::cout << "Front element : " << v1.front() << std::endl;
		}
		{
			title("Accessing the back element for const vector");
			std::cout << "Back element : " << v1.back() << std::endl;
		}
	}
	std::cout << "The vector after the front/back tests : " << v << std::endl;
	{
		title("Testing operator[] and at");
		{
			title("Testing operator[] with non const vector");
			for (NAMESPACE::vector<int>::size_type i = 0; i < v.size(); i++)
				std::cout << "element " << i << " : " << v[i] << std::endl;
		}
		{
			title("Testing operator[] with const vector");
			for (NAMESPACE::vector<int>::size_type i = 0; i < v1.size(); i++)
				std::cout << "element " << i << " : " << v1[i] << std::endl;
		}
		{
			title("Testing at with non const vector");
			for (NAMESPACE::vector<int>::size_type i = 0; i < v.size(); i++)
				std::cout << "element " << i << " : " << v.at(i) << std::endl;
		}
		{
			title("Testing at with const vector");
			for (NAMESPACE::vector<int>::size_type i = 0; i < v1.size(); i++)
				std::cout << "element " << i << " : " << v1.at(i) << std::endl;
		}
		{
			title("Testing at with wrong pos");
			try
			{
				v.at(4);
			}
			catch (const std::out_of_range &e)
			{
				std::cout << e.what() << std::endl;
			}
			try
			{
				v.at(-1);
			}
			catch (const std::out_of_range &e)
			{
				std::cout << e.what() << std::endl;
			}
		}
	}
	std::cout << "The vector after the operator[]/at tests : " << v << std::endl;
	std::cout << C_GREEN << "====END OF ACCESSORS TESTS====" << C_WHITE << std::endl << std::endl;
}

void vector_reverse_iterators()
{

	std::cout << C_GREEN << "====VECTOR REVERSE_ITERATORS TESTS====" << C_WHITE << std::endl;
	NAMESPACE::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	NAMESPACE::vector<int>::const_iterator itt = v.begin();
	//for (int)
	(void)itt;

	std::cout << "The vector (displayed with the standard iterator)\t: " << v << std::endl;

	std::cout << "The vector (displayed with the reverse iterator)\t:";
	for (NAMESPACE::vector<int>::reverse_iterator rit = v.rbegin(); rit != v.rend(); rit++)
		std::cout << " " << *rit;
	std::cout << std::endl;
	const NAMESPACE::vector<int> v1(v);
	std::cout << "The vector (displayed with the const iterator)\t\t:";
	for (NAMESPACE::vector<int>::const_iterator it = v1.begin(); it != v1.end(); it++)
		std::cout << " " << *it;
	std::cout << std::endl;
	std::cout << "The vector (displayed with the const reverse iterator)\t:";
	for (NAMESPACE::vector<int>::const_reverse_iterator rit = v1.rbegin(); rit != v1.rend(); rit++)
		std::cout << " " << *rit;
	std::cout << std::endl;
	std::cout << C_GREEN << "====END OF REVERSE_ITERATORS TESTS====" << C_WHITE << std::endl << std::endl;
}

void vector_resize()
{
	std::cout << C_GREEN << "====VECTOR RESIZE TESTS====" << C_WHITE << std::endl;

	{
		title("Shrinking vector");
		NAMESPACE::vector<int> l(10, 22);
		std::cout << "vector before calling resize : " << l << std::endl;
		l.resize(5);
		std::cout << "vector after calling resize :  " << l << std::endl;
	}
	{
		title("Extending vector");
		{
			title("With default value");
			NAMESPACE::vector<int> l(2, 22);
			std::cout << "vector before calling resize : " << l << std::endl;
			l.resize(5);
			std::cout << "vector after calling resize :  " << l << std::endl;
		}
		{
			title("With given value");
			NAMESPACE::vector<int> l(2, 22);
			std::cout << "vector before calling resize : " << l << std::endl;
			l.resize(5, 11);
			std::cout << "vector after calling resize :  " << l << std::endl;
		}
	}
	std::cout << C_GREEN << "====END OF RESIZE TESTS====" << C_WHITE << std::endl << std::endl;
}

void vector_reserve()
{
	std::cout << C_GREEN << "====VECTOR RESERVE TESTS====" << C_WHITE << std::endl;

	NAMESPACE::vector<int> v;
	std::cout << "Capacity before reserve : " << v.capacity() << std::endl;
	std::cout << "Size before reserve : " << v.size() << std::endl;
	v.reserve(10);
	std::cout << "Capacity after reserve : " << v.capacity() << std::endl;
	std::cout << "Size after reserve : " << v.size() << std::endl;

	v.assign(102, 98);

	std::cout << "Capacity before reserve : " << v.capacity() << std::endl;
	std::cout << "Size before reserve : " << v.size() << std::endl;
	v.reserve(98);
	std::cout << "Capacity after reserve : " << v.capacity() << std::endl;
	std::cout << "Size after reserve : " << v.size() << std::endl;

	std::cout << C_GREEN << "====END OF RESERVE TESTS====" << C_WHITE << std::endl << std::endl;
}

void vector_deleting_elements()
{
	std::cout << C_GREEN << "====VECTOR DELETE_ELEMENTS TESTS====" << C_WHITE << std::endl;

	{
		title("Test of pop_back");
		NAMESPACE::vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		std::cout << "The vector before popping everything : " << v << std::endl;
		v.pop_back();
		v.pop_back();
		v.pop_back();
		std::cout << "The vector after popping everything : " << v << std::endl;
		std::cout << "Checking that everything went well by adding new elements to the vector" << std::endl;
		v.push_back(4);
		v.push_back(5);
		v.push_back(6);
		std::cout << "The vector before popping everything : " << v << std::endl;
		v.pop_back();
		std::cout << "The vector after popping one element : " << v << std::endl;
	}
	{
		title("Test of clear");
		NAMESPACE::vector<int> v(10, 5);
		std::cout << "The vector before clearing it : " << v << std::endl;
		v.clear();
		std::cout << "The vector after clearing it : " << v << std::endl;
	}
	{
		title("Tests of erase");
		{
			title("Erasing a single element");
			NAMESPACE::vector<int> v;
			v.push_back(1);
			v.push_back(2);
			v.push_back(3);
			v.push_back(4);
			v.push_back(5);
			v.push_back(6);
			v.push_back(7);
			v.push_back(8);
			v.push_back(9);
			v.push_back(10);
			std::cout << "The vector before erasing anything : " << v << std::endl;

			while (!v.empty())
			{
				NAMESPACE::vector<int>::iterator res = v.erase(v.begin());
				std::cout << "The vector now (element following the erased one : ";
				if (!v.empty())
					std::cout << *res;
				std::cout << ") : " << v << std::endl;
			}
		}
		{
			title("Erasing a range of elements");
			NAMESPACE::vector<int> v;
			v.push_back(1);
			v.push_back(2);
			v.push_back(3);
			v.push_back(4);
			v.push_back(5);
			v.push_back(6);
			v.push_back(7);
			v.push_back(8);
			v.push_back(9);
			v.push_back(10);
			std::cout << "The list before erasing anything : " << v << std::endl;

			NAMESPACE::vector<int>::iterator it = v.begin();
			for (int i = 0; i < 3; i++)
				it++;
			NAMESPACE::vector<int>::iterator it1 = it;
			for (int i = 0; i < 3; i++)
				it1++;
			std::cout << "Range to erase :";
			for (NAMESPACE::vector<int>::iterator i = it; i != it1; i++)
				std::cout << " " << *i;
			std::cout << std::endl;
			v.erase(it, it1);
			std::cout << "The list after erasing : " << v << std::endl;
		}
	}
	std::cout << C_GREEN << "====END OF DELETE_ELEMENTS TESTS====" << C_WHITE << std::endl << std::endl;
}

void	vector_tests()
{
	vector_constructors();
	vector_copy();
	vector_capacity();
	vector_relational();
	vector_swap_non_member();
	vector_swap();
	vector_modifiers_insertions();
	vector_accessors();
	vector_reverse_iterators();
	vector_resize();
	vector_reserve();
	vector_deleting_elements();
}