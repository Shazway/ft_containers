/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 02:33:49 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/18 16:15:58 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

template<typename T1, typename T2>
std::ostream	&operator<<(std::ostream &os, NAMESPACE::pair<T1, T2> const& p)
{
	os << "[" << p.first << ", " << p.second << "]";
	return (os);
}

template<typename Key, typename T, typename Compare, typename Alloc>
std::ostream	&operator<<(std::ostream &os, NAMESPACE::map<Key, T, Compare, Alloc> const& map)
{
	if (map.empty() && PRINT)
		return (os << "Empty map");
	else if(map.empty())
		return (os);

	for (typename NAMESPACE::map<Key, T, Compare, Alloc>::const_iterator it = map.begin(), it1 = ++map.begin();
		it != map.end(); it++)
	{
		os << *(it);
		if (it1 != map.end())
		{
			os << " ";
			it1++;
		}
	}
	return (os);
}

NAMESPACE::vector<NAMESPACE::pair<int, int> > generate_map_data(int n = 20, bool use_i = true)
{
	NAMESPACE::vector<NAMESPACE::pair<int, int> > v;

	std::cout << "Initial data :";
	for (int i = 0; i < n; i++)
	{
		v.push_back(NAMESPACE::make_pair(use_i ? i : rand() % 100, rand() % 100));
		std::cout << " " << v.back();
	}
	std::cout << std::endl;
	return v;
}

void	map_constructors()
{
		std::cout << C_GREEN << "====MAP CONSTRUCTORS TESTS====" << C_WHITE << std::endl;
	{
		title("Default constructor");
		NAMESPACE::map<int, int> m;
		std::cout << "Map content: \n" << m << std::endl; // should be empty
	}

	{
		title("Range constructor");
		NAMESPACE::vector<NAMESPACE::pair<int, int> > v = generate_map_data();
		NAMESPACE::map<int, int> m(v.begin(), v.end());
		std::cout << "Map content: \n" << m << std::endl; // should be same content as the vec
	}
		std::cout << C_GREEN << "====END OF CONSTRUCTORS TESTS====" << C_END << std::endl << std::endl;
}

void map_comparators()
{
	std::cout << C_GREEN << "====MAP COMPARATOR TESTS====" << C_END << std::endl << std::endl;
	NAMESPACE::vector<NAMESPACE::pair<int, int> > v = generate_map_data(10, false);

	NAMESPACE::map<int, int, NAMESPACE::greater<int> > m(v.begin(), v.end());	// should sort in reverse order
	NAMESPACE::map<int, int> m1(v.begin(), v.end());							// should sort in reverse order

	std::cout << "m (comparator = greater): " << m << std::endl;
	std::cout << "m1 (comparator = less): " << m1 << std::endl;
	std::cout << C_GREEN << "====END OF COMPARATOR TESTS====" << C_END << std::endl << std::endl;
}

void map_copy()
{
	std::cout << C_GREEN << "====MAP COPY TESTS====" << C_WHITE << std::endl;
	{
		title("Test copy constructor");
		NAMESPACE::vector<NAMESPACE::pair<int, int> > v = generate_map_data(10, false);
		NAMESPACE::map<int, int> m(v.begin(), v.end());
		NAMESPACE::map<int, int> m1(m);

		std::cout << "initial m : " << m << std::endl;
		std::cout << "copied m1 : " << m1 << std::endl;
		std::cout << std::endl;
	}

	{
		title("Test operator=");
		NAMESPACE::vector<NAMESPACE::pair<int, int> > v = generate_map_data(10);
		NAMESPACE::vector<NAMESPACE::pair<int, int> > v1 = generate_map_data(10, false);
		NAMESPACE::map<int, int> m(v.begin(), v.end());
		NAMESPACE::map<int, int> m1(v1.begin(), v1.end());

		std::cout << "m with v : " << m << std::endl;
		std::cout << "m1 with v1 : " << m1 << std::endl << std::endl;
		m1 = m;
		std::cout << "m with v : " << m << std::endl;
		std::cout << "m1 copied (should be same as m): " << m1 << std::endl;
	}
	std::cout << C_GREEN << "====END OF COPY TESTS====" << C_END << std::endl << std::endl;
}

