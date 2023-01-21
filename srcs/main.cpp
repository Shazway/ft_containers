/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:31:23 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/21 16:53:18 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

void	title(std::string const title)
{
	std::cout << C_BLUE << title << C_WHITE << std::endl;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, NAMESPACE::vector<T> const& x)
{
	if (x.empty() && PRINT)
		return os << "is empty";
	else if (x.empty())
		return os;
	for (typename NAMESPACE::vector<T>::const_iterator it = x.begin(), it1 = ++x.begin(); it != x.end(); ++it)
	{
		os << *it;
		if (it1 != x.end())
		{
			os << " ";
			it1++;
		}
	}
	return os;
}

NAMESPACE::vector<int> gen_data(int n = 20, bool use_i = true)
{
	NAMESPACE::vector<int> v;

	std::cout << "Initial data :";
	for (int i = 0; i < n; i++)
	{
		v.push_back(use_i ? i : rand() % 100);
		std::cout << " " << v.back();
	}
	std::cout << std::endl;
	return v;
}

int		main(void)
{
	try
	{
		std::cout << C_RED << "====MAP TESTS====" << C_END << std::endl;
		map_tests();
		std::cout << C_RED << "====END OF MAP TESTS====" << C_END << std::endl << std::endl;

		std::cout << C_RED << "====SET TESTS====" << C_END << std::endl;
		set_tests();
		std::cout << C_RED << "====END OF SET TESTS====" << C_END << std::endl << std::endl;

		std::cout << C_RED << "====STACK TESTS====" << C_END << std::endl;
		stack_tests();
		std::cout << C_RED << "====END OF STACK TESTS====" << C_END << std::endl << std::endl;

		std::cout << C_RED << "====VECTOR TESTS====" << C_END << std::endl;
		vector_tests();
		std::cout << C_RED << "====END OF VECTOR TESTS====" << C_END << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}