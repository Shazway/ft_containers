/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:31:23 by tmoragli          #+#    #+#             */
/*   Updated: 2022/12/26 19:16:32 by tmoragli         ###   ########.fr       */
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
		std::cout << RED << "[" << (*i) << "]" << END << std::endl;
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
	std::vector<std::string>	tmp;
	ft::vector<std::string>		vec;
	std::string tmp_val = "oui";
	size_t		n = 10;

	for (size_t i = 0; i < 500; i++)
	{
		if (i % 3 == 0) {
			tmp.insert(tmp.begin(), n, tmp_val);
			vec.insert(vec.begin(), n, tmp_val);
		}
		else if (i % 3 == 1) {
			tmp.insert(tmp.begin() + tmp.size() / 2, n, tmp_val);
			vec.insert(vec.begin() + vec.size() / 2, n, tmp_val);
		}
		else {
			tmp.insert(tmp.end(), n, tmp_val);
			vec.insert(vec.end(), n, tmp_val);
		}
	}
	display_my_v(vec);
	display_std_v(tmp);
	return (0);
}