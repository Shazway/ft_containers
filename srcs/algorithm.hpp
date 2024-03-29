/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 22:44:40 by tmoragli          #+#    #+#             */
/*   Updated: 2023/01/24 06:32:52 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

#include <sstream>


namespace ft
{
	template <typename T>
	std::string to_string(T n)
	{
		std::ostringstream ss;
		ss << n;
		return (ss.str());
	}

	template <typename T>
	void	__swap(T &a, T &b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	template <typename T>
	struct less
	{
		bool operator()(T const& a, T const& b) const
		{
			return (a < b);
		}
	};

	template <typename T>
	struct greater
	{
		bool operator()(T const& a, T const& b) const
		{
			return (a > b);
		}
	};

	template <typename iterator1, typename iterator2>
	bool	lexicographical_compare(iterator1 begin1, iterator1 end1, iterator2 begin2, iterator2 end2)
	{
		while (begin1 != end1)
		{
			if (begin2 == end2 || *begin1 > *begin2)
				return (false);
			else if (*begin1 < *begin2)
				return (true);
			++begin1;
			++begin2;
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
			else if (compare(*begin1, *begin2))
				return (true);
			++begin1;
			++begin2;
		}
		return (begin2 != end2);
	}

	template<class iterator1, class iterator2>
	bool	equal(iterator1 first1, iterator1 end1, iterator2 first2, iterator2 end2)
	{
		if (end2 - first2 != end1 - first1)
			return (false);
		while (first1 != end1)
		{
			if (*first1 != *first2)
				return (false);
			first1++;
			first2++;
		}
		return (*first2 == *first2);
	}
}

#endif