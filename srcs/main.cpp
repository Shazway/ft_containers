/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:31:23 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/30 01:38:37 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"
#include <map>
#include "map.hpp"
#include <string>
#include <list>

static int iter = 0;

void	title(std::string const title)
{
	std::cout << C_BLUE << title << C_WHITE << std::endl;
}

template<typename T1, typename T2>
std::ostream	&operator<<(std::ostream &os, ft::pair<T1, T2> const& p)
{
	os << "[" << p.first << ", " << p.second << "]";
	return (os);
}

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}
template <typename MAP, typename U>
void	ft_erase(MAP &mp, U param)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	mp.erase(param);
	printSize(mp);
}

template <typename MAP, typename U, typename V>
void	ft_erase(MAP &mp, U param, V param2)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	mp.erase(param, param2);
	printSize(mp);
}
#define T1 int
#define T2 std::string
#include "vector.hpp"


typedef ft::pair<const T1, T2> T3;

int		main(void)
{
	//try
	//{
	//	std::cout << C_RED << "====MAP TESTS====" << C_END << std::endl;
		map_tests();
	//	std::cout << C_RED << "====END OF MAP TESTS====" << C_END << std::endl << std::endl;

		//std::cout << C_RED << "====SET TESTS====" << C_END << std::endl;
		//set_tests();
		//std::cout << C_RED << "====END OF SET TESTS====" << C_END << std::endl << std::endl;

		//std::cout << C_RED << "====STACK TESTS====" << C_END << std::endl;
		//stack_tests();
		//std::cout << C_RED << "====END OF STACK TESTS====" << C_END << std::endl << std::endl;

		//std::cout << C_RED << "====NAMESPACE::vector TESTS====" << C_END << std::endl;
		//vector_tests();
		//std::cout << C_RED << "====END OF NAMESPACE::vector TESTS====" << C_END << std::endl;
	//}
	//catch(const std::exception& e)
	//{
	//	std::cerr << e.what() << '\n';
	//}

	return (0);
}