/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:31:23 by tmoragli          #+#    #+#             */
/*   Updated: 2022/11/29 21:20:03 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector.hpp>
#include "vector.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"

int main()
{
	ft::vector<int>	v;

	v.push_back(5);
	for (ft::vector<int>::iterator it = v.begin(); it!= v.end(); it++)
		std::cout << (*it) << std::endl;
}