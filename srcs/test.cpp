/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:31:23 by tmoragli          #+#    #+#             */
/*   Updated: 2022/12/03 19:47:57 by tmoragli         ###   ########.fr       */
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
	// print_separator();
	// std::cout << WHITE << "Pushing 5 elements into std vector" << END << std::endl;
	// print_separator();
	// v1.push_back("Hello there");
	// v1.push_back("Hello there");
	// v1.push_back("Hello there");
	// v1.push_back("Hello there");
	// v1.push_back("Hello there");
	// std::cout << v1.size() << std::endl;
	// std::cout << WHITE << "Content:" << END << std::endl;
	// display_std_v(v1);
	// it = v1.begin();
	// it2 = v1.end();
	// {
	// 	print_separator();
	// 	std::cout << WHITE << "Creating my vector by copy v3" << END << std::endl;
	// 	print_separator();
	// 	ft::vector<_value>		v3(it, it2);

	// 	std::cout << WHITE << "Content:" << END << std::endl;
	// 	display_my_v(v3);
	// 	print_separator();
	// 	std::cout << WHITE << "Clearing my vector" << END << std::endl;
	// 	print_separator();
	// 	v3.clear();
	// 	if (v3.empty())
	// 		std::cout << BLUE << "Clear success" << END << std::endl;
	// 	display_my_v(v3);
	// 	print_separator();
	// 	std::cout << WHITE << "Checking size: " << v3.size() << END << std::endl;

	// 	print_separator();
	// 	std::cout << WHITE << "Pushing back in ft::vector v3" << END << std::endl;
	// 	print_separator();

	// 	v3.push_back("Yes sir, trains are fast");
	// 	v3.push_back("Yes sir, trains are fast");
	// 	v3.push_back("Yes sir, trains are fast");
	// 	v3.push_back("Yes sir, trains are fast");
	// 	std::cout << WHITE << "Creating a new ft::vector v4 from my previous vector" << END << std::endl;
	// 	ft::vector<_value>	v4(v3);
	// 	std::cout << WHITE << "New ft::vector v4 content: " << END << std::endl;
	// 	display_my_v(v4);
	// 	print_separator();
	// 	std::cout << WHITE << "Popping back 4 elements from v4" << END << std::endl;
	// 	print_separator();
	// 	v4.pop_back();
	// 	v4.pop_back();
	// 	v4.pop_back();
	// 	std::cout << WHITE << "There should be only 1 element left" << END << std::endl;
	// 	print_separator();
	// 	display_my_v(v4);
	// 	std::cout << WHITE << "Size: " << v4.size() << END << std::endl;
	// 	std::cout << WHITE << "Max size for this vector: " << v4.max_size() << END << std::endl;
	// }
}