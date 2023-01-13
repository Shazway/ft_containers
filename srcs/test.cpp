/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:31:23 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/13 04:29:27 by tmoragli         ###   ########.fr       */
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
	ft::map<int, std::string>	map2;

	int		a = 1;
	std::string	b = "a";
	ft::pair<int, std::string>	p;

	p.first = a;
	p.second = b;
	map2 = map;
	map.insert(p);
	map.at(5);
	map.begin();
	map.rbegin();
	map.end();
	map.rend();
	map.empty();
	map.swap(map2);
	map.count(1);
	map.key_comp();
	map.value_comp();
	return (0);
}