/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:31:23 by tmoragli          #+#    #+#             */
/*   Updated: 2022/12/07 17:47:25 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector.hpp>
#include "vector.hpp"
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
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(8);

	std::cout << RED << vct.size() << END << std::endl;
	printSize(vct, true);

	std::cout << "push_back():\n" << std::endl;
	vct.push_back("One long string");
	vct.pop_back();
	display_my_v(vct);

	return (0);
}