void map_reverse_iterators()
{
	std::cout << C_GREEN << "====MAP REVERSE_IT TESTS====" << C_WHITE << std::endl;
	typedef NAMESPACE::map<int, int>::reverse_iterator reverse_iterator;
	typedef NAMESPACE::map<int, int>::const_reverse_iterator const_reverse_iterator;
	typedef NAMESPACE::map<int, int>::const_iterator const_iterator;

	NAMESPACE::vector<NAMESPACE::pair<int, int> > v = generate_map_data(10);
	NAMESPACE::map<int, int> m(v.begin(), v.end());
	NAMESPACE::map<int, int> const m1(m);

	{
		title("Testing with non-const map");
	
		std::cout << "The map (displayed with reverse_iterator):";
		for (reverse_iterator rit = m.rbegin(); rit != m.rend(); rit++)
			std::cout << " " << *rit;
		std::cout << std::endl;
		std::cout << "The map (displayed with const_iterator):";
		for (const_iterator it = m.begin(); it != m.end(); it++)
			std::cout << " " << *it;
		std::cout << std::endl;
		std::cout << "The map (displayed with const_reverse_iterator):";
		for (const_reverse_iterator rit = m.rbegin(); rit != m.rend(); rit++)
			std::cout << " " << *rit;
		std::cout << std::endl;
	}
	{
		title("Testing with const map");

		std::cout << "The map (displayed with const_iterator):";
		for (const_iterator it = m1.begin(); it != m1.end(); it++)
			std::cout << " " << *it;
		std::cout << std::endl;
		std::cout << "The map (displayed with const_reverse_iterator):";
		for (const_reverse_iterator rit = m1.rbegin(); rit != m1.rend(); rit++)
			std::cout << " " << *rit;
		std::cout << std::endl;
	}
	std::cout << C_GREEN << "====END OF REVERSE_IT TESTS====" << C_END << std::endl << std::endl;
}

void map_inserts()
{
	std::cout << C_GREEN << "====MAP INSERT TESTS====" << C_WHITE << std::endl;
	{
		title("Test of operator[]");

		NAMESPACE::map<int, std::string> m;
		int random_key = rand() % 10 + 100;

		m[0] = "bonjour";
		m[1] = "yo mec";
		m[20000] = "bye mec";
		m[-213213] = "roi";
		m[random_key] = "oie"; // should be inserted between 1 and 20000

		std::cout << "The map after adding elements : " << m << std::endl;
		m[20000] = "hey mec";
		m[-213213] = "king";
		m[random_key] = "goose";

		std::cout << "The map after editing some elements : " << m << std::endl;
	}
	{
		title("Tests of insert");
		{
			title("Tests of insert with a value (inserting pairs of int)");
			NAMESPACE::vector<NAMESPACE::pair<int, int> > data = generate_map_data(3, false);
			NAMESPACE::map<int, int> m;

			data.push_back(data.back());
			data.push_back(data.front());
			data.push_back(NAMESPACE::make_pair(-12, 1212));

			for (size_t i = 0; i < data.size(); i++)
			{
				NAMESPACE::pair<NAMESPACE::map<int, int>::iterator, bool> p = m.insert(data[i]);
				std::string res = std::string(" ") + (p.second ? "was" : "was not");

				std::cout << *p.first << res << " inserted" << std::endl;
			}
			std::cout << "Final map : " << m << std::endl;
		}
		{
			title("Tests of insert with hint");
			NAMESPACE::vector<NAMESPACE::pair<int, int> > data = generate_map_data(10, false);
			NAMESPACE::map<int, int> m;

			for (size_t i = 0; i < data.size(); i++)
			{
				NAMESPACE::map<int, int>::iterator it = m.insert(m.end(), data[i]);

				std::cout << "Returned iterator : " << *it << std::endl;
			}
			std::cout << "Final map : " << m << std::endl;
		}
		{
			title("Tests of insert with range");

			NAMESPACE::vector<NAMESPACE::pair<int, int> > data = generate_map_data(10, false);
			NAMESPACE::map<int, int> m;

			m.insert(data.begin(), data.end());
			std::cout << "Final map : " << m << std::endl;
		}
	}
	std::cout << C_GREEN << "====END OF INSERT TESTS====" << C_END << std::endl << std::endl;
}

void map_erase()
{
	std::cout << C_GREEN << "====MAP ERASE TESTS====" << C_WHITE << std::endl;
	
	{
		title("Clearing a map");
		NAMESPACE::vector<NAMESPACE::pair<int, int> > data = generate_map_data(15);
		NAMESPACE::map<int, int> m(data.begin(), data.end());

		std::cout << "The map before clear : " << m << std::endl;
		m.clear();
		std::cout << "The map after clear : " << m << std::endl;

		std::cout << "\n\nTrying to reinsert new elements..." << std::endl;

		data = generate_map_data(10, false);
		m.insert(data.begin(), data.end());

		std::cout << "The map before clear : " << m << std::endl;
		m.clear();
		std::cout << "The map after clear : " << m << std::endl;
	}
	{
		title("Tests of erase");
		NAMESPACE::vector<NAMESPACE::pair<int, int> > data = generate_map_data(15);

		{

			NAMESPACE::map<int, int> m(data.begin(), data.end());

			std::cout << "Initial map : " << m << std::endl;
			std::cout << "Erasing " << *m.begin() << std::endl;
			m.erase(m.begin());
			std::cout << "The map after one erase : " << m << std::endl;
			std::cout << "Erasing " << *++m.begin() << std::endl;
			m.erase(++m.begin());
			std::cout << "The map after two erases : " << m << std::endl;
		}
		{
			title("Trying to erase specific value");
			NAMESPACE::map<int, int> m(data.begin(), data.end()); // Keys are from 0 to 14 inclusive

			std::cout << "Initial map : " << m << std::endl;
			std::cout << "Erasing " << 12 << std::endl;
			std::cout << "RESULT : " << m.erase(12) << std::endl;
			std::cout << "The map after one erase : " << m << std::endl;
			std::cout << "Erasing " << 23 << std::endl; // Nonexistent key...
			std::cout << "RESULT : " << m.erase(23) << std::endl;
			std::cout << "The map after two erases : " << m << std::endl; // should be same as before
		}
		{
			title("Trying to remove multiple elements at once");
			NAMESPACE::map<int, int> m(data.begin(), data.end());

			std::cout << "Initial map : " << m << std::endl;
			m.erase(++m.begin(), m.end()); // To keep erase from calling clear (already tested)
			std::cout << "The map after erasing : " << m << std::endl;
		}
	}
	std::cout << C_GREEN << "====END OF ERASE TESTS====" << C_END << std::endl << std::endl;
}

