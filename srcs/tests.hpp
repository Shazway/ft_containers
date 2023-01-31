/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 02:36:28 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/31 16:51:56 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_HPP
# define TESTS_HPP


#ifdef __STD
#include <set>
#include <vector>
#include <stack>
#include <map>
# define NAMESPACE	std //<-- Changing the namespace depending on the -D__STD include flag in the Makefile
#else
#include "algorithm.hpp"
#include "type_traits.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include "set.hpp"
#include "pair.hpp"
# define NAMESPACE	ft
#endif


#define PRINT 1

#include <deque>
#include <iostream>
#include <typeinfo>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Colors.hpp"

void	title(std::string const title);
void	map_tests();
void	set_tests();
void	stack_tests();
void	vector_tests();

#endif