/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:31:23 by tmoragli          #+#    #+#             */
/*   Updated: 2022/12/19 19:23:08 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector.hpp>
#include "vector.hpp"
#include "stack.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"
#include <istream>

#define TESTED_TYPE std::string
typedef std::string	_value;

void	print_separator()
{
	std::cout << WHITE << "~~~~~~~~~~~~~~~~~~" << END << std::endl;
}

void	display_my_v(ft::vector<TESTED_TYPE> vec)
{
	for (ft::vector<TESTED_TYPE>::iterator i = vec.begin(); i != vec.end(); i++)
		std::cout << GREEN << "[" << (*i) << "]" << END << std::endl;
	if (vec.empty())
		std::cout << YELLOW << "Empty arguments /!\\" << END << std::endl;
}

void	display_std_v(std::vector<TESTED_TYPE> vec)
{
	for (std::vector<TESTED_TYPE>::iterator i = vec.begin(); i != vec.end(); i++)
		std::cout << GREEN << "[" << (*i) << "]" << END << std::endl;
	if (vec.empty())
		std::cout << YELLOW << "Empty arguments /!\\" << END << std::endl;
}

#include "common.hpp"

int		main(void)
{
	ft::vector<ft::vector<int> >	v1;

	for (int i = 0; i < 20; i++)
	{
		ft::vector<int>	tmp(2, i);

		v1.push_back(tmp);
	}
	for (ft::vector<ft::vector<int> >::iterator it = v1.begin(); it != v1.end(); it++)
	{
		std::cout << (*it).size() << std::endl;
	}
	return (0);
}