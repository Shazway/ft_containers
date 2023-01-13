/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:31:23 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/13 03:38:13 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector.hpp>
#include "vector.hpp"
#include "stack.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"
#include <istream>
#include "map.hpp"
#define LEFT 
typedef typename ft::pair<int, std::string>	value_type;

template<typename T1, typename T2>
std::ostream	&operator<<(std::ostream &os, ft::pair<T1, T2> const& p)
{
	os << "(" << p.first;
	os << ", " << p.second << ")";
	return (os);
}

int		main(void)
{
	ft::map<int, std::string>	map;

	int		a = 1;
	std::string	b = "a";
	ft::pair<int, std::string>	p;

	for (; a < 15; a++, b += "a")
	{
		p.first = a;
		p.second = b;
		map.insert(p);

	}
	map.print_tree();
	while (map.size())
	{
		map.erase(a);
		std::cout << "a is :" << a << std::endl;
		map.print_tree();
		a--;
	}
	//std::cout << map.size() << std::endl;
	return (0);
}