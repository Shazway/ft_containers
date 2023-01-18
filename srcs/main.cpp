/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:31:23 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/18 19:14:06 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

void	title(std::string const title)
{
	std::cout << C_BLUE << title << C_WHITE << std::endl;
}

int		main(void)
{
	std::cout << C_RED << "====MAP TESTS====" << C_END << std::endl;
	map_tests();
	std::cout << C_RED << "====END OF MAP TESTS====" << C_END << std::endl << std::endl;

	std::cout << C_RED << "====SET TESTS====" << C_END << std::endl << std::endl;
	set_tests();
	std::cout << C_RED << "====END OF SET TESTS====" << C_END << std::endl << std::endl;

	std::cout << C_RED << "====STACK TESTS====" << C_END << std::endl << std::endl;
	stack_tests();
	std::cout << C_RED << "====END OF STACK TESTS====" << C_END << std::endl << std::endl;
	return (0);
}