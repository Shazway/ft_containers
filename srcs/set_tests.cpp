/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:44:08 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/18 16:16:10 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

template<typename T, typename Compare, typename Alloc>
std::ostream	&operator<<(std::ostream &os, NAMESPACE::set<T, Compare, Alloc> const& set)
{
	if (set.empty() && PRINT)
		return os << "Set is empty";
	else if(set.empty())

	for (typename NAMESPACE::set<T, Compare, Alloc>::const_iterator it = set.begin(), it1 = ++set.begin();
		it != set.end(); it++)
	{
		os << (*it);
		if (it1 != set.end())
		{
			os << ' ';
			it1++;
		}
	}
	return (os);
}

NAMESPACE::vector<int> generate_set_data(int n = 20, bool use_i = true)
{
	NAMESPACE::vector<int> v;

	std::cout << "Initial data :";
	for (int i = 0; i < n; i++)
	{
		v.push_back(use_i ? i : rand() % 100);
		std::cout << " " << v.back();
	}
	std::cout << std::endl;
	return v;
}

void	set_constructors()
{
	
	std::cout << C_GREEN << "====SET CONSTRUCTORS TESTS====" << C_WHITE << std::endl;
	{
		title("Default constructor");

		NAMESPACE::set<int> m;
		std::cout << "The set : " << m << std::endl;
	}
	{
		title("Range constructor");

		NAMESPACE::vector<int> v = generate_set_data();
		NAMESPACE::set<int> m(v.begin(), v.end());

		std::cout << "The set : " << m << std::endl;
	}
	std::cout << C_GREEN << "====END OF CONSTRUCTORS TESTS====" << C_END << std::endl << std::endl;
}

void	set_comparators()
{
	std::cout << C_GREEN << "====SET COMPARATORS TESTS====" << C_WHITE << std::endl;
	NAMESPACE::vector<int> v = generate_set_data(10, false);

	NAMESPACE::set<int, NAMESPACE::greater<int> > m(v.begin(), v.end());	// should sort in reverse order
	NAMESPACE::set<int> m1(v.begin(), v.end());								// should sort in reverse order

	std::cout << "m (comparator = greater): " << m << std::endl;
	std::cout << "m1 (comparator = less): " << m1 << std::endl;
	std::cout << C_GREEN << "====END OF COMPARATORS TESTS====" << C_END << std::endl << std::endl;
}

void	set_copy()
{
	std::cout << C_GREEN << "====SET COPY TESTS====" << C_WHITE << std::endl;
	{
		title("Test copy constructor");

		NAMESPACE::vector<int> v = generate_set_data(10, false);
		NAMESPACE::set<int> m(v.begin(), v.end());
		NAMESPACE::set<int> m1(m);

		std::cout << "initial m : " << m << std::endl;
		std::cout << "copied m1 : " << m1 << std::endl;
	}
	{
		title("Test operator=");

		NAMESPACE::vector<int> v = generate_set_data(10);
		NAMESPACE::vector<int> v1 = generate_set_data(10, false);

		std::cout << std::endl;
		NAMESPACE::set<int> m(v.begin(), v.end());
		NAMESPACE::set<int> m1(v1.begin(), v1.end());

		std::cout << "m with v : " << m << std::endl;
		std::cout << "m1 with v1 : " << m1 << std::endl
		<< std::endl;
		m1 = m;
		std::cout << "m with v : " << m << std::endl;
		std::cout << "m1 copied (should be same as m): " << m1 << std::endl;
	}
	std::cout << C_GREEN << "====END OF COPY TESTS====" << C_END << std::endl << std::endl;
}
void	set_reverse_iterators()
{
	std::cout << C_GREEN << "====SET REVERSE_ITERATORS TESTS====" << C_WHITE << std::endl;
	typedef NAMESPACE::set<int>::reverse_iterator reverse_iterator;
	typedef NAMESPACE::set<int>::const_reverse_iterator const_reverse_iterator;
	typedef NAMESPACE::set<int>::const_iterator const_iterator;

	NAMESPACE::vector<int> v = generate_set_data(10);
	NAMESPACE::set<int> m(v.begin(), v.end());
	NAMESPACE::set<int> const m1(m);

	{
		title("Testing with non-const set");
		std::cout << "The set (displayed with reverse_iterator):";
		for (reverse_iterator rit = m.rbegin(); rit != m.rend(); rit++)
			std::cout << " " << *rit;
		std::cout << std::endl;
		std::cout << "The set (displayed with const_iterator):";
		for (const_iterator it = m.begin(); it != m.end(); it++)
			std::cout << " " << *it;
		std::cout << std::endl;
		std::cout << "The set (displayed with const_reverse_iterator):";
		for (const_reverse_iterator rit = m.rbegin(); rit != m.rend(); rit++)
			std::cout << " " << *rit;
		std::cout << std::endl;
	}
	{
		title("Testing with const set");
		std::cout << "The set (displayed with const_iterator):";
		for (const_iterator it = m1.begin(); it != m1.end(); it++)
			std::cout << " " << *it;
		std::cout << std::endl;
		std::cout << "The set (displayed with const_reverse_iterator):";
		for (const_reverse_iterator rit = m1.rbegin(); rit != m1.rend(); rit++)
			std::cout << " " << *rit;
		std::cout << std::endl;
	}
	std::cout << C_GREEN << "====END OF REVERSE_ITERATORS TESTS====" << C_END << std::endl << std::endl;
}

