/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 02:33:49 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/17 03:15:23 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"
#include "Colors.hpp"

#define PRINT 1

void	print_separator()
{
	std::cout << C_WHITE << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << C_END << std::endl;
}

template<typename T1, typename T2>
std::ostream	&operator<<(std::ostream &os, NAMESPACE::pair<T1, T2> const& p)
{
	os << "[" << p.first << ", " << p.second << "]";
	return (os);
}

template<typename Key, typename T, typename Compare, typename Alloc>
static	std::ostream	&operator<<(std::ostream &os, NAMESPACE::map<Key, T, Compare, Alloc> const& map)
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

NAMESPACE::vector<NAMESPACE::pair<int, int> > generate_data(int n = 20, bool use_i = true)
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
	{
		std::cout << C_CYAN << "Testing classic map construct" << C_END << std::endl;
		NAMESPACE::map<int, int> m;
		std::cout << "Map content: \n" << m << std::endl; // should be empty
		print_separator();
	}

	{
		NAMESPACE::vector<NAMESPACE::pair<int, int> > v = generate_data();
		NAMESPACE::map<int, int> m(v.begin(), v.end());
		std::cout << "Map content: \n" << m << std::endl; // should be same content as the vec
	}
}

void map_comparators()
{
	NAMESPACE::vector<NAMESPACE::pair<int, int> > v = generate_data(10, false);

	NAMESPACE::map<int, int, NAMESPACE::greater<int> > m(v.begin(), v.end());	// should sort in reverse order
	NAMESPACE::map<int, int> m1(v.begin(), v.end());							// should sort in reverse order

	std::cout << "m (comparator = greater): " << m << std::endl;
	std::cout << "m1 (comparator = less): " << m1 << std::endl;
}

void map_copy()
{
	{
		NAMESPACE::vector<NAMESPACE::pair<int, int> > v = generate_data(10, false);
		NAMESPACE::map<int, int> m(v.begin(), v.end());
		NAMESPACE::map<int, int> m1(m);

		std::cout << "initial m : " << m << std::endl;
		std::cout << "copied m1 : " << m1 << std::endl;
		std::cout << std::endl;
	}

	{
		NAMESPACE::vector<NAMESPACE::pair<int, int> > v = generate_data(10);
		NAMESPACE::vector<NAMESPACE::pair<int, int> > v1 = generate_data(10, false);
		NAMESPACE::map<int, int> m(v.begin(), v.end());
		NAMESPACE::map<int, int> m1(v1.begin(), v1.end());

		std::cout << "m with v : " << m << std::endl;
		std::cout << "m1 with v1 : " << m1 << std::endl << std::endl;
		m1 = m;
		std::cout << "m with v : " << m << std::endl;
		std::cout << "m1 copied (should be same as m): " << m1 << std::endl;
	}
}

void map_reverse_iterators()
{
	typedef NAMESPACE::map<int, int>::reverse_iterator reverse_iterator;
	typedef NAMESPACE::map<int, int>::const_reverse_iterator const_reverse_iterator;
	typedef NAMESPACE::map<int, int>::const_iterator const_iterator;

	NAMESPACE::vector<NAMESPACE::pair<int, int> > v = generate_data(10);
	NAMESPACE::map<int, int> m(v.begin(), v.end());
	NAMESPACE::map<int, int> const m1(m);

	{
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
		std::cout << "The map (displayed with const_iterator):";
		for (const_iterator it = m1.begin(); it != m1.end(); it++)
			std::cout << " " << *it;
		std::cout << std::endl;
		std::cout << "The map (displayed with const_reverse_iterator):";
		for (const_reverse_iterator rit = m1.rbegin(); rit != m1.rend(); rit++)
			std::cout << " " << *rit;
		std::cout << std::endl;
	}
}

void	map_tests()
{
	map_constructors();
	//map_comparators();
	//map_copy();
	//map_reverse_iterators();
	return ;
}