/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:31:23 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/15 23:31:51 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector.hpp>
#include "vector.hpp"
#include "stack.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"
#include <istream>
#include "map.hpp"
#include "set.hpp"
#include <set>
#include <map>
#define LEFT 

#define T1 int
#define T2 int

int		main(void)
{
	int myints[] = {75,23,65,42,13};
	ft::set<int> set (&myints, &myints+5);
	// ft::set<T1> set(i, j);

	(void)set;
	return (0);
}