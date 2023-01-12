/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:31:23 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/12 19:38:38 by tmoragli         ###   ########.fr       */
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
	os << "(" << p.first << ", " << p.second << ")";
	return (os);
}

int		main(void)
{
	ft::map<int, std::string>	map;

	int		a = 1;
	std::string	b = "a";

	for (; a < 15; a++, b += "a")
		map.insert(ft::make_pair(a, b));
	map.print_tree();
	while (map.size())
	{
		map.erase(a);
		a--;
	}
	map.print_tree();
	return (0);
}