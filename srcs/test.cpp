/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:31:23 by tmoragli          #+#    #+#             */
/*   Updated: 2022/12/05 18:21:42 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector.hpp>
#include "vector.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"
#include <istream>

typedef std::string	_value;

void	print_separator()
{
	std::cout << WHITE << "~~~~~~~~~~~~~~~~~~" << END << std::endl;
}

void	display_my_v(ft::vector<_value> vec)
{
	for (ft::vector<_value>::iterator i = vec.begin(); i != vec.end(); i++)
		std::cout << GREEN << "[" << (*i) << "]" << END << std::endl;
	if (vec.empty())
		std::cout << YELLOW << "Empty arguments /!\\" << END << std::endl;
}

void	display_std_v(std::vector<_value> vec)
{
	for (std::vector<_value>::iterator i = vec.begin(); i != vec.end(); i++)
		std::cout << GREEN << "[" << (*i) << "]" << END << std::endl;
	if (vec.empty())
		std::cout << YELLOW << "Empty arguments /!\\" << END << std::endl;
}

int main()
{
	std::vector<_value>	v1;
	// ft::vector<_value>::iterator it;
	// ft::vector<_value>::iterator it2;

	v1.push_back("AAAAAAAAAA");
	v1.push_back("BBBBBBBBB");
	v1.push_back("CCCCCCCC");
	v1.push_back("DDDDDDD");
	v1.push_back("EEEEEE");
	v1.push_back("FFFFF");
	v1.push_back("GGGG");
	v1.push_back("HHH");
	v1.push_back("II");
	v1.push_back("J");

	ft::vector<_value>			v2(v1.begin(), v1.end());

	display_my_v(v2);
	v2.erase(v2.begin());
	print_separator();
	display_my_v(v2);
}