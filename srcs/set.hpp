/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 02:06:24 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/15 02:14:34 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

#include "RBTree.hpp"
#include <iostream>

namespace ft
{
	template <typename T, typename Compare = ft::less<T>, typename Alloc = std::allocator<T> >
	class set;

	template <typename T, typename Compare, typename Alloc>
	bool	operator>(set<T, Compare, Alloc> const& s1, set<T, Compare, Alloc> const& s2)
	{
		return (s2 < s1);
	}

	template <typename T,
}

#endif