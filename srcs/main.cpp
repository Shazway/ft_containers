/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:31:23 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/19 01:22:20 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

void	title(std::string const title)
{
	std::cout << C_BLUE << title << C_WHITE << std::endl;
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