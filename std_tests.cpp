/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:20:16 by tmoragli          #+#    #+#             */
/*   Updated: 2022/12/07 17:21:29 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <string>
int main()
{
	std::vector<std::string> v(8);

	std::cout << v.size() << std::endl;
}