void	set_insertion()
{
	std::cout << C_GREEN << "====SET SET_INSERTIONS TESTS====" << C_WHITE << std::endl;
	{
		NAMESPACE::set<std::string> m;

		title("Tests of insert");
		{
			m.insert("bonjour");
			m.insert("yo mec");
			m.insert("bye mec");
			m.insert("roi");
			m.insert("oie");

			std::cout << "The set after adding elements : " << m << std::endl;
		}
		{
			m.insert("hey mec");
			m.insert("king");
			m.insert("goose");
			std::cout << "The set after adding more elements : " << m << std::endl;
		}
	}
	{
		{
			NAMESPACE::vector<int> data = generate_set_data(3, false);
			NAMESPACE::set<int> m;

			data.push_back(data.back());
			data.push_back(data.front());
			data.push_back(1235);

			for (size_t i = 0; i < data.size(); i++)
			{
				NAMESPACE::pair<NAMESPACE::set<int>::iterator, bool> p = m.insert(data[i]);
				std::string res = std::string(" ") + (p.second ? "was" : "was not");

				std::cout << *p.first << res << " inserted" << std::endl;
			}
			std::cout << "Final set : " << m << std::endl;
		}
		{
			NAMESPACE::vector<int> data = generate_set_data(10, false);
			NAMESPACE::set<int> m;

			for (size_t i = 0; i < data.size(); i++)
			{
				NAMESPACE::set<int>::iterator it = m.insert(m.end(), data[i]);

				std::cout << "Returned iterator : " << *it << std::endl;
			}
			std::cout << "Final set : " << m << std::endl;
		}
		{
			title("Tests of insert with range");
			NAMESPACE::vector<int> data = generate_set_data(10, false);
			NAMESPACE::set<int> m;

			m.insert(data.begin(), data.end());
			std::cout << "Final set : " << m << std::endl;
		}
	}
	std::cout << C_GREEN << "====END OF SET_INSERTIONS TESTS====" << C_END << std::endl << std::endl;
}

