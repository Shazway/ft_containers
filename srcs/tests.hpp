/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 02:36:28 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/17 02:42:35 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_HPP
# define TESTS_HPP

#ifdef __STD
#include <set>
#include <vector>
#include <stack>
#include <map>
# define NAMESPACE	std
#else
#include "algorithm.hpp"
#include "type_traits.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include "set.hpp"
# define NAMESPACE	ft
#endif

#include <deque>
#include <iostream>
#include <typeinfo>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

void	map_tests();

#endif