/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:31:23 by tmoragli          #+#    #+#             */
/*   Updated: 2022/12/16 00:44:41 by tmoragli         ###   ########.fr       */
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
	{
		std::cout << "\nINSERT RANGE\n";
		std::vector<std::string>	insert_in_me;
		std::vector<std::string>	insert_bis;

		for (size_t i = 0; i < 7; i++)
			insert_bis.push_back(ft::to_string(3 * i));
		for (size_t i = 0; i < insert_bis.size(); i++)
			std::cout << insert_bis[i] << ' ';
		std::cout << '\n';

		insert_in_me.push_back("Oui");
		insert_in_me.push_back("Oui");
		insert_in_me.push_back("Oui");
		insert_bis.insert(insert_bis.begin() + 5, insert_in_me.begin(), insert_in_me.end());
		for (size_t i = 0; i < insert_bis.size(); i++)
			std::cout << insert_bis[i] << ' ';
		std::cout << '\n';
	}
	{
		std::cout << "\nINSERT RANGE\n";
		ft::vector<std::string>	insert_in_me;
		ft::vector<std::string>	insert_bis;

		for (size_t i = 0; i < 7; i++)
			insert_bis.push_back(ft::to_string(3 * i));
		for (size_t i = 0; i < insert_bis.size(); i++)
			std::cout << insert_bis[i] << ' ';
		std::cout << '\n';

		insert_in_me.push_back("Oui");
		insert_in_me.push_back("Oui");
		insert_in_me.push_back("Oui");
		insert_bis.insert(insert_bis.begin() + 5, insert_in_me.begin(), insert_in_me.end());
		for (size_t i = 0; i < insert_bis.size(); i++)
			std::cout << insert_bis[i] << ' ';
		std::cout << '\n';
	}
	return (0);
}