void set_erase()
{

	std::cout << C_GREEN << "====SET ERASE TESTS====" << C_WHITE << std::endl;
	{
		title("Clearing a set");
		NAMESPACE::vector<int> data = generate_set_data(15);
		NAMESPACE::set<int> m(data.begin(), data.end());

		std::cout << "The set before clear : " << m << std::endl;
		m.clear();
		std::cout << "The set after clear : " << m << std::endl;

		std::cout << "\n\nTrying to reinsert new elements..." << std::endl;

		data = generate_set_data(10, false);
		m.insert(data.begin(), data.end());

		std::cout << "The set before clear : " << m << std::endl;
		m.clear();
		std::cout << "The set after clear : " << m << std::endl;
	}
	{
		title("Tests of erase");
		NAMESPACE::vector<int> data = generate_set_data(15);
		{
			title("Trying to erase a specific iterator");
			NAMESPACE::set<int> m(data.begin(), data.end());

			std::cout << "Initial set : " << m << std::endl;
			std::cout << "Erasing " << *m.begin() << std::endl;
			m.erase(m.begin());
			std::cout << "The set after one erase : " << m << std::endl;
			std::cout << "Erasing " << *++m.begin() << std::endl;
			m.erase(++m.begin());
			std::cout << "The set after two erases : " << m << std::endl;
		}
		{
			title("Trying to erase specific value");
			NAMESPACE::set<int> m(data.begin(), data.end());

			std::cout << "Initial set : " << m << std::endl;
			std::cout << "Erasing " << 12 << std::endl;
			std::cout << "RESULT : " << m.erase(12) << std::endl;
			std::cout << "The set after one erase : " << m << std::endl;
			std::cout << "Erasing " << 23 << std::endl; // Nonexistent key...
			std::cout << "RESULT : " << m.erase(23) << std::endl;
			std::cout << "The set after two erases : " << m << std::endl;
		}
		{
			title("Trying to remove multiple elements at once");
			NAMESPACE::set<int> m(data.begin(), data.end());

			std::cout << "Initial set : " << m << std::endl;
			m.erase(++m.begin(), m.end());
			std::cout << "The set after erasing : " << m << std::endl;
		}
	}
	std::cout << C_GREEN << "====END OF ERASE TESTS====" << C_END << std::endl << std::endl;
}

void set_capacity()
{
	std::cout << C_GREEN << "====SET CAPACITY TESTS====" << C_WHITE << std::endl;
	NAMESPACE::set<int> m;

	std::cout << "max_size : " << m.max_size() << std::endl;
	std::cout << "empty : " << std::boolalpha << m.empty() << std::noboolalpha << std::endl;
	std::cout << "size : " << m.size() << std::endl;

	m.insert(22);
	std::cout << "empty : " << std::boolalpha << m.empty() << std::noboolalpha << std::endl;
	std::cout << "size : " << m.size() << std::endl;

	m.insert(45);
	std::cout << "empty : " << std::boolalpha << m.empty() << std::noboolalpha << std::endl;
	std::cout << "size : " << m.size() << std::endl;
	std::cout << C_GREEN << "====END OF CAPACITY TESTS====" << C_END << std::endl << std::endl;
}

void set_swap()
{
	std::cout << C_GREEN << "====SET SWAP TESTS====" << C_WHITE << std::endl;
	NAMESPACE::set<std::string>::iterator it, it1;
	NAMESPACE::set<std::string> m;

	m.insert("bonjour");
	m.insert("yo mec");
	m.insert("bye mec");
	m.insert("roi");
	m.insert("oie");

	NAMESPACE::set<std::string> m1;
	m1.insert("oppo");
	m1.insert("samsung");

	it = m.begin();
	it1 = m1.begin();

	std::cout << "Iterators : it -> " << *it << ", it1 -> " << *it1 << std::endl;

	std::cout << "The first set : " << m << std::endl;
	std::cout << "The second set : " << m1 << std::endl;
	m.swap(m1);
	std::cout << "The first set : " << m << std::endl;
	std::cout << "The second set : " << m1 << std::endl;

	std::cout << "Iterators : it -> " << *it << ", it1 -> " << *it1 << std::endl; // should not segfault nor swap

	swap(m, m1);
	std::cout << "The first set : " << m << std::endl;
	std::cout << "The second set : " << m1 << std::endl;

	std::cout << "Iterators : it -> " << *it << ", it1 -> " << *it1 << std::endl; // same as before
	std::cout << C_GREEN << "====END OF SWAP TESTS====" << C_END << std::endl << std::endl;
}