void map_capacity()
{
	std::cout << C_GREEN << "====MAP CAPACITY TESTS====" << C_WHITE << std::endl;
	NAMESPACE::map<int, int> m;

	std::cout << "max_size : " << m.max_size() << std::endl;
	std::cout << "empty : " << std::boolalpha << m.empty() << std::noboolalpha << std::endl;
	std::cout << "size : " << m.size() << std::endl;

	m[0] = 123124;
	std::cout << "empty : " << std::boolalpha << m.empty() << std::noboolalpha << std::endl;
	std::cout << "size : " << m.size() << std::endl;

	m[0] = 232;
	std::cout << "empty : " << std::boolalpha << m.empty() << std::noboolalpha << std::endl;
	std::cout << "size : " << m.size() << std::endl;

	m[12] = 232;
	std::cout << "empty : " << std::boolalpha << m.empty() << std::noboolalpha << std::endl;
	std::cout << "size : " << m.size() << std::endl;
	std::cout << C_GREEN << "====END OF CAPACITY TESTS====" << C_END << std::endl << std::endl;
}

void map_swap()
{
	std::cout << C_GREEN << "====MAP SWAP TESTS====" << C_WHITE << std::endl;
	NAMESPACE::map<int, std::string>::iterator it, it1;

	NAMESPACE::map<int, std::string> m;

	m[0] = "bonjour";
	m[1] = "yo mec";
	m[20000] = "bye mec";
	m[-213213] = "roi";
	m[212] = "oie";

	NAMESPACE::map<int, std::string> m1;
	m1[1243] = "oppo";
	m1[1324] = "samsung";

	it = m.begin();
	it1 = m1.begin();

	std::cout << "Iterators : it -> " << *it << ", it1 -> " << *it1 << std::endl;

	std::cout << "The first map : " << m << std::endl;
	std::cout << "The second map : " << m1 << std::endl;
	m.swap(m1);
	std::cout << "The first map : " << m << std::endl;
	std::cout << "The second map : " << m1 << std::endl;

	std::cout << "Iterators : it -> " << *it << ", it1 -> " << *it1 << std::endl; // should not segfault nor swap

	swap(m, m1);
	std::cout << "The first map : " << m << std::endl;
	std::cout << "The second map : " << m1 << std::endl;

	std::cout << "Iterators : it -> " << *it << ", it1 -> " << *it1 << std::endl; // same as before
	std::cout << C_GREEN << "====END OF SWAP TESTS====" << C_END << std::endl << std::endl;
}

void map_operators()
{
	std::cout << C_GREEN << "====MAP OPERATORS TESTS====" << C_WHITE << std::endl;
	typedef NAMESPACE::map<int, int>::iterator iterator;

	NAMESPACE::vector<NAMESPACE::pair<int, int> > data = generate_map_data(20);
	NAMESPACE::map<int, int> m(data.begin(), data.end());

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

void map_relational_operators()
{
	std::cout << C_GREEN << "====MAP RELATIONAL_OPERATORS TESTS====" << C_WHITE << std::endl;

	NAMESPACE::map<int, int> m, m1, m2;

	m[0] = 121;
	m[-12] = 1;
	m[20] = 0;

	m1[1] = 121;
	m1[-12] = 2;
	m1[12] = 0;

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
	std::cout << C_GREEN << "====END OF RELATIONAL_OPERATORS TESTS====" << C_END << std::endl << std::endl;
}

void	map_tests()
{
	map_constructors();
	map_comparators();
	map_copy();
	map_reverse_iterators();
	map_inserts();
	map_erase();
	map_capacity();
	map_swap();
	map_operators();
	map_relational_operators();
	return ;
}