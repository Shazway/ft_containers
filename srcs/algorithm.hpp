/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 22:44:40 by tmoragli          #+#    #+#             */
/*   Updated: 2022/12/01 17:42:38 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

namespace ft
{
	template <typename iterator1, typename iterator2>
	bool	lexicographical_compare(iterator1 begin1, iterator1 end1, iterator2 begin2, iterator2 end2)
	{
		while (begin1 != end1)
		{
			if (begin2 == end2 || *begin1 > *end2)
				return (false);
			else if (*begin1 < *end2)
				return (true);
			begin1++;
			begin2++;
		}
		return (begin2 != end2);
	}
	template <typename iterator1, typename iterator2, typename Comparator>
	bool	lexicographical_compare(iterator1 begin1, iterator1 end1, iterator2 begin2, iterator2 end2, Comparator compare)
	{
		while (begin1 != end1)
		{
			if (begin2 == end2 || !compare(*begin1, *begin2))
				return (false);
			else if (compare(*begin1, *end2))
				return (true);
			begin1++;
			begin2++;
		}
		return (compare(*begin2, *end2));
	}
}

#endif