void set_operation()
{
	std::cout << C_GREEN << "====SET OPERATORS TESTS====" << C_WHITE << std::endl;
	typedef NAMESPACE::set<int>::iterator iterator;

	NAMESPACE::vector<int> data = generate_set_data(20);
	NAMESPACE::set<int> m(data.begin(), data.end());

	{
		title("Testing find");

		std::cout << "Trying to find an existing element" << std::endl;
		iterator it = m.find(12); //existing element
		if (it == m.end())
			std::cout << "Element not found" << std::endl;
		else
			std::cout << "Element found : " << *it << std::endl;

		std::cout << "Trying to find a nonexistent element" << std::endl;
		it = m.find(112); //nonexistent element
		if (it == m.end())
			std::cout << "Element not found" << std::endl;
		else
			std::cout << "Element found : " << *it << std::endl;
	}
	{
		title("Testing count");

		std::cout	<< "There is " << m.count(12) << " elements with 12 as their key."
					<< std::endl; //existing element
		std::cout	<< "There is " << m.count(1212) << " elements with 1212 as their key."
					<< std::endl; //nonexistent element
	}
	{
		title("Testing upper_bound and lower_bound");
		iterator u, l;

		std::cout << "Upper and lower bound of existing element :" << std::endl;
		u = m.upper_bound(10);
		l = m.lower_bound(10);
		std::cout << "Upper bound : " << *u << ", lower bound : " << *l << std::endl;

		std::cout << "Upper and lower bound of nonexistent element :" << std::endl;
		u = m.upper_bound(-10);
		l = m.lower_bound(-10);
		std::cout << "Upper bound : " << *u << ", lower bound : " << *l << std::endl;

		std::cout << "Upper and lower bound of erased element :" << std::endl;
		m.erase(10);
		u = m.upper_bound(10);
		l = m.lower_bound(10);
		std::cout << "Upper bound : " << *u << ", lower bound : " << *l << std::endl;
	}
	{
		title("Testing equal_range");
		NAMESPACE::pair<iterator, iterator> ul;

		std::cout << "Upper and lower bound of existing element :" << std::endl;
		ul = m.equal_range(11);
		std::cout << "Upper bound : " << *ul.first << ", lower bound : " << *ul.second << std::endl;

		std::cout << "Upper and lower bound of nonexistent element :" << std::endl;
		ul = m.equal_range(-10);
		std::cout << "Upper bound : " << *ul.first << ", lower bound : " << *ul.second << std::endl;

		std::cout << "Upper and lower bound of erased element :" << std::endl;
		m.erase(11);
		ul = m.equal_range(11);
		std::cout << "Upper bound : " << *ul.first << ", lower bound : " << *ul.second << std::endl;
	}
	std::cout << C_GREEN << "====END OF OPERATORS TESTS====" << C_END << std::endl << std::endl;
}


void set_relational_operators()
{
	std::cout << C_GREEN << "====SET OPERATORS TESTS====" << C_WHITE << std::endl;
	NAMESPACE::set<int> m, m1, m2;

	m.insert(12);
	m.insert(2);
	m.insert(-12);

	m1.insert(2);
	m1.insert(546);
	m1.insert(54);

	m2 = m;

	std::cout << "Displaying m : " << m << std::endl;
	std::cout << "Displaying m1 : " << m1 << std::endl;
	std::cout << "Displaying m2 : " << m2 << std::endl;

	std::cout << std::boolalpha;
	std::cout << "m == m1 = " << (m == m1) << std::endl;
	std::cout << "m != m1 = " << (m != m1) << std::endl;
	std::cout << "m < m1 = " << (m < m1) << std::endl;
	std::cout << "m <= m1 = " << (m <= m1) << std::endl;
	std::cout << "m > m1 = " << (m > m1) << std::endl;
	std::cout << "m >= m1 = " << (m >= m1) << std::endl << std::endl;

	std::cout << "m == m2 = " << (m == m2) << std::endl;
	std::cout << "m != m2 = " << (m != m2) << std::endl;
	std::cout << "m < m2 = " << (m < m2) << std::endl;
	std::cout << "m <= m2 = " << (m <= m2) << std::endl;
	std::cout << "m > m2 = " << (m > m2) << std::endl;
	std::cout << "m >= m2 = " << (m >= m2) << std::endl;
	std::cout << std::noboolalpha;
	std::cout << C_GREEN << "====END OF OPERATORS TESTS====" << C_END << std::endl << std::endl;
}

void	set_tests()
{
	set_constructors();
	set_comparators();
	set_copy();
	set_reverse_iterators();
	set_insertion();
	set_erase();
	set_capacity();
	set_swap();
	set_operation();
	set_relational_operators();
	return ;
}